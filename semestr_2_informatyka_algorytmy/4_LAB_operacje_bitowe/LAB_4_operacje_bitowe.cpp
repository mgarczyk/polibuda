#include <iostream>
#include <bitset>
using namespace std;

void ile_jedynek(int tab[], int ile){
    int  maks_licznik  = 0;
    for (int i = 0; i < ile; i++) {
        int liczba = tab[i];
        unsigned int maska = 0x80000000;
        const int liczba_bitow = 8;
        int pierwsze_1 = 0;
        int tmp_licznik = 0;
        for (int i = 0; i < sizeof(liczba) * liczba_bitow; i++) {
            if (maska & liczba) {
                tmp_licznik++;

            }

            maska = maska >>= 1;
        }
        if (tmp_licznik > maks_licznik) maks_licznik = tmp_licznik;
    }
    cout<<maks_licznik;

    }


int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {

        case 1:
        {
            const int ile = 10;
            int tab[10];
            for (int i = 0; i < ile; i++) {
                cin >> tab[i];
            }
           ile_jedynek(tab, ile);
           break;

        }
        case 2:
        {
            int liczba;
            cin >> liczba;
            unsigned int maska = 0x80000000;
            const int liczba_bitow = 8;
            //najpierw szukamy pozycję pierwszej jedynki od lewej
            int pierwsze_1 = 0;
            for (int i = 0; i < sizeof(liczba) * liczba_bitow; i++) {
                if (!(liczba & maska) == 0) {
                    pierwsze_1 = i;
                    break;
                }
                maska = maska >> 1;
            }
            //potem szukamy drugiej jedynki od lewej
            maska = 0x80000000; //reset maski
            maska = maska >> pierwsze_1 + 1; //przesunięcie maski na pozycje pierwszej 1
            int drugie_1 = 0;
            for (int i = pierwsze_1 + 1; i < sizeof(liczba) * liczba_bitow; i++) {
                if (!(liczba & maska) == 0) {
                    drugie_1 = i;
                    break;
                }
                maska = maska >> 1;
            }
            //zliczamy 0 pomiędzy pierwszą jedynką a drugą jedynką np. 9 - 1001 -> pętla ustawi się na pozycji pierwszego 0 i zakończy na pozycji drugiego 0, licznik = 2
            int licznik = 0;
            if (drugie_1 != 0) {
                for (int i = pierwsze_1 + 1; i < drugie_1; i++) {
                    licznik++;
                }
                cout << licznik;
            }
            else cout << 0;
            break;
        }
        case 3:
        {
            int liczba;
            cin >> liczba;
            bool czy_palindrom = 1;
            //sprawdzimy czy każdy bit od lewej jest równy swojemu odpowiednikowi z prawej strony
            int lewa = 0; //numer pierwszego bitu
            int prawa = (sizeof(liczba) * 8) - 1; //numer ostatniego bitu
            while (lewa < prawa) {
                if (bool(liczba & (1 << lewa)) != bool(liczba & (1 << prawa))) czy_palindrom = 0;
                lewa++;
                prawa--;
            }
            cout << czy_palindrom; //palindrom jest sprawdzany dla 32 bitów czyli np. 5(10) = 101(2) nie będzie palindromem bo 0 z przodu dojdą
            break;
        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}
