#include <iostream>
#include <string>
using namespace std;

int sumator(int tab[], const int rozmiar) {
	int suma = 0;
	for (int i = 0; i < rozmiar; i++) {
		if (tab[i] % 2 == 0 && tab[i] % 4 != 0 && tab[i] % 6 != 0) { //jak modulo daje 0 to jest podzielna, jak nie to niepodzielna
			suma += tab[i];
		}
	}
	return suma;
}

int  hamming_odl(int pierwsza, int druga) {
	int EXOR = pierwsza ^ druga; //XOR da jako wynik ciąg bitów, gdzie 1 będzie tylko na pozycjach różnićych się, np. A = 4 = 0100 i B = 12 = 1100, A XOR B = 1000
	unsigned int maska = 0x80000000; //maska 1 i 31 zer (32 bity) zapis 16-stkowy
	const int bajt = 8; //bajt to 8 bitów
	int licznik = 0; //lciznik
	//sprawdzamy na którym bicie wystąpi róznica, działa to tak, że porównamy tą jedyną jedynkę z maski z kolejnymi bitami wyniku
	//XORA i jeżeli na pozycji danej i-tej XOR dał 1 i ta 1 z maski ją spotka, to funkcja AND da wynik 1 i zwiększamy licznik
	//bo to tam była ta różnica co jest tłumaczone wyżej
	for (int i = 0; i < sizeof(pierwsza) * bajt; i++) { //sizeof daje wielkość liczby w bajtach, my chcemy w bitach mnożymy * 8
		if (EXOR & maska) licznik++; //zwiększamy licznik zgodnie z tym co wyżej
		maska = maska >>= 1; //przesuwamy maskę to tu ta jedyna 1 z maski przesuwa się w prawo
		//jeżeli było 1 i 31 zer, to potem jest 0, 1, i 30 zer itd. jedynka po prostu przechodzi dalej, a z przodu dopisują się zera
	}
	return licznik;
}



int main()
{
    int choose;
    cin >> choose;
	switch (choose)
	{
	case 1: {
		const int rozmiar = 10;
		int tab[10];
		for (int i = 0; i < rozmiar; i++) {
			cin >> tab[i];
		}
		int suma = sumator(tab, rozmiar);
		cout << suma;
		break;
	}
	case 2: {
		cin.ignore();
		string text;
		getline(cin, text);
		break;
	}
	case 3: {
		int pierwsza;
		cin >> pierwsza;
		int druga;
		cin >> druga;
		if (druga > pierwsza) swap(pierwsza, druga);
		int hamming = hamming_odl(pierwsza, druga);
		cout << hamming;
		break;
	}
	default: {
		cout << "Wrong task number.";
	}
	}
}

