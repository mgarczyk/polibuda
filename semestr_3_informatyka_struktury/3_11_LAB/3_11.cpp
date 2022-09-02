#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

class kulka{

    public:
        int v;
        kulka  *next = NULL;
        kulka  *left = NULL;
        kulka  *right = NULL;
        kulka(int v){
            this->v = v;
            cout<<"V: "<<v<<endl;
        }
        void add_list(kulka *new_ball){
            if(next) next->add_list(new_ball);
            else next = new_ball;
        }
        void show_list(){


            cout<<"V: "<<v<<" ";
            if(next) next->show_list();

        }
        void add_BST(kulka *new_ball){
            if(new_ball->v < this->v){
                if(left) left->add_BST(new_ball);
                else left = new_ball;
            }else{
                if(right) right->add_BST(new_ball);
                else right = new_ball;
            }

        }
        void show_BST(){
            if(left) left->show_BST();
            cout<<"V: "<<v<<" ";
            if(right) right->show_BST();
        }
        void suma_BST(float &suma){
            if(left) left->suma_BST(suma);
            suma+=this->v;
            if(right) right->suma_BST(suma);
        }
        void najblizej_sredniej(kulka *&szukane, float &minimum, float srednia){
            if(left) left->najblizej_sredniej(szukane, minimum, srednia);
            if(abs(srednia - v) < minimum){
                minimum = abs(srednia - v);
                szukane = this;
            }
            if(right) right->najblizej_sredniej(szukane, minimum, srednia);
        }

        kulka *find_to_add(){ //metoda do szukania elemntu do dodadnia
            if(left->left == NULL){ //jeœli mamy tak¹ sytu³acjê, to znaczy ¿e kulka pod nami jest t¹ minimaln¹ (minimum na maksa po lewej zawsze)
                kulka *to_add = left; //czyli t¹ do dodania jest lewy potomek ttej w której jesteœmy
                left = to_add->right; //dalej jako nowego lewego potomka ustawiamy prawego potomka, starego lewego potomka (trochê zagmatwane)
                to_add->right = NULL; //wiemy, ¿e ta do dodania nie ma lewego potomka, jej prawego potomka zabezpiecza linia kodu wy¿ej, dlatego w tym miejscu ustawiamy wskaŸnik na prawego na NULL
                return to_add; //zwracamy
            }else{ //jeœli istnieje lewy potomek lewego potomka
                left->find_to_add(); //to szukamy dalej, czyli uruchamiamy metodê na lewym
            }
        }



};




int main()
{
    srand(time(NULL));
    cout<<"DRZEWO"<<endl;
    int v = rand()%11;
    kulka *root_BST = new kulka(v);
    for(int i=1;i<10;i++){
        v = rand()%11;
        kulka *new_ball = new kulka(v);
        root_BST->add_BST(new_ball);
    }
    cout<<"Wyswietl drzewo"<<endl;
    root_BST->show_BST();
    cout<<endl;

    //Z LISTY NA DRZEWO
    cout<<"Tworzenie roota listy "<<endl;
    kulka *root_list = NULL;
    kulka *to_add = NULL; //do dodania do listy
    while(root_BST!=NULL){ //dopóki root nie jest null
        if(root_BST->left == NULL){ //jak nie ma left to roota dodajemy do listy i rootem staje siê jego prawy potomek
            to_add = root_BST;
            root_BST = root_BST->right;
        }else{ //jak jest lewy
            to_add = root_BST->find_to_add(); //to elemntu do ddania szukamy t¹ funkcj¹ w klasie
        }
        if (root_list == NULL) root_list = to_add; //jak root jest pusty, to rootem staje siê aktualny element do dodania (to_add)
        else root_list->add_list(to_add); //w innym przypadku po prostu dodajemy do listy
    }
    cout<<"Wyswietl liste"<<endl;
    root_list->show_list();


    return 0;
}
