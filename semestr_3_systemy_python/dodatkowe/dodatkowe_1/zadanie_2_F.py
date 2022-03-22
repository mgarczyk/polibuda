def calculator_F(x, operation, y):
    result = 0
    blad = 0
    if (operation == '+'):
        result = x + y
    elif (operation == '-'):
        result = x - y

    elif (operation == '*'):
        result = x * y
    elif (operation == '/'):
        if y == 0:
            print("ERROR. Division by 0 attempt.")
            blad = 1
        else:
            result = x / y
    else:
        print("ERROR. Bad operation symbol.")
        blad = 1

    if blad == 0:
        print("Wynik: ", result)
    return


x, operation, y = input(
    "Wpisz trzy wartośći. Kolejno pierwszą liczbę, operację (+,-,*,/), drugą liczbę, dane podajemy ze spacją np. 2 * 3: ").split()
x = float(x)
y = float(y)
calculator_F(x, operation, y)