#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct karta {
  /*
  wartosc numeryczna karty
  as = 1
  2...10 = odpowiadajaca wartosc
  Walet = 11
  Dama = 12
  Krol = 13
  */
  int wartosc;

  // pomocniczna zmienna do wypisywania
  std::string symbol;

  // 0 = kier, 1 = karo, 2 = pik, 3 = trefl
  int kolor;

  // false = czarny, true = czerwony
  bool barwa;

  bool czy_odkryta;
};
std::vector<karta> karty = {
    // kier
    {1, "♥️ A ", 0, true, false},
    {2, "♥️ 2 ", 0, true, false},
    {3, "♥️ 3 ", 0, true, false},
    {4, "♥️ 4 ", 0, true, false},
    {5, "♥️ 5 ", 0, true, false},
    {6, "♥️ 6 ", 0, true, false},
    {7, "♥️ 7 ", 0, true, false},
    {8, "♥️ 8 ", 0, true, false},
    {9, "♥️ 9 ", 0, true, false},
    {10, "♥️ 10", 0, true, false},
    {11, "♥️ J ", 0, true, false},
    {12, "♥️ Q ", 0, true, false},
    {13, "♥️ K ", 0, true, false},
    // karo
    {1, "♦️A  ", 1, true, false},
    {2, "♦️2  ", 1, true, false},
    {3, "♦️3  ", 1, true, false},
    {4, "♦️4  ", 1, true, false},
    {5, "♦️5  ", 1, true, false},
    {6, "♦️6  ", 1, true, false},
    {7, "♦️7  ", 1, true, false},
    {8, "♦️8  ", 1, true, false},
    {9, "♦️9  ", 1, true, false},
    {10, "♦️10 ", 1, true, false},
    {11, "♦️J  ", 1, true, false},
    {12, "♦️Q  ", 1, true, false},
    {13, "♦️K  ", 1, true, false},
    // pik
    {1, "♠️A  ", 2, false, false},
    {2, "♠️2  ", 2, false, false},
    {3, "♠️3  ", 2, false, false},
    {4, "♠️4  ", 2, false, false},
    {5, "♠️5  ", 2, false, false},
    {6, "♠️6  ", 2, false, false},
    {7, "♠️7  ", 2, false, false},
    {8, "♠️8  ", 2, false, false},
    {9, "♠️9  ", 2, false, false},
    {10, "♠️10 ", 2, false, false},
    {11, "♠️J  ", 2, false, false},
    {12, "♠️Q  ", 2, false, false},
    {13, "♠️K  ", 2, false, false},
    // trefl
    {1, "♣️A  ", 3, false, false},
    {2, "♣️2  ", 3, false, false},
    {3, "♣️3  ", 3, false, false},
    {4, "♣️4  ", 3, false, false},
    {5, "♣️5  ", 3, false, false},
    {6, "♣️6  ", 3, false, false},
    {7, "♣️7  ", 3, false, false},
    {8, "♣️8  ", 3, false, false},
    {9, "♣️9  ", 3, false, false},
    {10, "♣️10 ", 3, false, false},
    {11, "♣️J ", 3, false, false},
    {12, "♣️Q  ", 3, false, false},
    {13, "♣️K  ", 3, false, false}};

std::vector<karta> kolumny[8];
std::vector<karta> stos_dobierania;
std::vector<int> stos_odkladania = {0, 0, 0, 0};

void przygotuj_gre() {
  // Przygotowanie gry
  // Losowanie kolejnosci kart
  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};
  std::shuffle(karty.begin(), karty.end(), rng);

  // Ulozenie kart na stosy
  int licznik = 0;
  for (int i = 1; i <= 7; i++) {
    int obecny_licznik = licznik;
    for (int j = licznik; j < obecny_licznik + i; j++) {
      kolumny[i - 1].push_back(karty[j]);
      licznik++;
    }
    kolumny[i - 1][i - 1].czy_odkryta = true;
  }

  for (int i = 28; i < 52; i++) {
    stos_dobierania.push_back(karty[i]);
  }
}

void wyswietl_plansze() {
  std::cout << std::endl << "------------------\n";
  for (int i = 0; i < 7; i++) {
    std::cout << i + 1 << ". ";
    for (auto j : kolumny[i]) {
      if (j.czy_odkryta) {
        std::cout << j.symbol;
      } else {
        std::cout << "? ";
      }
    }
    std::cout << '\n';
  }
  std::cout << "Stos Odkladania\n";
  std::cout << "♥️ " << stos_odkladania[0] << ' ' << "♦️" << stos_odkladania[1]
            << ' ' << "♠️" << stos_odkladania[2] << ' ' << "♣️"
            << stos_odkladania[3] << '\n';

  std::cout << "Stos dobierania\n8.";
  for (auto i : kolumny[7]) {
    std::cout << i.symbol << ' ';
  }
  std::cout << '\n';
}

void pomoc() {
  std::cout << std::endl << "Dostępne polecenia:" << std::endl;
  std::cout << "[i]nstrukcja, lista dostępnych poleceń" << std::endl;
  std::cout << "[p]rzesuń, używane do przesuwania kart na planszy" << std::endl;
  std::cout << "[d]obierz, dobieranie karty ze stosu" << std::endl;
  std::cout << "[o]dłuż, odłuż kartę z jednej z kolumn bądź stosu na stos odkładania" << std::endl;
  char t;
  do {
    std::cout << "Wpisz 't', jeśli chcesz wyjść z instrukcji: ";
    std::cin >> t;
  } while (t != 't');
}

