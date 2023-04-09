# Projekt PROI - “Angry Birds Remake”:

## Spis treści
* [Ogólne informacje](#ogólne-informacje)
* [Założenia gry](#założenia-gry)
* [Założenia edytora poziomów](#założenia-edytora-poziomów)
* [Główne klasy](#główne-klasy)
* [Klasy poboczne](#klasy-poboczne)

---

## Ogólne informacje
Autorzy:
- Piotr Patek
    * e-mail: piotr.patek.stud@pw.edu.pl
    * gitlab: @ppatek

- Jakub Wróblewski
    * e-mail: jakub.wroblewski4.stud@pw.edu.pl
    * gitlab: @jwroblew


## Wykorzystywane narzędnia i biblioteki
- SFML - interfejs graficzny oraz interfejs użytkownika + audio
- Box2D - silnik fizyczny


## Ogólne założenia:
Stworzenie dwóch oddzielnych aplikacji:
gra przypominająca swoją funkcjonalnością popularne “Angry Birds”
edytor poziomów do powyższej gry


## Założenia gry:
Gra przypominająca “Angry Birds” składająca się z kilkunastu poziomów z możliwością rozbudowy o nowe poziomy za pomocą edytora poziomów. Poziomy przy tworzeniu w edytorze zapisywane są do plików, a następnie, w trakcie działania gry, są odpowiednio do niej wczytywane. Plik zawiera informacje o rozmieszczeniu bloków, ich rodzaju oraz pozycji początkowej gracza.

W oknie mieści się cały poziom, nie używamy przesuwającej się kamery.
Możliwość zaprogramowania różnego rodzaju “ptaków”:
Czerwony - podstawowy
Żółty - szybki
Czarny - bomba
…
Możliwość dodawania różnych “świń”, o różnych rozmiarach i zdrowiu,
Możliwość dodawania różnych materiałów - drewno, kamień, szkło itp. Każdy materiał ma inną odporność na uderzenia,
System przyznawania punktów na podstawie zniszczeń i ilości niewystrzelonych ptaków.

## Założenia edytora poziomów:
Edytor umożliwia tworzenie poziomów. Przy tworzeniu poziomu ustawiamy bloki, świnie, pozycję początkową gracza, a także wybieramy jakie ptaki są dostępne dla gracza na danym poziomie.

## Główne klasy:
- `class Game` - główna klasa Gry
    metody:
    - `game.run(...)`
    - `game.setup(...)`
    - ...

- `class LevelEditor` - główna klasa Edytora Poziomów

## Klasy poboczne:
- `class Interface` - obsługująca SFML, rendering, user I/O

- `class UserIO` - klasa działająca w ramach interfejsu

- `class Graphics` - klasa działająca w ramach interfejsu

- `class File` - obsługuje zapis do pliku, odczyt z pliku (może będzie strukturą?)
    metody:
    - `file.load(...)`
    - `file.write(...)`
    - ...

- `class Level` - logika gry i poziomu, Box2D, wczytywania z pliku
    - funkcja `create_level(...)`
    - metoda `calculate_damage(...)`
    - ...

- `class Bird` - ogólna klasa dla ptaków
    parametry:
    - `speed`
    - `health`
    - `mass`
    - `size`
    - ...


Plus klasy dla innych typów ptaków, różniące się umiejętnościami specjalnymi

- `class Pig` - ogólna klasa dla świń
    parametry:
    - `position`
    - `health`
    - `armor`
    - `mass`
    - `size`
    - ...


Plus klasy dla innych typów świń

- `class DynamicBlock` - ogólne właściwości bloków dynamicznych (!)
    parametry:
    - `position`
    - `material`
    - `health`
    - `mass`
    - `size`
    - ...

- `class StaticBlock` - ogólne właściwości dla bloków statycznych
    parametry:
    - `position`
    - `size`
    - ...

- `class Slingshot` - klasa dla procy (?)
    parametry:
    - `position`
    - ...

- `class/method ScoringSystem` (?)

