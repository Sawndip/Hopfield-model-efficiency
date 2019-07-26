#include "Neuron.h"
#include <iostream>

//inizializzazione di default
Neuron::Neuron(){
	state = -1;
}

//inizializzazione manuale
Neuron::Neuron(int i):
state(i){
     if (state != -1 && state!= 1){
        std::cout<<"Stato Neurone non valido"<<std::endl;
     }
	update = true;
}

Neuron::~Neuron(){
}

// funzione per cambiare lo stato del neurone
void Neuron::flip(){
	state *= -1;
	update = false;
}

//richiamo lo stato
int Neuron::getState(){
	return state;
	
}

int Neuron::getCheck(){
	update = false;	
	return state;
}

bool Neuron::UpToDate(){

	return update;
}
