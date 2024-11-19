
#include "RandomNameGenerator.hpp"
#include <iostream>

class TypyPracownikow
{
public:
    std::string imie_pracownika;

    TypyPracownikow()
    {
        imie_pracownika = getRandomName();
        std::cout << "*** Nowy pracownik!\t" << imie_pracownika << "\t";
    }

    void print(){std::cout<<imie_pracownika<<"\t";}
};


class Inzynier : public TypyPracownikow
{
public:
    static const int CInz=300;
    static const int wynagrodzenie = 6000;

    Inzynier() { std::cout << "Zawod: Inzynier\t\tWynagrodzenie " << wynagrodzenie << "\tWydzial:"<<getRandomWydzial()<<"\n"; }
};

class Magazynier : public TypyPracownikow
{
public:
    static const int CMag=10;
    static const int wynagrodzenie = 5000;

    Magazynier() { std::cout << "Zawod: Magazynier\tWynagrodzenie " << wynagrodzenie << "\tUprawnienia na wozek: "<<losujUmiejetnosc()<<"\n"; }
};

class Marketer : public TypyPracownikow
{
public:
    static const int CMkt=20;
    static const int wynagrodzenie = 7000;

    Marketer() { std::cout << "Zawod: Marketer\tWynagrodzenie " << wynagrodzenie << "\t Liczba obserwujacych: "<<losujLiczbe()<<"\n"; }
};

class Robotnik : public TypyPracownikow
{
public:
    static const int CRob=30;
    static const int wynagrodzenie = 4000;

    Robotnik() { std::cout << "Zawod: Robotnik\tWynagrodzenie " << wynagrodzenie << "\tRozmiar buta: "<<losujRozmiarButa()<<"\n"; }
};
