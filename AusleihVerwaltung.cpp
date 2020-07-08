#include "AusleihVerwaltung.h"

std::vector<Ausleihe> AusleihVerwaltung::ausleihVektor;


AusleihVerwaltung::AusleihVerwaltung(){

}

const std::vector<Ausleihe>& AusleihVerwaltung::getAusleihen() {
    return AusleihVerwaltung::ausleihVektor;
}

void AusleihVerwaltung::leeren() {
    this->ausleihVektor.clear();
}

void AusleihVerwaltung::ausleihen(const Ausleihe& ausleihe) {
    AusleihVerwaltung::ausleihVektor.push_back(ausleihe);
}

void AusleihVerwaltung::zurueckgeben(std::string invNr) {
    for (std::vector<Ausleihe>::iterator it = AusleihVerwaltung::ausleihVektor.begin(); it != AusleihVerwaltung::ausleihVektor.end(); ++it) {
        if (it->getMedium()->getInventarNr() == invNr) {
            AusleihVerwaltung::ausleihVektor.erase(it);
            return;
        }
    }
}

bool AusleihVerwaltung::istAusgeliehen(std::string invNr) {
    for (std::vector<Ausleihe>::iterator it = AusleihVerwaltung::ausleihVektor.begin(); it != AusleihVerwaltung::ausleihVektor.end(); ++it) {
        if (it->getMedium()->getInventarNr() == invNr) {
            return true;
        }
    }
    return false;
}
