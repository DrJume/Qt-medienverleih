#include "Person.h"

Person::Person() {
    this->bibNr="";
    this->vorname="";
    this->nachname="";
    this->geburtsJahr=0;
}

Person::Person(std::string bibNr, std::string vorname, std::string nachname, int geburtsJahr) {
    this->bibNr=bibNr;
    this->vorname=vorname;
    this->nachname=nachname;
    this->geburtsJahr=geburtsJahr;
}

void Person::setGeburtsJahr(int geburtsJahr) {
    if (geburtsJahr < 0) throw "Geburtsjahr kann nicht kleiner als 0 sein.";
    this->geburtsJahr=geburtsJahr;
}

std::string Person::serialize() const {
    return this->bibNr + ";" + this->vorname + ";" + this->nachname + ";" + std::to_string(this->geburtsJahr);
}

Person Person::deserialize(std::string data) {
    size_t pos = 0;
    std::string token;

    pos = data.find(";");
    std::string bibNr = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string vorname = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string nachname = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    int geburtsJahr = std::stoi(data.substr(0, pos));

    return Person(bibNr, vorname, nachname, geburtsJahr);
}

Person* Person::findPerson(std::vector<Person> *personen, std::string id) {
    for (std::vector<Person>::iterator it = personen->begin(); it != personen->end(); ++it) {
        if (it->getID() == id) return &(*it);
    }
    return NULL;
}
