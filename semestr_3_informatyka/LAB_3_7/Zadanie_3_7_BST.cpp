// Zadanie_3_7_BST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class kulka {
public:
	int number;
	int v;
	kulka* right = NULL; //tym razem potrzeba wskaźnik na elemnt prawy i...
	kulka* left = NULL; //lewy
	kulka(int number) { //konstruktor
		this->number = number;
		this->v = 1 + rand() % 1000;
		cout << "Kulka numer: " << number << ", V= " << v << endl;
	}
	void show_BST() { //wyświetlanie od największych do najmniejszych (malejąco) -> jak miałoby być odwrotnie to te dwa if'y wystarczy zamienić miejscami
		if (right)  right->show_BST(); //prawe wyświetla jak jest na dole i nie ma możliwości znaleźć le
		cout << "Numer: " << number << " V: " << v << "   "; //wyśiwetlenie v
		if (left)  left->show_BST(); //przechodzi do ostatniego aktualnego lewego i wyświetla



	}
	void add_BST(kulka* new_ball) {
		if (new_ball->v < v) {                            //sprawdzi czy v nowej kulki jest mniejsze od tego w aktualnie rozpatrywanej (na początku root, potem kolejna kulk zależy jak się przesuniemy) ZAŁOŻENIE!! lewy -> mniejszy, prawy -> większy
			if (left)                                    //jak v w nowej jest mniejsze od v w tej której jesteśmy i wskaźnik na lewo (left) od tej kullki jest zajęty to...
				left->add_BST(new_ball);                //uruchom metodę na kulce którą wskazuje left
			else                                       //jeżeli jednak wskaźnik na kolejną kulkę na lewo jest pusty (NULL) to znaczy, że...
				left = new_ball;                      //miejsce zostało znalezione i należy tam wstawić nową kulkę (new_ball)
		}
		else {                                        //jeżeli v w nowej jest większe lub równe niż w tej aktualnie rozpatrywanej
			if (right)                              //to sprawdź czy prawy jest zajęty...
				right->add_BST(new_ball);          //jak tak uruchom metodę na kulce wskazywanej przez wskaźnik right
			else                                  //jeżeli jednak right okaże się pusty
				right = new_ball;                //wstaw jako kolejną prawą kulkę tą nową
		}
	}


};


int main()
{
	srand(time(NULL));
	cout << "Tworzenie i dolaczanie" << endl;
	cout << endl;
	kulka* root = new kulka(0), * new_ball;  //wskaźnik na korzeń + wskaźnik na nową kulkę
	for (int i = 1; i < 15; i++) {        //tworzenie kolejnych dodawanych to drzewa obiektów
		new_ball = new kulka(i);           //wskaźnik na nową dodawaną do drzewa kulkę
		root->add_BST(new_ball);          //dodawanie nowej kulki do drzewa przy pomocy funkcji add_BST(), UWAGA! funkcję zawsze uruchamiamy na korzeniu (root)
	}
	cout << endl;
	cout << "Wynikowe drzewo" << endl;
	cout << endl;
	root->show_BST();                  //wyświetlanie gotowego drzewa za pomocą funkcji show_BST(), funkcja jest uruchamiana na korzeniu (root)
	cout << endl;
	cout << endl;

}
