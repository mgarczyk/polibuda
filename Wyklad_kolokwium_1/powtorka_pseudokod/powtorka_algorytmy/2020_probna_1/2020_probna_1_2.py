
T = [1, 5, 8, 10, 12, 14, 19, 20, 23, 30, 38]
n = 11


def Rek(x, p, k):
    if p < k:
        s = (p+k) // 2
        if T[s] >= x:
            Rek(x, p, s)
        else:
            Rek(x, s+1, k)
    else:
        if T[p] == x:
            print (p)
        else:
            print(-1)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    while True:
        print("Podaj x, p, k, n, pamiętaj 1<=p<=k")
        x = int(input("Podaj x: "))
        p = int(input("Podaj p: "))
        k = int(input("Podaj k: "))
        if 1 <= p <= k:
            break
        else:
            print("Spróbuj ponownie")
    Rek(x, p, k)



# See PyCharm help at https://www.jetbrains.com/help/pycharm/
