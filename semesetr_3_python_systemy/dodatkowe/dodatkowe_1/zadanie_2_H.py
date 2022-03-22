import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from IPython.display import display
def draw_triangle(AB, BC, AC):
    A = (0,0)
    B = (AB, 0) #B przesunięty o długość boku
    x,y = symbols('x y')
    #szukamy x i y czyli przyrównujemy je do znanej długości boku odległość AC,
    #za pomocą zależnośći P=(p1,p2), Q=(q1,q2) d=AC=sqrt((q1-p1)^2+(q2-p2)^2)
    eq1 = Eq(x**2 + y**2, AC**2) #A=(0,0), #C=(x,y) odpowiednia w python lewa i prawa strona rówania jako argumenty funkcji
    eq2 = Eq((x-AB)**2 + y**2, BC**2) #B=(AB,0), #C=(x,y)
    C = (solve((eq1, eq2), (x,y))) #macierz rozwiązań
    print ("Rozwiązania równania czyli współrzędne x i y: ", C) #policzyliśmy brakujący nieznany nam punkt, a właściewie dwa
    first_triangle = np.array((A, B, C[0])) #Macierz z pierwszym rozwiązaniem C[0] oznacza wybór rozwiązania
    second_triangle = np.array((A, B, C[1]))
    display("Współrzędne pierwsze x1 i y1: ",first_triangle)
    display("Współrzędne drugie x2 i y2: ",second_triangle)
    print("Rysunek:")
    first_draw = plt.Polygon((first_triangle))
    second_draw = plt.Polygon((second_triangle))
    fig, ax = plt.subplots(1, 2)
    ax[0].add_patch(first_draw)
    ax[0].grid()
    ax[1].add_patch(second_draw)
    ax[1].grid()
    plt.setp(ax, xlim=[-5,5], ylim=[-5,5]) #ustawia limity do wszytkich subplotów naraz
    plt.show()
    return

AB = 3
BC = 4
AC = 5
draw_triangle(AB,BC,AC)