#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;


void wypisz_int(int liczby[], const int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        cout << liczby[i] << " ";

    }
}


void sortowanie(int liczby[], const int rozmiar) {
    int ilosc_jedynek[10] = { 0,0,0,0,0,0,0,0,0,0 }, kopia_liczby[10];
    for (int i = 0; i < rozmiar; i++) {
        kopia_liczby[i] = liczby[i];
    }
    for (int i = 0; i < rozmiar; i++) {
        while (kopia_liczby[i] > 0) {
            if (kopia_liczby[i] % 2 == 1) ilosc_jedynek[i]++;
            kopia_liczby[i] = kopia_liczby[i] / 2;
        }
    }
    //sortowanie - sortujemy po liczbie jedynek jednoczsnie zamieniając w liczbach
    int minimum;
    for (int i = 0; i < rozmiar; i++) {
        minimum = i;
        for (int j = i + 1; j < rozmiar; j++) {
            if (ilosc_jedynek[j] < ilosc_jedynek[minimum]) minimum = j;
        }
        swap(ilosc_jedynek[minimum], ilosc_jedynek[i]);
        swap(liczby[minimum], liczby[i]);
        wypisz_int(liczby, rozmiar);
    }
}


float wartosc_f_x(float x) {
    return pow(x, 3) - 4 * pow(x, 2) + x - 9;
}
float pochodna_f_x(float x) {
    return 3 * pow(x, 2) - 8 * x + 1;
}

double newton_rapshon(double x_1, double eps, int rekurencje, double& wynik) {
    rekurencje--;
    double x = x_1;
    double f_x = wartosc_f_x(x);
    double pochodna = pochodna_f_x(x);
    x_1 = x - (f_x / pochodna);
    if (rekurencje > 0 and (abs(x_1 - x) <= eps)) {
        wynik = x_1;
        return 1;
    }
    if (rekurencje == 0) return 0;
    return newton_rapshon(x_1, eps, rekurencje, wynik);
}

int main() {
    int info;
    cin >> info;
    switch (info) {
    case 1: {
        int liczby[10];
        const int rozmiar = 10;
        for (int i = 0; i < rozmiar; i++) {
            cin >> liczby[i];
        }
        sortowanie(liczby, rozmiar);
        break;
    }
    case 2: {
        break;
    }
    case 3: {
        double x_1, eps;
        int rekurencje;
        cin >> x_1 >> eps;
        cin >> rekurencje;
        double wynik;
        double czy_jest = newton_rapshon(x_1, eps, rekurencje, wynik);
        if (czy_jest == 1) cout << wynik << " ";
        else cout << "Nie znaleziono miejsca zerowego.";
    }
    }
    return 0;
}