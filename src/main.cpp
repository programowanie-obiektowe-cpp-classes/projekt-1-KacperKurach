#include "Kredyt.hpp"
#include "TypyPracownikow.hpp"
#include <iostream>

int n_inz = 0;
int n_mag = 0;
int n_mkt = 0;
int n_rob = 0;

const int pmax          = 100; // Maksymalna liczba pracownikow
int       l_pracownikow = 0;   // Liczba pracownikow

TypyPracownikow** tablica_pracownikow = new TypyPracownikow*[pmax];
int*              tablica_wynagrodzen = new int[pmax];

void zatrudnijInzyniera()
{
    tablica_pracownikow[l_pracownikow] = new Inzynier;
    tablica_wynagrodzen[l_pracownikow] = Inzynier::wynagrodzenie;
    n_inz++;
    l_pracownikow++;
}

void zatrudnijMagazyniera()
{
    tablica_pracownikow[l_pracownikow] = new Magazynier;
    tablica_wynagrodzen[l_pracownikow] = Magazynier::wynagrodzenie;
    n_mag++;
    l_pracownikow++;
}

void zatrudnijMarketera()
{
    tablica_pracownikow[l_pracownikow] = new Marketer;
    tablica_wynagrodzen[l_pracownikow] = Marketer::wynagrodzenie;
    n_mkt++;
    l_pracownikow++;
}

void zatrudnijRobotnika()
{
    tablica_pracownikow[l_pracownikow] = new Robotnik;
    tablica_wynagrodzen[l_pracownikow] = Robotnik::wynagrodzenie;
    n_rob++;
    l_pracownikow++;
}

double srednia(int N, double* tablica_przychodow, double nowy_przychod)
{
    double srd = 0;
    for (int i = N - 1; i > 0; i--)
    {
        tablica_przychodow[i] = tablica_przychodow[i - 1];
    }
    tablica_przychodow[0] = nowy_przychod;
    for (int i = 0; i < N; i++)
    {
        srd += tablica_przychodow[i];
    }
    return srd / N;
}

