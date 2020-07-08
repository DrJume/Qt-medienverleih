#include "Buch.h"

#include "Medium.h"

#include <iostream>

Buch::Buch() {
    this->author="";
    this->verlag="";
    this->seiten=0;
}

Buch::Buch(const Buch& buch) : Medium(buch.getInventarNr(), buch.getTitel(), buch.getWert()) {
    this->author=buch.author;
    this->verlag=buch.verlag;
    this->seiten=buch.seiten;
}

Buch::Buch(std::string inventarNr, std::string titel, int wert, std::string author, std::string verlag, int seiten) : Medium(inventarNr, titel, wert){
    this->author=author;
    this->verlag=verlag;
    this->seiten=seiten;
}

void Buch::setSeiten(int seiten) {
    if (seiten < 0) throw "Seitenanzahl kann nicht kleiner als 0 sein.";
    this->seiten=seiten;
}

std::string Buch::serialize() const {
    return Medium::serialize() + ";" + this->author + ";" + this->verlag + ";" + std::to_string(this->seiten);
}

Buch Buch::deserialize(std::string data) {
    size_t pos = 0;

    pos = data.find(";");
    std::string medienType = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string invNr = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string titel = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    int wert = std::stoi(data.substr(0, pos));
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string author = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string verlag = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    int seiten  = std::stoi(data.substr(0, pos));

    return Buch(invNr, titel, wert, author, verlag, seiten);
}

