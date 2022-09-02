#include<iostream>
#include<math.h>
using namespace std;
int permanent_funkcja(int tab_pernament[6][6], int rozmiar) {
    int permanent = 0;
    int tmp_macierz[6][6];
    if (rozmiar == 2)
        return ((tab_pernament[0][0] * tab_pernament[1][1]) + (tab_pernament[1][0] * tab_pernament[0][1]));
    else {
        for (int x = 0; x < rozmiar; x++) {
            int tmp_i = 0;
            for (int i = 1; i < rozmiar; i++) {
                int tmp_j = 0;
                for (int j = 0; j < rozmiar; j++) {
                    if (j == x)
                        continue;
                    tmp_macierz[tmp_i][tmp_j] = tab_pernament[i][j];
                    tmp_j++;
                }
                tmp_i++;
            }
            permanent = permanent + (tab_pernament[0][x] * permanent_funkcja(tmp_macierz, rozmiar - 1));
        }
    }
    return permanent;
}
int main() {
    int tab_permanent[6][6];
    const int rozmiar = 6;
    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++) {
            cin >> tab_permanent[i][j];
        }
            
    cout << permanent_funkcja(tab_permanent, rozmiar);
    return 0;
}