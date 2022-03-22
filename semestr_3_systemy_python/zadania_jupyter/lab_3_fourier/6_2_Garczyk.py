import sympy 
import numpy as np
import matplotlib.pyplot as plt 
from xInteractiveFourier import *


#Funkcja przymuje wzory na trygonometryczny szereg fouriera i wyznacza wzory na współczynniki - podpunkt C

#declare functions (fA, fB, ... fF)
def declare_function(t, T):
    #sympy.Picewise() służy do deklaracji funkcji z rózymi wzorami na różnych przedziałach
    fA = sympy.Piecewise((2*t/T, t<=T/2),(1-2*t/T, t>T/2)) #wzory funkcji w poszeczególnych przedzaiłach dla okresu T, w nawiasach przedały w których funkcja się zmienia
    fB = (-2*t)+1/T
    fC = sympy.Piecewise((2*t/T, t<=T/2), ((-2*t+2)/T, t>T/2))
    fD = sympy.Piecewise((1, t<=T/4), (0, t<=3*T/4), (1, t>=3*T/4))
    fE = sympy.Piecewise(((sympy.sin(2*sympy.pi*t/T)), t<=T/2), (0, t>T/2)) #sinus symboliczny z symby coś innego niż nympy
    fF = sympy.exp(-t/T)
    #selelect one function and draw
    currFun = fE
    return currFun


def determineFourierCoefficients_trigonometric(Function, RangeBeg, RangeEnd, DisplayCoeffs=True):
    print("Wzory na ak, bk i a0 - PODPUNKT C: ")
    #determine F0
    a0 = (1/T)*sympy.integrate(currFun, (t, RangeBeg, RangeEnd))
    #determine Fk
    #Trzeba pamiętać że musi być sympy.exp(), sympy.sqrt() itp. przy tworzeniu wzorów
    ak = (2/T)*sympy.integrate((currFun*sympy.cos(k * t * 2*sympy.pi/T)), (t, RangeBeg, RangeEnd))
    bk = (2/T)*sympy.integrate((currFun*sympy.sin(k * t * 2*sympy.pi/T)), (t, RangeBeg, RangeEnd))
    ak = sympy.simplify(ak)
    bk = sympy.simplify(bk)
    print("a0: ")
    display(a0)
    print("ak: ")
    display(ak)
    print("bk: ")
    display(bk)
    return a0, ak, bk


def display_coeffs(a0, ak, bk):
    print("Wypisz a0, ak i bk - PODPUNKT D")
    coeff_a0 = np.array(a0, dtype='double') #oblicza a0 i wpsije do tablicy
    coeff_ak = np.double(sympy.lambdify(k, ak, 'numpy')(np.arange(1,21))) #oblicza ak, dla każdego k od 1-10, k jest parametrem pod nią podstawiamy koljne numery
    coeff_bk = np.double(sympy.lambdify(k, bk, 'numpy')(np.arange(1,21))) #oblicza bk, dla każdego k od 1-10, k jest parametrem pod nią podstawiamy koljne numery
    #displaying a0, ak, bk
    print("a0: ", a0)
    for ki, iak in enumerate(coeff_ak): #pętla ki - kolejne numery wspolczynnika, a - kolejne obliczone ak
        print("a{} = {}".format(ki+1, iak.round(10))) #ładne wyświetlanie w nawiasach klamrowych beda zmienne
    for ki, ibk in enumerate(coeff_bk): #pętla ki - kolejne numery wspolczynnika, b - kolejne obliczone bk
        print("b{} = {}".format(ki+1, ibk.round(10))) #ładne wyświetlanie w nawiasach klamrowych beda zmienne
    return coeff_a0, coeff_ak, coeff_bk
    





#declare symbolic variable t (time) and period (T=1)
t = sympy.Symbol('t', real = 'True', nonzero = 'True') 
T = 1 #długość okresu
currFun = declare_function(t, T)
lam_current = sympy.lambdify(t, currFun, 'numpy')
t_vals = np.linspace(0, T, 200) #próbki na osi t, argumenty
f_vals = lam_current(t_vals) #wartośći funkcji currFun(t)
plt.plot(t_vals, f_vals)  #plot the selected function
NumberOfSamples = 200
a0, ak, bk = determineFourierCoefficients_trigonometric(currFun, 0, T)  #wzory na wspolczynniki z funkcji determine
#Stworzenie i wypisanie tablic zawierających wspolczynniki oraz zwrócenie ich do maina - podpunkt D
coeff_a0, coeff_ak, coeff_bk = display_coeffs(a0, ak, bk)
print("Modyfikacja complexFourierSeries E - F0 = a0, Fk = 1/2 * (ak-i*bk), jak widać wynik jest ok zgadza się z tym jak liczyły Fk programy z zajęć, ale nie do końca wiem jak poprawić tą klasę żeby chciała współpracować z tak wyliczonym Fk")
MaxNumCoeffs = 20  #max num coeff used for demo
F0 = coeff_a0
Fk = [None] * (MaxNumCoeffs-1)
print("F0 to: ", F0)
for i in range (MaxNumCoeffs-1):
    Fk[i] = np.cdouble((0.5) * (coeff_ak[i] - 1j * coeff_bk[i]))
    
print("Nowe policznone na podstawie ak i bk, Fk: ")
for ki, iFk in enumerate(Fk): #pętla ki - kolejne numery wspolczynnika, b - kolejne obliczone bk
        print("F{} = {}".format(ki+1, iFk.round(10))) #ładne wyświetlanie w nawiasach klamrowych beda zmienne

FigSize  = (16, 10)




