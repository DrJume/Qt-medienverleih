#include "Film.h"

Film::Film() {
    this->regisseur="";
    this->dauer=0;
    this->altersfreigabe=0;
}

Film::Film(const Film& film) : Medium(film.getInventarNr(), film.getTitel(), film.getWert()) {
    this->regisseur=film.regisseur;
    this->dauer=film.dauer;
    this->altersfreigabe=film.altersfreigabe;
}

Film::Film(std::string inventarNr, std::string titel, int wert, std::string regisseur, int dauer, int altersfreigabe) : Medium(inventarNr, titel, wert) {
    this->regisseur=regisseur;
    this->dauer=dauer;
    this->altersfreigabe=altersfreigabe;
}

void Film::setDauer(int dauer) {
    if (dauer < 0) throw "Dauer kann nicht kleiner als 0 sein.";
    this->dauer=dauer;
}

void Film::setAltersfreigabe(int altersfreigabe) {
    if (altersfreigabe < 0) throw "Altersfreigabe kann nicht kleiner als 0 sein.";
    this->altersfreigabe=altersfreigabe;
}

std::string Film::serialize() const {
    return Medium::serialize() + ";" + this->regisseur + ";" + std::to_string(this->dauer) + ";" + std::to_string(this->altersfreigabe);
}

Film Film::deserialize(std::string data) {
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
    std::string regisseur = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    int dauer = std::stoi(data.substr(0, pos));
    data.erase(0, pos+1);

    pos = data.find(";");
    int altersfreigabe = std::stoi(data.substr(0, pos));

    return Film(invNr, titel, wert, regisseur, dauer, altersfreigabe);
}
