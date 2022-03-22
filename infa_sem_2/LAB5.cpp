#include <iostream>
#include <string>
using namespace std;


void tablica_z_przedzialem(double a, double b, double *tab_przedzial, const int rozmiar_zadanie_pierwsze) {
    for (int i = 0; i < rozmiar_zadanie_pierwsze; i++) {
        double liczba_do_tablicy;
        do {
            cin >> liczba_do_tablicy;
        } while (liczba_do_tablicy < a or liczba_do_tablicy > b);
        tab_przedzial[i] = liczba_do_tablicy;
    }
    cout << "Resulting array:";
    for (int i = 0; i < rozmiar_zadanie_pierwsze; i++) {
        cout <<" "<<tab_przedzial[i];
    }
}

//sortowanie użyte potem
void sortowanie(int* tab, const int rozmiar_zadania_drugie) {
    for (int i = 0; i < rozmiar_zadania_drugie; i++)
        for (int j = 1; j < rozmiar_zadania_drugie - i; j++)
            if (tab[j - 1] > tab[j])
                swap(tab[j - 1], tab[j]);
}

bool porownanie_funkcja(int* tab_1, int* tab_2, const int rozmiar_zadanie_drugie){
       sortowanie(tab_1, rozmiar_zadanie_drugie);
       sortowanie(tab_2, rozmiar_zadanie_drugie);
       //skoro są już posortowane to sprawdzamy każdy element z pierwszej z każdym z drugiej 
       for (int i = 0; i < rozmiar_zadanie_drugie; i++) {
           if (tab_1[i] != tab_2[i]) return false;
       }
       return true;
    
    return true;
}

void rzymskie_funkcja(string *rzymskie, int *dziesietne, string wejscie) {
    int wynik = 0;
    int pozycja = 0;
    for (int i = 0; i < 13; i++) { //dla kazdego rzymskiego znaku z tablicy rzymskie
    
        //wiemy że dany rzymski znak musi wystąpić przed kolejnym z tablicy rzymskich znaków np. M musi być przed CM itd.
        //sprawdzamy czy dany znak wystąpił na odpowiedniej pozycji np. MCM, M szuka na pozycji 0 (dodaje 1000) pozycja przeskakuje o 1, CM szuka na pozycji 1 (dodaje 900)
        // XIV - M-brak,CM-brak (pozycja utrzymuje się na 0), znajudje X na pozyjci 0 (dodaje 10), pozycja zwiększa się, szuka dalej, aż znajduje IV na pozycji 1 (dodaje 4)
        while (wejscie.find(rzymskie[i], pozycja) == pozycja){  //używamy funkcji find z bibloeki <string> do wyszukania pozycji
            wynik = wynik + dziesietne[i];
            pozycja = pozycja + rzymskie[i].length();
        }

    }
    cout << wynik << endl;
    cout << "Converted " << wejscie << " to " << wynik << ".";
}


int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {
        case 1:
        {
            double a, b;
            cin >> a >> b;
            const int rozmiar_zadanie_pierwsze = 6;
            double tab_przedzial[6];
            tablica_z_przedzialem(a, b, tab_przedzial, rozmiar_zadanie_pierwsze);
            break;
        }
        case 2:
        {
            int tab_1[5], tab_2[5];
            const int rozmiar_zadanie_drugie = 5;
            for (int i = 0; i < rozmiar_zadanie_drugie; i++) {
                double tmp;
                cin >> tmp;
                tmp = static_cast<int>(tmp);
                tab_1[i] = tmp;
            }
            for (int i = 0; i < rozmiar_zadanie_drugie; i++) {
                double tmp;
                cin >> tmp;
                tmp = static_cast<int>(tmp);
                tab_2[i] = tmp;
            }
            bool porownanie = porownanie_funkcja(tab_1, tab_2, rozmiar_zadanie_drugie);
            if (porownanie == 1) cout << "Equal.";
            else {
                cout << "Diffrent.";
            }
            break;
        }
        case 3:
        {
            //indeksy obu tablic odpowiadają, dzięki czemu w łatwy sposób oznaczamy ile wynosi dany symbol rzymski dziesiętnie
            string rzymskie[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
            int dziesietne[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
            string wejscie = "";
            cin >> wejscie;
            rzymskie_funkcja(rzymskie, dziesietne, wejscie);

            break;
        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}