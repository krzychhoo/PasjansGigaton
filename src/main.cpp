#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <random>
#include <string>
#include <vector>
#include <nowide/iostream.hpp>
#include <nowide/fstream.hpp>

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
// Domyślna talia kart
std::vector<karta> karty = {
    // kier
    {1, "❤️ A ", 0, true, false},
    {2, "❤️ 2 ", 0, true, false},
    {3, "❤️ 3 ", 0, true, false},
    {4, "❤️ 4 ", 0, true, false},
    {5, "❤️ 5 ", 0, true, false},
    {6, "❤️ 6 ", 0, true, false},
    {7, "❤️ 7 ", 0, true, false},
    {8, "❤️ 8 ", 0, true, false},
    {9, "❤️ 9 ", 0, true, false},
    {10, "❤️ 10", 0, true, false},
    {11, "❤️ J ", 0, true, false},
    {12, "❤️ Q ", 0, true, false},
    {13, "❤️ K ", 0, true, false},
    // karo
    {1, "♦️ A ", 1, true, false},
    {2, "♦️ 2 ", 1, true, false},
    {3, "♦️ 3 ", 1, true, false},
    {4, "♦️ 4 ", 1, true, false},
    {5, "♦️ 5 ", 1, true, false},
    {6, "♦️ 6 ", 1, true, false},
    {7, "♦️ 7 ", 1, true, false},
    {8, "♦️ 8 ", 1, true, false},
    {9, "♦️ 9 ", 1, true, false},
    {10, "♦️ 10", 1, true, false},
    {11, "♦️ J ", 1, true, false},
    {12, "♦️ Q ", 1, true, false},
    {13, "♦️ K ", 1, true, false},
    // pik
    {1, "♠️ A ", 2, false, false},
    {2, "♠️ 2 ", 2, false, false},
    {3, "♠️ 3 ", 2, false, false},
    {4, "♠️ 4 ", 2, false, false},
    {5, "♠️ 5 ", 2, false, false},
    {6, "♠️ 6 ", 2, false, false},
    {7, "♠️ 7 ", 2, false, false},
    {8, "♠️ 8 ", 2, false, false},
    {9, "♠️ 9 ", 2, false, false},
    {10, "♠️ 10", 2, false, false},
    {11, "♠️ J ", 2, false, false},
    {12, "♠️ Q ", 2, false, false},
    {13, "♠️ K ", 2, false, false},
    // trefl
    {1, "♣️ A ", 3, false, false},
    {2, "♣️ 2 ", 3, false, false},
    {3, "♣️ 3 ", 3, false, false},
    {4, "♣️ 4 ", 3, false, false},
    {5, "♣️ 5 ", 3, false, false},
    {6, "♣️ 6 ", 3, false, false},
    {7, "♣️ 7 ", 3, false, false},
    {8, "♣️ 8 ", 3, false, false},
    {9, "♣️ 9 ", 3, false, false},
    {10, "♣️ 10", 3, false, false},
    {11, "♣️ J ", 3, false, false},
    {12, "♣️ Q ", 3, false, false},
    {13, "♣️ K ", 3, false, false}};

// Definicje najważniejszych zmiennych globalnych wykorzystywanych przez grę
struct plansza {
  std::vector<karta> kolumny[8];
  std::vector<karta> stos_dobierania;
  std::vector<int> stos_odkladania = {0, 0, 0, 0};
  int liczba_ruchow = 0;
};
plansza stol;
std::vector<plansza> historia_ruchow;
// Zmienna ograniczająca cofanie do 3 ruchów wstecz od maksymalnego ruchu)
int max_liczba_ruchow = 0;


