
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
Vehicle jest klasą abstrakcyjną reprezentującą pojazd. 

**Atrybuty**: związane są z właściwościami pojazdu (id, prędkość) oraz statusem wypożyczenia i stanem technicznym.

**Metody**: pozwalają na sprawdzenie i zmianę tych statusów i porównanie obiektów. Jest też metoda wirtualna takeOff, rozróżniająca sposób poruszania się klas dziedziczących.

**Klasy dziedziczące**: mają różne maksymalne prędkości i ceny wypozyczenia.
- Bike = Rower, wyróżniający się posiadaniem koszyka
- Scooter = Hulajnoga, którą da się złożyć
- ElectricScooter = Hulajnoga elektryczna, musi być naładowana, aby z niej korzystać
### 2. Station
### 3. Service
### 4. User
### 5. Interface






