import re
def config():
    host = "127.0.0.1"
    port = 9999
    """
    # IP adres
    while True:
        try:
            host = str(input("Podaj adres IPv4 do połączenia: "
                             "\n"))
            if not re.match(r"^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$", host): # walidacja adresu ip, za pomocą wyrażenia regilarnego (adres IPv4
                raise ValueError
            break
        except ValueError:
            print("Podano błędny adres, spróbuj ponownie")
    # port
    while True:
        try:
            port = int(input("Podaj numer portU:"
                             "\n"))
            if port < 9999 and port > 65.535:
                raise ValueError
            else:
                break
        except ValueError:
            print("Podano nieprawidłowy numer portu")
    """
    return host, port