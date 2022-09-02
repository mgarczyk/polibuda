

    #include <iostream> // cout
    #include <cstdlib>  // rand
    #include <cstdio>   // fflush // printf
    #include <cmath>    // floor

    using namespace std;

    int main()
    {
    int a = 22;
    cout << a <<  "\t" << &a << "\n"; //miejsce gdzie znajduje sie a w pamieci

    int z = 100;
    long long *b = (long long*) &a;
    cout << b << endl;
    cout << *b << endl;
    *b = 33;
    cout << a  << endl;

    int *c = NULL;
    cout << "c: " << c << endl;
    c = new int;
    *c = 20;
    cout << "*c: " << *c << endl;
    cout << "c: " << c << endl;

    b = (long long*) &a;
    cout << b << endl << *b << endl << a << endl;

    //TABLICA DYNAMICZNA NA WSKAZNIKACH
    int **t1 = new int*[10];
    for (int i = 0 ; i < 10 ; i ++)
    t1[i] = new int [10];

    for (int i = 0 ; i < 10 ; i ++)
    for (int j = 0 ; j < 10 ; j++)
    t1[i][j] = j*i;

    //t1++;

    for (int i = 0 ; i < 9 ; i ++)
    {

    for (int j = 0 ; j < 10 ; j++)
    cout << t1[i][j]  << "\t";
    cout << endl;
    }


    for (int i = 0 ; i < 10 ; i ++)
    delete[] t1[i];
    delete[] t1;


    cout << "\nXX\n";
    }
