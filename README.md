# Projekt PROI - “Angry Birds Remake”:

## Spis treści
* [Ostatni update](#ostatni-update)
* [Ogólne informacje](#ogólne-informacje)
* [Instalacja](#instalacja)
* [Ogólne założenia](#ogólne-założenia)
* [Założenia gry](#założenia-gry)
    * [Jak grać?](#jak-grać)
    * [Sterowanie](#sterowanie)
* [Założenia edytora poziomów](#założenia-edytora-poziomów)
    * [Jak edytować?](#jak-edytować)
        * [Akcje w pasku narzędziowym](#akcje-w-pasku-narzędziowym)
        * [Akcje w oknie gry](#akcje-w-oknie-gry)
        * [Zapisywanie i wczytywanie](#zapisywanie-i-wczytywanie)

---
## Ostatni update
Ostatnie rzeczy, która została zmieniona w projekcie to:
* dodano ...
* poprawiono ...


## Ogólne informacje
Autorzy:
- Piotr Patek
    * e-mail: piotr.patek.stud@pw.edu.pl
    * gitlab: @ppatek

- Jakub Wróblewski
    * e-mail: jakub.wroblewski4.stud@pw.edu.pl
    * gitlab: @jwroblew


### Wykorzystywane narzędnia i biblioteki
- SFML - interfejs graficzny oraz interfejs użytkownika + audio
- Box2D - silnik fizyczny


## Instalacja
Aby zainstalować projekt, należy sklonować repozytorium i zbudować projekt za pomocą CMake. Wymagane jest posiadanie biblioteki SFML w wersji 2.5.1 oraz Box2D w wersji 2.4.1. W przypadku problemów z kompilacją, należy sprawdzić czy ścieżki do bibliotek są poprawnie ustawione w pliku CMakeLists.txt.

## Ogólne założenia:
Stworzenie aplikacji przypominającej swoją funkcjonalnością popularne “Angry Birds”
wraz z wbudowanym edytorem poziomów do powyższej gry.

<img align="center" width="100%" src="textures/readme/ab_menu.png">

## Założenia gry:
Gra “Angry Birds Remake” składa się z kilkunastu poziomów z możliwością rozbudowy o nowe poziomy za pomocą edytora poziomów. Poziomy przy tworzeniu w edytorze zapisywane są do plików `.json`, a następnie, w trakcie działania gry, są odpowiednio do niej wczytywane. Plik zawiera informacje o wybranej mapie, rozmieszczeniu bloków i świń oraz ich rodzaju, a także o puli dostępnych na tym poziomie ptaków.

### Jak grać?
W grze mamy dostępne dwa tryby:
- adventure - tryb przygodowy, w którym gracz ma do przejścia 14 predefiniownych poziomów, z których każdy jest trudniejszy od poprzedniego.
- custom - tryb, w którym gracz może grać we własnoręcznie stworzone poziomy. Dostępnych jest 5 miejsc na zapisane poziomy.

Zbijając bloki lub świnie przyznawane są punkty, których ilość jest widoczna w prawym górnym rogu gry, a także po przejściu poziomu w oknie z rezultatami. Po wystrzeleniu wszystkich ptaków, gracz może zrestartować poziom lub przejść do następnego. Warunkiem sukcesu jest pokonanie wszystkich świń na planszy. W przypadku przejścia wszystkich poziomów, gracz zostaje przeniesiony do menu głównego.

<figure class="video_container">
  <video controls="false" allowfullscreen="false" poster="textures/readme/ab_game.gif" width="100%" autoplay loop muted>
    <source src="textures/readme/game.mp4" type="video/mp4">
    <source src="textures/readme/game.webm" type="video/webm">
    <img align="center" width="100%" src="textures/readme/ab_game.gif">
  </video>
</figure>

### Sterowanie:
- myszka - ustawienie kąta strzału
- lewy przycisk myszy - wystrzelenie ptaka (przytrzymanie myszki powoduje zwiększenie siły strzału)
- prawy przycisk myszy - aktywacja umiejętności specjalnej ptaka (jeśli jest dostępna)
- środkowy przycisk myszy - zmiana ptaka (jeśli jest dostępny inny ptak)
- klawisz ESC - powrót do menu

## Założenia edytora poziomów:
Edytor poziomów to część głównej aplikacji. Całość działa w graficznym interfejsie użytkownika. Możliwe jest w nim tworzenie nowych poziomów lub edycja aktualnie istniejących plansz. W te poziomy możemy grać w trybie "Custom".

### Jak edytować?
W edytorze mamy dostępnych kilka narzędzi:
- blok - dodaje blok do planszy
- świnia - dodaje świnie do planszy
- ptak - dodaje ptaka do puli dostępnych ptaków
- zmiana tła - zmienia tło planszy

<figure class="video_container">
  <video controls="false" allowfullscreen="false" poster="textures/readme/ab_editor.gif" width="100%" autoplay loop muted>
    <source src="textures/readme/editor.mp4" type="video/mp4">
    <source src="textures/readme/editor.webm" type="video/webm">
    <img align="center" width="100%" src="textures/readme/ab_editor.gif">
  </video>
</figure>

#### Akcje w pasku narzędziowym:
- lewy przycisk myszy - wybór danego bloku, świnii lub ptaka
- prawy przycisk myszy - zmiana typu bloku, świnii lub ptaka

#### Akcje w oknie gry:
- lewy przycisk myszy - dodanie bloku, świnii lub ptaka do planszy
- przeciągnięcie myszy - przesunięcie bloku lub świnii po planszy
- prawy przycisk myszy - usunięcie bloku, świnii lub ptaka z planszy
- środkowy przycisk myszy - obrót bloku, świnii lub ptaka

#### Zapisywanie i wczytywanie:
- strzałka w górę - zwiekszenie numeru zapisanego poziomu
- strzałka w dół - zmniejszenie numeru zapisanego poziomu
- zapisywanie - po wybraniu opcji zapisz, poziom zostaje zapisany do pliku `.json`
- wczytywanie - po wybraniu opcji wczytaj, poziom zostaje wczytany z pliku `.json`
