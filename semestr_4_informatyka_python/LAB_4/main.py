# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

class rectangle:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def area_rectangle(self):
        return self.a * self.b

    def perimeter(self):
        return (2*self.a + 2*self.b)

class square(rectangle):  #jako argument podajemy klase z ktorej dziedziczymy
    def __init__(self, a):
        super().__init__(a,a) #odwoanie sie do konstruktora klasy nadrzednej prostokat

    #def area(self):         #wyzszy priorytrt ma funkcja o danej nazwie wewnatrz akyualnej klasy nie ta dziedziczona
        #print(1)

class triangle:
    def __init__(self,a,h):
        self.a = a
        self.h = h
    def area_triangle(self):
        return float((self.a * self.h)/2)

class piramid(square, triangle):
    def __init__(self, base, slant_h):
        self.base = base
        self.slant_h = slant_h
        super.__init__(self.base)  #stworzenie kwadratu

    def area_piramid(self):

        print(1) #TODO cos do dodania





class point:
    def __init__(self, **kwargs):
        print(kwargs)
        self.x = kwargs['X']
        print(self.x)


def sum_args(*args):
    suma = 0
    for A in args:
        suma += A
    return suma

def sum_kwargs(**kwargs):
    suma=0
    for K in kwargs.values():
        suma += K
    return suma



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print("\n\nArgs i kwargs, podawanie danych")
    suma = sum_args(1,2,3)     #tuple
    print("Suma args: ", suma)
    suma = sum_kwargs(A=1, B=2, C=3)  #dict
    print("Suma kwargs: ", suma)
    #klasa
    print("\n\nKlasa punkt: ")
    point(X=4)
    #dzeidziczenie
    print("\n\nDziedziczenie: ")
    rectangle_1 = rectangle(2,3)
    print("Pole prostokata: ", rectangle_1.area_rectangle())
    print("Dziedziczenie z prostokta")
    square_1 = square(4)
    print("Pole kwadratu: ", square_1.area_rectangle())
    triangle_1 = triangle(2,4)
    print("Pole trojkata: ", triangle_1.area_triangle())
    piramid_1 = piramid(2,5)
    piramid_1.area_piramid()






    print("\n\n Funkcja __mro__ pokazuje powiazania naszej klasy, kolejnosc")
    print(square.__mro__)  #kolejnosc szukania metod
# See PyCharm help at https://www.jetbrains.com/help/pycharm/
