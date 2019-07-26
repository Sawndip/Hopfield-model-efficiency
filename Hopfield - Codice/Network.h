#ifndef Network_h
#define Network_h
#include <vector>
#include <string>
#include <fstream>
class Neuron;

class Network
   {
    public:
            Network(const int nnum, const int pnum, std::string file, double del);
            ~Network();

            // inizializzazione del network
            void initN();

	    //inizializzazione del network con impulso
	    void ExternalSignal(double impulse);

            // inizializzazione target (random)
            void initT();

            //costruzione della matrice W
            // chiamata dentro initT()
            void MetrixCalc(std::vector<int> t);

            //Stampa la matrice
            void getMetrix();

            //chiamata sequenziale dei neuroni
            void updateB(int cycle, int lenght, int count);

            //update del singolo neurone
            void updateN(Neuron*, int i, double T);

            //imposta temperatura del sistema
	    void setTemp();

	    //distruzione sinapsi
            void Deletion();

	    //Check impulso
            int M0(Neuron* n, int r);

	    //Overlap
	    void Overlap(bool check);

	    //Check ovelap
	    bool Iterate();

   private:
            //dimensione del network
            const int B;

            //numero di pattern da memorizzare
            const int N;

	    //Temperatura del sistema
	    double T;

	    //nome file
	    std::string F;

	    //rate cancellazione
	    double D;

	    //output
            std::ofstream output;

            //Store dei target
	    std::vector< std::vector<int> > store;

            //stato complessivo del network
            std::vector<Neuron> y;

	    //matrice
	    int metrix[1000][1000]={{0},{0}};

	    //check iterazione
	    bool iterate = true;

};


#endif
