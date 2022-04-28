Założenia:
Tworzymy relacyjną bazę danych, zawierającą pojazdy i ich właścicieli
zakładam, że jeden właściciel, może mieć wiele pojazdów, ale dany pojazd
zawsze należy do jednego właściciela. Tworzymy identyfikatory,
rozróżnające pojazdy, tak samo robimy dla właścicieli, część informacji o właścicielach
zawieramy w numeru PESEL (data urodzenia, wiek, płeć).

Bazę tworzymy za pomocą MySQL, ręcznie w skrypcie .sql

Wpisujemy w ten sposób kilku właścicieli i pojazdy.

Resztę daych wpisujemy, za pomocą skryptu w Pythonie, korzystając z bibloteki sql_connector_puthon.

Użytkownik, ma mieć możliwość wpisania zarówno pojazdu, jak i użytkownika do bazy, dodajemy też wyświetlanie.

Wykorzystano też biblotekę pesel_utils, do sprawdzania numerów PESEL.