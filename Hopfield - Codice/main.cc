#include "Exec1.h"
#include "Exec2.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){

    srand(time(NULL));
    int nnum;
    int pnum;
    int times;
    int lenght;
    double impulse;

    cout << "Inserire numero di neuroni: ";
    cin >> nnum;

    cout << "\nInserire numero di pattern da memorizzare: ";
    cin >> pnum;

    cout << "\nNumero di simulazioni: ";
    cin >> times;

    cout << "\nCicli con la stessa temperatura: ";
    cin >> lenght;

    if(*argv[1] == '1'){
            Exec1 run1;
            run1.run(nnum, pnum, times, lenght);
            }

    if(*argv[1] == '2'){
            Exec2 run2;
            run2.run(nnum, pnum, times, lenght);
            }

    else{cout << "Argomento non valido"<< endl;}


    return 0;
}


