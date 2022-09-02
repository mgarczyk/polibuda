#include <iostream>

using namespace std;
struct Edge{ //struktura zawierająca pojedynczą krawędź
    int u; //początkowy wierzchołek krawędzi
    int v; //końcowy wierzchołek
    int w; //waga danej krawędzi
};

struct Graph { //struktura zawierająca graf
    int V; //liczna wierzchołków
    int E; //liczba krawędzi
    struct Edge *edge; //tablica z krawędziami
};

struct Graph *create_graph(int V, int E){ //funkcja tworząca graf
    struct Graph *our_graph = new Graph; //stworzenie pustej struktury "przechowującej graf"
    our_graph->V = V;                   //wpisujemy ilość wierchołków
    our_graph->E = E;                  //wpisujemy ilość krawędzi
    our_graph->edge = new Edge[E];    //tworzymy tablice naszych krawędzi o wielkości ilości krawędzi
    return our_graph;                //zwracamy tę struktutrę
}
//wyswietlanie
void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout <<i<< " " << arr[i];
        cout<<endl;
    }
    cout << endl;
}

void bellman_ford(struct Graph* our_graph, int u) { //przekazujemy nasz graf i numer startowego wierzchołka
    int V = our_graph->V;
    int E = our_graph->E;
    int dist[V];                            //tablica zawierająca nasz wynik, czyli odległości
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;                  //wypełnienie "nieskończonościami"
    }
    dist[u] = 0;                           //ustalenie odległości od początkowego wierchołka (zero)
    //relaksowanie
    for (int i = 1; i <= V - 1; i++) { //przechodzimy po wierzchołkach (każdy obieg ustali koszt dojścia do co najmniej jednego wierzchoka)
        for (int j = 0; j < E; j++) { //przeglądamy wsztkie krawędzi
            //pobieramy informacje o krawędziach
            int u = our_graph->edge[j].u;
            int v = our_graph->edge[j].v;
            int w = our_graph->edge[j].w;
            //kluczowy warunek
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) { //jeżeli koszt dojścia do v jest mniejszy od aktualnego, po ścieżce do u o wadze w to zmienamy ten koszt
                dist[v] = dist[u] + w;                        //ustalenie nowego, mniejszego kosztu
            }
        }
    }
    //cykl ujemny - jeżeli będzie to wypisujemy błąd (przechodzimy jescze raz po krawędziach, jeżeli któyś dystans się zmniejszy to jest cykl
    for (int i = 0; i < E; i++) {
        int u = our_graph->edge[i].u;
        int v = our_graph->edge[i].v;
        int w = our_graph->edge[i].w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout<<"Graf zawiera ujemny cykl";
            return;
        }
    }
    print_arr(dist, V);



}
int main()
{

    int V = 4; // ilość wierzchołków
    int E = 6; // ilość krawędzi
    struct Graph* graph = create_graph(V, E);

    //dodaj krawędź 0-1
    graph->edge[0].u = 0; //weseł poczatkowy
    graph->edge[0].v = 1; //wezeł końcowy
    graph->edge[0].w = 5; //waga

    //dodaj krawędź 0-2
    graph->edge[1].u = 0;
    graph->edge[1].v = 2;
    graph->edge[1].w = 4;

    //dodaj krawędź 1-3
    graph->edge[2].u = 1;
    graph->edge[2].v = 3;
    graph->edge[2].w = 3;

    //dodaj krawędź 2-1
    graph->edge[3].u = 2;
    graph->edge[3].v = 1;
    graph->edge[3].w = 6;

    //dodaj krawędź 3-0
    graph->edge[4].u = 3;
    graph->edge[4].v = 0;
    graph->edge[4].w = 2;

     //dodaj krawędź 3-0
    graph->edge[5].u = 3;
    graph->edge[5].v = 2;
    graph->edge[5].w = 2;

    cout<<"Koszty dotarcia do poszczegolnych wezlow to: "<<endl;

    bellman_ford(graph, 0);

}

