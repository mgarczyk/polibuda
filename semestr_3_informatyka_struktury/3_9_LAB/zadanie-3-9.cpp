// Zadanie_3_7_BST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class kulka {
    public:
        int v;
        kulka *next = NULL;
        kulka* right = NULL; //tym razem potrzeba wskaźnik na elemnt prawy i...
        kulka* left = NULL; //lewy
        kulka(int v) { //konstruktor
            this->v = v;
            cout <<"V= "<<v<< endl;
        }



        void add_list(kulka* new_ball) { //dodawanie na koniec listy
            if (next) next->add_list(new_ball); //jak ma nexta pełnego to idź dalej
            else next = new_ball; //jak nie ma to wrzuć tam nową kulkę
        }

        void show_list() { //wyswietl liste od poczatku
            cout << v << " ";
            if (next) {
                next->show_list();
            }

        }

        void add_BST(kulka* new_ball) {
            if (new_ball->v/10 != v/10) {                      //wstawiamy po liczbie dziesiątek, taka sama w nowej jak w aktualnej kulce idziemy w prawo, jak inna w lewo
                if (left)
                    left->add_BST(new_ball);                //uruchom metodę na kulce którą wskazuje left
                else                                       //jeżeli jednak wskaźnik na kolejną kulkę na lewo jest pusty (NULL) to znaczy, że...
                    left = new_ball;                      //miejsce zostało znalezione i należy tam wstawić nową kulkę (new_ball)
            }
            else{                                        //jeżeli v w nowej jest większe lub równe niż w tej aktualnie rozpatrywanej
                if (right)                              //to sprawdź czy prawy jest zajęty...
                    right->add_BST(new_ball);          //jak tak uruchom metodę na kulce wskazywanej przez wskaźnik right
                else                                  //jeżeli jednak right okaże się pusty
                    right = new_ball;                //wstaw jako kolejną prawą kulkę tą nową
            }
        }

        void show_BST() {                 //wyświetlanie od największych do najmniejszych (malejąco) -> jak miałoby być odwrotnie to te dwa if'y wystarczy zamienić miejscami

            cout << v << " "; //wyswietl
            if (right){ //jak jest prawy
                right->show_BST(); //idz do niego

            }
            else cout<<endl;
             if (left){ //jak jest lewy
                left->show_BST(); //idz dalej w lewo

            }
        }

         int count_tree_BST() { //zliczanie
            int licznik_kulek = 1; //kazda kulka liczy sie jako jedna
            if (left)  licznik_kulek+=left->count_tree_BST(); //doda sie jeden za kazdym razem jak bedzie kulka z lewej
            if (right) licznik_kulek+=right->count_tree_BST(); //doda sie jeden za kazdym razem jak jest kulka z prawej
            return licznik_kulek; //zwracamy licznik odpowiednia powiekszany


        }


};


int main(int argc , char** argv)
{
    srand(time(NULL));
    cout << "Tworzenie i dolaczanie" << endl;
    cout << endl;
    int ile  = (argc>1) ? atoi(argv[1]):100;  //ilosc kulek -> przy wyswietlaniu programu po kompilacji piszemy ./a.out /15, musza byc w main te argumenty
    //cout<<ile<<endl;
    //TWORZENIE LISTY
    cout<<"TWORZENIE LISTY"<<endl;
    int v  =  rand() % 101;
    kulka *root_list = new kulka (v);
    kulka *root_list_2 = new kulka (v);
    for(int i=1;i<ile;i++){
        v = rand() % 101;
        kulka *new_ball = new kulka(v);
        root_list->add_list(new_ball); //jak chcesz to co nizej to tą linię zakomentuj
        //////////////////////////////////////TEN FRAGMENT DZIELI LISTĘ NA PARZYSTE I NIEPARZYSTE, ALBO INNE NP RESZTA 0,1,2 to modulo 3,  TUTAJ USTALAMY WARUNEK NIC NIE ZMIENIAMY W METODZIE add_list()/////////////////////////////////////////////////
        //if(v%2 == 0) root_list->add_list(new_ball);
        //else root_list_2->add_list(new_ball);/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    }
    cout<<endl;
    cout<<endl;
    cout<<"WYSWIETLANIE LISTY"<<endl;
    root_list->show_list();
    cout<<endl;
    kulka *root_BST = root_list; //root_BST to root listy (początek listy, jest początkiem drzewa)
    kulka* tmp = root_list->next; //następny na liście jest pierwszym tymczasowym do wstawienia do drzewa
    while(tmp){ //dopóki istnieje tymczasowy
        root_BST->add_BST(tmp);  //dodawaj tymzasowy do drzewa
        root_list = tmp->next;  //wtedy root musi wskazywać na kolejny po tymczasowy (w ten sposób 'usuniemy/zapominimy' o tym obiekcie patrząc na listę i będzie on na drzewie
        tmp=tmp->next; //przesuwamy wskaznik tymczasowy o jeden element dalej
    }

    //zlicznie przez show z wyswietlaniem
    cout<<"WYSWIETLANIE DRZEWA: "<<endl;
    cout<<endl;
    root_BST->show_BST(); //wyświetlanie gotowego drzewa za pomocą funkcji show_BST(), funkcja jest uruchamiana na korzeniu (root)




}
