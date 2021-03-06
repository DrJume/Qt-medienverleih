#include "mainWindowAusleihen.h"

#include <QApplication>

#include <iostream>

#include "Medium.h"
#include "Buch.h"
#include "Film.h"
#include "Person.h"
#include "Ausleihe.h"

int main(int argc, char *argv[]) {

//    Medium m("001", "Nichts", 420);
//    std::cout << m.serialize() << std::endl;

//    Buch b("101", "Die Bibel", 100, "Martin Luther", "Gutenberg Verlag", 666);
//    std::cout << b.serialize() << std::endl;

//    Film f("201", "Forrest Gump", 30, "Robert Zemeckis", 90, 6);
//    std::cout << f.serialize() << std::endl;

//    Medium *mf=&f;
//    std::cout << mf->serialize() << std::endl;

//    try {
//        Medium ds = Medium::deserialize("69;Test;");
//        std::cout << ds.serialize() << std::endl;
//    } catch (std::invalid_argument&) {
//        std::cout << "Deserialisierungsfehler!" << std::endl;
//    }

//    Person p("001", "Olaf", "Scholz", 1980);

//    Ausleihe ausl1(&p, &b, 30);
//    std::cout << ausl1.getAusleihZeitpunktString() << std::endl;
//    std::cout << ausl1.getRueckgabeZeitpunktString() << std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
