// 3_10.cpp.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int COUNT = 20; //zmienna globalna do funkcji wypisującej drzewo jak drzewo

class kulka {
    public:
        int v;
        int number; //tylko podczas opci 2 potrzebne
        kulka *next = NULL;
        kulka *left = NULL;
        kulka* right = NULL;
        //konstruktor
        kulka (int v, int number=0){
            this->v = v;
            this->number = number;
            cout << "V: " << v << endl;
        }
        //tworzenie bez sortowania
        void add_list(kulka* new_ball) {
            if (this->next) this->next->add_list(new_ball);
            else this->next = new_ball;
        }
       
        //wyswietlanie listy
        void show_list(int color, bool option_2 = false) { //flaga opcji 2 domyślnie fałszywa
            setColor(color);
            if (option_2 == false) {
                cout << "V: " << this->v << " ";
            }
            else {
                cout << "Numer: " << this->number << " V: " << this->v << " "; //jak flaga będzie prawdziwa to wyświetlamy v oraz numer potrzebny tylko w opcji_2
            }
            if (next) next->show_list(color);
            else cout << endl;
        }
        //tworzenie drzewa
        void add_BST(kulka* new_ball) {
            if (new_ball->v < this->v) {
                if (left) left->add_BST(new_ball);
                else left = new_ball;
            }
            else {
                if (right) right->add_BST(new_ball);
                else right = new_ball;
            }
        }
        //wyswietlanie drzewa
        void show_BST(int color=0) {
            if (left) left->show_BST(color);
            setColor(color);
            cout << "V: " << this->v << " ";
            if (right) right->show_BST(color);
        }
        //zliczanie listy
        void count_list(int& counter) {
            if (next) next->count_list(counter);
            counter++;
        }

        //zliczanie drzewa
        void count_BST(int &counter) {
            if (left) left->count_BST(counter);
            counter++;
            if (right) right->count_BST(counter);
        }
        //zmiana kolorow
        void setColor(int c_30_37 = 1) //kolory
        {
            if (c_30_37 == 1)
            {
                c_30_37 = rand() % 8 + 30;
                cout << "\033[1;" << c_30_37 << "m";
            }
            else
                if (c_30_37 == 256)
                {

                    c_30_37 = rand() % 256;
                    cout << "\x1b[38;5;" << c_30_37 << "m";
                   /*
                    // background
                    c_30_37 = rand() % 256;
                    cout << "\x1b[48;5;" << c_30_37 << "m";
                    */
                }
                else
                    if (((c_30_37 >= 30) & (c_30_37 <= 37)) | c_30_37 == 0)

                        cout << "\033[1;" << c_30_37 << "m";
                    else
                        cout << "\x1b[38;5;" << c_30_37 << "m";


        }
      
};



//najnizszy poziom
int lowest_level_BST(kulka* root_BST) { //uruchamiamy na roocie
    if (root_BST == NULL) return 0; //jesli root jest pusty kończymy nie bylo potomka
    int left_height = lowest_level_BST(root_BST->left); //szukamy ostatniego poziomu lewego poddrzewa, itd.. rekurencja
    int right_height = lowest_level_BST(root_BST->right); //szukamy ostatniego poziomu prawego poddrzewa, itd.. rekurencja
    return max(left_height, right_height) + 1; //ostatecznie wybieramy czy lewe czy prawe poddrzewo było "głębsze"
}


//wyswietlanie ostatniego poziomu
void print_lowest_level(kulka* root_BST, int lowest_level) { //podajemy wskaźnik na roota i pozi
    if (root_BST == NULL) return;
    if (lowest_level == 0) cout<<"V: "<<root_BST->v<<" ";
    else if (lowest_level > 0) {
        print_lowest_level(root_BST->left, lowest_level - 1); //idzemy w lewo
        print_lowest_level (root_BST->right, lowest_level - 1); //idziemy w prawo
    }

}

