#include <iostream>
#include <string>
using namespace std;

void tablica_suma(int tab[][5], const int wiersze, const int kolumny) {
    int suma = 0;
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            //gorny rzad
            //lewy gorny róg
            if (i == 0 && j == 0) {
                suma = tab[i + 1][j] + tab[i][j + 1] + tab[j + 1][i + 1];
            }
            //prawy gorny róg
            else if (i == 0 && j == kolumny - 1) {
                suma = tab[i][j - 1] + tab[i + 1][j] + tab[i + 1][j - 1];
            }
            //gorne prostakaty
            else if (i == 0 && (j != kolumny - 1 && j != 0)) {
                suma = tab[i][j - 1] + tab[i + 1][j - 1] + tab[i + 1][j] + tab[i][j + 1] + tab[i + 1][j + 1];
            }
            //dolny rzad
            //lewy dolny róg
            else if (i == wiersze - 1 && j == 0) {
                suma = tab[i - 1][j] + tab[i - 1][j + 1] + tab[i][j + 1];
            }
            //prawy dolny róg
            else if (i == wiersze - 1 && j == kolumny - 1) {
                suma = tab[i - 1][j] + tab[i - 1][j - 1] + tab[i][j - 1];
            }
            //dolne prostakaty
            else if (i == wiersze - 1 && (j != kolumny - 1 && j != 0)) {
                suma = tab[i][j - 1] + tab[i - 1][j - 1] + tab[i - 1][j] + tab[i][j + 1] + tab[i - 1][j + 1];
            }
            //lewo i prawo
            //lewe prostakaty
            else if (j == 0) {
                suma = tab[i - 1][j] + tab[i - 1][j + 1] + tab[i][j + 1] + tab[i + 1][j] + tab[i + 1][j + 1];
            }
            //prawe prostakaty
            else if (j == kolumny - 1) {
                suma = tab[i - 1][j] + tab[i - 1][j - 1] + tab[i][j - 1] + tab[i + 1][j] + tab[i + 1][j - 1];
            }
            else {
                suma = tab[i - 1][j] + tab[i + 1][j] + tab[i][j - 1] + tab[i - 1][j - 1] + tab[i + 1][j - 1] + tab[i][j + 1] + tab[i - 1][j + 1] + tab[i + 1][j + 1];
            }
            //gdyby nie ograniczający nas wyraźnie wymiar tablicy lepiej było by stworzyć tablicę o dwa wiersze i dwie kolumy większą wypełnioną zerami i potem odpowiednio dostowować ją do ilości kolumn i wierszu w zadaniu.
            //wtedy sumowalibyśmy tylko same kwadraty po 3x3 bo 0 nie wpływałby na sumę, a nie trzeba by się obawiać o wykroczenie poza zakres
            if(i == wiersze - 1 && j == kolumny - 1) cout<<suma;
            else cout<<suma<<" ";
            suma = 0;
        }
    }
}
bool palindrom(string tekst_spacje) {
    const int spacja = (int)(' ');
    const int duze_A = (int)('A');
    const int duze_Z = (int)('Z');
    const int male_a = (int)('a');
    const int male_z = (int)('z');
    string tekst;
    //usuniecie spacji
    for (int i = 0; i < tekst_spacje.length(); i++) {
        if ((int)tekst_spacje[i] != spacja) {
            tekst += tekst_spacje[i];
        }
    }
    //przejscie z duzych liter na male
    for (int i = 0; i < tekst.length(); i++) {
        int kod_ascii_znaku = (int)(tekst[i]);
        if (kod_ascii_znaku >= duze_A && kod_ascii_znaku <= duze_Z) {
            int kod_ascii_po_zamianie = kod_ascii_znaku + (male_a - duze_A); //do odpowiedniego znaku dużego dodajemy różnicę pozycji pomiędzy dużym 'A', a małym 'a' i otrzymujemy dany znak ale mały
            tekst[i] = char(kod_ascii_po_zamianie); //dodajemy do dużej litery ilość znaków pomiędzy dużym 'Z' (wcześniej w ASCII), a małym 'a' (później w ASCII) i otrzymujemy oczekiwaną literę tyle, że małą
        }
    }
    string tekst_odwrocony = "";
    //odwrócenie stringa
    for (int i = tekst.length() - 1; i >= 0; i--) {
        tekst_odwrocony = tekst_odwrocony + tekst[i];
    }
    //sprawdzenie czy to palindrom
    for (int i = 0; i <= tekst.length(); i++) {
        if (tekst[i] != tekst_odwrocony[i]) return false;
    }
    return true;
}

int przesuniecie_cykliczne(unsigned int wartosc, unsigned int przesun) {
    int wynik = (wartosc >> przesun) | (wartosc << (32 - przesun));
    return wynik;
}
int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {

        case 1:
        {
            const int wiersze = 4;
            const int kolumny = 5;
            int tab[wiersze][kolumny];
            for (int i = 0; i < wiersze; i++) {
                for (int j = 0; j < kolumny; j++) {
                    cin >> tab[i][j];
                }
            }
            tablica_suma(tab, wiersze, kolumny);
            break;
        }
        case 2:
        {
            cin.ignore();
            string tekst_spacje;
            getline(cin, tekst_spacje);
            bool palindrom_zmienna = palindrom(tekst_spacje);
            if (palindrom_zmienna == true) cout << 1;
            else
                cout<< 0;
            break;
        }
        case 3:
        {
           unsigned int  wartosc, przesun;
           cin >> wartosc >> przesun;
           int wynik = przesuniecie_cykliczne(wartosc, przesun);
           cout << wynik << endl;
           break;
        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}