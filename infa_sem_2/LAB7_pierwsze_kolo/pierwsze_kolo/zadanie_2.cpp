#include <iostream>
using namespace std;
int main()
{
    int info;
    cin >> info;
    if (info == 1 or info == 2 or info == 3) {
        switch (info) {
            double a, b, c, d, e;
        case 1:
        {
            cin >> a >> b >> c >> d >> e;
            double srednia = (a + b + c + d + e) / 5;
            cout<<endl;
            cout << srednia << endl;
            break;
        }
        case 2:
        {
            double bok_a, bok_b;
            cin >> bok_a >> bok_b;
            if (bok_a < 0 or bok_b < 0) cout << "NaN" << endl;
            else {
                double pole = bok_a * bok_b;
                cout << pole << endl;
            }
            break;
        }
        case 3:
        {
            int wykonaj;
            cin >> wykonaj;
            if (wykonaj == 1 or wykonaj == 2 or wykonaj == 3 or wykonaj == 4 or wykonaj == 5) {
                double x, y;
                cin >> x >> y;
                switch (wykonaj) {
                case 1:
                {
                    double dodaj = x + y;
                    cout << dodaj << endl;
                    break;
                }
                case 2:
                {
                    double odejmij = x - y;
                    cout << odejmij << endl;
                    break;
                }
                case 3:
                {
                    double mnoz = x * y;
                    cout << mnoz << endl;
                    break;
                }
                case 4:
                {
                    if (y != 0) {
                        double dziel = x / y;
                        cout << dziel << endl;
                    }
                    else {
                        cout << "NaN" << endl;
                    }
                    break;
                }
                case 5:
                {
                    if (y != 0) {
                        double modulo_licz = static_cast<int>(x) % static_cast<int>(y);
                        cout << modulo_licz << endl;
                    }
                    else {
                        cout << "NaN" << endl;
                    }
                    break;
                }
                }
            }
            else {
                cout << "Wrong task number" << endl;
            }
            break;
        }

        }
    }
    else {
        cout << "Wrong task number." << endl;
    }
}