# PasjansGigaton
 
## Wymagania wstępne
- [Narzędzia Visual Studio 2022](https://download.visualstudio.microsoft.com/download/pr/d99c7868-44a2-4254-9861-78e21c19bd34/d108dd0ed60e91cb38e1c0abe42f23f39c0b15adecdcef6961e9034a6d49dc3e/vs_BuildTools.exe)
- [CMake](https://github.com/Kitware/CMake/releases/download/v4.0.2/cmake-4.0.2-windows-x86_64.msi)
- [vcpkg](https://github.com/microsoft/vcpkg) (Należy sklonować repozytorium, a następnie uruchomić plik bootstrap-vcpkg.bat)

## Instrukcje kompilacji
UWAGA! Należy wpisać ścieżkę, gdzie zainstalowano vcpkg **na danym komputerze**.
Przykładowo: `C:\Users\Uzytkownik\vcpkg\scripts\buildsystems\vcpkg.cmake`
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=sciezka_do_folderu_vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build --config Release
cmake --install build
```

## Uruchomienie programu po kompilacji
Komendy zakładają korzystanie z powłoki Powershell, w przypadku innej powłoki należy zmienić katalog odpowiadającą komendą. Odpowiedni katalog jest kluczowy dla wyświetlania rankingu.
```
cd bin
.\PasjansGigaton.exe
```

## Instrukcja obsługi gry

### Wstęp
Gra nie posiada argumentów wywoływanych w konsoli.
Przy uruchomieniu gra wyświetla Top 10 wyników w rankingu.
Następnie gracz proszony jest o wybór poziomu trudności, wpisując 'n' dla normalnego albo 't' dla trudnego.

### Opis poleceń

Lista poleceń jest również dostępna w grze pod komendą 'i'
- [i]nstrukcja, lista dostępnych poleceń
- [p]rzesuń, używane do przesuwania kart na planszy
- [d]obierz, dobieranie karty ze stosu
- [o]dłuż, odłuż kartę z jednej z kolumn bądź stosu na stos odkładania
- [n]owa gra
- [c]ofnij ruch

### Koniec gry

Gra kończy się w momencie, kiedy wszystkie karty znalazły się na stosie odkładania.
Gra wywołuje wtedy komunikat informujący użytkownika o wygranej.
Wypisany jest wtedy zaktualizowany ranking, a program kończy działanie.

## Dokumentacja techniczna
Opis kodu (tzn. funkcji, zmiennych itd.) znajduje się w komentarzach w kodzie (src\main.cpp).

### Biblioteki
- `nowide` biblioteka umożliwiająca łatwe oraz przenośne wypisywanie znaków unicode,
           implementuje nagłówki z biblioteki standardowej c++ w wersji zgodnej z unicode
