#include "Exec2.h"
#include "Neuron.h"
#include "Network.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Exec2::Exec2(){
}

Exec2::~Exec2(){
}

void Exec2::run(int nnum, int pnum,int times, int lenght){

    
    double temp;
    double impulse;
    double del;
    int success = 0;

    string file = "" ;

    cout << "\nRate cancellazione sinapsi: ";
    cin >> del;

    cout << "\nm(0) con il primo pattern: ";
    cin >> impulse;
     

    for(int i=0; i<times; i++){
	cout << "N. "<<i+1<<endl;
        Network* net = new Network(nnum, pnum, file, del);
	net->ExternalSignal(impulse);
	net->Overlap(false);
	net->Deletion();
   	int t = 0;
    	cout << "\n";
	int count = 0;
	while(net->Iterate() && count != 4){
		net->setTemp();
    		while(t < lenght){
    		    net->updateB(t+1, lenght ,count);
    		    t++;
    		}
		t = 0;
		count++;

	}

	if(net->Iterate() == false){success ++;}
	    

	delete net;

    }

	cout << "\nNumero di successi:" <<success <<endl;
}
