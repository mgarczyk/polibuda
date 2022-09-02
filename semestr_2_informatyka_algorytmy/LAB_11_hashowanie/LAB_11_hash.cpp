#include <iostream>
#include <string>
using namespace std;

//REKURENCYJNE
int przeszukiwanie_binarne(int tab_szukaj[], int mini, int maxi, int element) {

    int srednia = (mini + maxi) / 2; //obliczamy srednią
    if (tab_szukaj[srednia] == element) { //sprawdzamy czy indeks odpowiadający średniej jest zawiera szukany element
        return srednia; //jeżeli tekst to znaleźliśmy szukany indeks
    }
    if (mini >= maxi) { //jeżeli indeks minimlany jest większy od maksymalnego
        return -1; //to znaczy że szukany element nie istnieje
    }
    if (tab_szukaj[srednia] > element) { //jeżeli element na który wskazuje indeks jest większy od szukanego
        return przeszukiwanie_binarne(tab_szukaj, mini, srednia - 1, element); //maksymalnym staje się indeks=srednia - 1
    }
    return przeszukiwanie_binarne(tab_szukaj, srednia + 1, maxi, element); //minimalnym staje się indeks=średnia + 1


}

//SONDOWANIE LINIOWE
void sondowanie(string tab_hash[], string element_do_wpisania, int M)
{
    int indeks, klucz = 0;
    bool wstawione = false;
    for (int i = 0; i < element_do_wpisania.length(); i++) {
        klucz = klucz + static_cast<int>(element_do_wpisania[i]);  //sumujemy elementy po kodach ascii
    }
    indeks = klucz % M;  //wyznaczamy odpowiedni indeks na który chcemy wstawić element
    while (wstawione == false)  //dopóki nie wstawione
    {
        if (tab_hash[indeks] == "_") //jezeli nie ma kolizji, tzn tablica[indeks]="_" (de facto pusty)
        {
            tab_hash[indeks] = element_do_wpisania; //można wpisać do tablicy
            wstawione = true;  //element został wstawiony
        }
        else //już coś jest w tym miejscu
        {
            indeks++; //szukamy dalej wolnego miejsca na ten element
            if (indeks >= 31) indeks = 0; //może się zdarzyć tak, że zajdzie konieczność powrotu na początek tablicy
        }
    }
}

void szukanie(string tab_hash[], int rozmiar_tab_hash, string element_do_znalezienia) {
    int znaleziono = false;
    for (int i = 0; i < rozmiar_tab_hash; i++) {
        if (tab_hash[i] == element_do_znalezienia) {  //przeszukiwanie liniowe bo tablica nie jest posortowna, gdy znajdziemy szukany element to wypisujemy jego indeks                                   
            cout << i << " ";
            znaleziono = true;
            }
        }
    if (znaleziono == false) cout << -1 << " ";
}

/* WYSZUKIWANIE BINARNE ITERACYJNE */
// wykorzystuje się do posortowanych tablic
template<class T> int search(T tab[], T toFind, const int size)     // szukanie indeksu szukanej wartości
{
    int begin = 0;
    int end = size - 1;

    while (begin <= end)
    {
        int middle = (begin + end) / 2;
        if (tab[middle] == toFind) return middle;
        if (tab[middle] > toFind) end = middle - 1;
        else begin = middle + 1;
        cout << "middle = " << middle << endl;
    }
    return -1;						// funkcja zwraca -1 jeśli danego elementu nie ma w tablicy
}

template<class T> void setTab(T tab[], const int size)
{
    for (int i = 0; i < size; i++) cin >> tab[i];
}

//SEKCJA HASZOWANIA_Z_TABLICĄ_DWUWYMAIROWĄ
// funkcja wyznacza klucz, jako sumę wartości znaków danej zmiennej string i oblicza z nich resztę z dzielenia przez numOfCols (liczbę pierwszą)
int h(string toAdd, const int numOfCols)
{
    int key = 0;
    for (int i = 0; i < toAdd.size(); i++)
        key += toAdd[i];
    return (key % numOfCols);
}

