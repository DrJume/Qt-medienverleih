#ifndef FILM_H
#define FILM_H

#include <string>

#include "Medium.h"

class Film : public Medium {
    std::string regisseur;
    int dauer, altersfreigabe;

public:
    Film();
    Film(const Film& film);
    Film(std::string inventarNr, std::string titel, int wert, std::string regisseur, int dauer, int altersfreigabe);
    std::string getRegisseur() const { return this->regisseur;}
    void setRegisseur(std::string regisseur) { this->regisseur=regisseur;}
    int getDauer() const { return this->dauer; }
    void setDauer(int dauer);
    int getAltersfreigabe() const { return this->altersfreigabe; }
    void setAltersfreigabe(int altersfreigabe);
    char getType() const { return MediumTypes::FILM; }
    virtual std::string serialize() const;
    static Film deserialize(std::string data);
};

#endif // FILM_H