std::vector<std::string> symbole_kart = {
    " ", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
bool poziom_trudny = false;
std::vector<int> wyniki;

void wyswietl_ranking() {
  nowide::ifstream ranking;
  ranking.open("ranking.txt");
  if (!ranking.is_open()) {
    ranking.close();
    nowide::ofstream nowy_ranking("ranking.txt");
    nowy_ranking.close();
    ranking.open("ranking.txt");
  }


  int wynik;
  wyniki.clear();
  while (ranking >> wynik) {
    wyniki.push_back(wynik);
  }
  std::sort(wyniki.begin(), wyniki.end());
  nowide::cout << "Obecny ranking 10. najlepszych wyników\n";
  for (int i = 0; i < std::min(10, int(wyniki.size())); i++) {
    nowide::cout << i+1 << ". " << wyniki[i] << " ruchów\n";
  }
  ranking.close();
}

void zaktualizuj_ranking() {
  wyniki.push_back(stol.liczba_ruchow);
  nowide::ofstream ranking_wyjscie;
  ranking_wyjscie.open("ranking.txt");
  for (auto i : wyniki) {
    ranking_wyjscie << i << '\n';
  }
  ranking_wyjscie.close();
  wyswietl_ranking();
}

void wykonaj_ruch() {
  stol.liczba_ruchow++;
  if (max_liczba_ruchow <= stol.liczba_ruchow) max_liczba_ruchow = stol.liczba_ruchow;
  historia_ruchow.push_back(stol);
}
void cofnij_ruch() {
  if (historia_ruchow.size() > 1 && max_liczba_ruchow < stol.liczba_ruchow + 3) {
    stol = historia_ruchow[historia_ruchow.size() - 2];
    historia_ruchow.pop_back();
  } else {
    nowide::cout << "Brak możliwości cofnięcia ruchu\n";
  }

}

void przygotuj_gre() {
  wyswietl_ranking();
  // Przygotowanie gry
  // Losowanie kolejnosci kart
  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};
  std::shuffle(karty.begin(), karty.end(), rng);


  // Ulozenie kart na stosy po uprzednim ich wyczyszczeniu (żeby dało się rozpocząć w trakcie rozgrywki nową grę)
  int licznik = 0;
  for (int i = 1; i <= 7; i++) {
    int obecny_licznik = licznik;
    stol.kolumny[i-1].clear();
    for (int j = licznik; j < obecny_licznik + i; j++) {
      stol.kolumny[i - 1].push_back(karty[j]);
      licznik++;
    }
    stol.kolumny[i - 1][i - 1].czy_odkryta = true;
  }
  stol.stos_dobierania.clear();
  for (int i = 28; i < 52; i++) {
    stol.stos_dobierania.push_back(karty[i]);
  }
  stol.stos_odkladania.clear();
  for (int i = 0; i < 4; i++) {
    stol.stos_odkladania.push_back(0);
  }
  poziom_trudny = false;
  stol.liczba_ruchow = 0;
  max_liczba_ruchow = 0;
  historia_ruchow.clear();
  historia_ruchow.push_back(stol);

  // Wybór poziomu trudności
  char wybor_trybu;
  do {
    nowide::cout << "Wpisz 't', jeżeli chcesz włączyć tryb trudny, bądź 'n' dla trybu normalnego: ";
    nowide::cin >> wybor_trybu;
    if (nowide::cin.fail()) {
      nowide::cin.clear();
      nowide::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      nowide::cout << "BŁĄD polecenia\n";
    } else if (wybor_trybu == 't') {
      poziom_trudny = true;
    }
  } while (wybor_trybu != 't' && wybor_trybu != 'n');

}



