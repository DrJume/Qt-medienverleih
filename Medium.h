#ifndef MEDIUM_H
#define MEDIUM_H

#include "Daten.h"

#include <string>
#include <vector>

namespace MediumTypes {
static const char ALLGEMEIN = 'A';
static const char BUCH = 'B';
static const char FILM = 'F';
}

class Medium : public Daten {
    std::string inventarNr;
    std::string titel;
    int wert;

public:
    Medium();
    Medium(std::string inventarNr, std::string titel, int wert);
    std::string getInventarNr() const { return this->inventarNr; }
    std::string getID() const { return this->inventarNr; }
    std::string getTitel() const {return this->titel;}
    void setTitel(std::string titel) {this->titel=titel;}
    int getWert() const {return this->wert;}
    void setWert(int wert) {this->wert=wert;}
    virtual char getType() const {return MediumTypes::ALLGEMEIN;}
    virtual std::string serialize() const;
    static Medium deserialize(std::string data);
    static Medium* findMedium(std::vector<Medium*> *medien, std::string id);
};

#endif // MEDIUM_H
