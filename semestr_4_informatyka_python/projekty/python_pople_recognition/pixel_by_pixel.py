



def pixel_by_pixel_test(img_to_recognize, data_image):
    # sprawdzamy pixel po pixelu,  czy każdy z pikseli obrazka z dataset mieści się w przedziale  +-10% względem testowaego obrazka
    # (jak tak to zliczmay ten piksel, potem patrzymy % ile pikseli względem całości  było zgodnych i jak jest powiedzmy >80% to uznajemy że jest git i zliczamy dany obrazek jako poprawny,
    # jeżeli 80% obrazków z dataset spełni warunek  uznajemy, że sprawdzany obrazek to człowiek, oczyiwście te wartości można modyfikować, metoda zwraca 1 jeżeli porównamy te same obrazy
    shape_width = img_to_recognize.shape[0]
    shape_height = img_to_recognize.shape[1]
    pixel_by_pixel_counter = 0 # licznik sprawdzający ile obrazków spełnia naszą metodę
    single_pixel_counter = 0   # zliczamy nasze prawidłowe piksele +-10% R G B
    for row in range(shape_height): # wysokość ilość wierszy obrazka na 1920x1080 to 1920 to szerokość 1080 to wysokość
        for column in range(shape_width):  # szerokość ilość kolumn
            red_0_9 = img_to_recognize[row][column][0] * 0.7  # tutaj ustalamy nasze progi akceptacji te +-10% do każdego piksela, w zależności od koloru
            red_1_1 = img_to_recognize[row][column][0] * 1.3
            green_0_9 = img_to_recognize[row][column][1] * 0.7
            green_1_1 = img_to_recognize[row][column][1] * 1.3
            blue_0_9 = img_to_recognize[row][column][2] * 0.7
            blue_1_1 = img_to_recognize[row][column][2] * 1.3
            # print(img_to_recognize[row][column][0])
            # print(img_to_recognize[row][column][1])
            # print(img_to_recognize[row][column][2])
            if red_0_9 <= data_image[row][column][0] <= red_1_1  and green_0_9 <= data_image[row][column][1] <= green_1_1 and blue_0_9 <= data_image[row][column][2] <= blue_1_1:
                single_pixel_counter += 1  # jeżeli każdy z trzech kolorów pikseli obrazka z datasetu, mieści się w przdziale +-10% względem tego samego piksela na obrazku sprawdzanym to zaliczamy ten piskel jako poprawny
    level_of_compliance = single_pixel_counter / (shape_height * shape_width)
    # print(img_to_recognize)
    return level_of_compliance  # ostatecznie funkcja zwróci poziom zgodności obrazu img_to_recognize z tym data_image
