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


    /*
    //POCZATEK ZAJEC
    cout<<"Rekurencyjne tworzenie listy z tworzniem 0 elemntu z palca: ";
    kulka *root = new kulka(0);
    cout<<endl;
    kulka *actual_ball = NULL;
    for(int i=1;i<=10;i++){
        actual_ball = new kulka(i); //tworzenie nowej kulki
        root->add_back(actual_ball); //
    }
    root->print_start_end();


    cout<<"Usun: "<<endl;
    cout<<endl;
    kulka *remove_ball = NULL;
    kulka *tmp_delete = root;
    while (tmp_delete != NULL)
     {
         remove_ball = tmp_delete;
         tmp_delete = tmp_delete -> next;
         delete remove_ball;
     }
     */
     //SORTOWANIE
     cout<<"Sortowanie: "<<endl;
     kulka *root = new kulka(0);
     root->v = 0;
     kulka *tmp = NULL; //wskaznik tymczasowy
     for(int i=1;i<=15;i++){
         kulka *nowa = new kulka(i); //nowa rozpatrywana kulka, kora chcemy dodac
         tmp = root; //tymczasowa wskazuje na poczatek listy - jeden raz dla kazdej kulki
             while(true){ //petla nieskonczona
                if(tmp->next == NULL){  //sprawdzenie czy nie ma nexta (jest pusty) - dla drugiego elemntu tylko
                    tmp->next = nowa; //wstawienie aktalnej jako druga kulke be nie ma nic innego
                    break;
                }else{ //jak nie ma nexta
                    if(tmp->next->v < nowa->v){ //sprawdzamy warunek mniejsze/wieksze v
                        tmp=tmp->next; //jak warunek jest prawdzimy przechodzimy dalej nie zmieniamy nic
                    }
                    else{//jak chcemy wsadzic pomiedzy
                        nowa->next = tmp->next; //na miejsce ostatniej wchodzi nowa,
                        tmp->next = nowa;       //a na miejsce nowej ostatnia
                        break;
                    }
                }
             }
        }
        root->print_start_end();











}

