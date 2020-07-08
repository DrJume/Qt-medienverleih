#include "Ausleihe.h"

#include <iostream>

Ausleihe::Ausleihe(Person *ausleiher, Medium *medium, int ausleihDauerTage) {
    this->ausleiher=ausleiher;
    this->medium=medium;
    this->ausleihZeitpunkt=time(0);

    struct std::tm *timeinfo;
    timeinfo = std::localtime(&(this->ausleihZeitpunkt));
    timeinfo->tm_mday += 30;
    this->rueckgabeZeitpunkt = std::mktime(timeinfo);
}

Ausleihe::Ausleihe(Person* ausleiher, Medium* medium, std::time_t ausleihZeitpunkt, std::time_t rueckgabeZeitpunkt) {
    this->ausleiher=ausleiher;
    this->medium=medium;
    this->ausleihZeitpunkt=ausleihZeitpunkt;
    this->rueckgabeZeitpunkt=rueckgabeZeitpunkt;
}

std::string Ausleihe::getAusleihZeitpunktString() {
    struct std::tm *timeinfo;
    timeinfo = std::localtime(&(this->ausleihZeitpunkt));

    char dateString[20];
    std::strftime(dateString, sizeof(dateString), "%a %e. %b %Y", timeinfo);

    return std::string(dateString);
}

std::string Ausleihe::getRueckgabeZeitpunktString() {
    struct std::tm *timeinfo;
    timeinfo = std::localtime(&(this->rueckgabeZeitpunkt));

    char dateString[20];
    std::strftime(dateString, sizeof(dateString), "%a %e. %b %Y", timeinfo);

    return std::string(dateString);
}

std::string Ausleihe::serialize() const {
    return this->ausleiher->getBibNr() + ";" + this->medium->getInventarNr() + ";" + std::to_string(this->ausleihZeitpunkt) + ";" + std::to_string(this->rueckgabeZeitpunkt);
}

//Ausleihe Ausleihe::deserialize(std::string data) {
//    size_t pos = 0;
//    std::string token;

//    pos = data.find(";");
//    std::string invNr = data.substr(0, pos);
//    data.erase(0, pos+1);

//    pos = data.find(";");
//    std::string titel = data.substr(0, pos);
//    data.erase(0, pos+1);

//    pos = data.find(";");
//    int wert = std::stoi(data.substr(0, pos));

//    pos = data.find(";");
//    std::string author = data.substr(0, pos);
//    data.erase(0, pos+1);

//    pos = data.find(";");
//    std::string verlag = data.substr(0, pos);
//    data.erase(0, pos+1);

//    pos = data.find(";");
//    int seiten = std::stoi(data.substr(0, pos));

//    return Ausleihe(invNr, titel, wert, author, verlag, seiten);
//}

