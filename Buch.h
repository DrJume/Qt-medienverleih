#ifndef BUCH_H
#define BUCH_H

#include "Medium.h"

#include <string>

class Buch : public Medium
{
    std::string author;
    std::string verlag;
    int seiten;

public:
    Buch();
    Buch(const Buch& buch);
    Buch(std::string inventarNr, std::string titel, int wert, std::string author, std::string verlag, int seiten);
    std::string getAuthor() const { return this->author; }
    void setAuthor(std::string author) { this->author=author;}
    std::string getVerlag() const { return this->verlag; }
    void setVerlag(std::string verlag) { this->verlag=verlag;}
    int getSeiten() const { return this->seiten; }
    void setSeiten(int seiten);
    char getType() const { return MediumTypes::BUCH; }
    virtual std::string serialize() const;
    static Buch deserialize(std::string data);
};

#endif // BUCH_H
