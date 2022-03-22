#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
//przyklad rekurencji wypisze ile razy da sie podzielić całkowicie liczbe przez dwa
void dziel(int liczba, int licznik){
    if(liczba == 0) return;
    else{
        cout<<licznik;
        dziel(liczba/2, licznik+=1);
    }
}
int main() {
    int info;
    cin>>info;
    switch(info){
        //ignoruj spacje
        case 1:{
            string tekst="", bez_spacji="";
            cin.ignore();
            getline(cin, tekst); //pobieranie tekstu ze spacjami
            for(int i=0;i<tekst.length();i++){
                if(tekst[i] != ' '){
                    bez_spacji+=tekst[i];
                }
            }
            cout<<bez_spacji;
            break;
        }
        //zamiana liter z duzych na male
        case 2:{
            string tekst="", male_litery="";
            cin.ignore();
            getline(cin, tekst);
            for(int i=0;i<tekst.length();i++){
               int kod_znaku = static_cast<int>(tekst[i]);
               int kod_po_zamianie = kod_znaku + (static_cast<int>('a') - static_cast<int>('A'));
               male_litery = male_litery + static_cast<char>(kod_po_zamianie);
            }
            cout<<male_litery;
            break;
        }
        case 3:{
            //ile razy calkowicie podzielono liczbe przez dwa
            int liczba,licznik=0;
            cin>>liczba;
            dziel(liczba,licznik);
            break;
        }
        default:{
            cout<<"Wrong task number.";
        }
    }
}