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


using namespace std;
/*
void whatIsSmaller(){
        inline bool operator() (const Contener& kon1, const Contener& kon2){
        return (kon1.field < kon2.field);
    }

    }
*/
void Pytanie::wczytaj(){
    fstream plik;
    plik.open("mojplik.txt", ios::in);

    if(plik.good() == false){
        cout<<"Nie uda³o siê otworzyæ pliku!"<< endl;
        exit(0);
    }
    if(sprawdzilosc()==0){
        cout<<"brak kontenerów do wczytania"<<endl;

    }

    int nr_linii = (nr_pytania -1)*6+1;
    int aktualny_nr = 1;
    string linia;

    while(getline(plik, linia)){
        if(aktualny_nr == nr_linii) tresc = linia;  //tresc
        if(aktualny_nr == nr_linii+1) a = linia;
        if(aktualny_nr == nr_linii+2) b = linia;
        if(aktualny_nr == nr_linii+3) c = linia;
        if(aktualny_nr == nr_linii+4) d = linia;
        if(aktualny_nr == nr_linii+5) poprawna = linia;
        aktualny_nr++;
    }
    plik.close();
}

void Contener::wczytajKontener(){

    //chcę aby brał po 1 i go usówał
    fstream plik;
    plik.open("conteners.txt", ios::in);

    if(plik.good() == false){
        cout<<"Nie udalo sie otworzyc kontenera!"<< endl;
        exit(0);
    }

    string linia;

    getline(plik, linia); // { 1, 2, 3, 4 }
    replace_if(linia.begin(), linia.end(),
                    [](const char& c) { return ((c == '[') || (c == ',') || (c == ']')); },
                    ' ');
    stringstream ss(linia); // 1 2 3 4

    vector<int> v(( istream_iterator<int>(ss)),
                 istream_iterator<int>());

    // cout<< v[0]<<v[1]<<endl;
    width =  v[0] ;
    length =  v[1] ;
  //  cout<< width<<length;

    // now open temp output file
    ofstream out("outfile.txt");
    // loop to read/write the file.  Note that you need to add code here to check
    // if you want to write the line
    string line;
    while (getline(plik, line)){
         out << line << "\n";
    }




    plik.close();
    out.close();
// delete the original file
    remove("conteners.txt");
    // rename old to new
   // Sleep(100);
    rename("outfile.txt","conteners.txt" );
    // all done!

}




void Pytanie::zadaj(){
    cout<<endl<<tresc<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
    cout<<d<<endl;

    cout<<"________________________________"<<endl<<"ODPOWIED :"<< endl;

    cin>>odpowiedz;

}

void Pytanie::sprawdz(){
    if(odpowiedz == poprawna){
        punkt =1;
    }else{
        punkt = 0;
    }
}


void Contener::losuj(){

    width = space[0] = (rand() % 9 )+1;            //szerokość do 10 od 1m
    length = space[1] = (rand() % 9 )+1;           //długość
   /* for(int i = 0 ; i<2; i++){
    cout << space[i]<<endl;
    }*/
}

 void Contener::nowyKontener(int len, int widt, int idd){
        space[1] = length = len;
        space[0] = width = widt;
        id = idd;

 }


void Contener::zapisz(){
    ofstream plik("conteners.txt", ios::app);       //otwarcie pliku w trybie dopisywania

 plik <<"["<<space[0]<<","<<space[1]<<"]"<<endl;

 plik.close();
}
void Contener::dopiszNaPoczatek(){
    //chcę aby brał po 1 i go usówał
    fstream plik;
    plik.open("conteners.txt", ios::in);

    if(plik.good() == false){
        cout<<"Nie udalo sie otworzyc kontenera!"<< endl;
        exit(0);
    }
    // now open temp output file
    ofstream out("outfile.txt");
    // loop to read/write the file.  Note that you need to add code here to check
    // if you want to write the line
    string line;
    out <<"["<<space[0]<<","<<space[1]<<"]"<<endl;

    while (getline(plik, line)){
         out << line << "\n";
    }
    plik.close();
    out.close();
// delete the original file
    remove("conteners.txt");
    // rename old to new
   // Sleep(100);
    rename("outfile.txt","conteners.txt" );
    // all done!
}


void Contener::wyczysc(){
    ofstream plik("conteners.txt", ios::trunc);     //kasuję zawartość

 plik.close();

}

void Contener::obliczPole(){
   field = width*length;
}

/*Contener::Contener(int idd, int widthh, int lengthh)
    : id (idd)
    , width(widthh)
    , length(lengthh)
    {}
*/
Contener::Contener(int idd, int widthh, int lengthh){
    id = idd;
    width=widthh;
    length=lengthh;
    }



