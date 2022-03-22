#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;



double f_zadanie_1(double x){ //wartość funkcji w punkcie x1 do zadania 1 i 2
    return 3*x - 5; //y=x^3+2x^2-2

}


double f_pochodna_zadanie_2(double x){ //wartość pochodnej w punkcie x1 do zadania 2
    return 2 * x - 2;  //y' = 3x^2 + 4x
}


double bisekcja(double a, double b, double eps, int max_iteracja) {
    if (f_zadanie_1(a) == 0.0) return a; //sprawdzamy czy punkt a nie jest miejscem zerowym
    if (f_zadanie_1(b) == 0.0) return b; //sprawdzamy czy punkt b nie jest miejscem zerowym
    double srodek = (a + b) / 2; //wyznaczamy srodek przedzialu
    if (b - a <= eps || max_iteracja == 1) return srodek; //warunek końcowy lub za dużo iteracji
    max_iteracja--; //zmniejszenie liczby kolejnych powtorzeń
    cout << max_iteracja << endl;
    if (f_zadanie_1(a) * f_zadanie_1(srodek) < 0) {
         return bisekcja(a, srodek, eps, max_iteracja);
    }
    return bisekcja(srodek, b, eps, max_iteracja);
    
 }


double newton_pierwiastek(double x1, double eps, int max_iteracja) {
    double x = x1; //jako wartość x podajemy ostatnią wartość x wyznaczoną przez x1
    double f_x = f_zadanie_1(x); //wyznaczamy wartość funkcji w punkcie x
    double f_x_pochodna = f_pochodna_zadanie_2(x); //wyznaczamy wartość pochodnej w punkcie x
    x1 = x - (f_x / f_x_pochodna); //ponownie wyznaczamy x1 za pomocą wzoru
    if (max_iteracja == 0 || abs(x1 - x) <= eps) {//wypisanie wyniku zgodnie z dokładnością lub ilością powtórzeń
        cout << max_iteracja << endl;
        return x1; //zwrócenie wartości
    }
    max_iteracja--;
    return newton_pierwiastek(x1, eps, max_iteracja); //rekurencja

}


//Szukanie minimum metodą Newtona

float wartosc_funkcji(float x, float y) {
    return pow(y, 2) + 2 * y + 2 * pow(x, 2) + x + 1;
}

float pochodna_pierwsza_po_x_trzecie(float x, float y){
    return (4*x) + 1;
}

float pochodna_pierwsza_po_y_trzecie(float x, float y) {
    return (2 * y) + 2;
}

float pochodna_druga_po_x_trzecie(float x,  float y) {
    return 4;
}

float pochodna_druga_po_y_trzecie(float x, float y) {
    return 2;
}

float minimum_funkcji(float x, float y, float eps, int max_rekurencje)
{
    if (((abs(pochodna_pierwsza_po_x_trzecie(x, y)) <= eps) && (abs(pochodna_pierwsza_po_y_trzecie(x, y)) <= eps)) || max_rekurencje <= 0)
    {
        return wartosc_funkcji(x, y);
    };

    if (abs(pochodna_pierwsza_po_x_trzecie(x, y)) <= eps)
    {
        return minimum_funkcji(x, (y - pochodna_pierwsza_po_y_trzecie(x, y) / pochodna_druga_po_y_trzecie(x, y)), eps, max_rekurencje - 1);
    }

    if (abs(pochodna_pierwsza_po_y_trzecie(x, y)) <= eps)
    {
        return minimum_funkcji((x - pochodna_pierwsza_po_x_trzecie(x, y) / pochodna_druga_po_x_trzecie(x, y)), y, eps, max_rekurencje - 1);
    }
    return minimum_funkcji(x - pochodna_pierwsza_po_x_trzecie(x, y) / pochodna_druga_po_x_trzecie(x, y), (y - pochodna_pierwsza_po_y_trzecie(x, y) / pochodna_druga_po_y_trzecie(x, y)), eps, max_rekurencje - 1);
}

int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {

        case 1:
        {
            double a, b, eps;
            cin >> a >> b >> eps;
            int max_iteracja;
            cin >> max_iteracja;
            double wynik = bisekcja(a, b, eps, max_iteracja);
            cout << setprecision(5) << wynik;
            break;
        }
        case 2:
        {
            double x1, eps;
            int max_iteracja;
            cin >> x1 >> eps;
            cin >> max_iteracja;
            double wynik = newton_pierwiastek(x1, eps, max_iteracja);
            cout << setprecision(5) << wynik << endl;
            break;
        }
        case 3:
        {
            float x, y, eps;
            cin >> x >> y >> eps;
            int max_rekurencja;
            cin >> max_rekurencja;
            float wynik = minimum_funkcji(x,y,eps,max_rekurencja);
            cout << wynik;
            break;
        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}