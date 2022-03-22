#include <iostream>
using namespace std;

void wypisz_dane(unsigned int dane[], const int wielkosc) {
    for (int i = 0; i < wielkosc; i++) {
        cout << dane[i] << " ";
    }
}


void sortowanie(unsigned int dane[], const int wielkosc) {
    int dane_kopia[15];
    for (int i = 0; i < wielkosc; i++) { 
        dane_kopia[i] = dane[i];
    }
    int  sumowanie[15];
    for (int i = 0; i < wielkosc; i++) {
        sumowanie[i] = 0;
        while (dane_kopia[i] > 0) {
            sumowanie[i] = sumowanie[i] + dane_kopia[i] % 10; 
            dane_kopia[i] = dane_kopia[i] / 10;
        }
    }
    int suma_aktualna, aktualna_liczba;
    for (int i = 1; i < wielkosc; i++) {
        int suma_aktualna = sumowanie[i], aktualna_liczba = dane[i], j = i - 1;
        while (j >= 0 && sumowanie[j] > suma_aktualna) { 
            sumowanie[j + 1] = sumowanie[j]; 
            dane[j + 1] = dane[j]; 
            j--;
        }
        sumowanie[j + 1] = suma_aktualna; 
        dane[j + 1] = aktualna_liczba; 
    }
    wypisz_dane(dane, wielkosc);
}

float srednia_f(float dane_2[], const int wielkosc_2) {
    float suma_indeks=0, suma_gora=0;
    for (int i = 0; i < wielkosc_2; i++) {
        suma_gora += i * dane_2[i];
        suma_indeks += i;
    }
    float srednia = suma_gora / suma_indeks;
    return srednia;
}

bool porownaj(float pierwsza, float druga) {
    int cecha_pierwsza = 0, cecha_druga = 0;
    if (pierwsza < 0) {
        pierwsza = (-1) * pierwsza;
    }
    if (druga < 0) {
        druga = (-1) * druga;
    }
    //cecha
    while (pierwsza >= 2){
        cecha_pierwsza+=1;
        pierwsza /= 2;
    }
    while (druga >= 2) {
        cecha_druga+=1;
        druga /= 2;
    }
    //mantysa
    bool to_samo = false;
    if ((cecha_pierwsza == cecha_druga) || pierwsza==druga) to_samo = true;
    return to_samo;
}




int main()
{
	int dane;
	cin >> dane;
	switch (dane) {
		case 1: {
            unsigned int dane[15];
            const int wielkosc = 15;
            for (int i = 0; i < wielkosc; i++) {
                cin >> dane[i];
            }
            sortowanie(dane, wielkosc);
			break;
		}
		case 2: {
            float dane_2[10];
            const int wielkosc_2 = 10;
            for (int i = 0; i < wielkosc_2; i++) {
                cin >> dane_2[i];
            }
            float srednia = srednia_f(dane_2, wielkosc_2);
            cout << srednia << " ";
			break;

		}
		case 3: {
            float pierwsza, druga;
            cin >> pierwsza;
            cin >> druga;
            bool to_samo = porownaj(pierwsza, druga);
            cout << to_samo << " ";
			break;

		}
		default: cout << "Blad";
	}

}

