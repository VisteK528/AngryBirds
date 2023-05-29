# Projekt PROI - “Angry Birds Remake”:

## Spis treści
* [Ostatni update](#ostatni-update)
* [Informacje o autorach](#informacje-o-autorach)
    * [Wykorzystywane narzędzia i biblioteki](#wykorzystywane-narzędzia-i-biblioteki)
* [Instalacja](#instalacja)
    * [Linux](#linux)
    * [macOS](#macos)
* [Ogólne założenia](#ogólne-założenia)
* [Założenia gry](#założenia-gry)
    * [Jak grać?](#jak-grać)
    * [Sterowanie](#sterowanie)
* [Założenia edytora poziomów](#założenia-edytora-poziomów)
    * [Jak edytować?](#jak-edytować)
        * [Akcje w pasku narzędziowym](#akcje-w-pasku-narzędziowym)
        * [Akcje w oknie gry](#akcje-w-oknie-gry)
        * [Zapisywanie i wczytywanie](#zapisywanie-i-wczytywanie)
* [Struktura projektu](#struktura-projektu)
* [Źródła](#źródła)

---
## Ostatni update
Ostatnie rzeczy, która została zmieniona w projekcie to:
* dodano dźwięki
* poprawiono menu
* naprawiono błędy w grze


## Informacje o autorach
Autorzy:
- Piotr Patek
    * e-mail: piotr.patek.stud@pw.edu.pl
    * gitlab: @ppatek

- Jakub Wróblewski
    * e-mail: jakub.wroblewski4.stud@pw.edu.pl
    * gitlab: @jwroblew


### Wykorzystywane narzędnia i biblioteki
- **SFML** - interfejs graficzny oraz interfejs użytkownika + audio
- **Box2D** - silnik fizyczny
- **Catch2** - testy jednostkowe
- **nlohmann/json** - biblioteka obsługująca parsowanie plików `.json`


## Instalacja
Aby zainstalować projekt, należy sklonować repozytorium i zbudować projekt za pomocą `CMake`. Wymagane jest posiadanie biblioteki **SFML** w wersji 2.5.1 oraz **Box2D** w wersji 2.4.1. W przypadku problemów z kompilacją, należy sprawdzić czy ścieżki do bibliotek są poprawnie ustawione w pliku `CMakeLists.txt`.

```bash
git clone --recurse-submodules -j8 https://gitlab-stud.elka.pw.edu.pl/ppatek/angrybirds.git
cd angrybirds
mkdir build
cd build
cmake ..
make
```

Aby skompilować projekt, należy wcześniej zainstalować **SFML**. W zależności od używanego systemu operacyjnego można to zrobić, wpisując:
### Linux
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```
### macOS
Na macOS zalecane jest użycie `brew` do zainstalowania **SFML**. Tutaj można zdobyć więcej informacji nt. instalacji `brew` na swoim urządzeniu: [https://brew.sh/](https://brew.sh/)
```bash
brew install sfml
```

Jeżeli **SFML** jest już zainstalowany na komputerze, powinien być do odnalezienia pod tą ścieżką w zależności od systemu operacyjnego:
* **Linux:** `/usr/include/SFML`
* **macOS:** `/opt/homebrew/Cellar/sfml/2.5.1_2/include`


## Ogólne założenia:
Zgodnie z założeniami projektu zrealizowano grę 2D, przypominającą swoją funkcjonalnością popularne “Angry Birds”, z zaimplementowanym silnikiem fizycznym oraz interfejsem graficznym.
Aplikacja posiada ponadto możliwość edycji poziomów oraz posiada warstwę trwałości poprzez umożliwianie zapisu oraz odczytu poziomu do i z pliku `.json`

<img align="center" width="100%" src="textures/readme/ab_menu.png">

## Założenia gry:
Gra “Angry Birds Remake” składa się z kilkunastu poziomów z możliwością rozbudowy o nowe poziomy za pomocą edytora poziomów. Poziomy przy tworzeniu w edytorze zapisywane są do plików `.json`, a następnie, w trakcie działania gry, są odpowiednio do niej wczytywane. Plik zawiera informacje o wybranej mapie, rozmieszczeniu bloków i świń oraz ich rodzaju, a także o puli dostępnych na tym poziomie ptaków.

### Jak grać?
W grze mamy dostępne dwa tryby:
- **adventure** - tryb przygodowy, w którym gracz ma do przejścia 14 predefiniownych poziomów, z których każdy jest trudniejszy od poprzedniego.
- **custom** - tryb, w którym gracz może grać we własnoręcznie stworzone poziomy. Dostępnych jest 5 miejsc na zapisane poziomy.

Zbijając bloki lub świnie przyznawane są punkty, których ilość jest widoczna w prawym górnym rogu gry, a także po przejściu poziomu w oknie z rezultatami. Po wystrzeleniu wszystkich ptaków, gracz może zrestartować poziom lub przejść do następnego. Warunkiem sukcesu jest pokonanie wszystkich świń na planszy. W przypadku przejścia wszystkich poziomów, gracz zostaje przeniesiony do menu głównego.

<figure class="video_container">
  <video controls="false" allowfullscreen="false" poster="textures/readme/ab_game.gif" width="100%" autoplay loop muted>
    <source src="textures/readme/game.mp4" type="video/mp4">
    <source src="textures/readme/game.webm" type="video/webm">
    <img align="center" width="100%" src="textures/readme/ab_game.gif">
  </video>
</figure>

### Sterowanie:
- **myszka** - ustawienie kąta strzału
- **lewy przycisk myszy** - wystrzelenie ptaka (przytrzymanie myszki powoduje zwiększenie siły strzału)
- **prawy przycisk myszy** - aktywacja umiejętności specjalnej ptaka (jeśli jest dostępna)
- **środkowy przycisk myszy** - zmiana ptaka (jeśli jest dostępny inny ptak)
- **klawisz Escape** - powrót do menu

## Założenia edytora poziomów:
Edytor poziomów to część głównej aplikacji. Całość działa w graficznym interfejsie użytkownika. Możliwe jest w nim tworzenie nowych poziomów lub edycja aktualnie istniejących plansz. W te poziomy możemy grać w trybie "Custom".

### Jak edytować?
W edytorze mamy dostępnych kilka narzędzi:
- **blok** - dodaje blok do planszy
- **świnia** - dodaje świnie do planszy
- **ptak** - dodaje ptaka do puli dostępnych ptaków
- **zmiana tła** - zmienia tło planszy

<figure class="video_container">
  <video controls="false" allowfullscreen="false" poster="textures/readme/ab_editor.gif" width="100%" autoplay loop muted>
    <source src="textures/readme/editor.mp4" type="video/mp4">
    <source src="textures/readme/editor.webm" type="video/webm">
    <img align="center" width="100%" src="textures/readme/ab_editor.gif">
  </video>
</figure>

#### Akcje w pasku narzędziowym:
- **lewy przycisk myszy** - wybór danego bloku, świnii lub ptaka
- **prawy przycisk myszy** - zmiana typu bloku, świnii lub ptaka

#### Akcje w oknie edytora:
- **lewy przycisk myszy** - dodanie bloku, świnii lub ptaka do planszy, w zależności od wyboru w pasku narzędziowym
- **przeciągnięcie myszy** - przesunięcie bloku lub świnii po planszy
- **prawy przycisk myszy** - usunięcie bloku, świnii lub ptaka z planszy
- **środkowy przycisk myszy / klawisz R** - obrót bloku, świnii lub ptaka

#### Zapisywanie i wczytywanie:
- **strzałka w górę** - zwiekszenie numeru zapisanego poziomu
- **strzałka w dół** - zmniejszenie numeru zapisanego poziomu
- **zapisywanie** - po wybraniu opcji zapisz, poziom zostaje zapisany do pliku `.json`
- **wczytywanie** - po wybraniu opcji wczytaj, poziom zostaje wczytany z pliku `.json`

## Struktura projektu

Całość aplikacji działa na zasadzie automatu o skończonej liczbie stanów. W zależności od aktualnego stanu do programu ładowane są odpowiednie zasoby, a aplikacja wyświetla inne okno. Wszystkie okna dziedziczą po klasie `State`, która jest klasą abstrakcyjną. Wszystkie okna są przechowywane w kontenerze `std::vector<std::unique_ptr<State>> states`, który jest zmienną składową klasy `Game`. W zależności od aktualnego stanu, wyświetlane jest odpowiednie okno. Wszystkie okna są wyświetlane w pętli `while` w funkcji `Game::run()`. W każdej iteracji pętli, aktualne okno jest rysowane na ekranie, a następnie sprawdzane jest, czy nastąpiła zmiana stanu. Jeśli tak, to następuje usunięcie aktualnego okna i dodanie nowego okna do kontenera `states`. Wszystkie okna są przechowywane w kontenerze `std::unique_ptr`, dzięki czemu nie musimy się martwić o ich zwalnianie z pamięci. Wszystkie okna są tworzone w funkcji `Game::init()`.

W aplikacji wykorzystywane są menedżery, które są odpowiedzialne za zarządzanie danymi. W aplikacji wykorzystywane są 3 menedżery:
- `entity_manager` - zarządza wszystkimi obiektami, które są wyświetlane na ekranie. Wszystkie obiekty dziedziczą po klasie `Entity`, która jest klasą abstrakcyjną. Wszystkie obiekty są przechowywane w kontenerze `std::vector<std::unique_ptr<Entity>> entities`.
- `gui_manager` - zarządza wszystkimi obiektami, które są wyświetlane na ekranie. Za pomocą niego tworzone są wszystkie przyciski i teksty, które są wyświetlane na ekranie.
- `sound_manager` - zarządza wszystkimi dźwiękami, które są wykorzystywane w aplikacji.

W aplikacji zrealizowano kreacyjny wzorzec projektowy fabryki. Ponadto w celu optymalizacji kodu nie tworzono oddzielnych klas fabryk dla każdego rodzaju `Entity`, tylko zdecydowano się na wykorzystanie szablonów. Dostępne są 3 fabryki, które są odpowiedzialne za tworzenie obiektów:
- `bird_factory` - to fabryka, która jest odpowiedzialna za tworzenie ptaków. Wszystkie ptaki dziedziczą po klasie `Bird`, która jest klasą abstrakcyjną.
- `box_factory` - to fabryka, która jest odpowiedzialna za tworzenie bloków. Wszystkie bloki dziedziczą po klasie `Box`, która jest klasą abstrakcyjną.
- `pig_factory` - to fabryka, która jest odpowiedzialna za tworzenie świń. Wszystkie świnie dziedziczą po klasie `Pig`, która jest klasą abstrakcyjną.

## Źródła:
Czcionka użyta w projekcie została wykonana przez Gangetsha Lyx i jest udostępniona na licencją CC BY-SA 3.0.

Muzyka i dźwięki zostały zaczerpnięte z gry "Angry Birds" firmy Rovio Entertainment Corporation oraz z gry "Bad Piggies" firmy Rovio Entertainment Corporation.

Tekstury są inspirowane na dostępnych w internecie grafikach.

Wszystkie zasoby są wykorzystywane do celów edukacyjnych i nie są wykorzystywane w celach komercyjnych.