#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
void wypisz_char(double tab_ascii[], const int rozmiar_1) {
    for (int i = 0; i < rozmiar_1; i++) {
        if (tab_ascii[i] - static_cast<int>(tab_ascii[i]) == 0.5) { //jeśli po odjęciu części całkowitej zostatnie tyle to znaczy że jest to duża litera
            cout << static_cast<char>(tab_ascii[i] - 32.5)<<" "; //w tych miejscach trzeba "wrócić do dużych liter"
        }
        else {
            cout << static_cast<char>(tab_ascii[i])<<" ";
        }

    }
}
void sortowanie_wybieranie(char tab_duze[], const int rozmiar_1) {
    int index_minimum;
    double tab_ascii[10]; //kody ascii (jak duża to +32.5)
    for (int i = 0; i < rozmiar_1; i++) {
        if (tab_duze[i] >= 'A' && tab_duze[i] <= 'Z') {
            tab_ascii[i] = static_cast<int>(tab_duze[i]) + 32.5;
        }
        else {
            tab_ascii[i] = static_cast<int>(tab_duze[i]);
        }
    }
    for (int i = 0; i < rozmiar_1; i++) {
        index_minimum = i;  //sortujemy po kodach ascii
        for (int j = i + 1; j < rozmiar_1; j++) {
            if (tab_ascii[j] < tab_ascii[index_minimum]) index_minimum = j; //ale sortujemy po tablicy z małymi literami
        }
        swap(tab_ascii[index_minimum], tab_ascii[i]); //sortujemy po kodach ascii, ale zamian dokonujemy w obrębie liter
        wypisz_char(tab_ascii, rozmiar_1);
    }   
}

void wypisz_int(int tab_liczby[], const int rozmiar_2) {
    for (int i = 0; i < rozmiar_2; i++) {
        cout << tab_liczby[i] << " ";
    }
}

void sortowanie_wstawianie(int tab_liczby[10], const int rozmiar_2) {
    int tab_sumy[10], tab_liczby_kopia[10];
    for (int i = 0; i < rozmiar_2; i++) { //kopia do sumowania
        tab_liczby_kopia[i] = tab_liczby[i];
    }
    for (int i = 0; i < rozmiar_2; i++) {
        tab_sumy[i] = 0;
        while (tab_liczby_kopia[i] > 0) {
            tab_sumy[i] = tab_sumy[i] + tab_liczby_kopia[i] % 10; //sumowanie
            tab_liczby_kopia[i] = tab_liczby_kopia[i] / 10;
        }
    }
    int tmp_suma, tmp_cyfra, j;
    for (int i = 1; i < rozmiar_2; i++) {
        tmp_suma = tab_sumy[i];  //aktalnie sprawdzana suma
        tmp_cyfra = tab_liczby[i]; //odpowiadająca jej liczba
        j = i - 1;
        while (j >= 0 && tab_sumy[j] < tmp_suma) { //sortowanie po sumie
            tab_sumy[j + 1] = tab_sumy[j]; //przesunięcie w tablicy sum
            tab_liczby[j + 1] = tab_liczby[j]; //odpowiadające przesunięcie w tablicy liczb
            j--;
        }
        tab_sumy[j + 1] = tmp_suma; //wstawienie wartości w odpowiednie miejsce w tablicy sum
        tab_liczby[j + 1] = tmp_cyfra; //odpowiadające wstawienie w tablcy liczb
        wypisz_int(tab_liczby, rozmiar_2);
    }
}
void sortowanie_babelkowe(int tab_hybryda[], const int rozmiar_3) {
    for (int i = 0; i < rozmiar_3; i++) {
        for (int j = 1; j < rozmiar_3 - i; j++) {
            if (tab_hybryda[j - 1] > tab_hybryda[j]) {
                swap(tab_hybryda[j - 1], tab_hybryda[j]);
            }
        }
           wypisz_int(tab_hybryda, rozmiar_3);
    }        
}
void sortowanie_szybkie(int tab_hybryda[], int pierwszy, int ostatni, int rozmiar_3){
    if (pierwszy >= ostatni) return;
    int piwot = tab_hybryda[pierwszy];
    cout <<"Piwot:" <<  piwot << endl;
    int lewy = pierwszy;
    int prawy = ostatni + 1;
    while (true) {
        do lewy++; while (lewy <= ostatni && tab_hybryda[lewy] < piwot);
        do prawy--; while (tab_hybryda[prawy] > piwot);
        if (lewy > prawy) break;
        swap(tab_hybryda[lewy], tab_hybryda[prawy]);
    }
    swap(tab_hybryda[pierwszy], tab_hybryda[prawy]);
    wypisz_int(tab_hybryda, rozmiar_3);
    sortowanie_szybkie(tab_hybryda, pierwszy, prawy - 1, rozmiar_3);
    sortowanie_szybkie(tab_hybryda, prawy+1, ostatni, rozmiar_3);
}

int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {
        //sortowanie przez wybieranie niesłownikowe a A b B c C itp. 
        case 1:
        {
            const int rozmiar_1 = 10;
            char tab_duze[10];
            bool ok;
            string tmp;
            for (int i = 0; i < rozmiar_1; i++) {
                ok = false;
                do {
                    cin >> tmp;
                    if (((tmp[0] >= 'A' && tmp[0] <= 'Z') or (tmp[0] >= 'a' && tmp[0] <= 'z')) && tmp.length() == 1) { //musi być w zakresie od A do Z lub od a do z oraz ma to być jeden znak
                        ok = true;
                    }
                    tab_duze[i] = tmp[0];
                } while(ok == false);
            }
            sortowanie_wybieranie(tab_duze, rozmiar_1);
            break;
        }
        case 2:
        {
            //sortowanie przez wstawanie po sumach cyfr
            int tab_liczby[10];
            int rozmiar_2 = 10;
            bool ok;
            string dane;
            for (int i = 0; i < rozmiar_2; i++) {
                ok = false;
                do {
                    cin >> dane;
                    for (int j = 0; j < dane.length(); j++) {
                        if (dane[j] >= '0' && dane[j] <= '9') {
                            ok = true;
                        }
                        else {
                            ok = false;
                            break;
                        }
                    }
                }while(ok == false); //jeśli do inta spróbujemy wpisać coś innego to cin może nas o tym poinformować
                tab_liczby[i] = atoi(dane.c_str());
            }

            sortowanie_wstawianie(tab_liczby, rozmiar_2);
            break;
        }
        case 3:
        {
            const int rozmiar_3 = 19;
            int tab_hybryda[19];
            for (int i = 0; i < rozmiar_3; i++) {
                cin >> tab_hybryda[i];
            }
            if (rozmiar_3 <= 9) {
                sortowanie_babelkowe(tab_hybryda, rozmiar_3);
            }
            else {
                sortowanie_szybkie(tab_hybryda,0,rozmiar_3-1,rozmiar_3);
            }
        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}