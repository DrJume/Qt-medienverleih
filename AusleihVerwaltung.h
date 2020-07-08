#ifndef AUSLEIHVERWALTUNG_H
#define AUSLEIHVERWALTUNG_H

#include "Ausleihe.h"

#include <vector>
#include <string>

class AusleihVerwaltung
{
    static std::vector<Ausleihe> ausleihVektor;
public:
    AusleihVerwaltung();
    const std::vector<Ausleihe>& getAusleihen();
    void leeren();
    void ausleihen(const Ausleihe& ausleihe);
    void zurueckgeben(std::string invNr);
    bool istAusgeliehen(std::string invNr);
};


#endif // AUSLEIHVERWALTUNG_H
