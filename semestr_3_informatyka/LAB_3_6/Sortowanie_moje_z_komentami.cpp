#include <iostream> // cout
#include <cstdlib>  // rand
#include <cstdio>   // fflush // printf
#include <cmath>    // floor
#include <ctime>
#include <cstdlib>



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
		cout << numer << ":" << v << " " << endl;

	}
	void add_back(kulka* actual_ball) {
		if (next) next->add_back(actual_ball); //przechodzimy po calej liscie do konca
		else next = actual_ball; //na koniec do ostatniego nexta dopisujemy aktualna kulke
	}
	void print_start_end() //funkcja do wypisania numeru oraz wartości v konkretnej, jednej kulki
	{
		//przechodzi przez wszytkie kulki i wypisuje od konca
		cout << numer << ":" << v << " " << endl; //wypisz
		if (next) next->print_start_end(); //jak masz next to powtorz na kolejnej
		else cout << endl;

	}
	void print_end_start() //funkcja do wypisania numeru oraz wartości v konkretnej, jednej kulki
	{
		//przechodzi przez wszytkie kulki i wypisuje od konca
		if (next) next->print_end_start();
		cout << numer << ":" << v << " " << endl;


	}
	void sort_list(kulka* actual_ball, kulka* tmp) {		    //funkcja sortująca
		while (true) {                                         //petla nieskonczona - do przechodzenia po liście
			if (tmp->next == NULL) {                          //ten warunek sprawdza czy dotarliśmy do końca listy, jeżeli tmp->next == NULL, to znaczy że nie ma już kolejnych elemntów
				tmp->next = actual_ball;                     //jeśli nie ma kolejnych elemntów, to śmiało umieszczamy naszą aktualną kulkę jako ostatnią na tej liście
				break;                                      //po czym przerywamy naszą nieskończoną pętlę, i idziemy do kolejnej iteracji
			}
			else {                                         //w innym przypadku, czyli kiedy nie jesteśmy na końcu listy
				if ( tmp->next->v > actual_ball->v) {     //sprawdzamy czy wartość v w aktualnej kulce, jest większe od tej w starej kulce wskazywanej przez tmp->next->v
					tmp = tmp -> next;                   //za każdym razem mamy jedną kulkę do wstawienia, i właśnie to zobiliśmy zatem kończymy pętlę
				}
				else {                                  //jeśli nie jest większa to
					actual_ball->next = tmp->next;     //jeśli tak to stara kulka, z mniejszym v idzie w dół listy, czyli będzie po aktualnej co realizuje ta linia kodu
					tmp->next = actual_ball;          //a na miejsce starej wchodzi ta aktualna z większym v (wyżej na liście), co robi ta linia kodu
					break;                           //po prostu przechodzimy dalej, a sprawę załatwi główny if, albo kolejne wykonanie ifa w którym teraz jesteśmy
				}
			}
		}
	}

	bool check_is_even() {
		if (v % 2 == 0) return true;
		return false; //Jak bylo TRUE to musi byc FALSE

	}

};
int main(int argc, char** argv) {


	/*
	//NA POCZATEK ZAJEC
	cout<<"Rekurencyjne tworzenie listy z tworzniem 0 elemntu z palca: ";
	kulka *root = new kulka(0);
	cout<<endl;
	kulka *actual_ball = NULL;
	for(int i=1;i<=10;i++){
		actual_ball = new kulka(i); //tworzenie nowej kulki
		root->add_back(actual_ball); //
	}
	root->print_start_end();


	cout<<"Usun: "<<endl;
	cout<<endl;
	kulka *remove_ball = NULL;
	kulka *tmp_delete = root;
	while (tmp_delete != NULL)
	 {
		 remove_ball = tmp_delete;
		 tmp_delete = tmp_delete -> next;
		 delete remove_ball;
	 }
	 */

	 //SORTOWANIE W FUNKCJI
	 /*
	 cout<<"Tworzenie listy z sortowaniem: "<<endl;
	 kulka *root = new kulka(0);                                        //tworzymy wskaźnik na pierwszy obiekt
	 root->v = 0;                                                      //ustawiamy jego wartość v na 0, by ułatrwić sortowanie
	 kulka *tmp = NULL;                                               //wskaznik tymczasowy, który pozwoli na przejśce po liście
	 for(int i=1;i<=15;i++){                                         //dla kolejnych n obiektów, teraz 14
		cout<<"Iteracja numer: "<<i<<endl;
		kulka *actual_ball = new kulka(i);                         //tworzymy nowy obiekt - kulkę, którą chcemy dodać w odpowiednie miejsce listy sortując po wartości v, wskazuje ją wskaźnik actual_ball
		cout<<endl;
		tmp=root;                                                //wskaźnik tymczasowy z każdą iteracja fora ustawiamy by wskazywał pierwszy obiekt na liście
		tmp->sort_list(actual_ball, tmp);                       //funkcja sortująca opisana wyżej, za argumenty przyjmuje aktualna_kulkę oraz tmp
		cout<<"Wyswietlanie listy po dodaniu aktualnej kulki do listy: "<<endl;
		root->print_start_end();
		}
	*/

	//SORTOWANIE W MAIN
	cout << "Tworzenie listy z sortowaniem: " << endl;
	kulka* root = new kulka(0);                                        //tworzymy wskaźnik na pierwszy obiekt
	root->v = 0;                                                      //ustawiamy jego wartość v na 0, by ułatrwić sortowanie
	kulka* tmp = NULL;                                               //wskaznik tymczasowy, który pozwoli na przejśce po liście
	for (int i = 1; i <= 15; i++) {                                 //dla kolejnych n obiektów, teraz 14
		cout << "Iteracja numer: " << i << endl;
		kulka* actual_ball = new kulka(i);                         //tworzymy nowy obiekt - kulkę, którą chcemy dodać w odpowiednie miejsce listy sortując po wartości v, wskazuje ją wskaźnik actual_ball
		cout << endl;
		tmp = root;                                              //wskaźnik tymczasowy z każdą iteracja fora ustawiamy by wskazywał pierwszy obiekt na liście
		while (true) {                                          //petla nieskonczona - do przechodzenia po liście
			if (tmp->next == NULL) {                           //ten warunek sprawdza czy dotarliśmy do końca listy, jeżeli tmp->next == NULL, to znaczy że nie ma już kolejnych elemntów
				tmp->next = actual_ball;                      //jeśli nie ma kolejnych elemntów, to śmiało umieszczamy naszą aktualną kulkę jako ostatnią na tej liście
				break;                                       //po czym przerywamy naszą nieskończoną pętlę, i idziemy do kolejnej iteracji
			}
			else {                                         //w innym przypadku, czyli kiedy nie jesteśmy na końcu listy
				if (actual_ball->v > tmp->next->v) {      //sprawdzamy czy wartość v w aktualnej kulce, jest większe od tej w starej kulce wskazywanej przez tmp->next->v
					actual_ball->next = tmp->next;       //jeśli tak to stara kulka, z mniejszym v idzie w dół listy, czyli będzie po aktualnej co realizuje ta linia kodu
					tmp->next = actual_ball;            //a na miejsce starej wchodzi ta aktualna z większym v (wyżej na liście), co robi ta linia kodu
					break;                             //za każdym razem mamy jedną kulkę do wstawienia, i właśnie to zobiliśmy zatem kończymy pętlę
				}
				else {                               //jeśli nie jest większa to
					tmp = tmp->next;                //po prostu przechodzimy dalej, a sprawę załatwi główny if, albo kolejne wykonanie ifa w którym teraz jesteśmy
				}
			}
		}
		cout << "Wyswietlanie listy po dodaniu aktualnej kulki do listy: " << endl;
		root->print_start_end();
	}
	cout<<"Ostateczne: "<<endl;
	root->print_start_end();













}

