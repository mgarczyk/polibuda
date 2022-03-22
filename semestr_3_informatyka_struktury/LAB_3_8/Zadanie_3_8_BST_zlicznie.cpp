// Zadanie_3_7_BST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class kulka {
    public:
        int v;
        kulka* right = NULL; //tym razem potrzeba wskaźnik na elemnt prawy i...
        kulka* left = NULL; //lewy
        kulka(int v) { //konstruktor
            this->v = v;
            cout <<"V= "<<v<< endl;
        }



        void add_BST(kulka* new_ball) {
            if (new_ball->v < v) {                            //sprawdzi czy v nowej kulki jest mniejsze od tego w aktualnie rozpatrywanej (na początku root, potem kolejna kulk zależy jak się przesuniemy) ZAŁOŻENIE!! lewy -> mniejszy, prawy -> większy
                if (left)                                    //jak v w nowej jest mniejsze od v w tej której jesteśmy i wskaźnik na lewo (left) od tej kullki jest zajęty to...
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

        void show_BST(int &licznik) {                 //wyświetlanie od największych do najmniejszych (malejąco) -> jak miałoby być odwrotnie to te dwa if'y wystarczy zamienić miejscami
            if (left){ //jak jest lewy
                left->show_BST(licznik); //idz dalej w lewo
                 licznik++; //dodaj do licznika bo jest nowa kulka
            }
            cout << " V: " << v << "   "; //wyswietl
            if (right){ //jak jest prawy
                right->show_BST(licznik); //idz do niego
                licznik++; //dodaj do licznika bo jest kolejna
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
    int ile  = (argc>1) ? atoi(argv[1]):10;  //ilosc kulek -> przy wyswietlaniu programu po kompilacji piszemy ./a.out /15, musza byc w main te argumenty
    //cout<<ile<<endl;
    kulka* root = new kulka(0), *new_ball;  //wskaźnik na korzeń + wskaźnik na nową kulkę
    for (int i = 1; i<ile; i++) {          //tworzenie kolejnych dodawanych to drzewa obiektów
       int v =  rand() % 10;
       new_ball = new kulka(v);           //wskaźnik na nową dodawaną do drzewa kulkę
       root->add_BST(new_ball);          //dodawanie nowej kulki do drzewa przy pomocy funkcji add_BST(), UWAGA! funkcję zawsze uruchamiamy na korzeniu (root)
    }
    cout << endl;
    cout << endl;
    cout << endl;
    //zlicznie przez show z wyswietlaniem
    int licznik = 1;
    cout<<"Wyswietlanie drzewa: "<<endl;
    cout<<endl;
    root->show_BST(licznik); //wyświetlanie gotowego drzewa za pomocą funkcji show_BST(), funkcja jest uruchamiana na korzeniu (root)
    cout<<endl;
    cout<<endl;
    cout<<"Ilosc kulek przez show: "<<licznik<<endl;
    //zliczanie rekurencyjne
    int licznik_kulek = 1;
    cout<<"Ilosc kulek metoda rekurencyjna: "<<root->count_tree_BST()<<endl;
    cout << endl;
    cout << endl;




}
