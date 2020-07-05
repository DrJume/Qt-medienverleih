#include "Medium.h"

Medium::Medium() {
    this->inventarNr="";
    this->titel="";
    this->wert=0;
}

Medium::Medium(std::string inventarNr, std::string titel, int wert) {
    this->inventarNr=inventarNr;
    this->titel=titel;
    this->wert=wert;
}

std::string Medium::serialize() const {
    return this->inventarNr + ";" + this->getType() + ";" + this->titel + ";" + std::to_string(this->wert);
}

Medium Medium::deserialize(std::string data) {
    size_t pos = 0;
    std::string token;

    pos = data.find(";");
    std::string inventarNr = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    std::string titel = data.substr(0, pos);
    data.erase(0, pos+1);

    pos = data.find(";");
    int wert = std::stoi(data.substr(0, pos));

    return Medium(inventarNr, titel, wert);
}
