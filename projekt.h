#include <iostream>
#include <array>
#include <ctime>
#include <time.h>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <vector>
using namespace std;


//void whatIsSmaller();


class Pytanie{
    public:

    string tresc;
    string a,b,c,d;
    int nr_pytania;
    string poprawna;
    string odpowiedz;
    int punkt;

    void wczytaj();
    void zadaj();
    void sprawdz();
};



class Contener{
public:
    int ilosc ;
    int id;
    int polozenie[2];
    bool wolny;
    int id_statku;
    int width, length, capacity;
    int space[2] = {width, length};
    long double field;

    std::time_t epoch_timeStartUp ;


    void losuj();
    void zapisz();
    void wyczysc();
    void wczytajKontener();
    void pokazKontener();
    void obliczPole();
    void dopiszNaPoczatek();
    void nowyKontener(int len, int widt, int idd);

    Contener(){
        //width = -1;
        //length = -1;
    }
    Contener(int idd, int widthh, int lengthh);

};

class Ship{
public:
    int id;
    int width,length;
    int liczba_zapakowanych_kontenerow;
    double field ;
    double zajetosc;
    int plansza[100][100];
    int space[2] = {width,length};
    int zajete_miejsce;

    void nowyStatek(int id, int width,int length);
    void neww();
    void losujStatek();
    void obliczPole();
    void obliczZajetosc();
    void pokazZaladunek();
    void generuj_polozenie_kontenerow_na_statku( vector<Contener> lista);
};

class Control{
public:
   std::time_t epoch_timeSetUp;


    void report();
};

int sprawdzilosc();

Ship nowyStatek(int id, int width,int length);
void generuj_raport(Ship statki[5], int zapakowane_kontenery);

