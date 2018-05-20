#include <iostream>
#include "projekt.h"
#include <fstream>
#include <cstdlib>
#include <array>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>       // std::vector
#include <cstdio>

int generator(){
    ////////////////////////losujê 100 kontenerów i zapisujê do pliku

    Contener contener[100];

    // contener[1].wyczysc();//czyœci plik z kontenerami

    for(int i = 0; i<100 ; i++)
    {
        contener[i].wolny = true;
        contener[i].id = i+1;
        contener[i].losuj();
        contener[i].obliczPole();
        contener[i].zapisz();
        //contener[i].pokazKontener();

       /*/ if(contener[i].wolny){
            cout <<"jestem Obiektem o numerze id: "<< contener[i].id<<contener[i].field<< endl;
            cout<<"moje pole:"<<contener[i].field<<endl;
        }*/

    }


return 0;
}
