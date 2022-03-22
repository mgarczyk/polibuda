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




};

 void order(kulka *N){
            if(N) {
                order(N->right);
                cout<<N->v<< " ";
                order(N->left);

                }
            }

int count_k(kulka *L){

    if(L==NULL) return 0;
    return(count_k(L->next)+1);

}





int main()
{
    srand(time(NULL));
    kulka *root_0 = NULL;
    kulka *root_1 = NULL;
    kulka *root_2 = NULL;
    kulka *new_ball = NULL;
    int v;
    int maksimum_v = INT_MIN; //zak³adamy losowanie od 0 do 11
    for(int i=0;i<15;i++){
        v = rand()%11; //zakladamy losowanie od 0 do 11
        if(v > maksimum_v) maksimum_v = v;
        if(v%3 == 0){
            if(root_0 == NULL) root_0 = new kulka(v);
            else{
                new_ball = new kulka (v);
                root_0->add_list(new_ball);
            }
        }else if(v%3 == 1){
            if(root_1 == NULL) root_1 = new kulka(v);
            else{
                new_ball = new kulka (v);
                root_1->add_list(new_ball);
            }
        }else{
            if(root_2 == NULL) root_2 = new kulka(v);
            else{
                new_ball = new kulka (v);
                root_2->add_list(new_ball);
            }

        }
    }
    cout<<"LISTA"<<endl;
    root_0->show_list();
    cout<<endl;
    root_1->show_list();
    cout<<endl;
    root_2->show_list();
    cout<<endl;
    int zlicz = count_k(root_2);
    cout<<zlicz<<endl;
    cout<<"Kulka o najwiêkszej wartoœci to kulka o v = "<<maksimum_v<<endl;
    cout<<endl;
    cout<<"DRZEWO"<<endl;
    cout<<"Podaj root"<<endl;
    cin>>v;
    kulka *root_BST = new kulka(v);
    for(int i=1;i<5;i++){
        cout<<"Podaj potomka"<<endl;
        cin>>v;
        new_ball = new kulka(v);
        root_BST->add_BST(new_ball);
    }
    root_BST->show_BST();
    cout<<"FUNKCJA ORDER"<<endl; //
    order(root_BST);
    cout<<endl;

    float suma = 0;
    cout<<endl;
    root_BST->suma_BST(suma);
    float srednia = suma/15.0;
    cout<<srednia<<endl;
    float minimum = abs(srednia - root_BST->v);
    kulka* szukane = NULL;
    root_BST->najblizej_sredniej(szukane, minimum, srednia);
    cout<<"Kulka o v najblizej sredniej: "<<szukane->v<<endl;
    return 0;
}
