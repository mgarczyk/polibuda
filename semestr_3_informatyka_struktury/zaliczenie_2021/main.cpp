#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
int countx = 10;
class kulka{
    public:
        int v;
        kulka *next = NULL;
        kulka *left = NULL;
        kulka *right = NULL;
        kulka (int v){
            cout<<"V: "<<v<<endl;
            this->v = v;
        }


        void add_list(kulka* new_ball) {
            if (this->next) this->next->add_list(new_ball);
            else this->next = new_ball;
        }


        void show_list() {
           cout<<"V: "<<v<<" ";
           if(next) next->show_list();

        }

        void add_BST(kulka* new_ball) {
            if (new_ball->v < this->v) {
                if (left) left->add_BST(new_ball);
                else left = new_ball;
            }
            else {
                if (right) right->add_BST(new_ball);
                else right = new_ball;
            }
        }

        void show_BST() {
            if (left) left->show_BST();
            cout << "V: " << this->v << " ";
            if (right) right->show_BST();
        }
        void count_BST(int &counter){
            if(left) left->count_BST(counter);
            if(this->v%3 == 0) counter++;
            if(right) right->count_BST(counter);
        }

        kulka * find_ball(){
            if(left->left == NULL){
                kulka* find = left;
                left = find->right;
                find->right = NULL;
                return find;

            }else{
                left->find_ball();
            }
        }


};




void show_like_tree(kulka *root_BST, int space){
    if(root_BST == NULL) return;
    space+=countx;
    show_like_tree(root_BST->right, space);
    cout<<endl;
    for(int i=countx;i<space;i++){
        cout<<" ";
    }
    cout<<root_BST->v;
    show_like_tree(root_BST->left, space);
}

void sort_when_creating(kulka * root_list, kulka* new_ball) { //UWAGA FUNKCJ� T� URUCHAMIAMY DLA KA�DEJ NOWEJ KULKI, CZYLI W MAIN MAMY P�TL� FOR TWORZ�C� KOLEJNE KULKI, NIE SORTUJE PIERWSZEGO ELEMENTU ROOTA
    kulka *tmp = root_list;
    while (true) {
        if (tmp->next == NULL) { //uda�o nam si� doj�� do ko�ca bez niespodzianek, umieszczamy tam now� kulk�
            tmp->next = new_ball; //dodanie na ko�cu
            break; //jak dodamy to break i koljena iteracja fora
        }
        else { //gdy nie jeste�my na ko�cu
            if (new_ball->v < tmp->next->v) { //sprawdzamy czy v nowej kulki jest wi�ksze od v nast�pnej po tmp (poprzedniej) np. tmp->v = 8, tmp->next->v = 10, new_ball->v = 9), ZAMIANA
                new_ball->next = tmp->next; //zamiana, next ze starej kulki (poprzedniej), wchodzi za now� kulk� (para kulek new_ball i tmp->next)
                tmp->next = new_ball;      //pod��czenie reszty listy do wy�ej utworzonej pary kulek, tmp, new_ball, new_ball->next
                break; //jak dokonali�my zamiany to zadanie wykonen i idziemy do kolejnej iteracji

            }
            else { //jak nie by�o zamiany
                tmp = tmp->next; //to idziemy dalej w kierunku ko�ca listy
            }
        }
    }
}



int main(){
    //NA 3.0 Stw�rz 30 obiekt�w w o losowych warto�ciach te parzyste wrzu� na list�, sortuj�c j� malej�co w czasie wk�adania, te nieparzyste wrzu� na drzewo. Wy�wietl list� posortowan� malej�co, a drzewo rosn�co.
    srand(time(NULL));
    kulka *root_list = NULL;
    kulka *root_BST = NULL;
    for(int i=0;i<30;i++){
        int v = rand()%90;
        kulka *new_ball = new kulka(v);
        if(v%2 == 0){
            if(root_list == NULL) root_list = new_ball;
            else sort_when_creating(root_list, new_ball); //sortowanie, tylko trzeba pami�ta�, �e to nie sortuje roota


        }else{
            if(root_BST == NULL) root_BST = new_ball;
            else root_BST->add_BST(new_ball);
        }


    }
    cout<<endl;
    cout<<"Posortowana lista: "<<endl;
    root_list->show_list();
    cout<<endl;
    cout<<"Posortowane drzewo: "<<endl;
    //4.0 Zliczanie elemnt�w podzielnych przez 3, znajuduj�cych si� na drzewie
    root_BST->show_BST();
    int counter = 0;
    root_BST->count_BST(counter); //metoda zliczaj�ca (w klasie)
    cout<<endl;
    cout<<endl;
    cout<<"Ilosc elemnt�w podzielnych przez 3 na drzewie: "<<counter<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    //NA 5.0, albo �adne (perfekcyjne) wy�wietlanie drzewa z kreskami, albo innymi bajerami, mojego mi nie chcia� zaliczy�.
    show_like_tree(root_BST, 0); //ta funkcja to realizuje
    cout<<endl;
    cout<<endl;
    cout<<endl;
    //ALBO przepisz elemnty z drzewa na list� w kolejno�ci od najmniejszych do najwi�kszych, to realizuje poni�sza cz�� kodu oraz metoda find_ball()
    cout<<"Nasze drzewo: "<<endl;
    root_BST->show_BST();
    cout<<endl;
    cout<<endl;
    kulka *root_list_2 = NULL;
    kulka* find = NULL;
    while(root_BST != NULL){
        if(root_BST->left == NULL){
            find = root_BST;
            root_BST = root_BST->right;
        }
        else{
            find = root_BST->find_ball(); //metoda w klasie
        }
        if(root_list_2 == NULL) root_list_2 = find;
        else root_list_2->add_list(find);
    }
    cout<<endl;
    cout<<endl;
    cout<<"Utworzona lista, ktora wyswietla sie identycznie jak drzewo: "<<endl;
    root_list_2->show_list();
    cout<<endl;
    cout<<endl;
    //POWODZENIA, ALE ON SPOKO JEST, TYM BARDZIEJ NA ZEROWYM TERMINIE



}


