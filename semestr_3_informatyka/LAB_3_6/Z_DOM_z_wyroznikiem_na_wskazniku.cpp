// 3_6_zadanie_dom.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


	class kulka
	{
	public:
		int numer; 
		int v;  //numer v  kulki po nim  sortujemy
		kulka *next = NULL; //wskaznik next wskazuje kolejna kulke
		string star = ""; //wyroznik standardowo nie istnieje
		kulka(int numer = 0) //konstruktor
		{
			this->numer = numer; //this->numer zmienna klasy, samo numer nazwa metody (funkcji)
			cout <<"Stworzono kulke: " <<  "K: " << numer <<  endl;
		}
		void print_start_end() //funkcja do wypisania numeru szystkich kulek na liście od początu do końca + wyróżnik nowej
		{

		
			cout << "Numer: " << star << numer <<", value: "<< v << endl; //wyswietlenie kulki i wyroznika
			if (next) next->print_start_end(); //jak masz next to powtorz na kolejnej
			else cout << endl;

		}
		
		
		
	


	};

int main(){
		srand(time(NULL)); 
		kulka *root = new kulka(0); //pierwsza kulka na liście
		root->numer = 0;
		root->star="*";
		root->print_start_end();
		root->star="";
		cout << endl;
		kulka* tmp = NULL; //wskaźnik tymczasowy do przechodzenia po liście
		for (int i = 1; i < 15; i++) {
			int losowy_numer = 1 + rand() % (1000 - 1 + 1); //generowanie numeru [q,p] -> [1,1000]
			kulka *actual_ball = new kulka(i); //tworzymy nową kulkę o losowym numerze
			actual_ball->star = "*"; //wyroznik ma jakąś wartość tylko dla aktalnej kulki
			actual_ball->v = losowy_numer;
			tmp = root;                         //tymczasowy zawsze na poczatku wskazuje początek listy
			while (true) {					   //pętla nieskończona
				if (tmp->next == NULL) {      //jeżeli dotarliśmy na koniec
					tmp->next = actual_ball; //dodajemy aktualną kulkę na koniec
					break;					//dojechaliśmy do końca i umieściliśmy kulkę w odpowiednim miejscu -> koniec pętli wewnętrznej
				}
				else { //innaczej
					if (actual_ball->v <= tmp->next->v) { //jeśli numer aktualnej kulki jest większy/mniejszy to 
						actual_ball->next = tmp->next;			//przesuwamy starą kulkę w miejsce aktualnej (jaby "niżej" na liście)
					    tmp->next = actual_ball;			   //a w jej miejsce wstawiamy tą aktualną ("wyżej" na liście)
						break;								  //z każdą iteracją pętli for, mamy tylko jedną aktalną kulkę, którą właśnie umieściliśmy w dobrym miejscu -> kończymy pętlę wewnętrzną
					}
					else { //jak nie to zostawiamy w spokoju bo jest już posrotwane, czyli
						tmp = tmp->next; //przechodzimy dalej bez zmiany
					}
				}

			}
			root->print_start_end(); //wyświetlanie
			actual_ball->star = ""; //usunięcie wyróżnika, żeby nie było kilku kulek z gwiazdkami
		}
		

 }

