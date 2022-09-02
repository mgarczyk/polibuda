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
    kulka* next = NULL; //Pole next wskazuje kolejna kulke
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
    bool check_is_even(){
        if(v%2 == 0) return true;
        return false; //Jak bylo TRUE to musi byc FALSE

    }

};
int main(int argc, char** argv) {
    cout << "Tworzenie kulek: " << endl;
    cout<<endl;
    kulka* root = new kulka(1); //Tworzymy kulke pierwsza
    kulka* tmp = root; //wskaznik tymczasowy wskazuje pierwsza kulke
    cout << endl;
    for (int i = 2; i <= 15; i++) { //tworzymy 15 kilejnych kulek
        tmp->next = new kulka(i); //tworzymy kulke o numerze i, od ostatniej kulki
        tmp = tmp->next; //wskaznik tymczasowy wskazuje ostatni element, zebysmy mogli na nim dalej dzialac
        cout << endl;
    }
    //normalne
    cout<<endl;
    cout << "Wyswietlanie normalnie: " << endl;
    cout << endl;
    tmp = root;
    while(tmp!=NULL){
        tmp->print_one_element();
        tmp = tmp->next;
    };
    //parzyste
    cout<<endl;
    cout << "Licznik: " << endl;
    cout << endl;
    int licznik = 0;
    tmp = root;
    while(tmp!=NULL){
        if(tmp->check_is_even() == true) licznik++;
        tmp = tmp->next;
    }
    cout << endl;
    cout<<"Zliczanie: "<<licznik<<endl;
    cout << endl;
    cout << "\n\n\nUsuwamy obiekty i zwalniamy pamiec:\n";

     kulka * remove_ball;
     tmp = root;
     while (tmp != NULL)
     {
         remove_ball = tmp;
         tmp = tmp -> next;
         delete remove_ball;
     }

     root = NULL;




}

