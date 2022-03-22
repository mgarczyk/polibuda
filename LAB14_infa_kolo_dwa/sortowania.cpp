#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

void wypisz_char(float litery_ascii[], const int rozmiar){
    //trzeba sprawdzić czy po odjęciu części całkowitej zostaje 0.5 wtedy jest to duża litera i możemy ją przekształcić i wypisać
    for(int i=0;i<rozmiar;i++){
        //jeżeli po odjęciu od całości części całkowitej będzie 0.5 to jest to duża litera i należy odjąć 32.5 w kodzie ascii w celu wupisania jeej na ekran
        if(litery_ascii[i] - static_cast<int>(litery_ascii[i]) == 0.5) cout<<static_cast<char>(litery_ascii[i] - 32.5)<<" ";
        else cout<<static_cast<char>(litery_ascii[i])<<" ";
    }
        
    
}

//sortowanie a A b B itp.
void sortowanie_liter(char litery[], const int rozmiar){
    float litery_ascii[10];
    //sortować będziemy po kodach ascii odpowiednio przekszatałconych
    for(int i=0;i<rozmiar;i++){
        if(litery[i] >='A' && litery[i] <= 'Z'){
             litery_ascii[i] = static_cast<int>(litery[i]) + 32.5; //zwiększamy wartość kodu ascii do dużej litery o 32.5 dzięki czemu łatwo możemy posrtować po liczbach
        }else{
            litery_ascii[i] = static_cast<int>(litery[i]); //jak mała to zostawiamy oryginalny kod
        }
    }
    //sortowanie
    int index_minimum;
    for(int i=0;i<rozmiar;i++){
        index_minimum = i;
        for(int j=i+1;j<rozmiar;j++){
            if(litery_ascii[j] < litery_ascii[index_minimum]) index_minimum = j;
        }
        swap(litery_ascii[i], litery_ascii[index_minimum]);
        //wypisanie
        wypisz_char(litery_ascii, rozmiar);
    }
}

void wypisz_int(int liczby_tab[], const int rozmiar){
    for(int i=0;i<rozmiar;i++){
        cout<<liczby_tab[i]<<" ";
    }
}
//sortowanie po iloczynie
void sortowanie_liczby(int liczby_tab[], const int rozmiar){
    //kopia tablicy z liczbami bo stracimy ją w wyniku liczenia iloczynu
    int kopia_liczby_tab[10];
    for(int i=0;i<rozmiar;i++){
        kopia_liczby_tab[i] = liczby_tab[i];
    }
    //tworzymy tablicę z iloczynami cyfr po której bedziemy sortować
    int iloczyny_tab[10] = {1,1,1,1,1,1,1,1,1,1};
    for(int  i=0;i<rozmiar;i++){
        while(kopia_liczby_tab[i] > 0){
            iloczyny_tab[i]*=kopia_liczby_tab[i]%10; //kolejne cyfry  przmnażamy
            kopia_liczby_tab[i]/=10;
        }
    }
    //sortujemy tablicę z iloczynami dokonując identycznych zamian w tablicy z liczbami przez co zostanie posortwana tak jak chcmey
    int tmp_iloczyn, tmp_liczba, j;
    for(int i=1;i<rozmiar;i++){
       tmp_liczba = liczby_tab[i];
       tmp_iloczyn = iloczyny_tab[i];
       j = i - 1;
       while(j >= 0 && iloczyny_tab[j] < tmp_iloczyn){ //przechodzimy po ilocznach
           iloczyny_tab[j+1] = iloczyny_tab[j]; //dokonujemy zamian w obu tablicach
           liczby_tab[j+1] = liczby_tab[j];
           j--;
       }
       iloczyny_tab[j + 1] = tmp_iloczyn;
       liczby_tab[j+1] = tmp_liczba;
       wypisz_int(liczby_tab, rozmiar);
    }
}

//sortowanie dwuwymiarowe
void wypisz_dwa_wymiary(int tab_sortuj[][5], int wiersze, int kolumny){
    for(int i=0;i<wiersze;i++){
        for(int j=0;j<kolumny;j++)
            cout<<tab_sortuj[i][j]<<" ";
    }
}
void sortowanie_dwuwymiarowe(int tab_sortuj[][5], int wiersze, int kolumny){
    int w, k;
    for(int i=0;i<wiersze;i++){
        for(int j=0;j<kolumny;j++){
            w = i; //szukać zaczynamy w następnej kolumnie w danym wierszu
            k = j+1;
            while(true){ //przechodzimy przez coałość dokonując zamian
                if(k == kolumny){ //jeżeli przejdziemy przez kolumny to
                    k = 0; //zerujemy licznik kolumn
                    w++; //zwiększamy licznik wierszy
                    if(w == wiersze) break; //jeżeli dojdziemy do końca wierszy i kolumn to kończymy
                }
                //zamiany
                if(tab_sortuj[i][j] > tab_sortuj[w][k]) swap(tab_sortuj[i][j] , tab_sortuj[w][k]);
                k++;
            }
        }
    }
    wypisz_dwa_wymiary(tab_sortuj, wiersze, kolumny);
    
}

