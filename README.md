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
cmake --build build
cmake --install build
```

## Uruchomienie programu po kompilacji
```
.\bin\PasjansGigaton.exe
```

## Instrukcja obsługi gry
Całość instrukcji zawarta jest w komendzie 'i' w grze.