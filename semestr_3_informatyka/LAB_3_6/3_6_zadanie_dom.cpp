// 3_6_zadanie_dom.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


	class kulka
	{
	public:
		int numer; //numer kulki po nim sortujemy
		int iterator;
		kulka *next = NULL; //wskaznik next wskazuje kolejna kulke
		kulka(int numer = 0) //konstruktor
		{
			this->numer = numer; //this->numer zmienna klasy, samo numer nazwa metody (funkcji)
			cout <<"Stworzono kulke: " <<  "K: " << numer <<  endl;
		}
		void print_one_element() //funkcja do wypisania numeru oraz  konkretnej, jednej kulki
		{
			cout << "Numer: " << numer << endl;

		}
		void print_start_end(int i) //funkcja do wypisania numeru oraz  wszystkich kulek na liście od początu do końca
		{
			//przechodzi przez wszytkie kulki i wypisuje od konca
			if(iterator == i) cout << "Numer: * " << numer << endl; //wyroznik -> iterator nie powtórzy się w przeciwieśtwie do losowego_numeru, da to pewność że wyświetli jedna *
			else cout << "Numer: " << numer << endl;
			if (next) next->print_start_end(i); //jak masz next to powtorz na kolejnej
			else cout << endl;

		}
		
		
		
	


	};

int main(){
		srand(time(NULL)); 
		kulka *root = new kulka(0); //pierwsza kulka na liście
		root->iterator = 0;
		root->print_start_end(0);
		cout << endl;
		kulka* tmp = NULL; //wskaźnik tymczasowy do przechodzenia po liście
		for (int i = 1; i < 15; i++) {
			int losowy_numer = 1 + rand() % (1000 - 1 + 1); //generowanie numeru [q,p] -> [1,1000]
			kulka *actual_ball = new kulka(losowy_numer); //tworzymy nową kulkę o losowym numerze
			actual_ball->iterator = i;
			tmp = root;                         //tymczasowy zawsze na poczatku wskazuje początek listy
			while (true) {					   //pętla nieskończona
				if (tmp->next == NULL) {      //jeżeli dotarliśmy na koniec
					tmp->next = actual_ball; //dodajemy aktualną kulkę na koniec
					break;					//dojechaliśmy do końca i umieściliśmy kulkę w odpowiednim miejscu -> koniec pętli wewnętrznej
				}
				else { //innaczej
					if (actual_ball->numer < tmp->next->numer) { //jeśli numer aktualnej kulki jest większy/mniejszy to 
						actual_ball->next = tmp->next;			//przesuwamy starą kulkę w miejsce aktualnej (jaby "niżej" na liście)
					    tmp->next = actual_ball;			   //a w jej miejsce wstawiamy tą aktualną ("wyżej" na liście)
						break;								  //z każdą iteracją pętli for, mamy tylko jedną aktalną kulkę, którą właśnie umieściliśmy w dobrym miejscu -> kończymy pętlę wewnętrzną
					}
					else { //jak nie to zostawiamy w spokoju bo jest już posrotwane, czyli
						tmp = tmp->next; //przechodzimy dalej bez zmiany
					}
				}

			}
			root->print_start_end(i);
		}
		

 }

