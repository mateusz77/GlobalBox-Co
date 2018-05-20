#include <iostream>
#include "projekt.h"
#include <array>
#include <chrono>
#include <ctime>
#include <time.h>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


int main()
{

    int element = 0; //powinno byc 0
    bool statekPelny = false;
   // int inkrementator_zajetosci_elementow = 0;  //nigdzie tego nie uywam ale jak usuné to nie działa :O w ogóle nie pakuje kontenerów chyba że zakomentuje też wypisywanie statku co petle to wtedy dziala
    int dem = 0;
    int zajetosc;
    srand(time(NULL));
    auto now     = std::chrono::system_clock::now();
    // transform the time into a duration since the epoch
    auto epoch   = now.time_since_epoch();


///////////////////////generujé statki recznie

 ////////////////////////generuję statki
    Ship statki[5];
    //////////////////////////petelka
    /*for(int f  = 0; f<5; f++){
        statki[f].id = f+1;
        statki[f].losujStatek();
        statki[f].obliczPole();
    }*/

    statki[0] = nowyStatek(1,25,30);
    statki[1] = nowyStatek(2,20,28);
    statki[2] = nowyStatek(3,25,30);
    statki[3] = nowyStatek(4,18,23);
    statki[4] = nowyStatek(5,20,27);

/////////////////////////////tworzę wektor do którego wrzucę kontenery
    vector<Contener> lista;                                                                      // gwiazdka
    vector<Contener>::iterator iteratorlisty = lista.begin();

///////////////////////////sprawdza ilosc kontenerów i wypisuje na ekran
    int ix = sprawdzilosc();


////////////////wczytanie i wypisanie na ekran kontenerów - usówa wszystkie z pliku
if(ix>0){
    Contener kontener;
    for(int i = 0 ; i < 100 ; i++)
    {

        kontener.id = i+1;
        kontener.wczytajKontener();
       // kontener.pokazKontener();
        kontener.obliczPole();
        lista.push_back( Contener(kontener.id,kontener.width,kontener.length) );
        lista[i].obliczPole();

    }
    //££££££££££££££££££££££££££££££££££££££££££££££££££££sortowanie

    std::sort(lista.begin(),
              lista.end(),
              [](const Contener& lhs, const Contener& rhs)
    {
        return lhs.field > rhs.field;
    });
    // sprawdzaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaam
    /*
        int kret = 0;
            while(kret<50){
               cout<<"pole"<<lista[kret].field<<endl;
               cout<<"le"<<lista[kret].length<<endl;
               cout<<"wi"<<lista[kret].width<<endl;
               kret++;
            }

    */




    /***********************************************************************************AlGO***********************************************************************************/
    for(int statek = 0 ; statek<5; statek++)
    {
        statekPelny=false;
       // cout<<"pole statku"<<statek<<" to : " <<statki[statek].field<<endl;

        int len = statki[statek].length;
        int wid = statki[statek].width;
        statki[statek].liczba_zapakowanych_kontenerow=0;
        int plansza[len][wid];

        cout<<"pole planszy"<<sizeof(plansza)/sizeof(plansza[0][0])<<"len"<<len<<"wid"<<wid<<endl;

        for (int j=0; j<wid; j++)
            for (int i=0; i<len; i++)
                plansza[i][j] = 0;

       bool koniec_listy = false;


        int znacznik[2];
        znacznik[0] = 0;
        znacznik[1] = 0;

        /*przesówam znacznik do momentu aż znajdzie miejsce dla mojego kontenera(wyjątek od nie zmieszczenia się )
        umieszczam kontener i przesówam znacznik(lekka optymalizacja, jeśli nie znajdzie to jedzie od nowa)
        jeśli brak elementu dla ostatniego elementu listy kończę układanie i zabieram się za następny statek

        */
        while(!statekPelny){
            bool czymamiejsce = false;
            cout<<"poczatek while statekkkkkk "<<statek<<"element"<<element<<endl;
            while(1){
                    cout<<"poczatek while"<<endl;

                for(int kek = 0 ; kek<statki[statek].width; kek++){            //szukam miejsca znacznikowi
                    for(int lol = 0+ dem; lol<statki[statek].length; lol++){

                        if(plansza[lol][kek] == 0){             //jeli w planszy jest 0 to ustawiam tam znacznik sprawdzam , czy mój kontener sie zmieści
                            znacznik[0] = kek;
                            znacznik[1] = lol;

        /**)(**/                if(element<100){   //czy nie wychodzę poza zakres listy if(element<lista.size())
                                int ink = 0;      //licznik wolnych kwadratów o wartości 0
                                if(lista[element].wolny){                        //jeśli  kontener jest wolny to czy pole na statku jest dostępne jeszcze od miejsca znacznika
                                    /*czy mam na tyle miejsca*/
                                    for (int j=0; j<lista[element].width; j++){
                                        for (int i=0; i<lista[element].length; i++){
                                            if(plansza[znacznik[1]+i][znacznik[0]+j]==0){
                                                ink++;
                                            }
                                            if(ink == lista[element].field){
                                                czymamiejsce = true;
                                                statki[statek].liczba_zapakowanych_kontenerow++;
                                                cout<<"MAAAAAAAAAAAAAAAAAAAAAM miejsce "<<endl;
                                                lista[element].polozenie[0] = znacznik[0] ;//widtch
                                                lista[element].polozenie[1] = znacznik[1] ;//length
                                                lista[element].id_statku = statek; //widtch
                                                break;
                                            }
                                        }
                                        if(czymamiejsce){
                                                break;
                                        }
                                    }

                                }
                                else{

                                    element++;
                                }

                        }else{
                                cout<<"dotarłem na koniec listy kontenerów"<<endl; /**********************************************/

                                koniec_listy = true;


                                element = 0;//!!!!!!!!!!!
                                break; //wywalam sie z wewn fora jak koniec listy kontenerów piatek 00:50 dalej nawet jak znajdzie to nie poprawia albo zapisuje stare miejsca

                            }

                            if(!lista[element].wolny){
                            //cout<<"czymamiejsce tu "<<czymamiejsce<<" ele "<<element<<" wymiary kontenera "<<lista[element].width<<" "<<lista[element].length<<" "<<lista[element].field <<endl;
                            //cout<<"statki length + width  "<<statki[statek].length<<"+"<<statki[statek].width<<" lol: "<<lol<<" kek: "<<kek<<endl;
                            }
                            if (czymamiejsce){                                   //jeśli ma miejsce na statku to wypełnij statek i zatrudnij kontener,
                                for (int j=0; j<lista[element].width; j++)
                                    for (int i=0; i<lista[element].length; i++){
                                        plansza[znacznik[1]+i][znacznik[0]+j] = 1;  // zamiana ta sama co linia 189 pt16:39
                                        statki[statek].plansza[znacznik[1]+i][znacznik[0]+j] = 1;   //dla statku (funkcjonalnosci)
                                    }

                                lista[element].wolny = false;


                            }
                            if(czymamiejsce){
                                for (int j=0; j<wid; j++){        ////////////////// wypisz plansze bez tego nie działa ?????
                                    for (int i=0; i<len; i++){
                                        cout<<plansza[i][j];
                                    }
                                    cout<<endl;
                                }
                                cout<<endl<<endl;               //////////////////
                            }
                           if(czymamiejsce){
                            break;                  //jeśli znalazlem miejsce to już wychodzę z lol i kek
                             element = 0;           // tutaj zeruję jeśli element ma miejsce
                           }
                        }
                    }//koniec for lol wewn
                    //cout<<"koniec listy: "<<koniec_listy<<endl;///////////////////////////////////////////////////////tututututututututututu
                    if(koniec_listy) break;
                    if(czymamiejsce){
                        break;
                    }
                }//koniec for kek zewn

                if(!czymamiejsce ){
                       if(element<98){
                        element++;
                       }else{
                            koniec_listy = true;
                            statekPelny = true;
                            element = 0;
                       }
                } //działa zajebiście
                cout<<"czymamiejsce"<<czymamiejsce<<endl; /******************************************************/
                break;
            }
            if(koniec_listy) break;   //kiedy statek będzie pelen - ostatni kontener do niego nie wejdzie elementy się skończyły

        }
    }





    for(int statek = 0 ; statek<5; statek++){

        //cout<<"pole: "<<statki[statek].field<< "zajete_miejsce "<<statki[statek].zajete_miejsce<<endl;//zajete_mejsce się nie zmienia ne czemu
        statki[statek].obliczZajetosc();
        statki[statek].pokazZaladunek();
        statki[statek].generuj_polozenie_kontenerow_na_statku(lista);
     }

         zajetosc = 0;
    for(int ppopo=0; ppopo<100;ppopo++){
        if(!lista[ppopo].wolny){
            zajetosc++;
        }else{
            cout<<"kontener o numerze id "<<ppopo<<"nie zostal wykorzystany"<<endl;
            lista[ppopo].dopiszNaPoczatek(); // zwraca niewykorzystane kontenery na poczatek pliku z kontenerami

        }
    }

    cout<<"zajeto "<<zajetosc<<" kontenetow z listy"<<endl;

    generuj_raport(statki, zajetosc);        //raport




}else{
    cout<<"brak kontenerów w pliku"<<endl;
}


    return 0;
}
