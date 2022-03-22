#include <iostream> // cout
#include <cstdlib>  // rand
#include <cstdio>   // fflush // printf
#include <cmath>    // floor
#include <ctime>



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

void print_list(kulka *first){ //wyswietlanie parzystch lub nieparzystych zależnie od argumentu
    kulka *print_even = first; //wskaznik do wyswetlania na poczatku wskazuje pierwszą kulkę o parzystym v
    while(print_even!=NULL){    //warunek na idealną pętle która ładnie wyświtli, dopiero jak next ostatniej jest == NULL, to print_even też przyjmie NULL i pętla się nie zrobi dalej
        print_even->print_one_element();
        print_even = print_even->next;
    }
}

void remove_list(kulka *first){ //usuwanie parzystch lub nieparzystych zależnie od argumentu
    kulka *remove_ball = NULL; //wskaznik na usuwany element
    kulka *tmp_delete = first; //wskazujemy pierwszy usuwany
    while (tmp_delete != NULL){ //przelatujemy po wszytkich
        remove_ball = tmp_delete; //aktualnie usuwaną wskazuej tmp_delete
        tmp_delete = tmp_delete -> next; //następną wskazywana jest przez nexta
        delete remove_ball; //usuwamy aktualną
     }
     first = NULL; //usuwamy pierwsza
}

int length_list_f(kulka *first){ //zliczanie ellemntow na liscie
    int counter = 0;
    kulka *tmp_counter = first;
    while(tmp_counter!=NULL){
        counter++;
        tmp_counter=tmp_counter->next;
    }
    return counter;

}

void sort_list(kulka *first, int length_list){
        kulka *actual_ball = first; //aktalna kulka
        kulka *next_ball = first; //kolejna kulka
        for(int i=0;i<length_list;i++){ //pętla zewnętrzna
            for(int j=0;j<length_list-1;j++){ //pętla wewnętrzna wyknuje się raz mniej
                if(next_ball->v < actual_ball->v){ //jesli następne v jest większe od
                    int tmp_v = actual_ball->v; //w pomocniczym mamy aktalną kulkę
                    int tmp_numer = actual_ball->numer;
                    actual_ball->v = next_ball->v; //zamiana kulki z mniejszym v na tą o więkskszym v
                    actual_ball->numer = next_ball->numer;
                    next_ball->v = tmp_v;
                    next_ball->numer = tmp_numer;
                }
                next_ball = next_ball->next; //przechodzenie po j, kolejnych kulkach

            }
            //PRZESUWAMY JAK W BĄBELKOWYM TYLKO NA WSKAŹNIKACH
            next_ball = first; //jako kolejną ustawiamy ponownie pierwszą kulkę (zmieniła wartość ale nie pozycję)
            actual_ball = first->next; //jako aktualną ustwiamy next z pierwszej, żeby były jedna za drugą (druga kulka w rzędzie)
            for(int k=0;k<i;k++){ //i przesuwamy jescze k razy tą aktualną
                actual_ball = actual_ball->next; //pomijamy juz posortowany obszar (chyba) i ustawiamy kulkę do dalszego porównywania
        }

    }
}





int main(int argc, char** argv) {
    srand(time(NULL));

    //tworzenie list
    cout << "Tworzenie kulek: " << endl;
    cout<<endl;
    cout<<endl;
    kulka *first_even = NULL; //poczatek listy z parzysta v
    kulka *first_odd = NULL; //poczatek listy z nieparzysta v
    kulka *last_even = NULL; //tymczasowo ostatnia parzysta v na liście
    kulka *last_odd = NULL;  //tymczasowo ostatnia nieparzysta v na liście
    kulka *actual_ball = NULL; //pomocniczy ktory chwilowo wskazuje na kazdą kolejną kulkę
    for (int i = 1; i <= 15; i++) { //tworzymy 15 kilejnych kulek
        actual_ball = new kulka(i); //nowa kulka wskazywana przez wskaźnik actual_ball
        cout<<endl;
        if(actual_ball->check_is_even() == true){ //dla kulek z parzystym v
            if(first_even == NULL){ //dla pierwszej kulki z parzystym v, nasze poprzednie tmp = z, rozpoczęcie listy
                first_even = actual_ball; //first_even bedzie wskazywal pierwszą kulkę z parzystym v
                last_even = first_even;   //w tej sytułacji pierwsza kulka jest też ostatnią
            }
            last_even->next = actual_ball; //ustawaimay by wskaźnik next poprzedniej ostatniej parzystej kulki, czyli last_even, wskazywał na aktualnie znalezioną nową ostatnią parzystą kulkę last_even->next = actual_ball
            last_even = last_even->next; //ustawienie by wskaźnik last_even, narazie wskazujący poprzednią parzystą kulkę, wskazywał aktalną ostatnią parzystą kulkę
        }else{ //dalej co do komentarzy ZASADA DUALNOŚCI xDD, nie no serio to jest to samo tylko dla nieparzystych, i tak można by dokładać inne reszty z dzielenia
             if(first_odd == NULL){
                first_odd = actual_ball;
                last_odd = first_odd;
            }
            last_odd->next = actual_ball;
            last_odd = last_odd->next;

        }
    }
    cout<<endl;
    cout<<endl;


    //wyswetlanie przed sortowaniem
    cout<<"Wyswietlanie parzystych: "<<endl;
    cout<<endl;
    print_list(first_even); //wyswietlanie: argument first_even dla parzystych
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Wyswietlanie nieparzystch: "<<endl;
    cout<<endl;
    print_list(first_odd); //wyswietlanie: first_odd dla nieparzystch
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;


    //dlugosc listy
    cout<<"Dlugosc listy: "<<endl;
    cout<<endl;
    int length_list_even = length_list_f(first_even); //dlugosc listy parzystej
    int length_list_odd = length_list_f(first_odd);   //dlugosc listy nieparzystej
    cout<<"Dlugosc listy parzystej: "<<length_list_even<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Dlugosc listy nieparzystej: "<<length_list_odd<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;


    //sortowanie
    cout<<"Sortowanie: "<<endl;
    sort_list(first_even, length_list_even); //zaleznie od parametru parzyste lub nieparzyste
    sort_list(first_odd, length_list_odd);



    cout<<"Wyswietlanie parzystych po sortowaniu: "<<endl;
    cout<<endl;
    print_list(first_even); //wyswietlanie: argument first_even dla parzystych
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Wyswietlanie nieparzystch po sortowaniu: "<<endl;
    cout<<endl;
    print_list(first_odd); //wyswietlanie: first_odd dla nieparzystch
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;


    //usuwanko
    cout<<"Usun parzyste: "<<endl;
    cout<<endl;

    remove_list(first_even); //usuwanie: argument first_even dla parzystych
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Usun nieparzyste: "<<endl;
    cout<<endl;
    remove_list(first_odd); //usuwanie: argument first_odd dla nieparzystych
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;








}

