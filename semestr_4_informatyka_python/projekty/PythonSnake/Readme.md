# Opis
Prosty projekt mający za zadanie zapoznanie z podstawowymi możliwościami bibloteki pygame.
Cel jest realizowany poprzez implementację gry Snake przy pomocy tej bibloteki.


#Istotne informacje na temat szczegółów snake'a:

1) Cały czas patrzymy na pozycję głowy węża to ona jest śledzona, jej koordynaty są zapisywane do tablicy snake_body.
2) Na podstawie jej aktualnej pozycji, poprzednich znanych pozycji oraz prawdziwej długośći węża (len_of_snake) możemy go narysować.
3) Gdy długość snake_body (tablicy z aktualną oraz poprzednimi koordynatami głowy) przekroczy, reczywsitą długość węża,
należy usunąć pierszy elemnt z tej tablicy (jest to de facto obszar kratka za ostatnim blokiem reperzentującym ciało
węża) i narysować ponownie, co przy odpowiednim odświeżaniu (FPS) wygląda jak ruch.