//zliczanie potomkow
void child_BST(kulka *root_BST, int& zero_child_counter, int& single_child_counter, int& double_child_counter) {
    if (root_BST == NULL) return;                                                                                                              //doszliśmy do końca w poprzednim kroku left lub right był NULL
    if (root_BST->left == NULL && root_BST->right == NULL) zero_child_counter++;                                                               //jak lewy i prawy pusty to nie ma potomka
    else if (root_BST->left != NULL && root_BST->right == NULL or root_BST->left == NULL && root_BST->right != NULL) single_child_counter++; //jak jest lewy to nie może być prawego lub odwrotnie i wtedy jest 1 potomek
    else double_child_counter++;                                                                         //w pozostałych przypadkach ma dwóch potomkow         
    child_BST(root_BST->left, zero_child_counter, single_child_counter, double_child_counter);          //dalej lewe poddrzewo
    child_BST(root_BST->right, zero_child_counter, single_child_counter, double_child_counter);        //dalej prawe poddrzewo
}

void show_BST_like_tree(kulka* root_BST, int space) { //wypisywanie drzewa jak drzewo 

    //warunek kończący
    if (root_BST == NULL) return;
    //zwiększanie przestrzenii (co piętro potrzeba więcej miejsca
    space += COUNT;
    //przejście do prawego
    show_BST_like_tree(root_BST->right, space);
    //wypisanie
    cout << endl;
    for (int i = COUNT; i < space; i++) {
        cout << " "; //odpowiednia ilość spacji
    }
    cout << root_BST->v;
    //przejście do lewego
    show_BST_like_tree(root_BST->left, space);
}


void sort_when_creating(kulka * root_list, kulka* new_ball) { //UWAGA FUNKCJĘ TĄ URUCHAMIAMY DLA KAŻDEJ NOWEJ KULKI, CZYLI W MAIN MAMY PĘTLĘ FOR TWORZĄCĄ KOLEJNE KULKI, NIE SORTUJE PIERWSZEGO ELEMENTU ROOTA
    kulka *tmp = root_list;
    while (true) {
        if (tmp->next == NULL) { //udało nam się dojść do końca bez niespodzianek, umieszczamy tam nową kulkę
            tmp->next = new_ball; //dodanie na końcu
            break; //jak dodamy to break i koljena iteracja fora
        }
        else { //gdy nie jesteśmy na końcu
            if (new_ball->v > tmp->next->v) { //sprawdzamy czy v nowej kulki jest większe od v następnej po tmp (poprzedniej) np. tmp->v = 8, tmp->next->v = 10, new_ball->v = 9), ZAMIANA
                new_ball->next = tmp->next; //zamiana, next ze starej kulki (poprzedniej), wchodzi za nową kulkę (para kulek new_ball i tmp->next)
                tmp->next = new_ball;      //podłączenie reszty listy do wyżej utworzonej pary kulek, tmp, new_ball, new_ball->next
                break; //jak dokonaliśmy zamiany to zadanie wykonen i idziemy do kolejnej iteracji

            }
            else { //jak nie było zamiany
                tmp = tmp->next; //to idziemy dalej w kierunku końca listy
            }
        }
    }
}

void sort_list_after_creation_v(kulka* first, int length_list) { //sortowanie po stworzeniu UWAGA TA FUNKCJA NIE ZAMIENIA WSKAŹNIKÓW TYLKO WARTOŚCI, po v
    kulka* actual_ball = first; //aktalna kulka
    kulka* next_ball = first; //kolejna kulka
    for (int i = 0; i < length_list; i++) { //pętla zewnętrzna
        for (int j = 0; j < length_list - 1; j++) { //pętla wewnętrzna wyknuje się raz mniej
            if (next_ball->v < actual_ball->v) { //jesli następne v jest większe od
                int tmp_v = actual_ball->v; //w pomocniczym mamy aktalną kulkę
                int tmp_number = actual_ball->number;
                actual_ball->v = next_ball->v; //zamiana kulki z mniejszym v na tą o więkskszym v
                actual_ball->number = next_ball->number;
                next_ball->v = tmp_v;
                next_ball->number = tmp_number;
            }
            next_ball = next_ball->next; //przechodzenie po j, kolejnych kulkach

        }
        //PRZESUWAMY JAK W BĄBELKOWYM TYLKO NA WSKAŹNIKACH
        next_ball = first; //jako kolejną ustawiamy ponownie pierwszą kulkę (zmieniła wartość ale nie pozycję)
        actual_ball = first->next; //jako aktualną ustwiamy next z pierwszej, żeby były jedna za drugą (druga kulka w rzędzie)
        for (int k = 0; k < i; k++) { //i przesuwamy jescze k razy tą aktualną
            actual_ball = actual_ball->next; //pomijamy juz posortowany obszar (chyba) i ustawiamy kulkę do dalszego porównywania
        }

    }
}

