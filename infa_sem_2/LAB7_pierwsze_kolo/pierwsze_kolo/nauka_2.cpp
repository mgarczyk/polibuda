#include <iostream>
using namespace std;
void kalkulator (int wybor){
    if(wybor == 1 or wybor == 2 or wybor == 3 or wybor == 4 or wybor == 5){
                    double a, b;
                    double wartosc;
                    cin>>a>>b;
                    switch (wybor){
                        case 1: {
                            wartosc = a + b;
                            cout<<wartosc;
                            break;
                        }
                         case 2: {
                            wartosc = a-b;
                            cout<<wartosc;
                            break;
                        }
                         case 3: {
                            wartosc = a*b;
                            cout<<wartosc;
                            break;
                        }
                         case 4: {
                             if(b != 0){
                                 wartosc = a/b;
                                 cout<<wartosc;
                             }else{
                                 cout<<"Dzielic przez zero nie bedzie Ci dane";
                             }
                            break;
                        }
                         case 5: {
                               if(b != 0){
                                 wartosc = static_cast<int>(a)/static_cast<int>(b); //rzutowanko
                                 cout<<wartosc;
                             }else{
                                 cout<<"Modulo przez zero - nie przejdzie";
                             }
                            break;
                        }
                    }
                    
                }
                else{
                    cout<<"There is no task like this.";
                }
}
void drugie_maksimum(double tab[3], const int rozmiar){
    
                //szukamy pierwsze maksimum
                double pierwsze_max = tab[0];
                for(int i=1;i<rozmiar;i++){
                    if(tab[i] > pierwsze_max) pierwsze_max = tab[i];
                }
                //sprawdzamy czy istnieje jezeli tak to ustawiamy kandyta na drugie maksimum
                double drugie_max;
                bool brak_drugiego_maksimum = true;
                int indeks = 0;
                for(int i=0;i<rozmiar;i++){
                    if(tab[i]!=pierwsze_max){
                        drugie_max = tab[i];
                        brak_drugiego_maksimum = false;
                        indeks = i; //indeks od jakiego ewentualnie zaczniemy szukac drugie maksimum (pierwsza pozycja czegoś co nie jest równe pierwszemu maksimum)
                        break;
                    }
                }
                //jezeli jest to szukamy drugie maksimum jezeli nie to nie szukamy dalej
                if(brak_drugiego_maksimum == false){
                    for(int i=indeks;i<rozmiar;i++){
                        if(tab[i] != pierwsze_max){
                            if(tab[i] > drugie_max) drugie_max = tab[i];
                        }
                    }
                    cout<<drugie_max;
                }else{
                    cout<<"Nie istnieje drugie maksimum";
                }
}
void sumowanie(int tab_suma[][5], const int stala_ilosc, int kolumny, int wiersze){
    for(int i=0;i<wiersze;i++){
                    for(int j=0;j<kolumny;j++){
                        tab_suma[i][j] = 0;
                    }
                }
                //wpisujemy interesującą nas ilość danych
                for(int i=1;i<=wiersze-stala_ilosc;i++){
                    for(int j=1;j<=kolumny-stala_ilosc;j++){
                        cin>>tab_suma[i][j];
                    }
                }
                //jak to wygląda
                 for(int i=0;i<wiersze;i++){
                    for(int j=0;j<kolumny;j++){
                        cout<<tab_suma[i][j]<<" ";
                    }
                    cout<<endl;
                }
                int suma = 0;
                 for(int i=1;i<=wiersze-stala_ilosc;i++){
                    for(int j=1;j<=kolumny-stala_ilosc;j++){
                        suma = 0;
                        suma = tab_suma[i-1][j] + tab_suma[i][j] + tab_suma[i+1][j] + tab_suma[i-1][j-1] + tab_suma[i][j-1] + tab_suma[i+1][j-1] + tab_suma[i-1][j+1] + tab_suma[i][j+1] + tab_suma[i+1][j+1];
                        cout<<suma<<" ";
                    }
                }
}
int main(){
    int info;
    cin>>info;
    if(info == 1 or info == 2 or info == 3 or info == 4 ){
        switch(info){
            //kalkulator
            case 1: {
                int wybor;
                cin>>wybor;
                kalkulator(wybor);
                break;
            }
            //drugi najwiekszy
             case 2: {
                double tab[3];
                const int rozmiar = 3;
                for(int i=0;i<rozmiar;i++){
                    cin >> tab[i];
                }
                drugie_maksimum(tab, rozmiar);
                break;
            }
            //wyswietl wartosci pomiedzy 2 a 3 jedynka znaczoca łącznie z 2 i 3 jędynką znaczącą
             case 3: {
                unsigned int maska = 0x80000000;
                const int ilosc_bitow  = 8;
                int liczba;
                cin>>liczba;
                //wyswietl liczbe
                for(int i=0;i<sizeof(liczba)*ilosc_bitow;i++){
                    if(maska & liczba) cout<<1;
                    else cout<<0;
                    maska = maska >> 1;
                }
                cout<<endl;
                maska = 0x80000000; //reset maski
                //znajdz pozycje 2 i 3 jedynki znacacej
                int pierwsza_jedynka = 0, druga_jedynka = 0, trzecia_jedynka=0, ile_jedynek = 3;
                for(int i=0;i<sizeof(liczba) * ilosc_bitow;i++){
                        if(maska & liczba && pierwsza_jedynka == 0 && druga_jedynka==0 && trzecia_jedynka==0){
                            pierwsza_jedynka = i;
                            ile_jedynek = ile_jedynek - 1;
                        }else if(maska & liczba && druga_jedynka==0 && trzecia_jedynka==0){
                            druga_jedynka = i;
                            ile_jedynek = ile_jedynek - 1;
                        }else if(maska & liczba &&  trzecia_jedynka==0){
                            trzecia_jedynka = i;
                            ile_jedynek = ile_jedynek - 1;
                            break;
                        }
                    maska = maska >> 1;
                }
                maska = 0x80000000; //reset maski
                maska = maska >> druga_jedynka; //przesuniecie maski
                //wypsanie drugiej jedynki 0 pomiędzy i trzecej jedynki
                for(int i=druga_jedynka; i<=trzecia_jedynka; i++){
                    if(maska & liczba) cout<<1;
                    else cout<< 0;
                    maska = maska >> 1;
                }
                cout<<endl;
                break;
            }
             case 4: {
                const int stala_ilosc = 2;
                int wiersze = 2;
                int kolumny = 3;
                wiersze = wiersze + stala_ilosc;
                kolumny = kolumny + stala_ilosc;
                //naszą tablice "obudowujemy zerami" tworząc dokoła naszej struktury mur wypełniony zerami
                int tab_suma[4][5];
                sumowanie(tab_suma, stala_ilosc, wiersze, kolumny);
                break;
            }
        }
    }
    else{
        cout<<"There is no task like this.";
    }
    
    
}