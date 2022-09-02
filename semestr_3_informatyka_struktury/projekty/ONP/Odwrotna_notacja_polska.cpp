#include <iostream>
#include<string>
#include<stack>
using namespace std;

bool is_digit(char symbol) { //funkcja sprawdzająca czy mamy do czynienia z liczbą
    if (symbol >= '0' && symbol <= '9') {
        return true;
    }
}

bool is_operator(char symbol) { //funkcja zwracająca rodzaj operacji
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol=='/') return true;

}


int operation(int b, int a, char opera_tor){
    switch (opera_tor)
    {
    case '+': return b + a;
    case '-': return b - a;
    case '*': return b * a;
    case '/': return b / a;
    }
    cout << "Zły operator" << endl;
    return 0;
}


int main()
{
    cout << "Realizujemy dodawanie, odejmowanie, mnożenie i dzielenie całkowite" << endl;
    cout << "Podawaj cyfry oraz symbole +,-,*,/, liczby podajemy w postaci cyfra-enter-cyfra-enter-cyfra...-enter-N, podanie X kończy program" << endl;
    char symbol_RPN = ' '; //aktualny wpisany symbol
    string number_string = ""; //pusty string na liczbę
    stack<int>stack_RPN;   //stos
    int a, b, result;

    while (symbol_RPN != 'X') { //dopóki nie wpiszemy symbolu X to...
        cin >> symbol_RPN; //wpisuj kolejne symbole
        if (is_digit(symbol_RPN) == true) { //jak cyfra...
            number_string += symbol_RPN; //to dopisz to stringa zawierającego aktalną liczbę
        }
        else if (symbol_RPN == 'N') {               //jak wpisano N lub operatror to...
            int number_int = stoi(number_string); //konwertuj string zawierający liczbę na intiger
            number_string = "";             //wyczyść string, aby mógł zawierać nową liczbę
            stack_RPN.push(number_int);     //wrzuć aktualną liczbę na stos
        }
        else if (is_operator(symbol_RPN) == true) {
            if (stack_RPN.size() < 2) { //gdy liczb jest za mało, a ma być wykonana operacja (ważna kolejność najpierw na stos, potem wykonujemy operacje)
                cout << "Niepoprawne wyrazenie (na stosie był jeden element)" << endl;
                return 0;
            }
            a = stack_RPN.top(); //pobieramy pierwszą wartość z początku stosu
            stack_RPN.pop(); //usuwamy tą wartość
            b = stack_RPN.top(); //pobieramy kolejną pierwszą wartość z początku stosu
            stack_RPN.pop(); //usuwamy tą wartość
            if (symbol_RPN == '/' && a == 0) { // wykonaj działanie b operator a i wrzuć wynik na stos UWAGA!!! (PIERWSZA LICZBA NA DZIAŁNIA TO B, a POTEM A)
                cout << "Dzielenie przez 0" << endl;
                return 0;
            }
            else {
                result = operation(b, a, symbol_RPN); //wykonanie działania za pomocą funkcji
                stack_RPN.push(result); //wrzucenie wyniku na stos
             }
          }
        else if(symbol_RPN != 'X') cout << "Niedozwolony symbol" << endl;

        if (stack_RPN.size() > 0) //wypisywanie góry stosu na bieżącu
        {
            if (symbol_RPN == 'N' || is_operator(symbol_RPN) == true) cout << "TOP: " << stack_RPN.top() << endl;

        }
    }
    cout << stack_RPN.top() << endl;

}