void Contener::pokazKontener(){
    cout<<endl<<"to moje wymiary"<<endl;
    cout<<"width "<<width<<endl;
    cout<<"length "<<length<<endl;

}
void Ship::nowyStatek(int idd, int widthh, int lengthh){
        id = idd;
        width = widthh;
        length = lengthh;
        zajete_miejsce = 0;

        for (int j=0; j<width; j++)
            for (int i=0; i<length; i++)
                plansza[i][j] = 0;
    }
Ship nowyStatek(int idd, int widthh,int lengthh){
        Ship statek;
        statek.id = idd;
        statek.width = widthh;
        statek.length = lengthh;
        statek.zajete_miejsce = 0;
        statek.obliczPole();

        for (int j=0; j<widthh; j++)
            for (int i=0; i<lengthh; i++)
                statek.plansza[i][j] = 0;

        return statek;
    }

void Ship::losujStatek(){

    width = space[0] = (rand() % 99 )+1;            //szerokość do 10 od 1m
    length = space[1] = (rand() % 99 )+1;            //długość

    for (int j=0; j<width; j++)
        for (int i=0; i<length; i++)
            plansza[i][j] = 0;

    cout<<"["<< space[0]<<","<<space[1]<<"]"<<endl;
    zajete_miejsce = 0;
}


void Ship::obliczZajetosc(){

    int franek = 0;
    for (int j=0; j<width; j++){
        for (int i=0; i<length; i++){
            if(plansza[i][j]==1)
                franek++;

        }
    }
    zajete_miejsce = franek;
    zajetosc = zajete_miejsce/field*100;
    cout<<"statek "<<id<<" zajeto "<<zajete_miejsce<<"m^2 statku, to az "<<zajetosc<<"procent statku"<<endl;
}

void Ship::pokazZaladunek(){

    for (int j=0; j<width; j++){        ////////////////// wypisz plansze
        for (int i=0; i<length; i++){
            cout<<plansza[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;               //////////////////


}

void Ship::neww(){
        id = 1111;
        width = 2;
        length = 4;
        zajete_miejsce = 0;
         for (int j=0; j<width; j++)
            for (int i=0; i<length; i++)
                plansza[i][j] = 0;
}
void Ship::obliczPole(){
   field = width*length;
}
void Ship::generuj_polozenie_kontenerow_na_statku( vector<Contener> lista){

    ofstream plik("polozenie.txt", ios::app);       //otwarcie pliku w trybie dopisywania

    time_t result = std::time(nullptr);

    plik <<"polecenie pakowania z  " << asctime(localtime(&result))<<endl;

    plik <<"Na statek o id: "<< id<<" należy zapakować "<<liczba_zapakowanych_kontenerow<<" kontenerów zajmując przy tym "<<zajetosc<<"% powierzchni statku. Poniżej przedstawiono ich położenie "<<endl;

    for(int i = 0; i<100; i++){
            if(id==lista[i].id_statku){
                plik <<"kontener o id: "<< lista[i].id<<" zapakować w miejscu mającym początek na  "<<lista[i].polozenie[0]<<" metrze szerokości oraz"<<lista[i].polozenie[1]<<" metrze długości statku"<<endl;
            }

    }
    plik <<endl<<endl;

    plik.close();
   /*********************/
}


int sprawdzilosc(){

  ifstream myfile("conteners.txt");

    // new lines will be skipped unless we stop it from happening:
    myfile.unsetf(ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = count(
        istream_iterator<char>(myfile),
        istream_iterator<char>(),
        '\n');

    cout << "ilość kontenerów: " << line_count << "\n";
    return line_count;

}

void generuj_raport(Ship statki[5], int zapakowane_kontenery){

    time_t result = std::time(nullptr);

int srednia_zajetosc = 0;
for(int i = 0; i<5; i++){
    statki[i].obliczZajetosc();
    srednia_zajetosc=srednia_zajetosc+statki[i].zajetosc;
}
srednia_zajetosc = srednia_zajetosc/5;

    ofstream plik("raport.txt", ios::app);       //otwarcie pliku w trybie dopisywania

plik <<endl<<endl<<"Raport wygenerowano: " << asctime(localtime(&result))<< result << " seconds since the Epoch\n"<<endl;

 plik <<"Średnia zajętość wyniosła: "<< srednia_zajetosc<<"%"<<endl;

 plik <<"Łącznie zapakowano : "<< zapakowane_kontenery<<" kontenerów"<<endl;
 for(int i = 0; i<5; i++){
    plik <<"Na statek o id: "<< statki[i].id<<" zapakowano "<<statki[i].liczba_zapakowanych_kontenerow<<" kontenerów zajmując przy tym"<<statki[i].zajetosc<<"% powierzchni statku"<<endl;
}






 plik.close();

}
