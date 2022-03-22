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
    string wyroznik = "";
    kulka *left = NULL, *right = NULL; //lewy na lewego potomka, prawy na prawego
    kulka(int numer = 0) //konstruktor
    {
        this->numer = numer; //this->numer zmienna klasy, samo numer nazwa metody (funkcji)
        this->v = rand() % 899 + 100;
        cout<<endl;
        cout << "K:" << numer << "=" << v << "\t";

    }


     void show() //funkcja do wypisania numeru oraz wartości v wszytkich kulek z drzewa
    {
        if(left) left->show();  //wyswietlanie od lewej
        cout <<wyroznik<<" "<< numer << ":" << v << " ";
        if(right) right->show(); //wyswietlanie od prawej
    }

    void add_BST(kulka *nowa){ //funkcja do dodania
        if(nowa->v < v){ //jesli value nowej kulki jest mniejsze od v starej kulki to idziena lewo
            if(left != NULL){ //jesli prawy nie jest pusty
                left->add_BST(nowa); //lewy nie jest pusty czyli idziemy dalej
            }else{ //jak lewy jest pusty
                left = nowa;  //to doczepiamy nowa z lewej strony
            }
        }else{ //jak jest wieksza to idzie na prawo
             if(right != NULL){ //jak jest prawy zajety to
                right->add_BST(nowa); //odpal na prawej i szukaj dalej
            }else{ //innaczej jak jest pusty
                right = nowa; //dopisz na koncu z prawej strony
            }
        }
    }


};
int main(int argc, char** argv) {

    kulka *root = new kulka(0);
    cout<<endl;
    root->wyroznik = "*";
    root->show();
    cout<<endl;
    root->wyroznik = "";
    for(int i=1;i<=10;i++){
        kulka *nowa = new kulka(i);
        root->add_BST(nowa);
        cout<<endl;
        nowa->wyroznik = "*";
        root->show();
        nowa->wyroznik = "";
        cout<<endl;

    }
    cout<<endl;



}

