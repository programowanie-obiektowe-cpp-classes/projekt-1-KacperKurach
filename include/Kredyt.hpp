#include <iostream>
#include <cmath>

class Kredyt {
public:
    double kwota;
    int czasSplaty;
    double odsetki;
    double rataMiesieczna;
    static int liczba_kredytow;

    static constexpr int maxCzasSplaty = 24;
    static constexpr double maxZadluzenieRatio = 10;

    void obliczRateMiesieczna() {
        rataMiesieczna = (kwota + odsetki) / czasSplaty;
    }


    Kredyt(double _kwota, int _czasSplaty, double wartoscSpolki) : kwota(_kwota), czasSplaty(_czasSplaty) {
        if (czasSplaty > maxCzasSplaty) {
            czasSplaty = maxCzasSplaty;
        }

        odsetki = kwota * 0.02 * czasSplaty;

        if (kwota > wartoscSpolki * maxZadluzenieRatio) {
            std::cerr << "*** Blad: Przekroczono maksymalne zadluzenie w stosunku do wartosci spolki.\n";
            kwota = 0;
            czasSplaty = 0;
            odsetki = 0;
            rataMiesieczna = 0;
            return;
        }
        liczba_kredytow++;
        obliczRateMiesieczna();
    }

    void wyswietlSzczegoly() const {
        std::cout << "Kwota kredytu: " << kwota
                  << ", Czas splaty: " << czasSplaty
                  << " miesiecy, Odsetki: " << odsetki
                  << ", Rata miesieczna: " << rataMiesieczna << std::endl;
    }
};

int Kredyt::liczba_kredytow=0;