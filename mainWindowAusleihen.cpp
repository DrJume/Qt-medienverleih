#include "mainWindowAusleihen.h"
#include "ui_mainWindowAusleihen.h"
#include "verwaltePersonenDialog.h"
#include "verwalteMedienDialog.h"

#include <QContextMenuEvent>
#include <QMessageBox>

#include <iostream>
#include <fstream>

#include "Buch.h"
#include "Film.h"
#include "Ausleihe.h"
#include "Medium.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ausleihTable->setHeaderCells({"Inventar-Nummer", "Typ", "Titel", "Ausleiher", "ausgeliehen am", "zurückgeben bis"});
    ui->ausleihTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ausleihTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->ausleihTable,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(ausleihContextMenu(const QPoint&)));


//    this->personen = { Person("001", "Olaf", "Scholz", 1980),
//                       Person("002", "Heinrich", "Mueller", 1957)
//                     };

//    this->medien = { new Buch("101", "Die Bibel", 100, "Martin Luther", "Gutenberg Verlag", 666),
//                     new Film("201", "Forrest Gump", 30, "Robert Zemeckis", 90, 6)
//                   };

    this->updateAusleihTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ausleihContextMenu(const QPoint& pos) {
    QTableWidgetItem* selected = ui->ausleihTable->itemAt(pos);
    if (selected == nullptr) return; // wenn keine Zeilen gerechtsklickt, dann auch kein context menu

    ui->ausleihTable->selectRow(selected->row()); // die Zeile der gerechtsklickten Zelle auswaehlen

    // context menu
    QMenu menu(ui->ausleihTable);
    menu.addAction(QIcon::fromTheme("edit-undo"), "Zurückgeben", this, [this, selected] { MainWindow::ausleiheZurueckgeben(selected->row()); });
    menu.exec(ui->ausleihTable->viewport()->mapToGlobal(pos));
}

void MainWindow::ausleiheZurueckgeben(int row) {
    this->ausleihenVerwaltung.zurueckgeben(ui->ausleihTable->getCellText(row,0));
    this->updateAusleihTable();
}

void MainWindow::updateAusleihTable() {
    ui->ausleihTable->setRowCount(0);

    for (std::vector<Ausleihe>::const_iterator it = this->ausleihenVerwaltung.getAusleihen().begin(); it != this->ausleihenVerwaltung.getAusleihen().end(); ++it) {
        int newRow = ui->ausleihTable->rowCount();
        ui->ausleihTable->insertRow(newRow);

        Ausleihe ausleihe = *it;

        ui->ausleihTable->setCellText(newRow, 0, ausleihe.getMedium()->getInventarNr());
        ui->ausleihTable->setCellText(newRow, 1, std::string(1, ausleihe.getMedium()->getType()));
        ui->ausleihTable->setCellText(newRow, 2, ausleihe.getMedium()->getTitel());
        ui->ausleihTable->setCellText(newRow, 3, ausleihe.getAusleiher().getNachname());
        ui->ausleihTable->setCellText(newRow, 4, ausleihe.getAusleihZeitpunktString());
        ui->ausleihTable->setCellText(newRow, 5, ausleihe.getRueckgabeZeitpunktString());
    }
}

void MainWindow::on_actionPersonen_verwalten_triggered()
{
    VerwaltePersonenDialog verwaltePersonen;
    verwaltePersonen.setTableData(&(this->personen));
    connect(&verwaltePersonen,
            SIGNAL(accepted()),
            SLOT(updateAusleihTable()));
    verwaltePersonen.exec();
}

