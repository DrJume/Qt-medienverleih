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
    return std::string(1, this->getType()) + ";" + this->inventarNr + ";" + this->titel + ";" + std::to_string(this->wert);
}

Medium Medium::deserialize(std::string data) {
    size_t pos = 0;

    pos = data.find(";");
    std::string medienType = data.substr(0, pos);
    data.erase(0, pos+1);

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

Medium* Medium::findMedium(std::vector<Medium*> *medien, std::string id) {
    for (std::vector<Medium*>::iterator it = medien->begin(); it != medien->end(); ++it) {
        if ((*it)->getID() == id) return *it;
    }
    return NULL;
}
