#include <iostream>

using namespace std;

int main()
{

    int tab[10];
    int rozmiar = 10;
    bool to = false;
    int liczba;
    for(int i=0;i<rozmiar;i++){
        do{
           to = false;
           cin>>liczba;
           for(int j=0;j<i;j++){
            if(tab[j] == liczba) to = true;
           }
        }while(to==true);
        tab[i] = liczba;
    }
    for(int i=0;i<rozmiar;i++){
        cout<<tab[i]<< " ";
    }

}
