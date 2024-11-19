#ifndef P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP
#define P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP

#include <array>
#include <format>
#include <random>

#include <iostream>

inline constexpr std::array first_names{
    "Ann",
    "Andrew",
    "John",
    "Jane",
    "Bob",
    "Alice",
    "Bertram",
    "Monica",
    "Laura",
    "Eric",
    "Richard",
    "Karen",
    "Clara",
    "Rupert",
    "Bruce",
    "Martha",
    "Elizabeth",
    "Corey",
    "Nancy",
    "Joe",
    "Amy",
    "Mike",
    "James",
    "Naomi"
};

inline constexpr std::array last_names{
    "Hendricks",
    "Smith",
    "Gates",
    "Stein",
    "Warren",
    "Booker",
    "Williamson",
    "Walters",
    "Dunn",
    "Swanson",
    "Knope",
    "Haverford",
    "Ludgate",
    "Meagle",
    "Favreau",
    "Vietor",
    "Lovett",
    "Pfeifer",
    "Rhodes",
    "Abrams",
    "McFaul",
    "Stone",
    "Sisley",
    "Hanneman",
    "Holden",
    "Nagata"
};

inline auto getRandomName() -> std::string {
    static auto prng = std::mt19937{std::random_device{}()};
    auto fnd = std::uniform_int_distribution<std::size_t>{0, first_names.size() - 1};
    auto lnd = std::uniform_int_distribution<std::size_t>{0, last_names.size() - 1};
    const auto first_name = first_names[fnd(prng)];
    const auto last_name = last_names[lnd(prng)];
    return std::format("{} {}", first_name, last_name);
}

inline constexpr std::array nazwa_wydzial{
    "MEL",
    "EITI",
    "MINI",
    "AINS",
    "IBHIS",
    "SIMR"
};

inline auto getRandomWydzial() -> std::string {
    static auto prng = std::mt19937{std::random_device{}()};
    auto fnd = std::uniform_int_distribution<std::size_t>{0, nazwa_wydzial.size() - 1};
    const auto random_wydzial = nazwa_wydzial[fnd(prng)];
    return std::format("{}", random_wydzial);
}

std::string losujUmiejetnosc() {
    std::srand(std::time(nullptr));
    return (std::rand() % 2 == 0) ? "Tak" : "Nie";
}

int losujLiczbe() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    return dis(gen);
}

double losujRozmiarButa() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(35.0, 50.0);
    return dis(gen);
}

#endif //P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP