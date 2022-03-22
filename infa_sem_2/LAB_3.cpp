#include <iostream>
using namespace std;
int main() {
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {

        case 1:
        {
            int tab_1[10];
            for (int i = 0; i < 10; i++) {
                cin >> tab_1[i];
            }
            int maksi = tab_1[0], licznik = 0;
            for (int i = 1; i < 10; i++) {
                if (maksi < tab_1[i]) maksi = tab_1[i]; //maksimum
            }
            for (int i = 0; i < 10; i++) {
                if (tab_1[i] == maksi) licznik++; //ile razy wystąpiło
            }
            cout << maksi << " " << licznik << endl;
            break;
        }
        case 2:
        {
            string tekst, wzorzec;
            cin >> tekst >> wzorzec;
            int dl_tekst = tekst.length(), dl_wzorzec = wzorzec.length(), licznik = 0;
            for (int i = 0; i <= dl_tekst - dl_wzorzec; i++) {
                bool wzorzec_jest = true;
                for (int j = 0; j < dl_wzorzec; j++) {
                    if (tekst[i + j] != wzorzec[j]) wzorzec_jest = false;
                }
                if (wzorzec_jest == true) licznik++;
            }
            cout << licznik << endl;
            break;
        }
        case 3:
        {
            double tab_2[10];
            for (int i = 0; i < 10; i++) {
                cin >> tab_2[i];
            }
            bool rowne = true;
            for (int i = 1; i < 10; i++) {
                if (tab_2[0] != tab_2[i]) rowne = false;
            }
            if (rowne == false) {
                double minimum = tab_2[0];
                for (int i = 1; i < 10; i++) {
                    if (minimum > tab_2[i]) {   
                        minimum = tab_2[i];
                    }
                }
                double drugie_minimum;
                if (tab_2[0] != minimum) drugie_minimum = tab_2[0];
                else drugie_minimum = tab_2[1];
                for (int i = 0; i < 10; i++) {
                    if (tab_2[i] != minimum) {
                        if (tab_2[i] < drugie_minimum) drugie_minimum = tab_2[i];
                    }
                    else {
                        continue;
                    }
                }
                cout << drugie_minimum << endl;
            }
            else {
                cout << "Not existing";
            }
            break;
        }

        }
    }
    else {
        cout << "Wrong task number" << endl;
    }
}