void sort_list_after_creation_number(kulka* first, int length_list) { //sortowanie po stworzeniu UWAGA TA FUNKCJA NIE ZAMIENIA WSKAŹNIKÓW TYLKO WARTOŚCI, po number
    kulka* actual_ball = first; //aktalna kulka
    kulka* next_ball = first; //kolejna kulka
    for (int i = 0; i < length_list; i++) { //pętla zewnętrzna
        for (int j = 0; j < length_list - 1; j++) { //pętla wewnętrzna wyknuje się raz mniej
            if (next_ball->number > actual_ball->number) { //jesli następne v jest większe od
                int tmp_v = actual_ball->v; //w pomocniczym mamy aktalną kulkę
                int tmp_number = actual_ball->number;
                actual_ball->v = next_ball->v; //zamiana kulki z mniejszym v na tą o więkskszym v
                actual_ball->number = next_ball->number;
                next_ball->v = tmp_v;
                next_ball->number = tmp_number;
            }
            next_ball = next_ball->next; //przechodzenie po j, kolejnych kulkach

        }
        //PRZESUWAMY JAK W BĄBELKOWYM TYLKO NA WSKAŹNIKACH
        next_ball = first; //jako kolejną ustawiamy ponownie pierwszą kulkę (zmieniła wartość ale nie pozycję)
        actual_ball = first->next; //jako aktualną ustwiamy next z pierwszej, żeby były jedna za drugą (druga kulka w rzędzie)
        for (int k = 0; k < i; k++) { //i przesuwamy jescze k razy tą aktualną
            actual_ball = actual_ball->next; //pomijamy juz posortowany obszar (chyba) i ustawiamy kulkę do dalszego porównywania
        }

    }
}





