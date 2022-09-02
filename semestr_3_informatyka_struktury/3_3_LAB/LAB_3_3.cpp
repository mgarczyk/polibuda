#include <iostream> // cout
#include <cstdlib>  // rand
#include <cstdio>   // fflush // printf
#include <cmath>    // floor



using namespace std;


class kulka
{
public:
    int v;
    int numer;
    kulka* next; //Pole next wskazuje kolejna kulke
    kulka(int numer = 0) //konstruktor  // uwaga na przesłonięcie nazwy zmiennej klasy przez nazwę argumentu metody
    {
        this->numer = numer; //this->numer zmienna klasy, samo numer nazwa metody (funkcji)
        this->v = rand() % 899 + 100;
        cout << "K:" << numer << "=" << v << "\t";
    }

    virtual ~kulka() {
        cout << "D:" << numer << "=" << v << "\t";
    }

    void print_one_element() //funkcja do wypisania numeru oraz wartości v konkretnej, jednej kulki
    {
         //przechodzi przez wszytkie kulki i wypisuje od konca
        cout << numer << ":" << v << " ";
    }
    void print_from_beginning() //funkcja rekurenycjna służąca do wypisania numerów oraz wartości v wszytkich kulek od początku do końca listy
    {
        //przechodzi przez wszytkie kulki i wypisuje od konca
        cout << numer << ":" << v <<" ";
        if (next) next->print_from_beginning();  //if za cout, od poczatku do końca, jeżeli jest next, czyli następna kulka, to użyj na niej tej funkcji, czyli wypisz jej dane i powtórz

    }
    void print_from_end() //funkcja rekurenycjna służąca do wypisania numerów oraz wartości v wszytkich kulek od końca do poczatku listy
    {
        //przechodzi przez wszytkie kulki i wypisuje od konca
        if (next) next->print_from_end();  //if przed cout od końca do poczatku, jeżeli jest next, czyli następna kulka, to użyj na niej tej funkcji, czyli wypisz jej dane i powtórz
        cout << numer << ":" << v << " ";

    }
    void zwieksz() {
        this->v = 2 * v;
    }

};
int main(int argc, char** argv) {
    cout << "Zagadnienie 1: " << endl;
    kulka* z = new kulka(-11); //Tworzymy kulke pierwsza
    kulka* tmp = z; //wskaznik tymczasowy wskazuje pierwsza kulke
    cout << endl;
    for (int i = 0; i < 10; i++) { //tworzymy 10 kilejnych kulek
        tmp->next = new kulka(i); //tworzymy kulke o numerze i, od ostatniej kulki
        tmp = tmp->next; //wskaznik tymczasowy wskazuje ostatni element
        cout << endl;
    }
    cout << "Zagadnienie 2: " << endl;
    cout << endl;
    tmp = z;
    //Wskaznikami do prozdu
    cout << "Wskaznikami od przodu: " << endl;
    while (tmp->next) {
        cout << tmp->numer << ":" << tmp->v << " ";
        tmp = tmp->next;

    };
    cout << tmp->numer << ":" << tmp->v << " ";
    cout << endl;
    cout << "Funkcja wypisujadca od poczatku do konca: " << endl;
    tmp = z; //ustawiamy tak zeby tmp wskazywal pierszy element
    tmp->print_from_beginning(); //uruchomienie rekurencyjnej funkcji print_from_beginning() na obiekcie wskazywanym przez wskaźnik tmp
    cout << endl;
    cout << "Funkcja od tylu: " << endl;
    tmp->print_from_end(); //uruchomienie rekurencyjnej funkcji print_from_end() na obiekcie wskazywanym przez wskaźnik tmp
    cout << endl;
    cout << endl;



}
