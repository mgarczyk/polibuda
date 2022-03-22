# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.






if __name__ == '__main__':
    #zwieksz samogloski reszte zostaw jak bylo
    data = input("Podaj dane: ") #dane
    result_1 = "" #wynik_1
    vowels = "aeoiuyAEOIUY"
    for i in range(0, len(data)): #po kolei po literach
        if(data[i] in vowels): #warunek
            result_1 += data[i].upper() #zwiekasza i doaje do wyniku zgodnie z warunkiem
        else: result_1+=data[i].lower() #po prostu doda do wyniku
    print("Po zmanie pierwsze: ", result_1) #wypisz wynik 1

    #zapisanie do txt i wyciecie samoglosek
    result_2 = ""  # wynik_2
    for i in range(0, len(data)):  # po kolei po literach
        if (data[i] not in vowels):  # warunek zeby dodal do wyniku tylko samaogloski
            result_2 += data[i]  #wycina samogloski
    print("Po wycieciu drugie: ", result_2)
    #zapis do pliku
    with open('f.txt', 'w') as f: #w
        f.write(result_2)

    #WSTEP TABLICE
    x = [1,2,3,4,5,6]
    print(x[:3]) #wypisze pierwzse trzy elementy z tablicy
    print(x[3:]) #wszytkie elemnty po trzecim
    print(x[-1]) #pierwszy od konca
    print(x[1:1])





