#ifndef Neuron_h
#define Neuron_h

class Neuron
 {

  public:
         Neuron();
         Neuron(int i);
        ~Neuron();

         // funzione per cambiare lo stato del neurone
         void flip();

         // il valore di soglia e' il medesimo per tutti i neuroni
         double threshold = 0.0;

         //richiamo lo stato
         int getState();

	 //check
	 int getCheck();
	 bool UpToDate();

  private:
          // stato del neurone (+1,-1)
          int state;

	  //check flip;
	  bool update;
 };


#endif
