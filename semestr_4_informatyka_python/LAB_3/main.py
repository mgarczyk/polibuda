# This is a sample Python script.
import math
import random
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

def odl(punkt):
    D = int(math.sqrt((punkt.x)**2 + (punkt.y)**2 +  (punkt.z)**2))
    return D



class punkt:
    def __init__(self):
        self.x = int(input("Podaj x:"))                                 #random.randint(0,9)
        self.y = int(input("Podaj y:"))                                 #random.randint(0,9)
        self.z = int(input("Podaj z:"))                                 #random.randint(0,9)
    def get_data(self):
        print("X: ", self.x, "Y: ", self.y, "Z: ", self.z)

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    #fajna i przydantna struktura dictionary (slownik)
    dict = {'X': 1, 'Y': 0, 'Z': -1}
    print(dict['X']) #to jest ok, zauwazamy ze kluczem jest X, a nie numer indeksu
    print(dict)
    #sortownie klas
    ile = int(input("Podaj ile pkt:"))
    punkty = []
    print("Przed sortowaniem: ")
    for i in range (ile):
        punkty.append(punkt())
    #wypisz punkty przed sortowaniem2
    for P in punkty:
        P.get_data()
    #sortowanie po X z klasy
    punkty = sorted(punkty, key=lambda P: P.x) #uwaga wynik funkcji trzeba do czegos przypisac, albo tej samej listy albo innej
    print("Po sortowaniu: ")
    #po sortowaniu
    for P in punkty:
        P.get_data()
    #odleglosci od poczatku ukladu
    print("Po sortowaniu po odleglosci: ") #funkcja ktora pozowli sortowac po odleglosci dziala na liscie, przyjmuke dopiero wyzej jako grgument jeden punkt
    punkty_po_odleglosci = sorted(punkty, key=odl)
    for P in punkty:
        P.get_data()





# See PyCharm help at https://www.jetbrains.com/help/pycharm/
