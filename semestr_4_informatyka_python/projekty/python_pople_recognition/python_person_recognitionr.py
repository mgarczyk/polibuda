import cv2
import glob
import sewar
from skimage.metrics import structural_similarity as ssim
# moje
import pixel_by_pixel

class Person_recognition:
    def __init__(self, data_set):
            while True:
                try:
                    self.filename = str(input("Podaj nazwę pliku zawierającego obraz do porównania."
                                              "\n"))
                    break
                except ValueError:
                    print("Błędne dane")
            self.load_image_to_recognize()  #pobranie danych o obrazku do rozpoznani
            self.rmse_test()  # sprawdzamy ile elementów znalazło się w oczekiwanym przedziale rmse
            self.ssim_test()
            self.pixel_by_pixel_test()
            if (self.rmse_index and self.ssim_index) or ( self.rmse_index and self.pixel_by_pixel_index) or (self.ssim_index and self.pixel_by_pixel_index):
                self.test_passed = True
            else:
                self.test_passed = False



    def load_image_to_recognize(self):
            self.actual_img_to_recognize = cv2.imread(f'data_test/{self.filename}')  # pobieramy w skali szarości polepsza porównyanie
            dsize = (1024, 1024)
            self.actual_img_to_recognize = cv2.resize(self.actual_img_to_recognize, dsize)  # skalujemy
            self.actual_img_to_recognize = self.actual_img_to_recognize[200:900, 200:900]  # 'wycianamy' same twarze bez tła, nie zawsze trafi idealnie, ale ogółem trafia też znacznie polepasza rozpoznawanie
            cv2.imshow('image', self.actual_img_to_recognize)
            cv2.waitKey(0)
            cv2.destroyAllWindows()

    def rmse_test(self):
        self.rmse_counter = 0
        for image in data_set:
            rmse  = sewar.full_ref.rmse(image, self.actual_img_to_recognize)
            print("RMSE: ", rmse)
            if rmse < 80:   # tutaj wybieramy 'czułość' testu, typu do jakiej wartośći RMSE uznajemy że danym obrazku jest człowiek, a od ilu że już nie
                self.rmse_counter += 1
        # wskaźnik informuje nas ile % elemntów ze zbioru 'załapało' się do oczekiwanego przedału RMSE (pozwoli to określić czy dany obrazek jest zgodny czy nie)
        self.rmse_index = (self.rmse_counter / len(data_set)) * 100
        #tutaj ustalamy jaby ile procentowo elemntów ze zbioru musi zostać pozytywanie porównanych z testowym obrazkiem, żeby uznać że spełnia on założenie
        if self.rmse_index > 80:
            self.rmse_test_result = True
            print("RMSE: Zgodne")
        else:
            self.rmse_test_result = False
            print("RMSE: Niezgoddne")


    def ssim_test(self):
        self.ssim_counter = 0
        for image in data_set:
            ssim_value  = ssim(image, self.actual_img_to_recognize, channel_axis = 2)  # tutaj SSIM z bibloteki skimage, bo ten z sewar był strasznie powolny
            print("SSIM: ", ssim_value)
            if ssim_value > 0.35:  # ssim zwraca wartość  od 0,0 do 1.0 gdzie idelanie takie same to 1.0
                self.ssim_counter += 1
        self.ssim_index = (self.ssim_counter /len(data_set)) * 100 # też wskaźnik
        if self.ssim_index > 80:
            self.ssim_test_result = True
            print("SSIM: Zgodne")
        else:
            self.ssim_test_result = False
            print("SSIM: Niezgoddne")

    def pixel_by_pixel_test(self):
        self.pixel_by_pixel_counter = 0
        for image in data_set:
            pixel_by_pixel_value  = pixel_by_pixel.pixel_by_pixel_test(self.actual_img_to_recognize, image)  # wywołujemy naszą metodę
            print("pixel_pixel : ", pixel_by_pixel_value)
            if pixel_by_pixel_value >= 0.3:  # podobnie jak ssim nasz pixel_by_pixel dla tych samych obrazów zwraca 1.0
                self.pixel_by_pixel_counter += 1
        self.pixel_by_pixel_index = (self.pixel_by_pixel_counter / len(data_set)) * 100
        if self.pixel_by_pixel_index > 80:
            self.pixel_by_pixel_test_result = True
            print("pixel_by_pixel: Zgodne")
        else:
            self.rmse_test_result = False
            print("pixel_by_pixel: Niezgoddne")


def load_data_set():
    imdir = 'data_set/'
    ext = ['png', 'jpg', 'gif']    # Add image formats here
    files = []
    data_set = []
    [files.extend(glob.glob(imdir + '*.' + e)) for e in ext]  # lista plików do wczytania jako data_set
    for file in files:
        image = cv2.imread(file)  # pobieranie danych z datasetu
        image = image[200:900, 200:900]                 # 'wycinanie twarzyu
        data_set.append(image)
    # cv2.imshow('image', data_set[17])
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

      # rzeczywiste wczytanie data setu
    for image in data_set:
        image = image[200:900, 200:900]
    # cv2.imshow('image', data_set[99])
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()
    return data_set







if __name__ == '__main__':
    data_set = load_data_set()
    list_of_recognize_pictures = []
    print("Ideal RMSE: ", sewar.rmse(data_set[0], data_set[0]))
    print("Ideal SSIM: ", ssim(data_set[0], data_set[0], channel_axis = 2 ))  # nie jestem na 100 % tego pewien, ale są trzy kanały R, G, B i chyba to liczy od 0, bo jak 3 się ustawi to nie działa, można dać multichannel = True
    print("Ideal pixel_by_pixel: ", pixel_by_pixel.pixel_by_pixel_test(data_set[0], data_set[0]))
    while True:
        while True:
            try:
                choose = str(input("Czy chcesz podać zdjęcie do testu? Y/N:"
                                   "\n"))
                break
            except ValueError:
                print("Błędne dane, spróbuj ponownie")
        if choose in ['Y', 'y']:
            try:
                person_recognize = Person_recognition(data_set)
                if person_recognize.test_passed == True:
                    print("Na tym obrazku jest człowiek")
                else:
                    print("To nie jest człowiek")
                list_of_recognize_pictures.append(person_recognize)
            except cv2.error:
                print("Plik o podanej nazwie nie istnieje spróbuj ponownie.")
        else:
            print("Koniec.")
            quit()










