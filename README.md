
# Projekt PROI - VeloC++ity

## Główne założenia
Celem projektu jest wykonanie programu, który będzie miejskim systemem wypożyczeń pojazdów (na przykład rowerów).
Projekt będzie składać się z klas, części wykonującej określoną sekwencję procedur (odpowiadającą np. wypożyczeniu pojazdu) oraz warstwy, która będzie odpowiadać za rozmowy z użytkownikiem - w początkowej wersji w terminalu. 

Poprzez użycie poniższych klas program będzie pozwalał na przemieszczanie pojazdów między stacjami (np. poprzez wypożyczenie przez użytkownika lub przy transporcie do miejsc z większym zapotrzebowaniem na pojazdy) co skutkuje zmianą lokalizacji pojazdu, dodawanie salda użytkownika, z którego będą pobierane 'środki' na wypożyczenie pojazdu, monitorowanie stanu technicznego, położenia i statusu wypożyczenia pojazdu.

## Autorzy
    Angelika Ostrowska
    Kacper Straszak
    Adrian Murawski

## Aktualny podział zadań
    Angelika Ostrowska - klasa Vehicle
    Kacper Straszak - klasa User, Location
    Adrian Murawski - klasa Station, Service

## Struktura projektu
### 1. Vehicle
Vehicle jest klasą abstrakcyjną reprezentującą pojazd. Dostępne są różne typy pojazdów.

**Atrybuty**: związane są z właściwościami pojazdu (id, prędkość) oraz statusem wypożyczenia i stanem technicznym.

**Metody**: pozwalają na sprawdzenie i zmianę tych statusów i porównanie obiektów. Jest też metoda wirtualna takeOff, rozróżniająca sposób poruszania się klas dziedziczących.

**Klasy dziedziczące**: mają różne maksymalne prędkości i ceny wypożyczenia.
- ***Bike*** = Rower, wyróżniający się posiadaniem koszyka
- ***Scooter*** = Hulajnoga, którą da się złożyć
- ***ElectricScooter*** = Hulajnoga elektryczna, musi być naładowana, aby z niej korzystać

### 2. Station
Station jest klasą abstrakcyjną reprezentującą stację. Jest kilka rodzajów stacji różniących się rozmiarem.

**Atrybuty**: dane stacji (nazwa i kod, lokalizacja) i atrybuty związane z pojazdami (maksymalna liczba pojazdów na stacji - zależne od jej rozmiaru, wektor pojazdów będących aktualnie na stacji i sumaryczna liczba wypożyczeń z tej stacji).

**Metody**:

**a) związane z atrybutami stacji**
- wirtualna metoda z opisem stacji
- zwiększenie licznika wypożyczeń z tej stacji
- zmiana maksymalnej liczby pojazdów na stacji
- sprawdzenie i zmiana lokalizacji
- operator porównania, wypisania i wczytania ze strumienia
- sprawdzenie dostępności miejsc na stacji

**b) związane z pojazdami**
- dodanie i usunięcie pojazdu ze stacji (usuinięcie przez podanie obiektu lub indeksu pojazdu)
- sprawdzenie czy dany pojazd jest aktualnie na tej stacji
- wypisanie wszystkich aktualnych pojazdów
- iteratory po pojazdach na stacji

**Klasy dziedziczące**: 
- ***MainStation*** = Stacja główna, miejsce na 50 pojazdów, z popką do rowerów i stacją naprawczą
- ***SubStation*** = Stacja podrzędna, miejsce na 25 pojazdów, z automatem na jedzeniem i napojami
- ***LocalStation*** = Stacja lokalna, miejsce na 5 pojazdów, z telefonem alarmowym

### 3. Service
Klasa reprezentująca obsługę techniczną stacji i pojazdów.

**Atrybuty**: identyfikator i wektor obsługiwanych stacji

**Metody**:
- wyświetlenie obsługiwanych stacji
- wyświetlenie pojazdów na danej stacji
- zmiana lokalizacji i maksymalnej liczby pojazdów na stacji
- dodanie i usunięcie pojazdu ze stacji
- przeniesienie pojazdu między stacjami i sprawdzenie czy jest to możliwe
- naprawa pojazdu (ustawienie jego stanu technicznego na maksymalny)
- iteratory po obsługiwanych stacjach

**Klasy dziedziczące**:
- AdminService = nadrzędny zespół obsługi technicznej, zarządzający innymi zespołami, przydzielający im stacje, którymi mają się zajmować

### 4. User
Vehicle jest klasą abstrakcyjną reprezentującą użytkownika. Istnieje kilka poziomów konta użytkownika.

**Atrybuty**: związane z użytkownikiem (nazwa użytkownika, prawo jazdy), jego finansami (aktualny i minimalny balans, zniżka), wypożyczonymi i zarezerwowanymi urządzeniami (ich lista i maksymalna liczba) oraz aktualna lokalizacja.

**Metody**: pozwalają na zarządzanie pieniędzmi na koncie, wypożyczanie, oddawanie pojazdów, rezerwowanie ich i anulowanie rezerwacji. Umożliwiają sprawdzenie czy dany pojazd jest aktualnie wypożyczony/zarezerwowany przez tego użytkownika oraz czy użytkownik może jeszcze wypożyczyć pojazd. Istnieją też metody na zmianę lokalizacji, zwiększenie licznika wypożyczeń i wyświetlenie informacji o koncie.

**Klasy dziedziczące**: 
- ***StandardUser*** = zwykły użytkownik, bez zniżki, może zarezerwować i wypożyczyć 3 pojazdy
- ***SilverUser*** = srebrny użytkownik, ma zniżkę, może zarezerwować i wypożyczyć 4 pojazdy
- ***GoldenUser*** = złoty użytkownik, ma większą zniżkę, może zarezerwować i wypożyczyć 5 pojazdów oraz dodać prawo jazdy umożliwiające wypożyczanie pojazdów silnikowych

### 5. Location
Klasa przechowująca informacje o lokalizacji.

**Atrybuty**: dane adresowe (miasto, dystrykt, nazwa i numer ulicy) i współrzędne x,y

**Metody**: obliczenie odległości między dwoma lokacjami na podstawie współrzędnych (|x1-x2|+|y1-y2|)

### 6. Velocity
Główna klasa łącząca całą funkcjonalność. Wykorzystuje klasy Vehicle, Station, User.

**Atrybuty**: aktualny użytkownik i lista stacji

**Metody**: 

Wypożyczenie, oddanie, zarezerwowanie i anulowanie rezerwacji - zbierają w całość wszystkie kroki potrzebne do wykonania danej czynności, korzystają z odpowiednich metod stacji, użytkownika, pojazdu.

Umożliwia też dodanie balansu na koncie użytkowanika, obliczenie odległości użytkownika od wszystkich stacji i znalezienie tej najbliższej.

## Interfejs
### ServiceInterface
### UserInterface






