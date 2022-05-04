import mysql.connector
class configuration:
    def __init__(self):
        config = {
            'user': 'root',
            'password': 'Kamera97',
            'host': '127.0.0.1',
            'database': 'cars_db',
            'raise_on_warnings': True
        }

        try:
            self.cnx = mysql.connector.connect(**config)
        except mysql.connector.Error:
            print("Błąd podczas łączenia się z bazą danych, spróbuj poprawić hasło lub nazwę użytkownika.")
        self.cursor = self.cnx.cursor()