// Funkcja wypisująca obecny stan stołu
void wyswietl_plansze() {
  nowide::cout << "-------------------------STÓŁ-------------------------\n";
  nowide::cout << "Liczba ruchów: " << stol.liczba_ruchow << '\n';
  nowide::cout << "Stos Odkladania\n";
  nowide::cout << "❤️ " << symbole_kart[stol.stos_odkladania[0]] << ' ' << "♦️ "
            << symbole_kart[stol.stos_odkladania[1]] << ' ' << "♠️ "
            << symbole_kart[stol.stos_odkladania[2]] << ' ' << "♣️ "
            << symbole_kart[stol.stos_odkladania[3]] << '\n';

  int max_dlugosc_kolumny = 0;
  for (auto i : stol.kolumny) {
    max_dlugosc_kolumny = std::max(max_dlugosc_kolumny, int(i.size()));
  }
  nowide::cout << "Plansza\n";
  nowide::cout << " 1.   2.   3.   4.   5.   6.   7.  Stos Dobierania(8.)\n";
  for (int i = 0; i < max_dlugosc_kolumny; i++) {
    for (int j = 0; j < 8; j++) {
      if (stol.kolumny[j].size() > i) {
        if (stol.kolumny[j][i].czy_odkryta) {
          nowide::cout << stol.kolumny[j][i].symbol;
        } else {
          nowide::cout << " 🂠  ";
        }
        nowide::cout << " ";
      } else {
        nowide::cout << "     ";
      }
      if (j == 6) {
        nowide::cout << "         ";
      }
    }
    nowide::cout << '\n';
  }

  nowide::cout << "------------------------------------------------------\n";
}
// Funkcja pomoc, przypominająca użytkownikowi komendy
void pomoc() {
  nowide::cout << std::endl << "Dostępne polecenia:" << std::endl;
  nowide::cout << "[i]nstrukcja, lista dostępnych poleceń" << std::endl;
  nowide::cout << "[p]rzesuń, używane do przesuwania kart na planszy" << std::endl;
  nowide::cout << "[d]obierz, dobieranie karty ze stosu" << std::endl;
  nowide::cout
      << "[o]dłuż, odłuż kartę z jednej z kolumn bądź stosu na stos odkładania"
      << std::endl;
  nowide::cout << "[n]owa gra";
  nowide::cout << "[c]ofnij ruch";
  char t;
  do {
    nowide::cout << "Wpisz 't', jeśli chcesz wyjść z instrukcji: ";
    nowide::cin >> t;
  } while (t != 't');
}
// Funkcja przesuwania kart między stosami
void przesun() {
  int kolumna_poczotkowa;
  int kolumna_docelowa;
  int liczba_kart = 1;
  // 1-7 zrozumiałe, 8 - stos dobierania
  nowide::cout << "Wybierz kolumnę początkową: ";
  nowide::cin >> kolumna_poczotkowa;
  kolumna_poczotkowa--;
  if (nowide::cin.fail() || kolumna_poczotkowa < 0 || kolumna_poczotkowa > 7) {
    nowide::cin.clear();
    nowide::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    nowide::cout << "BŁĄD polecenia\n";
    return;
  }
  nowide::cout << "Wybierz kolumnę docelową: ";
  nowide::cin >> kolumna_docelowa;
  kolumna_docelowa--;
  if (nowide::cin.fail() || kolumna_docelowa < 0 || kolumna_docelowa > 6 ||
      kolumna_poczotkowa == kolumna_docelowa) {
    nowide::cin.clear();
    nowide::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    nowide::cout << "BŁĄD polecenia\n";
    return;
  }
  if (kolumna_poczotkowa != 7) {
    nowide::cout << "Wybierz liczbę kart: ";
    nowide::cin >> liczba_kart;
    if (nowide::cin.fail()) {
      nowide::cin.clear();
      nowide::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      nowide::cout << "BŁĄD polecenia\n";
      return;
    }
  }
  // Faktyczna logika przesuwania kart
  if (liczba_kart <= stol.kolumny[kolumna_poczotkowa].size()) {
    int pierwsza_karta = stol.kolumny[kolumna_poczotkowa].size() - liczba_kart;
    karta& pierwsza_karta2 = stol.kolumny[kolumna_poczotkowa][pierwsza_karta];
    int ostatnia_karta = stol.kolumny[kolumna_docelowa].size() - 1;
    if ((stol.kolumny[kolumna_poczotkowa][pierwsza_karta].barwa !=
             stol.kolumny[kolumna_docelowa][ostatnia_karta].barwa &&
         stol.kolumny[kolumna_poczotkowa][pierwsza_karta].wartosc + 1 ==
             stol.kolumny[kolumna_docelowa][ostatnia_karta].wartosc &&
         stol.kolumny[kolumna_poczotkowa][pierwsza_karta].czy_odkryta) ||
        (stol.kolumny[kolumna_poczotkowa][pierwsza_karta].wartosc == 13 &&
         stol.kolumny[kolumna_docelowa].empty())) {
      for (int i = 0; i < liczba_kart; i++) {
        stol.kolumny[kolumna_docelowa].push_back(
            stol.kolumny[kolumna_poczotkowa][pierwsza_karta]);
        stol.kolumny[kolumna_poczotkowa].erase(stol.kolumny[kolumna_poczotkowa].begin() +
                                          pierwsza_karta);
      }
      if (kolumna_poczotkowa != 7 && !stol.kolumny[kolumna_poczotkowa].empty()) {
        stol.kolumny[kolumna_poczotkowa].back().czy_odkryta = true;
      }
    } else {
      nowide::cout << "BŁĄD polecenia\n";
      return;
    }
  } else {
    nowide::cout << "BŁĄD polecenia\n";
    return;
  }
  wykonaj_ruch();
}
// Dobierz kartę na stos dobierania
void dobierz() {
  int liczba_dobieranych_kart = 1;
  if (poziom_trudny)
    liczba_dobieranych_kart = 3;
  for (int i = 0; i < liczba_dobieranych_kart; i++) {
    if (!stol.stos_dobierania.empty()) {
      stol.kolumny[7].push_back(stol.stos_dobierania.back());
      stol.kolumny[7].back().czy_odkryta = true;
      stol.stos_dobierania.pop_back();
    } else {
      for (auto j : stol.kolumny[7]) {
        stol.stos_dobierania.insert(stol.stos_dobierania.begin(), j);
        stol.stos_dobierania.front().czy_odkryta = false;
        stol.kolumny[7].pop_back();
      }
    }
  }
  wykonaj_ruch();
}
// Odłóż kartę na jeden z 4 stosów odkładania
void odloz_karte() {
  int kolumna;
  nowide::cout << "\nWpisz kolumnę z której chcesz odłożyć kartę: ";
  nowide::cin >> kolumna;
  kolumna--;
  if (nowide::cin.fail() || kolumna < 0 || kolumna > 7) {
    nowide::cin.clear();
    nowide::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    nowide::cout << "BŁĄD polecenia\n";
    return;
  }
  if (stol.kolumny[kolumna].back().wartosc - 1 ==
      stol.stos_odkladania[stol.kolumny[kolumna].back().kolor]) {
    stol.stos_odkladania[stol.kolumny[kolumna].back().kolor]++;
    stol.kolumny[kolumna].pop_back();
    if (!stol.kolumny[kolumna].empty()) {
      stol.kolumny[kolumna].back().czy_odkryta = true;
    }
  } else {
    nowide::cout << "BŁĄD polecenia\n";
  }
  wykonaj_ruch();
}

