#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
    std::string bibNr;
    std::string vorname;
    std::string nachname;
    int geburtsJahr;

public:
    Person();
    Person(std::string bibNr, std::string vorname, std::string nachname, int alter);
    std::string getBibNr() const { return this->bibNr; }
    std::string getID() const { return this->bibNr; }
    std::string getVorname() const { return this->vorname; }
    void setVorname(std::string vorname) { this->vorname=vorname; }
    std::string getNachname() const { return this->nachname; }
    void setNachname(std::string nachname) { this->nachname=nachname; }
    int getGeburtsJahr() const { return this->geburtsJahr; }
    void setGeburtsJahr(int geburtsJahr);
    std::string serialize() const;
    static Person deserialize(std::string data);
};

#endif // PERSON_H