void przesun() {
  int kolumna_poczotkowa;
  int kolumna_docelowa;
  int liczba_kart = 1;
  // 1-7 zrozumiałe, 8 - stos dobierania
  std::cout << "Wybierz kolumnę początkową: ";
  std::cin >> kolumna_poczotkowa;
  kolumna_poczotkowa--;
  if (std::cin.fail() || kolumna_poczotkowa < 0 || kolumna_poczotkowa > 7) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  std::cout << "Wybierz kolumnę docelową: ";
  std::cin >> kolumna_docelowa;
  kolumna_docelowa--;
  if (std::cin.fail() || kolumna_docelowa < 0 || kolumna_docelowa > 6 ||
      kolumna_poczotkowa == kolumna_docelowa) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  if (kolumna_poczotkowa != 7) {
    std::cout << "Wybierz liczbę kart: ";
    std::cin >> liczba_kart;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }
  }
  if (liczba_kart <= kolumny[kolumna_poczotkowa].size()) {
    int pierwsza_karta = kolumny[kolumna_poczotkowa].size() - liczba_kart;
    int ostatnia_karta = kolumny[kolumna_docelowa].size() - 1;
    if ((kolumny[kolumna_poczotkowa][pierwsza_karta].barwa !=
             kolumny[kolumna_docelowa][ostatnia_karta].barwa &&
         kolumny[kolumna_poczotkowa][pierwsza_karta].wartosc + 1 ==
             kolumny[kolumna_docelowa][ostatnia_karta].wartosc &&
         kolumny[kolumna_poczotkowa][pierwsza_karta].czy_odkryta) ||
        (kolumny[kolumna_poczotkowa][pierwsza_karta].wartosc == 13 &&
         kolumny[kolumna_docelowa].empty())) {
      for (int i = 0; i < liczba_kart; i++) {
        kolumny[kolumna_docelowa].push_back(
            kolumny[kolumna_poczotkowa][pierwsza_karta]);
        kolumny[kolumna_poczotkowa].erase(kolumny[kolumna_poczotkowa].begin() +
                                          pierwsza_karta);
      }
      if (kolumna_poczotkowa != 7 && !kolumny[kolumna_poczotkowa].empty()) {
        kolumny[kolumna_poczotkowa].back().czy_odkryta = true;
      }
    }
  }
}

void dobierz() {
  if (!stos_dobierania.empty()) {
    kolumny[7].push_back(stos_dobierania.back());
    kolumny[7].back().czy_odkryta = true;
    stos_dobierania.pop_back();
  } else {
    for (auto i : kolumny[7]) {
      stos_dobierania.insert(stos_dobierania.begin(), i);
      stos_dobierania.front().czy_odkryta = false;
      kolumny[7].pop_back();
    }
  }
}

void odloz_karte() {
  int kolumna;
  std::cout << "\n Wpisz kolumnę z której chcesz odłożyć kartę: ";
  std::cin >> kolumna;
  kolumna--;
  if (std::cin.fail() || kolumna < 0 || kolumna > 7) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  if (kolumny[kolumna].back().wartosc - 1 ==
      stos_odkladania[kolumny[kolumna].back().kolor]) {
    stos_odkladania[kolumny[kolumna].back().kolor]++;
    kolumny[kolumna].pop_back();
    if (!kolumny[kolumna].empty()) {
      kolumny[kolumna].back().czy_odkryta = true;
    }
  }
}
void sprawdz_warunek_gry() {
  if (stos_odkladania[0] == 13 and stos_odkladania[1] == 13 and
      stos_odkladania[2] == 13 and stos_odkladania[3] == 13) {
    std::cout << "\n Gratulacje, wygrałeś.\n";
    exit(1);
  }
}

void wykonaj_polecenie() {
  std::cout << "Wpisz polecenie: ";
  char polecenie;
  std::cin >> polecenie;
  switch (polecenie) {
  case 'i':
    pomoc();
    break;
  case 'p':
    przesun();
    break;
  case 'd':
    dobierz();
    break;
  case 'o':
    odloz_karte();
    break;
  case 'q':
    exit(1);
    break;
  default:
    std::cout << "Błędne polecenie, użyj komendy 'i' w celu przeczytania "
                 "instrukcji\n";
    wykonaj_polecenie();
    break;
  }
}

int main(int argc, char *argv[]) {

  przygotuj_gre();
  do {
    wyswietl_plansze();
    wykonaj_polecenie();
    sprawdz_warunek_gry();
    /*std::cout << "\n" << wejscie << "\n";*/
  } while (true);

  /*for (auto j : kolumny) {*/
  /*  for (auto i : j) {*/
  /*    std::cout << i.wartosc << ' ' << i.symbol << ' ' << i.kolor << ' '*/
  /*              << i.barwa << '\n';*/
  /*  }*/
  /*  std::cout << "NOWA KOLUMNA\n";*/
  /*}*/
  /*std::cout << "STOS DOBIERANIA\n";*/
  /*for (auto i : stos_dobierania) {*/
  /*  std::cout << i.wartosc << ' ' << i.symbol << ' ' << i.kolor << ' '*/
  /*            << i.barwa << '\n';*/
  /*}*/
  return 0;
}
