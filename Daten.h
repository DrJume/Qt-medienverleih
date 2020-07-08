#ifndef DATEN_H
#define DATEN_H

#include <string>

class Daten
{
public:
    Daten() {}
    virtual std::string serialize() const {}
    static Daten deserialize(std::string data) { }
};

#endif // DATEN_H
