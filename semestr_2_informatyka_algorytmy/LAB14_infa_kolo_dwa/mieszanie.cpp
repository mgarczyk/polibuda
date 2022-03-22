#include <iostream>
#include <string>
using namespace std;

//przeszukiwanie binarne należy pamiętac że tablica musi byc posortowana
int indeks_szukanego(int dane[], int szukana, int poczatek, int koniec){
    int srednia = (poczatek+koniec)/2;  //wyznaczamy srodkowy indeks
    if(dane[srednia] == szukana) return srednia; //sprawdzamy czy jest tam nasz szukany element
    if(poczatek>=koniec){ //jezeli przjdziemy przez cala tablice i nastapi taki warunek to dalej nie ma juz szukaneog elemnetu zwracamy -1
        return -1;  
    } 
    if(dane[srednia] < szukana){ //jezeli elemnt na srodku jest mniejszy niz ten szukany
        return indeks_szukanego(dane, szukana, srednia+1, koniec); //to szukamy dalej wśród elemntów większych od niego
    }
    return indeks_szukanego(dane, szukana, poczatek, srednia-1); //jak element na środku jes większy niż ten który szukamy to szukamy wśród mniejszych do niego
}


//sondowanie liniowe
void sondowanie_liniowe(string tablica_liniowe[], int rozmiar_tablica, string wyraz, int M){
    int suma = 0;
    for(int i=0;i<wyraz.length();i++){
        suma+=static_cast<int>(wyraz[i]); //sumujemy kody ascii
    }
    int klucz = suma%M;
    while(tablica_liniowe[klucz] != "_"){ //dopóki kolejne miejsca będą zajęte
        klucz+=1; //zwiększaj klucz i 1 i sprawdzaj następny indeks
        if(klucz >= rozmiar_tablica) klucz = 0; //jeżeli dojdziesz do końca tablicy wyzeruj klucz
    }
    tablica_liniowe[klucz] = wyraz; //ostatecznie w pierwsze wolne miejsce wpisz dany wyraz
    //wypsanie tablicy co każdy wpisany wyraz
    cout<<endl<<endl;
    for(int i=0;i<rozmiar_tablica;i++){
        cout<<i<<" "<<tablica_liniowe[i]<<endl;
    }
    cout<<endl<<endl;
}

//sondowanie_kwadratowe
void sondowanie_kwadratowe(string tablica_kwadratowe[], int rozmiar_tablica, string wyraz, int M, int N){
    int suma = 0;
    for(int i=0;i<wyraz.length();i++){
        suma+=static_cast<int>(wyraz[i]);
    }
    int klucz = suma%N; //pierwszy klucz
    cout<<"pierwszy klucz: " << klucz<<endl;
    int h0 = klucz; //pierwszy klucz
    int i = 1; //
    while(tablica_kwadratowe[klucz] != "_"){ //jak jest zajety to szukamy nowy klucz
        klucz = (h0 + i * ((h0 % M) + 1))%N; //nowy klucz
        cout<<"nowy klucz numer: "<<i<<" to: "<<klucz<<endl;
        i++;
        
    }
    tablica_kwadratowe[klucz] = wyraz; //ostatecznie wpiszemy wyraz w puste moiejsce
    //wypisanie
    cout<<endl<<endl;
    for(int i=0;i<rozmiar_tablica;i++){
        cout<<i<<" "<<tablica_kwadratowe[i]<<endl;
    }
    cout<<endl<<endl;
}




int main(){
    int info;
    cin>>info;
    switch(info){
        case 1:{
            int rozmiar =10;
            int dane[10];
            for(int i=0;i<rozmiar;i++){
                cin>>dane[i];
            }
            int szukana;
            cin>>szukana;
            int indeks = indeks_szukanego(dane, szukana, 0, rozmiar-1);
            cout<<indeks;
            break;
        }
        case 2:{
            int rozmiar_tablica = 31, rozmiar_do_wpisu = 20, M=31;
            string tablica_liniowe[31], wyraz;
            for(int i=0;i<rozmiar_tablica;i++){
                tablica_liniowe[i] = "_";
            }
            for(int i=0;i<rozmiar_do_wpisu;i++){
                cin>>wyraz;
                sondowanie_liniowe(tablica_liniowe, rozmiar_tablica, wyraz, M);
                
            }
            break;
        }
        case 3:{
            int rozmiar_tablica = 31, rozmiar_do_wpisu = 20, M=11, N=13;
            string tablica_liniowe[31], wyraz;
            for(int i=0;i<rozmiar_tablica;i++){
                tablica_liniowe[i] = "_";
            }
            for(int i=0;i<rozmiar_do_wpisu;i++){
                cin>>wyraz;
                sondowanie_kwadratowe(tablica_liniowe, rozmiar_tablica, wyraz, M, N);
                
            }
            break;
        }
        default: cout<<"Nastapil problem.";
    }
    return 0;
}