int main()
{   //tworzenie listy
    srand(time(NULL));
    int number_of_balls = 10; //ilość kulek
    cout << "Tworzenie listy: " << endl;
    cout << endl;
    int v = 10 + rand() % 90;
    kulka* root_list = new kulka(v);
    root_list->setColor(0);
    int option_list; //zmienna do wybrania opcji
    cout << "Kliknij, 0 - (sortowanie malejąco tworzenie), 1 - (sortowanie rosnąco po stworzeniu) , 2 - (najpierw sortowana podczas wkladania po v, a potem po i (numerze kulki jak ja tworzymy)), inny - default:" << endl;
    cin >> option_list;
    switch (option_list){
        case 0: { //opcja 0, sortowanie przy tworzeniu
            for (int i = 1; i < number_of_balls; i++) {
                v = 10 + rand() % 90;
                kulka* new_ball = new kulka(v);
                sort_when_creating(root_list, new_ball);
            }
            break;
        }
        case 1: { //sortowanie rosnąco po stworzneiu
            for (int i = 1; i < number_of_balls; i++) {
                v = 10 + rand() % 90;
                kulka* new_ball = new kulka(v);
                root_list->add_list(new_ball);
            }
            sort_list_after_creation_v(root_list, number_of_balls); //sortowanie po stworzeniu, root sortowanej listy i ilość elemntów
            break;
        }
        case 2: {
            for (int i = 1; i < number_of_balls; i++) { //najpierw sortujemy po v (malejąco) w czasie wkładania, a potem po numerze kulki (rosnąco) przy tworzeniu. Numerujemy od 0.
                v = 10 + rand() % 90;
                kulka* new_ball = new kulka(v, i); //root ma wartość numer = 0, a kolejne kulki kolejne numery zgodne z forem
                sort_when_creating(root_list, new_ball); //sortowanie po v podczas tworzenia
            }
            cout << endl;
            cout << endl;
            cout << "Wyswietlanie po posortowaniu po v: " << endl;
            root_list->show_list(256, true); //wyświetlanie po stworzeniu, przed sortowaniem osatecznym po numerze, pamiętamy o przestawieniu flagi na true, wyświetlanie numeru
            sort_list_after_creation_number(root_list, number_of_balls);
            break;
        }
        default: { //opcja podstawowa po prostu tworzymy listę
            for (int i = 1; i < number_of_balls; i++) {
                v = 10 + rand() % 90;
                kulka* new_ball = new kulka(v);
                root_list->add_list(new_ball);
            }
            break;
        }
    }
   
   

    //wyswietlanie listy
    cout << endl;
    cout << "Wyswielanie listy: " << endl;
    cout << endl;
    root_list->show_list(256); //ustawienie kolory
    root_list->setColor(0); //reset koloru
    cout << endl;
    cout << "Tworzenie drzewa: " << endl;
    cout << endl;
    kulka *root_BST_0 = NULL, * root_BST_1 = NULL, * root_BST_2 = NULL;


    //Tworzenie drzewa
    
    cout << "Kliknij, 3 -  (kulki nie są wyciagane po kolei tylko najpierw podzielne przez 3, wyswiela, zlicza, itd.), inny - dzialanie domyslne)" << endl;
    int option_tree;
    cin >> option_tree;
    kulka* tmp = root_list; //zaczynamy od tmp wskazującego na roota
    switch (option_tree)
    {
    /*
    case 3: {
        int counter = 0; //licznik listy
        //Podzielne przez 3
        while (tmp) { //powtarzamy tę pętlę trzy razy, najpierw dla podzelnych przez 3
            if (tmp->v % 3 == 0) { //jeżeli jest podzielna przez 3
                
                root_list->next = tmp->next; //przesuwamy początek listy, "pomijając" aktualny elemnt
                
            }
            tmp = tmp->next;
        }

        cout << "Lista po usunięciu podzielnych przez 3" << endl;
        root_list->show_list(34); //drugie wyświetlnie po usunięciu tych podzelnych przez 3
        /*
        //Podzielne przez 2
        tmp = root_list;
        while (tmp) { //powtarzamy tę pętlę dla podzelnych przez 2
            if (tmp->v % 2 == 0) { //jeżeli jest podzielna przez 2
                if (root_BST_1 == NULL)  root_BST_1 = tmp; 
                else root_BST_1->add_BST(tmp);  
                root_list = tmp->next;
            }
            tmp = tmp->next;
        }

        cout << "Lista po usunięciu podzielnych przez 2" << endl;
        root_list->show_list(35); //trzecie wyświetlenie bez podzielnych przez 2

        //POZOSTAŁE
        while (tmp) { //powtarzamy tę pętlę dla pozostałych
            if (root_BST_2 == NULL)  root_BST_2 = tmp;
            else root_BST_2->add_BST(tmp);
            root_list = tmp->next;
            tmp = tmp->next;
        }
        
        
        break;
        
        
    }
    */
    default:
        while (tmp) { //w pętli
            if (tmp->v % 3 == 0) { //jeżeli jest podzielna przez 3
                if (root_BST_0 == NULL)  root_BST_0 = tmp; //jezeli root pierwszego drzewa jest pusty, wrzucamy tam aktualne tmp i wyrzucamu je z listy
                else root_BST_0->add_BST(tmp);  //jak juz jest root danego drzewa to znaleziony element dodajemy do drzewa
            }
            else if (tmp->v % 2 == 0) { //tak samo tu
                if (root_BST_1 == NULL)  root_BST_1 = tmp;
                else root_BST_1->add_BST(tmp);
            }
            else { //i tu te pozostałe
                if (root_BST_2 == NULL)  root_BST_2 = tmp;
                else root_BST_2->add_BST(tmp);
            }
            root_list = tmp->next; //przesuwamy początek listy, "pomijając" aktualny elemnt
            tmp = tmp->next; //przesunięcie się dalej
        }
        break;
    }
    


    //znalezione rooty
    cout << "Rooty drzewa: " << endl;
    if (root_BST_0 != NULL && root_BST_1 != NULL && root_BST_2 != NULL) {
        cout << "Drzewo 0 -> x%3 = 0: " << root_BST_0->v << endl;
        cout << "Drzewo 1 -> x%2 = 0: " << root_BST_1->v << endl;
        cout << "Drzewo 2 -> pozostale: " << root_BST_2->v << endl;
    }
   


    //wyswietlanie drzew i zliczanie
    cout << endl;
    cout << "Drzewa " << endl;
    cout << endl;
    int counter = 0;
    cout << "Drzewo x % 3 = 0: " <<endl;
    if (root_BST_0 != NULL) {
        root_BST_0->show_BST(31);
        root_list->setColor(0);
        counter = 0;
        root_BST_0->count_BST(counter);
        cout << endl;
        cout << "Ilosc elemntow drzewo 0: " << counter << endl;
        cout << endl;
        cout << "Drzewo x % 2 = 0 " << endl;
    }
    if (root_BST_1 != NULL) {
        root_BST_1->show_BST(32);
        root_list->setColor(0);
        counter = 0;
        root_BST_1->count_BST(counter);
        cout << endl;
        cout << "Ilosc elementow drzewo 1: " << counter << endl;
        cout << endl;
        cout << "Drzewo pozostale " << endl;
    }
    if (root_BST_1 != NULL) {
        root_BST_2->show_BST(34);
        root_list->setColor(0);
        counter = 0;
        root_BST_2->count_BST(counter);
        cout << endl;
        cout << "Ilosc elementow drzewo 2: " << counter << endl;
        cout << endl;
        cout << endl;
    }
    

    //drzewo jak drzewo wyśiwetlone
    //drzewo 0
    cout << "Drzewo x % 3 = 0: " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    show_BST_like_tree(root_BST_0, 0);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    //drzewo 1
    cout << "Drzewo x % 2 = 0: " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    show_BST_like_tree(root_BST_1, 0);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    //drzewo 2
    cout << "Pozostale: " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    show_BST_like_tree(root_BST_2, 0);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;


    //poziomy drzewa
    cout << "Poziomy" << endl;
    int lowest_level = lowest_level_BST(root_BST_0) - 1;
    cout << "Najnizszy poziom drzewo 0: " << lowest_level << endl;
    print_lowest_level(root_BST_0, lowest_level); //wypiswyanie, podajemy root odpowiedniego drzewa i poziom który hcemy wypisać
    cout << endl;
    lowest_level = lowest_level_BST(root_BST_1) - 1;
    cout << "Najnizszy poziom drzewo 1: " << lowest_level << endl;
    print_lowest_level(root_BST_1, lowest_level);
    cout << endl;
    lowest_level = lowest_level_BST(root_BST_2) - 1;
    cout << "Najnizszy poziom drzewo 2: " << lowest_level << endl;
    print_lowest_level(root_BST_2, lowest_level);
    cout << endl;
    cout << endl;


    //statystyka
    cout << "Statystyka: " << endl;
    int zero_child_counter = 0, single_child_counter = 0, double_child_counter = 0;
    child_BST(root_BST_0, zero_child_counter, single_child_counter, double_child_counter);
    cout << "Ilosc wezlow z bez potomka drzewo 0: " << zero_child_counter << endl;
    cout << "Ilosc wezlow z jednym potomkiem drzewo 0: " << single_child_counter << endl;
    cout << "Ilosc wezlow z dwoma potomkami drzewo 0: " << double_child_counter << endl;
    cout << endl;
    zero_child_counter = 0, single_child_counter = 0, double_child_counter = 0;
    child_BST(root_BST_1, zero_child_counter, single_child_counter, double_child_counter);
    cout << "Ilosc wezlow z bez potomka drzewo 1: " << zero_child_counter << endl;
    cout << "Ilosc wezlow z jednym potomkiem drzewo 1: " << single_child_counter << endl;
    cout << "Ilosc wezlow z dwoma potomkami drzewo 1: " << double_child_counter << endl;
    cout << endl;
    zero_child_counter = 0, single_child_counter = 0, double_child_counter = 0;
    child_BST(root_BST_2, zero_child_counter, single_child_counter, double_child_counter);
    cout << "Ilosc wezlow z bez potomka drzewo 2: " << zero_child_counter << endl;
    cout << "Ilosc wezlow z jednym potomkiem drzewo 2: " << single_child_counter << endl;
    cout << "Ilosc wezlow z dwoma potomkami drzewo 2: " << double_child_counter << endl;
    cout << endl;
    //KOLORY
    int x = rand() % 256;
    cout << "\u001b[38;5;"<<77<<"mHelloWorld";


    

}
