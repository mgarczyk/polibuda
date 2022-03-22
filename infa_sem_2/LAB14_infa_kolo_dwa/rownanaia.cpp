#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

double wartosc_funkcji(double x){ //funkcja zwraca wartość funkcji dla danego punktu
    return pow(x,3) + 2*pow(x,2) - 2;
}

double pochodna_funkcji(double x){
    return 3*pow(x,2) + 4*x;
}

//bisekcja
double bisekcja_f(double poczatek, double koniec, double eps, int ilosc_rekurencji){
    ilosc_rekurencji--; //z kazdym kazdym rozpoczeciem funkcji zmniejszamy ilosc kolejnych wywowłań
    if(wartosc_funkcji(poczatek) == 0) return poczatek; //jezeli poczatek to miejsce zerowe to zwróć wynik
    if(wartosc_funkcji(koniec) == 0) return koniec;     //jezeli koniec to miejsce zerowe to zwróć wynik
    double srodek = (poczatek+koniec)/2; //wyznaczamy srodek przedzialu
    if((koniec-poczatek<=eps || ilosc_rekurencji == 0)){ //jeżeli przedział w którym szukamy jest mniejszy niż dokładność lub 
         return srodek;
    }
    if(wartosc_funkcji(srodek) * wartosc_funkcji(koniec) < 0){ //jezeli pomiedzy srodkiem a koncem jest zmiana znaku 
        return bisekcja_f(srodek, koniec, eps, ilosc_rekurencji); //to miejsce zerwoe jest pomiedzy srodkeim a koncem
    }
    return bisekcja_f(poczatek, srodek, eps, ilosc_rekurencji); //innaczaej musi byc pomiedzy poczatkiem a srodkiem
}
    
    
    //newton rapshon
double newton_rapshon(double x_1, double eps, int ilosc_rekurencji){
        ilosc_rekurencji--;
        double x = x_1; //ustawiamy x_1 jako sprawdzany element dla którego szukamy wartości funkcji i pochodnej
        double f_x = wartosc_funkcji(x); //wartość funkcji f(x)
        double f_x_pochodna = pochodna_funkcji(x); //wartość pochodnej f'(x)
        x_1 = x - (f_x/f_x_pochodna); //wyznaczamy kolejny punkt
        if(ilosc_rekurencji == 0 || abs(x_1 - x) <= eps){
            return x_1;
        }
        return newton_rapshon(x_1,eps,ilosc_rekurencji);
    }
    
int main(){
    int info;
    cin>>info;
    switch(info){
        case 1:{
            double poczatek, koniec, eps; //podajemy poczatek przedziału, koniec przedziału i dokładność
            cin>>poczatek>>koniec>>eps;
            int ilosc_rekurencji; //podajemy maksymalną ilość kolejnych wywołań funkcji
            cin>>ilosc_rekurencji;
            double wynik = bisekcja_f(poczatek, koniec, eps, ilosc_rekurencji);
            cout<<setprecision(5)<<wynik<<endl;
            break;
        }
        case 2:{
            double x_1, eps; //podajemy miejsce startowe
            cin>>x_1>>eps;
            int ilosc_rekurencji; //podajemy maksymalną ilość kolejnych wywołań funkcji
            cin>>ilosc_rekurencji;
            double wynik = newton_rapshon(x_1, eps, ilosc_rekurencji);
            cout<<setprecision(5)<<wynik<<endl;
            break;
        }
        default: cout<<"Nastapil problem.";
    }
    return 0;
}