

#include <cstdio>   // printf
#include <cstdlib>  // rand
#include <time.h>
#include <iostream>

using namespace std;
int COUNT = 20;

class kulka
{
public:
	int v; //zostaje tylko v nie potrzeba nam numeru kulki
	kulka* right = NULL; //tym razem potrzeba wskaźnik na elemnt prawy i...
	kulka* left = NULL; //lewy
	kulka* next = NULL; //next do listy
	kulka(int v) {
		this->v = v;
		cout << "V= " << v << endl;
	}

	void add_list(kulka* new_ball) { //dodawanie na koniec listy
		if (next) next->add_list(new_ball); //jak ma nexta pełnego to idź dalej
		else next = new_ball; //jak nie ma to wrzuć tam nową kulkę
	}

	void show_list() { //wyswietl liste od poczatku
		cout << " V: " << v << "   ";
		if (next) {
			next->show_list();
		}
	}

	void count_list_reference(int& counter, int& sum, int& sum_even, int& counter_odd) { //zliczanie i roznego typu sumowannia, niby to samo co wyzej, ale lepiej miec osobno, metoda przez referencje
		if (next) {
			next->count_list_reference(counter, sum, sum_even, counter_odd);
		}
		//CAŁE ZLICZANIE DZIEJE SIĘ TAM GDZIE WYŚWIETLANIE -> IDZIEMY DO OSTATNIEJ KULKI I COFAMY SIĘ ZLICZAJĄC
		counter++;
		sum += this->v;
		if (this->v % 2 == 0) sum_even += this->v; //UWAGA SUMUJEMY PARZYSTE, A ZLICZAMY NIEPARZYSTE
		else counter_odd++;
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

	void show_BST() { //wyświetlanie od największych do najmniejszych (malejąco) -> jak miałoby być odwrotnie to te dwa if'y wystarczy zamienić miejscami

		if (left) {
			left->show_BST();
		}
		cout << " V: " << v << "   ";
		if (right) {
			right->show_BST();
		}
	}

	void count_BST_reference(int& counter, int& sum, int& sum_even, int& counter_odd) { //funkcja zliczająca na dzrzewie
		if (left) { //jak jest lewy
			left->count_BST_reference(counter, sum, sum_even, counter_odd); //uruchom na nim funkcje
		}
		//ZLICZANIE NASTĘPUJE TAM GDZIE NORMALNI WYŚWIETLANIE
		counter++; //dodaj do licznika bo jest nowa kulka
		sum += this->v;
		if (this->v % 2 == 0) sum_even += this->v;
		else counter_odd++;

		if (right) { //jak jest prawy
			right->count_BST_reference(counter, sum, sum_even, counter_odd); //idz do niego
		}
	}

	int count_list_RETURN() { //metoda z zwracaniem po zakończeniu - lsita
		int counter = 1;
		if (next) counter += next->count_list_RETURN();
		return counter;
	}

	int count_tree_BST_RETURN() { //metoda z zwracaniem po zakończeniu - drzewo
		int counter = 1; //na początku jest 1 kulka
		if (left)  counter += left->count_tree_BST_RETURN(); //doda sie jeden za kazdym razem jak bedzie kulka z lewej
		if (right) counter += right->count_tree_BST_RETURN(); //doda sie jeden za kazdym razem jak jest kulka z prawej
		return counter; //na końcu zwracamy odpowiednio powiększony licznik_kulek


	}
};

//ŁADNE WYŚWIETLANIE AKTUALNEGO WĘZŁA FUNKCJA Z POZA KLASY
void show_BST_like_tree(kulka *root_BST, int space) { //

		//warunek kończący
		if(root_BST == NULL) return;
		//zwiększanie przestrzenii (co piętro potrzeba więcej miejsca
        space+=COUNT;
        //przejście do prawego
        show_BST_like_tree(root_BST->right, space);
        //wypisanie
        cout<<endl;
        for(int i=COUNT;i<space;i++) cout<<" "; //odpowiednia ilość spacji
        cout<<root_BST->v;
        //przejście do lewego
        show_BST_like_tree(root_BST->left, space);
}



int main(int argc, char** argv)
{
	int seed = (argc > 2) ? atoi(argv[2]) : 10;
	int ile = (argc > 1) ? atoi(argv[1]) : 20;
	printf("Seed=%d Liczba elementow=%d\n", seed, ile);
	srand(seed);

	int d1a = 0, d1b = 0, d2 = 0, d3 = 0, d4 = 0; // zmienne do wyników pracy funkcjonalności 1-4 na drzewie
	int l1a = 0, l1b = 0, l2 = 0, l3 = 0, l4 = 0; // zmienne do wyników pracy funkcjonalności 1-4 na liście

	//tworzenie listy
	cout << "Tworzenie listy" << endl;
	cout << endl;
	int v = 10 + rand() % 90;
	kulka* root_list = new kulka(v);
	for (int i = 1; i < ile; i++) {
		int v = 10 + rand() % 90; //p+rand(q-p+1) -> losowanko
		kulka* new_ball = new kulka(v); //kulka o losowym v z przedziału
		root_list->add_list(new_ball);
	}
	//wyswietl liste
	cout << "Wyswietl liste:" << endl;
	cout << endl;
	root_list->show_list();
	cout << endl;
	cout << endl;


	//tworzenie drzewa
	cout << "Tworzenie drzewa: " << endl;
	cout << endl;
	v = 10 + rand() % 90;
	kulka* root_tree = new kulka(v);
	for (int i = 1; i < ile; i++) {
		v = 10 + rand() % 90; //p+rand(q-p+1) -> losowanko
		kulka* new_ball = new kulka(v); //kulka o losowym v z przedziału
		root_tree->add_BST(new_ball);
	}
	//wyswietl liste
	cout << "Wyswietl drzewo:" << endl;
	cout << endl;
	root_tree->show_BST();
	cout << endl;
	cout << endl;

	//ZLICZANIE

	//METODA ZWRACAJĄCA KOD ZAKOŃCZENIA
	//zliczanie na liście metoda zwraca kod zakończenia
	int counter = root_list->count_list_RETURN();
	l1a = counter;
	//zliczanie na drzewie metoda zwraca kod zakończenia
	counter = 1;
	counter = root_tree->count_tree_BST_RETURN();
	d1a = counter;

	//METODA Z REFERENCJĄ
	//resetujemy ustawienia liczników i ustawiamy nowe -> ROOT JEST SPRAWDZANY W FUNKCJI
	counter = 0; //mamy root zaczynamy od 1
	int sum = 0, sum_even = 0, counter_odd = 0; //suma aczynamy od v roota
	//zliczanie na liście metoda przez referencję + suma, parzyste, nieparzyste
	root_list->count_list_reference(counter, sum, sum_even, counter_odd);
	l1b = counter;
	l2 = sum;
	l3 = sum_even;
	l4 = counter_odd;
	cout << endl;
	cout << endl;
	//zliczanie na drzewie metoda przez referencję + suma, parzyste, nieparzyste
	counter = 0, sum = 0, sum_even = 0, counter_odd = 0;
	root_tree->count_BST_reference(counter, sum, sum_even, counter_odd);
	d1b = counter;
	d2 = sum;
	d3 = sum_even;
	d4 = counter_odd;

    //ŁADNE WYŚWIETLANIE
    int n = 10; //ilość spacji na kolejnym poziomie (żęby robiło się drzewo, na pierwszym 0
    show_BST_like_tree(root_tree, 0);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

	//wyświetlanie może zostać - o ile wypełni się wartościami odopwiednie zmienne
	cout << "d1a:" << d1a << "\n";
	cout << "d1b:" << d1b << "\n";
	cout << "d2:" << d2 << "\n";
	cout << "d3:" << d3 << "\n";
	cout << "d4:" << d4 << "\n";
	cout << "l1a:" << l1a << "\n";
	cout << "l1b:" << l1b << "\n";
	cout << "l2:" << l2 << "\n";
	cout << "l3:" << l3 << "\n";
	cout << "l4:" << l4 << "\n";
}
