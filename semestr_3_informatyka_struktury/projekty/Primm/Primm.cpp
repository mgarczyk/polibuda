#include <iostream>
using namespace std;
const int V = 5; //zmienna globalna z ilością wierzchołków

int min_cost(int cost[], bool mst_set[]) { //funkcja znajduje wierchołek, o minimalnym koszcie dodarcia spośród tych które nie są dodane do MST, ale znamy koszt dotarcia do nich (nie jest INF)
	int mini = INT_MAX, mini_index;
	for (int v = 0; v < V; v++) {
		if (mst_set[v] == false && cost[v] < mini)
			mini = cost[v], mini_index = v;
	}
	return mini_index;
}

void printMST(int arr[], int our_graph[V][V]) { //wypisanie drzewa MST
	cout << "Krawedz" << " " << "Waga" << endl;;
	for (int i = 1; i < V; i++)
		cout << arr[i] << " - " << i << " " << our_graph[i][arr[i]] << endl; //koszt dotarcia od danego do danego wierzchołka
}


void primMST(int our_graph[V][V]) {
	int MST[V];								//przechowuje gotowe MST (zbiór wierchołków)
	int cost[V];						   //przechowuje wartości kosztówm do wybrania krawędzi dodwanej do drzewa
	bool mst_set[V];				      //przechowuje informację czy wierzchołek jest już dodany do drzewa
	for (int i = 0; i < V; i++) {
		cost[i] = INT_MAX;				//ustawiamy wszystkie koszty na "nieskończoność"
		mst_set[i] = false;			   //oraz to że żaden wierzchołek nie jest na drzewie
	}
	cost[0] = 0;					 //ustawiamy koszt dotarcia do pierwszego elemntu drzewa MST na 0
	MST[0] = -1;					//pierwszy element jest rootem MST
	for (int i = 0; i < V - 1; i++) {		//wykonamy V-1 razy bo znamy pierwszy wierchołek już jest na drzewie
		int u = min_cost(cost, mst_set);   //szukamy wierzchołeko minimalnym koszcie dotarcia (spośród możliwych)
		mst_set[u] = true;				  //dodajemy do drzewa
		for (int v = 0; v < V; v++) {

			if (our_graph[u][v] != 0 && mst_set[v] == false && our_graph[u][v] < cost[v]) { //jeżeli dana ścieżka istnieje (nie jest 0) oraz węzeł końcowu v nie jest już dodany oraz koszt od u (począrku) do v jest mniejszy niż znany obecnie koszt do v
				cost[v] = our_graph[u][v];											   //ustalamy nowy koszt dotarcia do v
				MST[v] = u;															  //ostatczne dodanie węzła u do drzewa -> u zostaje rodzicem v
			}
		}
	}
	printMST(MST, our_graph);
}


int main() {
	int graph[V][V] = { //podajemy koszty dotaracia do poszczególnych węzłów od i-tego węzła, 0 moze być gdy podajemy koszt z danego węzła do tego samego węzła lub, gdy nie da się dotrzeć do danego węzła z tego w któym jesteśmy
                        { 0, 2, 0, 6, 0 },  // np. od węzła 0 do 0 jest waga 0, od węzła 0 do 1 jest waga 2, od węzła 0 do 2 nie ma przejścia
						{ 2, 0, 3, 8, 5 },
						{ 0, 3, 0, 0, 7 },
						{ 6, 8, 0, 0, 9 },
						{ 0, 5, 7, 9, 0 }
                      };

	// Print the solution
	primMST(graph);

}
