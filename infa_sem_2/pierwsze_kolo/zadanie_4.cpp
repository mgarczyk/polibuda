#include <iostream>
using namespace std;

int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {

        case 1:
        {
            int decimal;
            cin >> decimal;
            unsigned int maska = 0x80000000;
            const int liczba_bitow = 8;
            //najpierw szukamy pozycję pierwszej jedynki od lewej
            int pierwsze_1 = 0;
            for (int i = 0; i < sizeof(decimal) * liczba_bitow; i++){
                if (!(decimal & maska) == 0) {
                    pierwsze_1 = i;
                    break;
                }
                maska = maska >> 1;
            }
            //wypisujemy od pozycji pierwszej jedynki do końca pomijając poprzedające ją 0
            maska = 0x80000000; //reset maski
            maska = maska >> pierwsze_1; //przesunięcie maski na pozycje pierwszej 1
            for (int i = pierwsze_1; i < sizeof(int) * liczba_bitow; i++) { //ustawienie pętli na pozycji pierwszej jedynki
                if (maska & decimal) cout << 1;
                else cout << 0;
                maska = maska >> 1;
            }
            break;
        }
        case 2:
        {
            int decimal;
            cin >> decimal;
            unsigned int maska = 0x80000000;
            const int liczba_bitow = 8;
            //najpierw szukamy pozycję pierwszej jedynki od lewej
            int pierwsze_1 = 0;
            for (int i = 0; i < sizeof(decimal) * liczba_bitow; i++) {
                if (!(decimal & maska) == 0) {
                    pierwsze_1 = i;
                    break;
                }
                maska = maska >> 1;
            }
            //potem szukamy drugiej jedynki od lewej
            maska = 0x80000000; //reset maski
            maska = maska >> pierwsze_1 + 1; //przesunięcie maski na pozycje pierwszej 1
            int drugie_1 = 0;
            for (int i = pierwsze_1 + 1; i < sizeof(decimal) * liczba_bitow; i++) {
                if (!(decimal & maska) == 0) {
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
                cout << licznik << endl;
            }
            else cout << "Druga jedynka nie wystąpiła." << endl;
            break;
        }
        case 3:
        {
            int decimal;
            cin >> decimal;
            bool czy_palindrom = 1;
            //sprawdzimy czy każdy bit od lewej jest równy swojemu odpowiednikowi z prawej strony
            int lewa = 0; //numer pierwszego bitu
            int prawa = (sizeof(decimal) * 8) - 1; //numer ostatniego bitu
            while (lewa < prawa) {
                if (bool(decimal & (1 << lewa)) != bool(decimal & (1 << prawa))) czy_palindrom = 0;
                lewa++;
                prawa--;
            }
            cout << czy_palindrom << endl;
            break;
        }

      }
    }
    else {
        cout << "Wrong task number." << endl;
    }
    return 0;
}