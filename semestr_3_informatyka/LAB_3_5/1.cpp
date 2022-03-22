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
        cout << numer << ":" << v << " "<<endl;

    }
    void add_back(kulka *actual_ball){
        if(next) next->add_back(actual_ball); //przechodzimy po calej liscie do konca
        else next = actual_ball; //na koniec do ostatniego nexta dopisujemy aktualna kulke
    }
    void print_start_end() //funkcja do wypisania numeru oraz wartości v konkretnej, jednej kulki
    {
         //przechodzi przez wszytkie kulki i wypisuje od konca
        cout << numer << ":" << v << " "<<endl; //wypisz
        if(next) next->print_start_end(); //jak masz next to powtorz na kolejnej
        else cout<<endl;

    }
     void print_end_start() //funkcja do wypisania numeru oraz wartości v konkretnej, jednej kulki
    {
         //przechodzi przez wszytkie kulki i wypisuje od konca
        if(next) next->print_end_start();
        cout << numer << ":" << v << " "<<endl;


    }
    bool check_is_even(){
        if(v%2 == 0) return true;
        return false; //Jak bylo TRUE to musi byc FALSE

    }

};
int main(int argc, char** argv) {
    //tworzenie_kulek
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
    //normalne wyswietlanie
    cout<<endl;
    cout << "Wyswietlanie normalnie: " << endl;
    tmp = root; //pierwszy element
    while(tmp!=NULL){ //dopoki tmp nie jest pusty
        tmp->print_one_element(); //wyswietlanie koljenych
        tmp = tmp->next;
    };
    cout<<endl;

    //wypisanie od pocztku do konca
    cout<<"Wypisanie od poczatku do konca rekurencyjnie"<<endl;
    root->print_start_end();
    cout<<"Wypisanie od konca do poczatku rekurencyjnie"<<endl;
    root->print_end_start();



    //usuwanie
    cout << "\n\n\nUsuwamy obiekty i zwalniamy pamiec:\n";

     kulka * remove_ball = NULL;
     tmp = root;
     while (tmp != NULL)
     {
         remove_ball = tmp;
         tmp = tmp -> next;
         delete remove_ball;
         cout<<endl;
     }
     root = NULL;
     cout<<endl;
     cout<<endl;


    //DRUGA LISTA - inny sposob
    cout<<"Rekurencyjne tworzenie listy z tworzniem 0 elemntu z palca: ";
    kulka *root_2 = new kulka(0);
    cout<<endl;
    kulka *actual_ball = NULL;
    for(int i=1;i<=10;i++){
        actual_ball = new kulka(i); //tworzenie nowej kulki
        root_2->add_back(actual_ball); //
    }
    root_2->print_start_end();
    /*
    cout<<"Rekurencyjne tworzenie listy z tworzniem 0 z autoamtu: ";
    kulka *root_2 = NULL;
    cout<<endl;
    kulka *actual_ball = NULL;
    for(int i=0;i<=10;i++){
        actual_ball = new kulka(i); //tworzenie nowej kulki
        if(root_2 == NULL) root_2 = actual_ball;
        else root_2->add_back(actual_ball); //
    }
    root_2->print_start_end();
    */






}

