import numpy as np
def translator_G(poly):
    len_poly = len(poly)
    poly_text = ""
    for i in range (len_poly+1): #pętla po długości tablicy ze współczynnikami wielomianu przy odpowienich potęgach
        if i==0 and poly[i]>0: #wyraz wolny > 0
            poly_text = " + " +  str(poly[0])  #dla wyrazy wolnego jeżeli nie jest to 0 dodaj bez x
        elif i==0 and poly[i]<0: #wyraz wolny < 0
            poly_text =  " " +  str(poly[0])
        elif i>0 and poly[i] > 0:  #kolejne współczynniki przy potęgach > 0
            poly_text =  " + " + str(poly[i]) + "x^" + str(i) + str(poly_text) #dla kolejnych wyrazów dodawaj z odpowiednią potęg x
        elif i>0 and poly[i] < 0: #kolejne współczynniki przy potęgach < 0
            poly_text =  " " +  str(poly[i]) + "x^" + str(i) + str(poly_text)
        elif i>=0 and poly[i] == 0: #dla zerowej wartości
            poly_text =  "" + str(poly_text)
    poly_text = "f(x) = " + str(poly_text)
    print("Zapis tekstowy: ", poly_text)
    return


poly = np.poly1d([-5,3,-1,0,1,6])
translator_G(poly)