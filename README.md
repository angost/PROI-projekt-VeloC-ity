
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

**Klasy dziedziczące**: mają różne maksymalne prędkości i ceny wypozyczenia.
- ***Bike*** = Rower, wyróżniający się posiadaniem koszyka
- ***Scooter*** = Hulajnoga, którą da się złożyć
- ***ElectricScooter*** = Hulajnoga elektryczna, musi być naładowana, aby z niej korzystać
### 2. Station

### 3. Service
### 4. User
Vehicle jest klasą abstrakcyjną reprezentującą użytkownika. Istnieje kilka poziomów konta użytkownika.

**Atrybuty**: związane z użytkownikiem (nazwa użytkownika, prawo jazdy), jego finansami (aktualny i minimalny balans, zniżka), wypożyczonymi i zarezerwowanymi urządzeniami (ich lista i maksymalna liczba) oraz aktualna lokalizacja.

**Metody**: pozwalają na zarządzanie pieniędzmi na koncie, wypożyczanie, oddawanie pojazdów, rezerwowanie ich i anulowanie rezerwacji. Umożliwiają sprawdzenie czy dany pojazd jest aktualnie wypożyczony/zarezerwowany przez tego użytkownika oraz czy użytkownik może jeszcze wypożyczyć pojazd. Istnieją też metody na zmianę lokalizacji, zwiększenie licznika wypożyczeń i wyświetlenie informacji o koncie.

**Klasy dziedziczące**: 
- ***StandardUser*** = zwykły użytkownik, bez zniżki, może zarezerwować i wypożyczyć 3 pojazdy
- ***SilverUser*** = srebrny użytkownik, ma zniżkę, może zarezerwować i wypożyczyć 4 pojazdy
- ***GoldenUser*** = złoty użytkownik, ma większą zniżkę, może zarezerwować i wypożyczyć 5 pojazdów oraz dodać prawo jazdy umożliwiające wypożyczanie pojazdów silnikowych
### 5. Interface