// funkcja przypisuje daną zmienną do miejsca tabeli zdefioniowanej przez klucz. Jeśli dany element tablicy jest już zapełniony przez inną wartość, wówczas zapisuje w kolejnym wierszu tabeli
bool hashing(string tab[][11], string toAdd, const int numOfRows = 5, const int numOfCols = 11)
{
    int key = h(toAdd, numOfCols);			// wyznaczanie klucza

    for (int i = 0; i < numOfRows; i++)
    {
        if (tab[i][key] == "")
        {
            tab[i][key] = toAdd;
            return true;
        }
    }
    return false;
}

void dispTab(string tab[][11], const int numOfRows = 5, const int numOfCols = 11)
{
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            if (tab[i][j] == "") cout << "_ ";
            else cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}



int main(){
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3 or info == 4 or info == 5) {
        switch (info) {

        case 1:
        {
            int tab_szukaj[10], element;
            int rozmiar = 10;
            for (int i = 0; i < rozmiar; i++) {
                cin >> tab_szukaj[i];
            }
            cin >> element;
            int indeks = przeszukiwanie_binarne(tab_szukaj, 0, rozmiar - 1, element); //ustawiamy minimum na indeks=0 oraz maksimum na indeks=rozmiar-1
            cout << indeks;
            break;
        }

        case 2:
        {
            string tab_hash[31], element_do_wpisania;
            int rozmiar_tab_hash = 31, M = 31;
            for (int i = 0; i < rozmiar_tab_hash; i++) {
                tab_hash[i] = "_";          //wypełniamy tablicę symbolem '_'
            }
            int ilosc_do_wpisania = 20;
            for (int i = 0; i < ilosc_do_wpisania; i++)
            {
                cin >> element_do_wpisania;
                sondowanie(tab_hash,element_do_wpisania, M);   //umieszczamy element w indeksie obliczonym na podstawie klucza (suma ascii)%M
            }
            for (int j = 0; j < rozmiar_tab_hash; j++) // po hashowaniu, wypisujemy tablice
            {
                cout << tab_hash[j] << " ";
            }
            return 0;
            break;
        }
        case 3:
        {   
            string tab_hash_dwa[31], element_do_wpisania;
            int rozmiar_tab_hash = 31, M=31;
            for (int i = 0; i < rozmiar_tab_hash; i++) {
                tab_hash_dwa[i] = "_";          //wypełniamy tablicę symbolem '_'
            }

            int ilosc_do_wpisania = 20; //ile wpisujmey
            for (int i = 0; i < ilosc_do_wpisania; i++)
            {
                cin >> element_do_wpisania;
                sondowanie(tab_hash_dwa, element_do_wpisania, M);   //umieszczamy element w indeksie obliczonym na podstawie klucza (suma ascii)%M
            }
            int ilosc_do_znalezienia = 10; //ile szukamy
            string element_do_znalezienia;
            for (int i = 0; i < ilosc_do_znalezienia; i++) {
                cin >> element_do_znalezienia;
                szukanie(tab_hash_dwa, rozmiar_tab_hash, element_do_znalezienia);
            }
            break;
        }

        case 4:
        {   
            const int size = 11;
            int tab[size];
            setTab<int>(tab, size);
            int toFind;
            cout << "szukaj: ";
            cin >> toFind;
            cout << search<int>(tab, toFind, size) << endl;
        break;
        }

        case 5:
        {
            const int numOfRows = 5;				// pewna niekolizyjna liczba wprowadzonych wyrazów
            const int numOfCols = 11;
            string tab[numOfRows][numOfCols];
            string toAdd;
            int L = 5;							// liczba wprowadzonych wyrazów
            for (int i = 0; i < L; i++)			// wprowadzanie danych
            {
                cin >> toAdd;
                hashing(tab, toAdd);
                dispTab(tab);
            }

        }

        }
    }
    else {
        cout << "Wrong task number.";
    }
    return 0;
}