void sortowanie_koktajlowe(int tab_3[], const int rozmiar_2) {
    int dol = 0, gora = rozmiar_2 - 1;
    bool zamiana = true;
    while (zamiana) {
        zamiana = false;
        for (int i = dol; i < gora; i++) {
            if (tab_3[i] < tab_3[i + 1]) {
                swap(tab_3[i], tab_3[i + 1]);
                zamiana = true;

            }

        }
        gora--;
        for (int i = gora; i > dol; i--) {
            if (tab_3[i] > tab_3[i - 1]) {
                swap(tab_3[i], tab_3[i - 1]);
                zamiana = true;

            }

        }
        dol++;
        if (zamiana == true) wypisz_int(tab_3, rozmiar_2);
    }

}

int main(){
    int info;
    cin>>info;
    switch(info){
        case 1:{
        char litery[10];
        string znak;
        const int rozmiar = 10;
        for(int i=0;i<rozmiar;i++){
            do{
                cin>>znak;
                //jezeli (nie nalezy do przedziału od a do z LUB A do Z) lub (jest wiecej niz jeden znak) to wpisz ponownie
            }while(!((znak[0]>='a' && znak[0]<='z') || (znak[0]>='A' && znak[0]<='Z')) || znak.length()!=1); 
            litery[i] = znak[0]; //jest ok to zapisz w tablicy
        }
        sortowanie_liter(litery, rozmiar);
        break;    
        }
         case 2:{
            int liczby_tab[10];
            const int rozmiar = 10;
            string liczba;
            bool ok = true;
            //wpisywanie
            for(int i=0;i<rozmiar;i++){
                do{
                    ok = true;
                    cin>>liczba;
                    for(int i=0;i<liczba.length();i++){
                        if(!(liczba[i] >= '0' && liczba[i] <= '9') || liczba[0] == '0'){ //jezeli w liczbie są snaki inne niż 0 do 9 LUB na pozycji pierwszej jest 0 to błąd
                            ok = false;
                            break;
                        }
                    }
                }while(ok==false);
                liczby_tab[i] = atoi(liczba.c_str()); //przejscie ze string na int bibloteka <cstdlib>
            }
            sortowanie_liczby(liczby_tab, rozmiar);
            break;    
        }
         case 3:{
             int tab_sortuj[4][5], wiersze = 4, kolumny = 5;
             for(int i=0;i<wiersze;i++){
                 for(int j=0;j<kolumny;j++){
                     cin>>tab_sortuj[i][j];
                 }
             }
             sortowanie_dwuwymiarowe(tab_sortuj, wiersze, kolumny);
        break;    
        }
               //wstawianie
         case 4: {
             const int rozmiar_3 = 6;
             int tab_4[6];
             for (int i = 0; i < rozmiar_3; i++) {
                 cin >> tab_4[i];
             }
             //sortowanie
             int tmp, j;
             for (int i = 1; i < rozmiar_3; i++) {
                 tmp = tab_4[i];
                 j = i - 1;
                 while (j >= 0 && tab_4[j] > tmp) {
                     tab_4[j + 1] = tab_4[j];
                     j--;
                 }
                 tab_4[j + 1] = tmp;
                 cout << endl;
                 wypisz_int(tab_4, rozmiar_3);

             }
             break;
         }
             //wybieranie
         case 5: {
             const int rozmiar_4 = 7;
             int tab_5[7];
             for (int i = 0; i < rozmiar_4; i++) {
                 cin >> tab_5[i];
             }
             //sortowanie
             int index_minimum;
             for (int i = 0; i < rozmiar_4; i++) {
                 index_minimum = i;
                 for (int j = i + 1; j < rozmiar_4; j++) {
                     if (tab_5[j] < tab_5[index_minimum]) index_minimum = j;
                 }
                 swap(tab_5[index_minimum], tab_5[i]);
                 cout << endl;
                 wypisz_int(tab_5, rozmiar_4);
                 

             }
             break;
         }
         case 6: {
             const int rozmiar_5 = 6;
             int tab_6[6];
             for (int i = 0; i < rozmiar_5; i++) {
                 cin >> tab_6[i];
             }
             for (int i = 0; i < rozmiar_5; i++) {
                 for (int j = 1; j < rozmiar_5 - i; j++) { //pętla wewnętrzna
                     if (tab_6[j - 1] > tab_6[j]) {
                         //zamiana miejscami
                         swap(tab_6[j - 1], tab_6[j]);
                     }
                 }
                 cout << endl;
                 wypisz_int(tab_6, rozmiar_5);
             }
             break;
         }
         }
        default: cout<<"Blad";

    }
    return 0;
}