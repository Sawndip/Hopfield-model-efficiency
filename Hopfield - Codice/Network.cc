#include "Network.h"
#include "Neuron.h"
#include <cstdlib>
#include <random>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

normal_distribution<double> distribution(0.641, 0.18);
random_device randomness_device{};
mt19937 pseudorandom_generator{randomness_device()};

Network::Network(int nnum, int pnum, string file, double del):
B(nnum), N(pnum), F(file), D(del){
    output.open(F);
    initT();
    initN();
    
}

Network::~Network(){
	output.close();
}

// inizializzazione del network
void Network::initN(){

	for(int i = 0; i<B; i++){
		
		int s;

		//PER LA SIMULAZIONE
		//genero numeri casuali tra 0 e 1
		//e assegno valore al neurone
                //double r = rand()%2;
		//if(r == 1){ s = 1; }
		//else s = -1;

		//PER IL TEST A 1 PATTERN

		s = store.at(0).at(i);
		Neuron n(s);
		y.push_back(n);

		//Per mostrare lo stato
		//cout<<n.getState()<<" ";
	}

	

}

void Network::ExternalSignal(double impulse){
	
	int s = 0;

	//PER LA SIMULAZIONE
	//int signal = impulse*B;

	//PER IL TEST A 1 PATTERN
	int signal = 0.5*B - 0.5*impulse*B;

	while(s<signal){
		//genero numeri casuali tra 0 e B-1
		//e assegno valore al neurone
                int r = rand()%B;
		s += M0(&(y.at(r)),r);
	}

	for(int j=0; j<N; j++){

		double m = 0;
		for(int i = 0; i<B; i++){
			//calcolo dell'overlap
			m += (y.at(i).getState()*store.at(j).at(i));
		}

			cout <<"\n" <<j+1 <<" Overlap : "<< m/B;
	}
}

void Network::initT(){

	
	for(int j=0; j<N; j++){

		vector<int> t(B);

	//per mostrare i target	
        // std::cout<< "Target " << j+1 << " = ";

		for(int i = 0; i<B; i++){

			//genero numeri casuali tra 0 e 1
			//e assegno valore al target
	                double r = rand()%2;
			int s;
			if(r == 1){ s = 1; }
			else s = -1;
			t.at(i) = s;
			//cout << t.at(i) <<" ";
		}

		//calcolo della matrice e pulizia del vettore target
		MetrixCalc(t);
		store.push_back(t);

	}
		

}

//costruzione della matrice di connessione
void Network::MetrixCalc(vector<int> t){

    for(int i = 0; i<B; i++){
        for(int j = 0; j<B; j++){
            if (i == j){metrix[i][j] = 0;}
            else {metrix[i][j] += (t.at(i)*t.at(j));}
        }
    }

}

//mostrare la matrice
void Network::getMetrix(){

   cout << "\n\t\tMatrice:"<<endl;
   for(int i = 0; i<B; i++){
        for(int j = 0; j<B; j++){
            cout << metrix[i][j] << "\t";
        }
	cout<<endl;
    }

}

//setting della temperatura
void Network::setTemp(){
   
   T = distribution(pseudorandom_generator);
	
   if (T >= 0){}
   else {T = 0;}
   cout << "\nTemperatura: "<<T;
}

//ciclo sui neuroni del cervello
void Network::updateB(int cycle,int lenght ,int count){
	
    //getMetrix();

    cout << "\n";
    for(int i = 0; i<B; i++){
        updateN(&(y.at(i)), i, T);
    }
    output << (count*lenght)+cycle << "\t";

    
    Overlap(true);
    

}

//update del singolo neurone
void Network::updateN(Neuron* n, int i, double T){

        double U = 0;
	if( T == 0){
       	 	for(int j = 0; j<B; j++){
       	    		U += metrix[i][j]*( y.at(j).getState() +1 );
       	 	}

        	U = 0.5*U;

        	if((U - n->threshold) > 0 && n->getState() == -1){n->flip();}
        	if((U - n->threshold) <= 0 && n->getState() == +1){n->flip();}
	}


	if(T != 0){

		double h = 0;
		double beta = (1/T) ;
		for(int j = 0; j<B; j++){
       	    		h += metrix[i][j]*( y.at(j).getState() );
       	 	}

		double P = 0.5*( 1 + tanh(beta * h * n->getState()) );

		//check della probabilità
		//cout <<"P(" <<0.5*( 1 + tanh(beta * h * n->getState()) ) << ") ";

		double r = (1.0*rand())/RAND_MAX;
		if(P < r){n->flip();}
	}
}

//distruzione sinapsi
void Network::Deletion(){

    int d = 0;
    int cut = D*B*B;
	

    while(d<cut){

        int i = (rand()%(B+1));
        int j = (rand()%(B+1));

        if(metrix[i][j] == 0){
        }

        else{
                metrix[i][j] = 0;
                d++;
        }

    }
}

//scambio valore neurone
int Network::M0(Neuron* n, int r){
	if(n->UpToDate()){
			if(n->getCheck() != store.at(0).at(r) ){
				return +1;}

			else{ 	n->flip();				
				return +1;}
	}

	else return 0;
}

//check dell'overlap
void Network::Overlap(bool check){
	cout << "\n";
   	for(int j = 0; j<N; j++){

   	         double overlap = 0;
		
       	         for(int i = 0; i<B; i++){
        	        overlap += (y.at(i).getState()*store.at(j).at(i));

       		 }
		
		 // se l'overlap è circa 1 il ciclo si ferma e si segna un successo
		 if(/*j == 0 && */overlap/B > 0.995){iterate = false;}

        if(check) {output << overlap/B << "\t";}
        //cout <<"\n" <<j+1 <<" Overlap : "<< overlap/B;
        }

    if(check){output << "\n";}
}


bool Network::Iterate(){
	return iterate;
}
