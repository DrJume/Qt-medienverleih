#ifndef MEDIUM_H
#define MEDIUM_H

#include <string>

namespace MediumTypes {
static char ALLGEMEIN = 'A';
static char BUCH = 'B';
static char FILM = 'F';
}

class Medium {
    std::string inventarNr;
    std::string titel;
    int wert;

public:
    Medium();
    Medium(std::string inventarNr, std::string titel, int wert);
    std::string getInvNr() const { return this->inventarNr; }
    std::string getID() const { return this->inventarNr; }
    std::string getTitel() const {return this->titel;}
    void setTitel(std::string titel) {this->titel=titel;}
    int getWert() const {return this->wert;}
    void setWert(int wert) {this->wert=wert;}
    virtual char getType() const {return MediumTypes::ALLGEMEIN;}
    virtual std::string serialize() const;
    static Medium deserialize(std::string data);
};

#endif // MEDIUM_H