int main()
{
    const int N           = 5;
    const int maxKredytow = 50;

    const double cel = 1e6;

    int tura = 0;

    std::string komenda;
    std::string exit;

    double kwota_kredytu, czas_splaty_kredytu;

    bool main_loop = 1;
    bool tura_loop = 1;

    double pojemnosc_magazynu, cena_produktu, popyt, liczba_wyprodukow_teor, liczba_wyprodukow_real, liczba_sprzedanych,
        przychod, wynagrodzenia, dochod;

    double stan_konta     = 200000;
    double wartosc_spolki = 100;

    double srd                    = 0;
    double suma_rat_kredytow      = 0;
    int    liczbaKredytow         = 0;
    double suma_rat_do_zaplacenia = 0;

    Kredyt* kredyty[maxKredytow];
    double* tablica_przychodow = new double[N];
    for (int i = 0; i < N; i++)
    {
        tablica_przychodow[i] = 0;
    }

    std::cout << "\n\n\n*** WITAJ W GRZE!\n";

    zatrudnijInzyniera();
    zatrudnijMagazyniera();
    zatrudnijMarketera();
    zatrudnijRobotnika();

    while (main_loop)
    {
        std::cout << "*** Miesiac " << tura << "\n";
        while (tura_loop)
        {
            std::cout << "*** Podaj komende [zinz/zmag/zmkt/zrob/kred/kt/lp] \n";
            std::cin >> komenda;

            if (komenda == "zinz")
            {
                zatrudnijInzyniera();
            }
            else if (komenda == "zmag")
            {
                zatrudnijMagazyniera();
            }
            else if (komenda == "zmkt")
            {
                zatrudnijMarketera();
            }
            else if (komenda == "zrob")
            {
                zatrudnijRobotnika();
            }
            else if (komenda == "kred")
            {
                std::cout << "*** Podaj kwote kredytu\n";
                std::cin >> kwota_kredytu;
                std::cout << "*** Podaj czas splaty kredytu\n";
                std::cin >> czas_splaty_kredytu;
                kredyty[liczbaKredytow] = new Kredyt(kwota_kredytu, czas_splaty_kredytu, wartosc_spolki);
                std::cout << "\nLista zaciagnietych kredytow:\n";

                for (int i = 0; i < Kredyt::liczba_kredytow; ++i)
                {
                    kredyty[i]->wyswietlSzczegoly();
                }
                liczbaKredytow++;
            }
            else if (komenda == "kt")
            {
                tura_loop = 0;
            }
            else if (komenda == "lp")
            {
                for (int i = 0; i < l_pracownikow; i++)
                {
                    tablica_pracownikow[i]->print();
                    std::cout << "\t" << tablica_wynagrodzen[i] << "\n";
                }
                std::cout << "*** Liczba: Inzynierow: " << n_inz << "\tMagazynierow: " << n_mag
                          << "\t\tMarketerow: " << n_mkt << "\t\tRobotnikow: " << n_rob << "\n";
            }
            else if (komenda == "0")
            {
                tura_loop = 0;
            }
            else
            {
                std::cout << "*** BLAD Wpisz poprawna komende \n";
            }
        }
        tura_loop = 1;

        pojemnosc_magazynu     = Magazynier::CMag * n_mag;
        cena_produktu          = Inzynier::CInz * n_inz;
        popyt                  = Marketer::CMkt * n_mkt;
        liczba_wyprodukow_teor = Robotnik::CRob * n_rob;

        if (liczba_wyprodukow_teor >= pojemnosc_magazynu)
        {
            liczba_wyprodukow_real = pojemnosc_magazynu;
        }
        else
        {
            liczba_wyprodukow_real = liczba_wyprodukow_teor;
        }

        if (popyt >= liczba_wyprodukow_real)
        {
            liczba_sprzedanych = liczba_wyprodukow_real;
        }
        else
        {
            liczba_sprzedanych = popyt;
        }

        przychod = liczba_sprzedanych * cena_produktu;
        for (int i = 0; i < l_pracownikow; i++)
        {
            wynagrodzenia += tablica_wynagrodzen[i];
        }

        for (int i = 0; i < liczbaKredytow; i++)
        {
            suma_rat_kredytow += kredyty[i]->rataMiesieczna;
            kredyty[i]->czasSplaty--;

            if (kredyty[i]->czasSplaty == 0)
            {
                kredyty[i]->rataMiesieczna = 0;
            }
        }

        dochod = przychod - wynagrodzenia - suma_rat_kredytow;
        stan_konta += dochod;

        wartosc_spolki = srednia(N, tablica_przychodow, przychod);

        std::cout << "\n\npoj magaz " << pojemnosc_magazynu << "\tcena " << cena_produktu << "\tpopyt " << popyt
                  << "\tl.teor " << liczba_wyprodukow_teor << "\tl.real " << liczba_wyprodukow_real
                  << "\tl.sprzedanych " << liczba_sprzedanych << "\n";

        std::cout << "*** Koniec miesiaca: Wynagrodzenia: -" << wynagrodzenia << "\tPrzychod: " << przychod
                  << "\tSuma rat kred. -" << suma_rat_kredytow << "\tDochod: " << dochod
                  << "\tStan konta: " << stan_konta << "\tWartosc spolki: " << wartosc_spolki << "\n";

        if (stan_konta < 0)
        {
            std::cout << "*** FIRMA UPADLA - GAME OVER\n";
            main_loop = 0;
        }
        else
        {
            std::cout << "*** Dowolny klawsz by dalej grac, 0 by wyjsc \n";
            std::cin >> exit;
            if (exit == "0")
            {
                main_loop = 0;
            }
        }

        for (int i = 0; i < liczbaKredytow; i++)
        {
            suma_rat_do_zaplacenia += kredyty[i]->czasSplaty * kredyty[i]->rataMiesieczna;
        }

        if (wartosc_spolki - suma_rat_do_zaplacenia > cel)
        {
            std::cout << "\n\n\n>>>>>>>>> ZWYCIESTWO! Osiagnieto cel! <<<<<<<<\n\n";
            break;
        }

        suma_rat_kredytow      = 0;
        suma_rat_do_zaplacenia = 0;
        wynagrodzenia          = 0;
        tura++;
    }

    for (int i = 0; i < liczbaKredytow; ++i)
    {
        delete kredyty[i];
    }

    for (int i = 0; i < maxKredytow; i++)
    {
        delete kredyty[i];
    }

    delete[] tablica_przychodow;
}