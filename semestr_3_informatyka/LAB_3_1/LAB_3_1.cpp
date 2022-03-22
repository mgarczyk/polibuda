#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
	//z1
	cout << "Z1" << endl;
	cout << "For" << endl;
	for (int i = 1; i <= 20; i++) {
		cout << i << " ";
	}
	cout << endl;
	int i = 1;
	cout << "While" << endl;
	while (i <= 20) {
		cout << i << " ";
		i++;
	}
	cout << endl;
	cout << "Do while" << endl;
	i = 1;
	do {
		cout << i << " ";
		i++;

	} while (i != 21);
	cout << endl;
	cout << endl;
	cout << endl;
	//Z2
	cout << "Z2" << endl;
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		cout << rand() % 100 << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	//Z3
	cout << "Z3" << endl;
	for (int i = 0; i < 10; i++) {
		cout << 10 + rand() % 81 << " "; //liczba = p + rand()%(q-p+1) generowanie liczb losowych [p,q]
	}
	cout << endl;
	cout << "Z4" << endl;
	int tab_1[20], tab_2[20], tab_3[20];
	for (int i = 0; i < 20; i++) {
		tab_1[i] = i;
		tab_2[i] = pow(i, 2);
		tab_3[i] = static_cast<int>(pow(i, 2)) % 2;
	}
	//NORMALNIE
	cout << "Normalnie" << endl;
	cout << "TAB 1" << endl;
	for (int i = 0; i < 20; i++) {
		cout << tab_1[i] << " ";
	}
	cout << endl;
	cout << "TAB 2" << endl;
	for (int i = 0; i < 20; i++) {
		cout << tab_2[i] << " ";
	}
	cout << endl;
	cout << "TAB 3" << endl;
	for (int i = 0; i < 20; i++) {
		cout << tab_3[i] << " ";
	}
	cout << endl;
	//ODWROTNIE
	cout << "Odwrotnie" << endl;
	cout << "TAB 1" << endl;
	for (int i = 19; i >= 0; i--) {
		cout << tab_1[i] << " ";
	}
	cout << endl;
	cout << "TAB 2" << endl;
	for (int i = 19; i >= 0; i--) {
		cout << tab_2[i] << " ";
	}
	cout << endl;
	cout << "TAB 3" << endl;
	for (int i = 19; i >= 0; i--) {
		cout << tab_3[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	//Z5
	cout << "Z5" << endl;
	int tab_los[30];
	for (int i = 0; i < 30; i++) {
		tab_los[i] = 100 + rand() % 900;
		cout << tab_los[i] << " ";
	}
	cout << endl;
	cout << endl;
	//MAX
	int maxi = tab_los[0], index_max = 0;
	for (int i = 1; i < 30; i++) {
		if (tab_los[i] > maxi) {
			index_max = i;
			maxi = tab_los[i];  //maskymalna
		}
	}
	cout << "Maksymalna: " << maxi << " indeks " << index_max << endl;
	cout << endl;
	cout << endl;
	//MIN
	int mini = tab_los[0], index_min = 0;
	for (int i = 1; i < 30; i++) {
		if (tab_los[i] < mini) {
			index_min = i;
			mini = tab_los[i]; //maskymalna
		}
	}
	cout << "Minimalna: " << mini << " indeks " << index_min << endl;
	cout << endl;
	cout << endl;
	//srednia
	double suma = 0;
	for (int i = 0; i < 30; i++) {
		suma = suma + tab_los[i];	//srednia
	}
	double srednia = suma / 30.0;
	cout << "Srednia: " << srednia << endl;
	cout << endl;
	cout << endl;
	//szukanie najdalej od sredniej
	int roznica_najdalej = abs(tab_los[0] - srednia), indeks_najwieksza_roznica = 0;
	for (int i = 1; i < 30; i++) {
		if (tab_los[i] - srednia > roznica_najdalej) {
			roznica_najdalej = abs(tab_los[i] - srednia);
			indeks_najwieksza_roznica = i;
		}
	}
	cout << "Najwieksza roznica " << roznica_najdalej << " indeks " << indeks_najwieksza_roznica << endl;
	cout << endl;
	cout << endl;
	//szukanie nablizej do sredniej
	int roznica_najblizej = abs(tab_los[0] - srednia), indeks_najmniejsza_roznica = 0;
	for (int i = 1; i < 30; i++) {
		if (tab_los[i] - srednia < roznica_najblizej) { 
			roznica_najblizej = abs(tab_los[i] - srednia); //moduł z różnicy danej wartości z tablicy i średniej, sprawdzamy czy poprzednia różnica była mniejsza
			indeks_najwieksza_roznica = i;
		}
	}
	cout << "Najwieksza roznica " << roznica_najblizej << " indeks " << indeks_najmniejsza_roznica << endl;
	cout << endl;
	cout << endl;
	//sasiadujace parzyste
	int licznik_parzyste = 0;
	for (int i = 0; i < 29; i++) { //jeden element mniej by nie wyjść poza zakres tablicy
		if (tab_los[i] % 2 == 0 && tab_los[i + 1] % 2 == 0) licznik_parzyste++;
	}
	cout << "Parzyste kolo siebie: " << licznik_parzyste << endl;
	cout << endl;
	cout << endl;
	//poprzedajaca wieksza od kolejnej
	int licznik_poprzednia_wieksza = 0;
	for (int i = 0; i < 29; i++) { //jeden element mniej by nie wyjść poza zakres tablicy
		if (tab_los[i] > tab_los[i + 1]) licznik_poprzednia_wieksza++;
	}
	cout << "Poprzedzajaca wieksza od kolejnej: " << licznik_poprzednia_wieksza << endl;
	cout << endl;
	cout << endl;
	//rozncia mniejsza od 10
	cout << "Roznica mniejsza niz 10: ";
	for (int i = 0; i < 29; i++) { //jeden element mniej by nie wyjść poza zakres tablicy
		if (abs(tab_los[i] - tab_los[i + 1]) < 10) cout << tab_los[i] << " "; //chyba z wartoscią bezwzględną ale nie na 100%
	}
	cout << endl;
	cout << endl;
	//Z6
	cout << "Z6" << endl;
	int tab_wszystko[100], tab_parzyste[100] = {};
	cout << "Wszystko: ";
	for (int i = 0; i < 100; i++) {
		tab_wszystko[i] = 1 + rand() % 100;
		cout << tab_wszystko[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "Parzyste: ";
	for (int i = 0; i < 100; i++) {
		if (tab_wszystko[i] % 2 == 0) tab_parzyste[i] = tab_wszystko[i];
		cout << tab_parzyste[i] << " ";
	}
	//kompaktowanie - usuwanie duplukatów - zerowanie
	for (int i = 0; i < 100; i++) {
		swap(tab_parzyste[i], tab_parzyste[0]); //aktualna sprawdzana wartość idzie na początek
		for (int j = 1; j < 100; j++) { //podpętla sprawdza wyszytkie elemnty poza pierwszym
			if ((tab_parzyste[j] == tab_parzyste[0])  && tab_parzyste[0] != 0) { //jeżeli w podpędli będzie element równy pierwszemu i pierwszy element nie jest zerem to mamy powtórkę..,
				tab_parzyste[j] = 0; //którą zastępujemy zerem itd.
			}
		}
	}
	//wyswietl
	cout << endl;
	cout << endl;
	cout << "Po kompaktowaniu: ";
	for (int i = 0; i < 100; i++) {
		cout << tab_parzyste[i] << " ";
	}
	cout << endl;
	cout << endl;
	//Z7
	cout << "Z7" << endl;
	int suma_10 = 0, srednia_10, tab_10[100000];
	for (int i = 0; i < 10; i++) {
		tab_10[i] = 2;
	}
	for (int i = 0; i < 10000; i++) {
		suma_10 += rand() % 101;
		tab_10[i] = rand() % 101;
	}
	srednia_10 = suma_10 / 10000.0;
	cout << "Srednia: " << srednia_10 << " " <<  endl;
	cout << endl;
	cout << endl;
	//dwie koljne tak jak wczesniej jeden element mniej i sprawdzamy czy dany element i kolejny są przyste jak tak to zwiekszamy licznik
	int licznik_dwie = 0;
	cout << "Wypisz dwie parzyste koło siebie: " << endl;
	for (int i = 0; i < 9998; i++) {
		if (tab_10[i] % 2 == 0 && tab_10[i + 1] % 2 == 0) {
			licznik_dwie++;
			cout << tab_10[i] << " " << tab_10[i + 1] << endl;
		}
	}
	cout << "Tyle razy dwie kolejne byly parzyste: " << licznik_dwie << endl;
	cout << endl;
	cout << endl;
	//trzy koljne tak jak wczesniej ale, rezerwujemy 3 ostatnie miejsca i po kolei sprawdzamy czy dany, większy o 1 indeksem i o 2 indeksem są parzyste
	int licznik_trzy = 0;
	cout << "Wypisz trzy parzyste koło siebie: "<<endl;
	for (int i = 0; i < 9997; i++) {
		if (tab_10[i] % 2 == 0 && tab_10[i + 1] % 2 == 0 && tab_10[i + 2] % 2 == 0) {
			licznik_trzy++;
			cout << tab_10[i] << " " << tab_10[i + 1] << " " << tab_10[i + 2]<<endl;
		}
	}
	cout << "Tyle razy trzy kolejne byly parzyste: " << licznik_trzy << endl;
	cout << endl;
	cout << endl;
	//dziesiec kolenych tu innaczej wezmiemy petle i zmienna bool, if sprawdzi czy ktorej jest nieparzyste i jak tak bedzie przerwie przejscie podpetli i nie zwiększy licznika przez zmianę wartości zmiennej  bool na false
	int licznik_dziesiec = 0; 
	bool zwieksz = true;
	cout << "Wypisz dziesiec parzystych koło siebie: " << endl;
	for (int i = 0; i < 9991; i++) {
		if (tab_10[i] % 2 == 0 && tab_10[i + 1] % 2 == 0 && tab_10[i + 2] % 2 == 0 && tab_10[i + 3] % 2 == 0 && tab_10[i + 4] % 2 == 0 && tab_10[i + 5] % 2 == 0 && tab_10[i + 6] % 2 == 0 && tab_10[i + 7] % 2 == 0 && tab_10[i + 8] % 2 == 0 && tab_10[i + 9] % 2 == 0) {
			licznik_dziesiec++;
			cout << tab_10[i] << " " << tab_10[i + 1] << " " << tab_10[i + 2] << " " << tab_10[i + 3] << " " << tab_10[i + 4] << " " << tab_10[i + 5] << " " << tab_10[i + 6] << " " << tab_10[i + 7] << " " << tab_10[i + 8] << " " << tab_10[i + 9] << endl;
		}
	}
	cout << "Tyle razy dziesiec kolejnych bylo parzystych: " << licznik_dziesiec << endl;
	cout << endl;
	cout << endl;
	//Z8
	int tab_babel[10];
	cout << "Wpisanie i wypisanie: ";
	for (int i = 0; i < 10; i++) {
		tab_babel[i] = 10 + rand() % 90;
		cout << tab_babel[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "Sortownie i wyswietlnaie + zlicznie zamian: " << endl;
	cout << endl;
	cout << endl;
	int licznik_swap = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < 10 - i; j++) {
			if (tab_babel[j - 1] > tab_babel[j]) {
				swap(tab_babel[j - 1], tab_babel[j]);
				licznik_swap++;
				for (int i = 0; i < 10; i++) {
					cout << tab_babel[i] << " ";
				}
				cout << endl;
				cout << endl;
			}
		}
	}
	cout << "Ilosc zamian: " << licznik_swap << endl;
	
	




}
