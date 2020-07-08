#ifndef AUSLEIHE_H
#define AUSLEIHE_H

#include "Person.h"
#include "Medium.h"

#include <ctime>

class Ausleihe {
    Person *ausleiher;
    Medium *medium;
    std::time_t ausleihZeitpunkt;
    std::time_t rueckgabeZeitpunkt;

public:
    Ausleihe(Person *ausleiher, Medium *medium, int ausleihDauerTage);
    Ausleihe(Person *ausleiher, Medium *medium, std::time_t ausleihZeitpunkt, std::time_t rueckgabeZeitpunkt);
    Person getAusleiher() { return *ausleiher; }
    Medium* getMedium() { return medium; }
    std::time_t getAusleihZeitpunkt() { return this->ausleihZeitpunkt; }
    std::string getAusleihZeitpunktString();
    std::time_t getRueckgabeZeitpunkt() { return this->rueckgabeZeitpunkt; }
    std::string getRueckgabeZeitpunktString();
    std::string serialize() const;
    static Ausleihe deserialize(std::string data);
};

#endif // AUSLEIHE_H