void MainWindow::on_actionOeffnen_triggered()
{
    std::string line;

    // Mediendatei oeffnen
    std::ifstream medienFile("medien.csv");
    if (!medienFile.is_open()) {
        std::cout << "Mediendatei konnte nicht geoeffnet werden!" << std::endl;

        // Beispieldaten eintragen, wenn keine Datei vorhanden ist
        this->medien = { new Buch("101", "Die Bibel", 100, "Martin Luther", "Gutenberg Verlag", 666),
                         new Film("201", "Forrest Gump", 30, "Robert Zemeckis", 90, 6)
                       };

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setWindowTitle("Mediendaten");
        msgBox.setText("Ein paar Beispieldaten wurden eingetragen.");
        msgBox.exec();
    } else {
        // vorherige geoeffnete Daten loeschen
        this->medien.clear();

        while ( std::getline(medienFile,line) ) {
            // erster Buchstabe bestimmt den Medientyp
            size_t pos = line.find(";");
            char medienType = line.substr(0, pos)[0];

            switch (medienType) {
            case MediumTypes::BUCH:
                this->medien.push_back(new Buch(Buch::deserialize(line)));
                break;
            case MediumTypes::FILM:
                this->medien.push_back(new Film(Film::deserialize(line)));
                break;
            default:
                break;
            }
        }
        medienFile.close();
    }

    // Personendatei lesen
    std::ifstream personenFile("personen.csv");
    if (!personenFile.is_open()) {
        std::cout << "Personendatei konnte nicht geoeffnet werden!" << std::endl;

        // Beispieldaten eintragen, wenn keine Datei vorhanden ist
        this->personen = { Person("001", "Olaf", "Scholz", 1980),
                           Person("002", "Heinrich", "Mueller", 1957)
                         };

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setWindowTitle("Personendaten");
        msgBox.setText("Ein paar Beispieldaten wurden eingetragen.");
        msgBox.exec();
    } else {
        // Personendatei einlesen
        this->personen.clear();

        while ( std::getline(personenFile,line) ) {
            this->personen.push_back(Person::deserialize(line));
        }
        personenFile.close();
    }

    // Ausleihendatei lesen
    std::ifstream ausleihenFile("ausleihen.csv");
    if (!ausleihenFile.is_open()) {
        std::cout << "Ausleihen konnte nicht geoffnet werden!" << std::endl;
        return;
    } else {
        this->ausleihenVerwaltung.leeren();
        while ( std::getline(ausleihenFile,line) ) {
            size_t pos = 0;

            pos = line.find(";");
            std::string ausleiherID = line.substr(0, pos);
            line.erase(0, pos+1);

            pos = line.find(";");
            std::string mediumID = line.substr(0, pos);
            line.erase(0, pos+1);

            pos = line.find(";");
            std::time_t ausleihZeitpunkt = std::stol(line.substr(0, pos));
            line.erase(0, pos+1);

            pos = line.find(";");
            std::time_t rueckgabeZeitpunkt = std::stol(line.substr(0, pos));
            line.erase(0, pos+1);

            this->ausleihenVerwaltung.ausleihen(Ausleihe(Person::findPerson(&this->personen, ausleiherID),
                                                         Medium::findMedium(&this->medien, mediumID),
                                                         ausleihZeitpunkt,
                                                         rueckgabeZeitpunkt
                                                         ));
        }

        ausleihenFile.close();

        this->updateAusleihTable();
    }
}


void MainWindow::on_actionSpeichern_triggered()
{
    // Mediendatei speichern
    std::ofstream medienFile("medien.csv", std::ios::trunc);
    if (!medienFile.is_open()) {
        std::cout << "Mediendatei konnte nicht geschrieben werden!" << std::endl;
        return;
    }

    for (std::vector<Medium*>::iterator it = this->medien.begin(); it != this->medien.end(); ++it) {
        medienFile << (*it)->serialize() << std::endl;
    }

    medienFile.close();

    // Personendatei speichern
    std::ofstream personenFile("personen.csv", std::ios::trunc);
    if (!personenFile.is_open()) {
        std::cout << "Personendatei konnte nicht geschrieben werden!" << std::endl;
        return;
    }

    for (std::vector<Person>::iterator it = this->personen.begin(); it != this->personen.end(); ++it) {
        personenFile << it->serialize() << std::endl;
    }

    personenFile.close();

    // Ausleihdatei speichern
    std::ofstream ausleihenFile("ausleihen.csv", std::ios::trunc);
    if (!ausleihenFile.is_open()) {
        std::cout << "Ausleihen konnte nicht geschrieben werden!" << std::endl;
        return;
    }

    for (std::vector<Ausleihe>::const_iterator it = this->ausleihenVerwaltung.getAusleihen().begin(); it != this->ausleihenVerwaltung.getAusleihen().end(); ++it) {
        ausleihenFile << it->serialize() << std::endl;
    }

    ausleihenFile.close();


}

void MainWindow::on_neueAusleihe_clicked() {
    // ausleihende Person auswaehlen
    VerwaltePersonenDialog verwaltePersonen;
    verwaltePersonen.setTableData(&(this->personen));

    Person *ausleiher;
    verwaltePersonen.selectionMode(&ausleiher);
    verwaltePersonen.exec();

    if (ausleiher == NULL) return;

    std::cout << ausleiher->serialize() << std::endl;

    // auszuleihendes Medium auswaehlen
    VerwalteMedienDialog verwalteMedien;
    verwalteMedien.setTableData(&(this->medien));

    Medium *medium;
    verwalteMedien.selectionMode(&medium);
    verwalteMedien.exec();

    if (medium == NULL) return;

    std::cout << medium->serialize() << std::endl;

    // Ausleihe erzeugen
    Ausleihe ausleihe(ausleiher, medium, 30);

    std::cout << ausleihe.serialize() << std::endl;

    this->ausleihenVerwaltung.ausleihen(ausleihe);

    this->updateAusleihTable();
}

void MainWindow::on_actionBuecher_verwalten_triggered()
{
    VerwalteMedienDialog verwalteMedien;
    verwalteMedien.setTableData(&(this->medien));
    verwalteMedien.setTab(MediumTypes::BUCH);
    connect(&verwalteMedien,
            SIGNAL(accepted()),
            SLOT(updateAusleihTable()));
    verwalteMedien.exec();
}

void MainWindow::on_actionFilme_verwalten_triggered()
{
    VerwalteMedienDialog verwalteMedien;
    verwalteMedien.setTableData(&(this->medien));
    verwalteMedien.setTab(MediumTypes::FILM);
    connect(&verwalteMedien,
            SIGNAL(accepted()),
            SLOT(updateAusleihTable()));
    verwalteMedien.exec();
}