// Sprawdzanie, czy użytkownik wygrał
void sprawdz_warunek_gry() {
  if (stol.stos_odkladania[0] == 13 and stol.stos_odkladania[1] == 13 and
      stol.stos_odkladania[2] == 13 and stol.stos_odkladania[3] == 13) {
    nowide::cout << "\nGratulacje, wygrałeś.\n";
    zaktualizuj_ranking();
    exit(1);
  }
  /*bool ulozone_karty = true;
  for (auto kolumna : kolumny) {
     for (auto karta : kolumna) {
       if (!karta.czy_odkryta) {
        ulozone_karty = false;
        return;
      }
     }   
  }
  if (!stos_dobierania.empty()) {
    ulozone_karty = false;
  }
  if (ulozone_karty) {
    nowide::cout << "\nGratulacje, wszystkie karty są ułożone na planszy, wygrałeś.\n";
  }*/
}




// Przetwarzanie komend użytkownika
void wykonaj_polecenie() {
  nowide::cout << "Wpisz polecenie: ";
  char polecenie;
  nowide::cin >> polecenie;
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
  case 'n':
    przygotuj_gre();
    break;
  case 'q':
    exit(1);
  case 'c':
    cofnij_ruch();
    break;
  default:
    nowide::cout << "Błędne polecenie, użyj komendy 'i' w celu przeczytania "
                 "instrukcji\n";
    wykonaj_polecenie();
    break;
  }
}

int main(int argc, char *argv[]) {
  // Rozpoczęcie gry
  /*przygotuj_gre();
  // Główna pętla gry
  do {
    wyswietl_plansze();
    wykonaj_polecenie();
    sprawdz_warunek_gry();
  } while (true);*/
  wyswietl_ranking();

  return 0;
}
