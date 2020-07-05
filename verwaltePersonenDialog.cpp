#include "verwaltePersonenDialog.h"
#include "ui_verwaltePersonenDialog.h"

#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>

#include <vector>
#include <iostream>

VerwaltePersonenDialog::VerwaltePersonenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerwaltePersonenDialog)
{
    ui->setupUi(this);

    QStringList personenTableSpalten({"Bib-Nr", "Vorname", "Nachname", "Geburtsjahr"});
    ui->personenTable->setColumnCount(personenTableSpalten.length());
    ui->personenTable->setHorizontalHeaderLabels(personenTableSpalten);
    ui->personenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void VerwaltePersonenDialog::contextMenuEvent(QContextMenuEvent *event){
    // gerechtsklickte Zeile aus der umgerechneten Position bekommen
    QTableWidgetItem* selected = ui->personenTable->itemAt(ui->personenTable->viewport()->mapFrom(this, event->pos()));
    if (selected == nullptr) return; // wenn keine Zeilen gerechtsklickt, dann auch kein context menu

    ui->personenTable->selectRow(selected->row()); // die Zeile der gerechtsklickten Zelle auswaehlen

    // context menu
    QMenu menu(this);
    menu.addAction(QIcon::fromTheme("edit-delete"), "Löschen", this, &VerwaltePersonenDialog::deleteRow);
    menu.exec(event->globalPos());
}

void VerwaltePersonenDialog::deleteRow(){
    // selektierte Zeilen (nur 1)
    QModelIndexList selection = ui->personenTable->selectionModel()->selectedRows();

    // loeschen der Zeilen
    for (QModelIndexList::iterator it = selection.begin(); it != selection.end(); ++it) {
        ui->personenTable->removeRow((*it).row());
    }
}

VerwaltePersonenDialog::~VerwaltePersonenDialog()
{
    delete ui;
}

void VerwaltePersonenDialog::setTableData(std::vector<Person>& personen) {
    this->ui->personenTable->setRowCount(personen.size());

    for (int row=0; row < personen.size(); row++) {
        QTableWidgetItem *bibNrItem = new QTableWidgetItem(QString::fromStdString(personen[row].getBibNr()));
        bibNrItem->setFlags(bibNrItem->flags() ^ Qt::ItemIsEditable); // bibNr uneditierbar machen (in der normalen Ansicht)

        ui->personenTable->setItem(row, 0, bibNrItem);
        ui->personenTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(personen[row].getVorname())));
        ui->personenTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(personen[row].getNachname())));
        ui->personenTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(personen[row].getGeburtsJahr()))));
    }

    // interne referenz behalten
    this->personen=&personen;
}

void VerwaltePersonenDialog::on_buttonBox_accepted() {
    std::vector<Person>& personen = *(this->personen);

    // durch alle Zeilen iterieren
    for (int row = 0; row < ui->personenTable->rowCount(); row++) {
        // Daten rauslesen
        std::string vorname = ui->personenTable->item(row,1)->text().toStdString();
        std::string nachname = ui->personenTable->item(row,2)->text().toStdString();
        int geburtsJahr;
        try {
            geburtsJahr = std::stoi(ui->personenTable->item(row,3)->text().toStdString());
        } catch (std::invalid_argument) {
            geburtsJahr = 0;
        }

        // bei neuen Daten: auf Vorhandensein von bibNr pruefen und erstellen eines neuen Objekts in den Vector
        if (row > personen.size()-1) {
            std::string bibNr = ui->personenTable->item(row,0)->text().toStdString();
            if (bibNr == "") {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setStandardButtons(QMessageBox::Close);
                msgBox.setWindowTitle("Fehler");
                msgBox.setText("BibNr darf nicht leer sein!");
                msgBox.exec();
                return;
            };

            personen.push_back(Person(bibNr, vorname, nachname, geburtsJahr));
            continue;
        }

        // bei reinem editieren Werte anpassen
        personen[row].setVorname(vorname);
        personen[row].setNachname(nachname);
        personen[row].setGeburtsJahr(geburtsJahr);
    }

    // wenn alles ok ist, Dialog schliessen
    this->accept();
}

void VerwaltePersonenDialog::on_neuePerson_clicked()
{
    // neue Zeile am Ende hinzufuegen und initialisieren
    int newRow = ui->personenTable->rowCount();
    ui->personenTable->insertRow(newRow);

    for (int col=0; col < ui->personenTable->columnCount(); col++) {
        ui->personenTable->setItem(newRow, col, new QTableWidgetItem());
    }
}
