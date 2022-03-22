#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void float_ieee754(string tablica_wynikowa[], float liczba, const int rozmiar){
    //bit znaku
    if(liczba < 0) tablica_wynikowa[0] = '0';
    else tablica_wynikowa[0] = '1';
    //cecha i mantysa dziesitenie
    int cecha_dziesietnie = 0;
    float kopia_liczba = liczba;
    while(liczba>=2){ //gdy liczba jest >= 2 to dzielimy
        cecha_dziesietnie = cecha_dziesietnie + 1; //przed każdym dzieleniem zwiększamy cechę
        liczba = liczba / 2; //dzilimy
    }

    cecha_dziesietnie+=127; //BIAS
    float mantysa_dziesietnie = liczba - 1; //odejmujemy 1 od mantesy by ją zapisać
    //cecha binarnie
    for(int i=8;i>=1;i--){
        if(cecha_dziesietnie%2 == 1) tablica_wynikowa[i] = '1'; //zapisujemy cechę binarnie
        else tablica_wynikowa[i] = '0';
        cecha_dziesietnie = cecha_dziesietnie/2;
    }
    //mantysa binarnie
    for(int i=9;i<rozmiar;i++){
        mantysa_dziesietnie = mantysa_dziesietnie * 2;
        if(mantysa_dziesietnie >=1){
            tablica_wynikowa[i] = '1';
            mantysa_dziesietnie-=1;
        }else{
            tablica_wynikowa[i] = '0';
        }
    }
    for(int i=0;i<rozmiar;i++){
        cout<<tablica_wynikowa[i]<< " ";
    }
}

void ieee_754_float(char liczba_ieee754[], float wynik, const int rozmiar){
    //znak
    int znak = static_cast<int>(liczba_ieee754[0]) - 48; //znak 0 lub 1
    cout<<znak<<endl;
    //cecha
    int cecha = 0, przmnozenie = 1; //1,2,4,8,16itp.
    for(int i=8;i>=1;i--){
        if(liczba_ieee754[i] == '1') cecha+= 1*przmnozenie;
        else cecha+=0;
        przmnozenie = przmnozenie*2;
    }
    cecha = cecha - 127; //odejmujemy przesuniecie
    //mantysa
    float mantysa=0, przmnozenie_float=0.5; // 1/2, 1/4, 1/8
    for(int i=9;i<32;i++){
        if(liczba_ieee754[i] == '1') mantysa+=(1*przmnozenie_float);
        else cecha+=0;
        przmnozenie_float = przmnozenie_float * 0.5;
    }
    mantysa+=1;//dodajemy 1
   float float_wynik = pow(-1, znak) * mantysa * pow(2, cecha);
   cout<<setprecision(10)<<float_wynik<<endl;
    
}


int main(){
    int info;
    cin>>info;
    switch(info){
        case 1:{
            //float na ieee754
            float liczba;
            const int rozmiar = 32;
            string tablica_wynikowa[32];
            cin>>liczba;
            float_ieee754(tablica_wynikowa, liczba, rozmiar);
            break;
        }
        case 2:{
            const int rozmiar = 32;
            char liczba_ieee754[32];
            float wynik;
            bool ok = true;
            do{
                for(int i=0;i<32;i++){
                    cin>>liczba_ieee754[i];
                    if(liczba_ieee754[i] != '1' && liczba_ieee754[i] != '0'){ //jeśli zostanie wbiasanego coś innego niż 0 lub 1
                        ok = false;
                         cout<<i<<endl;
                         break;
                     }
                 }
             }while(ok == false);
            ieee_754_float(liczba_ieee754, wynik, rozmiar);
            break;
        }
        default: cout<<"Cos sie zepsulo";
    }
    
    return 0;
}