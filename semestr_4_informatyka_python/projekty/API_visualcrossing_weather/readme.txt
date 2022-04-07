Aplikacja pozwala na pobieranie danych o pogodzie w opraciu o API visualcrossing, dane mogą być pobierane bezpośrednio po
nazwie miasta lub po koordynatach geogeraficznych (wtedy są one tłumaczone na nazwę miasta na podstawie
pliku csv ze strony (https://simplemaps.com/data/world-cities) przkonwertowanego na json), w opraciu o te dane wyświetlane są
wykresy temperatury w danym mieście.
Wymagane bibloteki:
- os (podstawowa)
- json (podstawowa)
- datetime (podstawowa)
- requests (terminal/pip install requests)
- matplotlib (terminal/pip install matplotlib)



Więcej informacji:
Projekt - wykres temperatury w czsie iluś dni w danym mieście - wybranym
1) Znaleźć API pogodowe:
	a) Autoryzacja - wo dokumentacji API (założenie konta czy coś) - najczęśćiej klucz w headers/url param
	b) Udostępnia endpoint (minimum - długość i szerokość geograficzna)
	c) można korzystać z API jak są ograniczenia - może być konieczne utworzenia nowego maila (np. 1000 requestów na dzień)

2) Przechowywanie danych (storage - database) - N plików z nazwą maista a w nich
	a) plik json (nazwa pliku - to nazwa miasta):

3) Przejście z nazwy miasta na szerokość i długość geograficzną
	a)Może być API, które zwróci szerokość/długość podanego miasta.
	b)Albo znaleźć bazę danych gdzie będzie to podane do danego miasta.
	c)Można znaleźć API które nie będzie szukać po szerokośći i długości geograficznej, a po nazwie miasta (najłatwiej chyba)

4) Wykres - MATPLOTLIB - wykres temperatury od daty

5) User:
	a) pobiera dane /get:
		-albo po nazwie
		-albo po szerokości i długości
	b) wyświetla /disp
		-wykres (trzeba podać zakres dat do wystarczenia)
	c) /end - kończy działanie




