

    #include <cstdio>   // printf
    #include <cstdlib>  // rand
    #include <time.h>
    #include <iostream>



    class kulka {
    public: int v; kulka *lewy, *prawy; bool jestem_lewy; int jestem_nowy;
    kulka(int v) : v(v), lewy(NULL), prawy (NULL), jestem_nowy(1) {printf(" K%3d ",v);}
    kulka()      :       lewy(NULL), prawy (NULL), jestem_nowy(1) {printf("X");}
    virtual
     ~kulka () {    if (lewy) delete lewy;  if (prawy) delete prawy;    printf("~D%3d ",v); fflush(stdout);}



    void add(kulka *nowa)
    {
     if (nowa-> v < v)  if (lewy)       lewy->add(nowa);
                        else            { lewy = nowa;  nowa->jestem_lewy = 1; }
     else
                        if (prawy)      prawy->add(nowa);
                        else            { prawy = nowa; nowa->jestem_lewy = 0; } }



    // to samo co add - ale bardziej przykładowo (nie jest używane w tym programie, ale do analizy przez Studentów)
    void przyjmij_kulke(kulka *nowa)
    {
     if (nowa-> v < v)
          if (lewy)
                lewy->przyjmij_kulke(nowa);
          else
               lewy = nowa;
     else
           if (prawy)
                prawy->przyjmij_kulke(nowa);
           else
                prawy = nowa;
    }

    void show()
    {
        if (lewy) lewy -> show();
        printf("  %3d ",v);
        if (prawy) prawy -> show();
    }




    };

    class kuleczka_p : public kulka
    {   public:
        kuleczka_p (int a) {v=a; printf ("p%d ",v);}
        //virtual
         ~kuleczka_p() {printf("~p%3d ",v); fflush(stdout);}
    };

    class kuleczka_n : public kulka
    {   public:
        kuleczka_n (int a) {v=a; printf ("n%d ",v);}
        //virtual
        ~kuleczka_n() {printf("~n%3d ",v); fflush(stdout);}
    };

    int main(int argc , char** argv)
    {
        int seed = (argc>2)? atoi(argv[2]):time(NULL);
        int ile  = (argc>1)? atoi(argv[1]):10;
        printf("Seed=%d Liczba elementow=%d\nEtap 1:\n",seed, ile) ;
        srand(seed); // time(NULL));

        printf("Tworzenie obiektów:\n");

        kulka *root1 = new kulka(rand()%100+100), *nowa;

        for (int i = 1 ; i < ile ; i++) {
            nowa =  new kulka(rand ()% 100 + 100);
                    root1->add(nowa);
            }
            printf("\nShow:\n");
            root1->show();
            printf("\nKasowanie:\n");
            delete root1;   root1=NULL;
        printf("\n\nEtap 2:\n");


            printf("Tworzenie obiektów:\n");
            int l = rand()%100 + 500;
        kulka *root2 ;
        if (l%2 == 0 )      root2= new kuleczka_p(l) ;
        else                root2 = new kuleczka_n(l);
        for (int i = 1 ; i < ile ; i++) {
            l = rand()%100 + 500;
            if ( l%2 == 0)      nowa =  new kuleczka_p(l);
            else                nowa =  new kuleczka_n(l);
            root2->add(nowa);
        }

        printf("\nShow:\n");
        root2 -> show();
            printf("\nKasowanie:\n");
        delete root2; root2 = NULL ;

            printf("\n\n");
    }
