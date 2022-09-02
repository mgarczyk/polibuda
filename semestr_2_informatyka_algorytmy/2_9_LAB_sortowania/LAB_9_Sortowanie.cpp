#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;
void wypisz_char(char tab_1[], const int rozmiar_1) {
    for (int i = 0; i < rozmiar_1; i++) {
        cout << tab_1[i] << " ";
    }
}
void sortowanie_wybieranie(char tab_1[], const int rozmiar_1) {
    int index_minimum;
    for (int i = 0; i < rozmiar_1; i++) {
        index_minimum = i;
        for (int j = i + 1; j < rozmiar_1; j++) {
            if (tab_1[j] < tab_1[index_minimum]) index_minimum = j;
        }
        swap(tab_1[index_minimum], tab_1[i]);
        wypisz_char(tab_1, rozmiar_1);
    }
}
void sortowanie_dwuwymiarowe(int tab_2[][5], const int wiersze, const int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            int w = i;  //standardowo szukanie mniejszeczego elemntu zaczynamy w tym samym wierszu i nstępnej kolumnie
            int k = j + 1;
            while (true) {
                if (k == kolumny) { //jeżeli jesteśmy w ostatniej kolumnie to zaczynamy od pierwszej kolumny w następnym wierszu
                    k = 0;
                    w++;
                    if (w == wiersze) break; // warunek końcowy: w==wiersze && k == kolumny
                }

                if (tab_2[i][j] > tab_2[w][k]) swap(tab_2[i][j], tab_2[w][k]); //jeśli znajdujemy coś mniejszego niż aktualny element to zamieniamy je
                k++;
            }
        }
    }
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (i == wiersze - 1 && j == kolumny - 1) cout << tab_2[i][j];
            else cout << tab_2[i][j] << " ";
        }
    }
}
void wypisz_int(int tab_3[], const int rozmiar_2) {
    for (int i = 0; i < rozmiar_2; i++) {
        cout << tab_3[i] << " ";
    }
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

int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3 or info == 4 or info == 5 or info == 6 or info == 7 or info == 8) {
        switch (info) {
        case 1:
        {
            const int rozmiar_1 = 10;
            char tab_1[10];
            for (int i = 0; i < rozmiar_1; i++) {
                cin >> tab_1[i];
            }
            sortowanie_wybieranie(tab_1, rozmiar_1);
            break;
        }
        case 2:
        {
            const int wiersze = 4;
            const int kolumny = 5;
            int tab_2[4][5];
            for (int i = 0; i < wiersze; i++) {
                for (int j = 0; j < kolumny; j++) {
                    cin >> tab_2[i][j];
                }
            }
            sortowanie_dwuwymiarowe(tab_2, wiersze, kolumny);
            break;
        }
        //koktajl
        case 3:
        {
            const int rozmiar_2 = 6;
            int tab_3[6];
            for (int i = 0; i < rozmiar_2; i++) {
                cin >> tab_3[i];
            }
            cout << endl;
            sortowanie_koktajlowe(tab_3, rozmiar_2);
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
            int tmp,j;
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
        //babelek
        case 6: {
            const int rozmiar_5 = 7;
            int tab_6[7];
            for (int i = 0; i < rozmiar_5; i++) {
                cin >> tab_6[i];
            }
            for (int i = 0; i < rozmiar_5; i++){
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
        //kopiec - budowa
        case 7: {
                const int N = 11; // liczba elementów
                int d[N + 1], i, j, k, x;

                srand((unsigned)time(NULL));

           

                // Inicjujemy zbiór d[] liczbami pseudolosowymi od 0 do 9

                for (i = 1; i <= N; i++) cin >> d[i];

                // Budujemy kopiec

                for (i = 2; i <= N; i++)
                {
                    j = i; k = j / 2;
                    x = d[i];
                    while ((k > 0) && (d[k] > x)) //zmiana znaku przy k (teraz jest mnimalny w korzeniu, jak damy > to będzie maksymalny)
                    {
                        d[j] = d[k];
                        j = k; k = j / 2;
                    }
                    d[j] = x;
                }

                // Prezentujemy wyniki psuje się jak za dużo elementów ale działa

                x = (N + 1) / 2; k = 2;
                for (i = 1; i <= N; i++)
                {
                    for (j = 1; j <= x - 1; j++) cout << " ";
                    cout << d[i];
                    for (j = 1; j <= x; j++) cout << " ";
                    if (i + 1 == k)
                    {
                        k += k; x /= 2; cout << endl;
                    }
                }
                cout << endl;
                cout << endl;
                //wypisanie normalne
                cout << "Odp: " << endl;
                for (int i = 1; i <= N; i++) {
                    cout << d[i] << " ";
                }
                // Gotowe

                cout << endl << endl;
        break;
        }
        case 8: {

           
                const int N = 10;  // liczebność zbioru
                int d[N + 1], i, j, k, m, x;

                srand((unsigned)time(NULL));
                // Wypełniamy tablicę liczbami pseudolosowymi i wyświetlamy je
                 cout << "Podaj dane:" << endl;
                for (i = 1; i <= N; i++)
                {
                    cin>>d[i];
                }
                cout << endl;

                // Budujemy kopiec

                for (i = 2; i <= N; i++)
                {
                    j = i; k = j / 2;
                    x = d[i];
                    while ((k > 0) && (d[k] < x))
                    {
                        d[j] = d[k];
                        j = k; k = j / 2;
                    }
                    d[j] = x;
                }

                // Rozbieramy kopiec

                for (i = N; i > 1; i--)
                {
                    swap(d[1], d[i]);
                    j = 1; k = 2;
                    while (k < i)
                    {
                        if ((k + 1 < i) && (d[k + 1] > d[k]))
                            m = k + 1;
                        else
                            m = k;
                        if (d[m] <= d[j]) break;
                        swap(d[j], d[m]);
                        j = m; k = j + j;
                    }
                    cout << endl;
                    cout << endl;
                    cout << "Etap: ";
                    for (int pisz = 1; pisz <= N; pisz++) cout << setw(4) << d[pisz];
                }

                // Wyświetlamy wynik sortowania
                cout << endl;
                cout << endl;
                cout << "Po sortowaniu:\n\n";
                for (i = 1; i <= N; i++) cout << setw(4) << d[i];
                cout << endl;
                break;
        }
        

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}