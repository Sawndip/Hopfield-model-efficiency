#include "Exec1.h"
#include "Neuron.h"
#include "Network.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Exec1::Exec1(){
}

Exec1::~Exec1(){
}

void Exec1::run(int nnum, int pnum,int times, int lenght){

    int count = 0;
    char c;
    double temp;
    double impulse;
    double del;

     

    for(int i=0; i<times; i++){

     string file ;
     cout << "\nNome file:";
     cin >>file;

     cout << "\nRate cancellazione sinapsi: ";
     cin >> del;
       

        Network* net = new Network(nnum, pnum, file, del);
	
	cout << "\n\nm(0) con il primo pattern: ";
    	cin >> impulse;
	net->ExternalSignal(impulse);
	net->Overlap(false);
	
	
   	int t = 0;
    	cout << "\n";

	do{
		net->setTemp();
    		while(t < lenght){
    		    net->updateB(t+1, lenght ,count);
    		    t++;
    		}

		cout << "\nContinuare? ('q' per uscire) ";
		cin >> c;
		t = 0;
		count++;

	}while(c != 'q');

    	ofstream comando;
    	comando.open("comando.txt");
    	comando << "set yrange[-1.4:1.4] \n set xrange[1:"<< lenght*count <<"]\n set xlabel 'Cicli'\n set ylabel 'Overlap'\nset terminal jpeg \n set output '"<<file<<".jpg' \n";

	    for(int i=1; i<= pnum; i++){
	        if(i==1){comando << "plot '" << file <<"' u 1:"<<i+1<<" w line title 'Target "<< i <<"' ,\\\n " ;}
		else if(i==(pnum)){comando << "'" << file <<"' u 1:"<<i+1<< " w line notitle ";}
	        else{comando << "'" << file <<"' u 1:"<<i+1<<" w line notitle ,\\\n " ;}

	    }

	    delete net;

	    comando.close();

	    system("gnuplot comando.txt");

    }
}
