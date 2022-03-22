

    #include <iostream> // cout
    #include <cstdlib>  // rand
    #include <cstdio>   // fflush // printf
    #include <cmath>    // floor



    using namespace std;


    class kulka
    {
    public:
        int v;
        int numer;
        kulka(int numer=0) //konstruktor  // uwaga na przesłonięcie nazwy zmiennej klasy przez nazwę argumentu metody
        {
            this->numer=numer; //this->numer zmienna klasy, samo numer nazwa metody (funkcji)
            this->v = rand()%899+100;
            cout << "K:" << numer << "="<< v << "\t";
        }

        virtual ~kulka() {
            cout << "D:" << numer << "="<< v << "\t";
        }

        void print()
        {
            cout << numer << ":"<< v << "\t";
        }
        void zwieksz(){
            this->v = 2*v;
        }

    };

    /*
     *
     */
    int main(int argc, char** argv) {

        kulka a(-1),b(-2); //dwa obiekty a i b, klasy kulka
        kulka *c; //wskazniki na obiekty c i d
        kulka *d;
        kulka *m = &a; //wskaznik wskaze adres ktore a zawiera w pamieci

        c = new kulka(-3); //stworzenie obiektow c i d klasy kulka, te obiekty bedzie wskazywal wskaznik
        d = new kulka(-4);


        cout << "\n"<< &a << "\t"  << &b << "\t" << c << "\t" << d <<"\n";
        cout << a.v << "\t"  << b.v << "\t" << c->v << "\t" << d->v <<"\n";
        ///drukowanie  losowego numeru  v z kulki. Jezeli cos jest stworzone przez referencje to uzywamy . zeby dostac sie do danych, a przez wskaznik ->


        kulka* tab[100] = {NULL}; //tablica 100 wskaznikow, majacych wskazywac kulki


        for (int i = 0 ; i < 100; i++)
            tab[i] = new kulka(i); //stworzenie 100 wskazywanych obiektow (kulek) o numerach i, i wartoscach losoywch v

        cout<<endl;
        cout<<"Wyswietl: "<<endl;
        for (int i = 0 ; i < 100; i++){
            tab[i]->print(); //wybisanie informacji na temat kulki i, za pomoca metody print

        }
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Przemnozenie v * 2: "<<endl;
        for(int i=0;i<100;i++){
            tab[i]->zwieksz();
        }
        cout<<"Przed sortowaniem: "<<endl;
        for (int i = 0 ; i < 100; i++){
            tab[i]->print(); //wybisanie informacji na temat kulki i, za pomoca metody print

        }
        //SORTOWANIE
        kulka * pom = NULL; //wskaznik pomocniczy zapobiegajacy utracie pamieci
        for (int a = 0 ; a < 100; a++)//
            for (int b = 0 ; b < 99; b++)// petla do sortowania babelkowego
            {
                if (tab[b]->v > tab[b+1]->v ) //porownywanie wartosci v z obiektow wskazywanych przez wskazniki
                {
                    pom = tab[b]; //aktalny wskaznik przypisujemy do pom
                    tab[b] = tab[b+1]; //dokonujemy zamiany zgodnej z warunkiem
                    tab[b+1] = pom; //przypisanie starego wskaznika do innego obiektu
                }
            }
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Po sortowaniu: "<<endl;
        for (int i = 0 ; i < 100; i++)
             tab[i]->print();

        delete c;
        delete d;
        cout << "\n";
        cout<<endl;
        cout<<endl;
        cout<<"Usuwanie obiektow: "<<endl;
        for (int i = 0 ; i < 100; i++)
            delete tab[i];


        return 0;
    }
