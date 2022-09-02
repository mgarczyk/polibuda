#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;


void ieee_754_na_float(char ieee_754[], int precyzja){

	//bias
	int bias = 127;


	//określenie znaku
	int znak = static_cast<int>(ieee_754[0]) - 48; //odejmujemy zgodnie z ascii z '0' na 0.



	//wyznaczenie cechy dziesiętnie
	int cecha = 0, dwa_do_potegi = 1, element_cecha = 0, rozmiar_cecha = 8;
	for (int i = rozmiar_cecha; i > 0; i--) { //przeliczenie binarne cechy (od 'końca' cechy do 'początku')
		element_cecha = static_cast<int>(ieee_754[i]) - 48; //aktualny znak w cesze od jej końca
		//cout << element_cecha << " " << dwa_do_potegi << endl;
		cecha  = cecha + (element_cecha * dwa_do_potegi); //potęgowanie np. 1*64 = 2^6 itp. do przeliczenia na binarke
		dwa_do_potegi = dwa_do_potegi * 2;; //odpowiednie przeliczone potęgi 2
	}
	cecha = cecha - bias; //przesunięcie
	cout << "Cecha: "<<cecha << endl;



	//wyznczenie masntysy
	float mantysa = 0, dwa_do_potegi_odwrotnie=0.5; // 1/2
	int element_mantysa = 0;
	for(int i=rozmiar_cecha + 1;i<precyzja;i++){
		element_mantysa = static_cast<int>(ieee_754[i]) - 48; //aktualny znak w mantysie
		mantysa = mantysa + (element_mantysa * dwa_do_potegi_odwrotnie); //potęgowanie np. 1/2 = 1*2^(-1) = 1/(2^1),  1/4 = 1*2^(-2) = 1/(2^2) = 1/2 * 1/2 = 1/4, 1/8 = 1*2^(-3) = 1/(2^3) = 1/2 * 1/2 * 1/2 = 1/8. itd.
		dwa_do_potegi_odwrotnie = dwa_do_potegi_odwrotnie * (0.5); //odpowiednie przeliczenie odwrotnej potęgi dwójki
	}
	mantysa = mantysa + 1;
	cout << "Mantysa:"<<mantysa << endl;
	
	//finalnie podstawiamy do wzoru: liczba = ((-1)^znak) * mantysa * (2^cecha)
	float liczba_ieee_754_dziesietna = pow(-1, znak) * mantysa * pow(2, cecha);
	cout << liczba_ieee_754_dziesietna;


}







//z float na ieee_754
void float_na_ieee_754(string wynik_ieee_754[], int precyzja, float wartosc) {
	
	//bias(przesunięcie dla pojedynczej precyzji)
	int bias = 127;


	//określenie bitu znaku jeżeli 0 to same 0 w tablicy
	if (wartosc == 0) {
		for (int i = 0; i < precyzja; i++) {
			cout << wynik_ieee_754[i] << " ";
		}
	}
	else if (wartosc > 0) wynik_ieee_754[0] = '0';
	else {
		wynik_ieee_754[0] = '1';
		wartosc = wartosc * (-1); //korzystamy z informacji i zmieniamy znak, potem przemnażamy by dalej dokonać obliczeń na liczbie dodatniej
	}


	//określenie cechy
	float kopia_wartosc_calkowita = wartosc;
	int cecha_dziesietnie = 0;
	while (!(kopia_wartosc_calkowita >= 1 && kopia_wartosc_calkowita < 2)) {
		cecha_dziesietnie = cecha_dziesietnie + 1;
		kopia_wartosc_calkowita = kopia_wartosc_calkowita / 2; //wyznaczenie cechy dziesiętnie
	}
	cecha_dziesietnie = cecha_dziesietnie + bias; //przesunięcie o 127
	string cecha_binarnie[8];
	int rozmiar_cecha = 8;
	cout << "Cecha binarnie: " << endl;
	for (int i = rozmiar_cecha - 1; i >= 0; i--) {
		if (cecha_dziesietnie % 2 == 1) cecha_binarnie[i] = '1';  //przeliczenie cechy na kod binarny
		else if (cecha_dziesietnie % 2 == 0) cecha_binarnie[i] = '0';
		cecha_dziesietnie = cecha_dziesietnie / 2;
	}
	for (int i = 1; i < rozmiar_cecha+1; i++) {
		cout << cecha_binarnie[i-1] << endl;
		wynik_ieee_754[i] = cecha_binarnie[i - 1]; //przepisanie cechy do ostatcznego wyniku
	}



	//określenie mantysy
	float mantysa_dziesietnie = kopia_wartosc_calkowita - 1; //mantysa czyli reszta z dzielnia - 1
	string mantysa_binarnie[23];
	int rozmiar_mantysa = 23;
	for (int i = 0; i < rozmiar_mantysa; i++) { //przeliczenie mantysy na postać binarną
			mantysa_dziesietnie = mantysa_dziesietnie * 2;
			if (mantysa_dziesietnie >= 1) {
				mantysa_binarnie[i] = '1';
				mantysa_dziesietnie = mantysa_dziesietnie - 1;
			}
			else if (mantysa_dziesietnie < 1) {
				mantysa_binarnie[i] = '0';
			}
			else {
				mantysa_binarnie[i] = '1';
			}
			
	}	cout << "Mantysa binarnie: " << endl;
		for (int i = rozmiar_cecha+1; i < precyzja; i++) {
			cout << mantysa_binarnie[i - 9] << endl;
			wynik_ieee_754[i] = mantysa_binarnie[i - 9]; //przepisanie do końcowego wyniku
		}
		
		for (int i = 0; i < precyzja; i++) {  //wypisanie całej liczby
			cout << wynik_ieee_754[i];
		}
		

}




int main() {
	int info;
	cin >> info;
	if (info == 1 or info == 2) {
		switch (info) {
		case 1:
		{
			char ieee_754[32];
			int precyzja = 32;
			bool dane_ok = true;
			do {
				dane_ok = true;
				for (int i = 0; i < precyzja; i++) { //wpisanie danych i sprawdzenie
					cin >> ieee_754[i];
					if (ieee_754[i] != '0' && ieee_754[i] != '1') {
						dane_ok = false;
						break;
					}
				}
			}while (dane_ok == false);
			ieee_754_na_float(ieee_754, precyzja);
			break;

		}
		case 2:
		{
			string dane_wpisane = { '0' }, wynik_ieee_754[32];
			bool dane_ok, ujemna;
			int licznik_kropek, precyzja = 32;
			do {
				dane_ok = true;
				licznik_kropek = 0;
				cin >> dane_wpisane;
				for (int i = 0; i < dane_wpisane.length(); i++) {

					if ((dane_wpisane[i] >= '0' && dane_wpisane[i] <= '9') or (dane_wpisane[i] == '.' && licznik_kropek == 0) or (dane_wpisane[0] == '-')){
						if (dane_wpisane[i] == '.') licznik_kropek++;
						continue;
					}
					else {
						dane_ok = false;
						break;
					}
				}
			}while (dane_ok == false);

			//Problem ujemnego znaku - mamy już informację że wystąpił
			float wartosc;
			stringstream(dane_wpisane) >> wartosc; //przejście z string na int (współpracuje  ujemnymi)
			float_na_ieee_754(wynik_ieee_754, precyzja, wartosc);
			break;
		}

		}
	}
	else {
		cout << "Wrong task number.";
	}
	return 0;
}