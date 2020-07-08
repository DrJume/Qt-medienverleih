#include "verwaltePersonenDialog.h"
#include "ui_verwaltePersonenDialog.h"

#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractItemView>

#include <vector>
#include <iostream>

#include "verwalteDatenTabelle.h"

VerwaltePersonenDialog::VerwaltePersonenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerwaltePersonenDialog)
{
    ui->setupUi(this);

    this->isSelectionMode=false;

    ui->personenTable->setHeaderCells({"Bib-Nr", "Vorname", "Nachname", "Geburtsjahr"});
    ui->personenTable->setColumnWidthWeights({1,3,3,2});

    ui->personenTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->personenTable,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(personenTableContextMenu(const QPoint&)));
}

VerwaltePersonenDialog::~VerwaltePersonenDialog()
{
    delete ui;
}

void VerwaltePersonenDialog::handleCellChange(int row, int col) {
    if (col != 0) return;

    QTableWidgetItem *cell = ui->personenTable->item(row, col);
    if (Person::findPerson(this->personen, cell->text().toStdString()) == NULL) return;

    cell->setText("");

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setWindowTitle("Ungültige Eingabe");
    msgBox.setText("'Bib-Nr' muss eindeutig bleiben!");
    msgBox.exec();

    return;
}

void VerwaltePersonenDialog::setTableData(std::vector<Person>* personen) {
    this->ui->personenTable->setRowCount(personen->size());

    for (int row=0; row < personen->size(); row++) {
        QTableWidgetItem *bibNrItem = new QTableWidgetItem(QString::fromStdString((*personen)[row].getBibNr()));
        bibNrItem->setFlags(bibNrItem->flags() ^ Qt::ItemIsEditable); // bibNr uneditierbar machen (in der normalen Auflistung)

        ui->personenTable->setItem(row, 0, bibNrItem);
        ui->personenTable->setCellText(row, 1, (*personen)[row].getVorname());
        ui->personenTable->setCellText(row, 2, (*personen)[row].getNachname());
        ui->personenTable->setCellText(row, 3, std::to_string((*personen)[row].getGeburtsJahr()));
    }

    // interne referenz behalten
    this->personen=personen;

    connect(ui->personenTable,
            SIGNAL(cellChanged(int,int)),
            SLOT(handleCellChange(int,int)));
}

void VerwaltePersonenDialog::on_modalButtons_accepted() { // Bei druecken von "Save"
    std::vector<Person>& personen = *(this->personen);

    // Daten aus der Tabelle in die Datenstruktur schreiben

    // durch alle Zeilen iterieren
    for (int row = 0; row < ui->personenTable->rowCount(); row++) {
        // Daten rauslesen
        std::string bibNr = ui->personenTable->getCellText(row,0);
        if (bibNr == "") {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setStandardButtons(QMessageBox::Close);
            msgBox.setWindowTitle("Ungültige Eingabe");
            msgBox.setText("'Bib-Nr' darf nicht leer sein!");
            msgBox.exec();
            return;
        }

        std::string vorname = ui->personenTable->getCellText(row,1);
        std::string nachname = ui->personenTable->getCellText(row,2);

        int geburtsJahr;
        try {
            geburtsJahr = ui->personenTable->getCellInt(row,3);
        } catch (...) {
            return;
        }

        // bei neuen Daten: auf Vorhandensein von bibNr pruefen und erstellen eines neuen Objekts in den Vector
        Person* existPerson = Person::findPerson(this->personen, bibNr);
        if (existPerson == NULL) { // (neues) Medium mit neuer inventarNr
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
    ui->personenTable->addNewEmptyRow();
}

void VerwaltePersonenDialog::selectionMode(Person **selection) { // Selektionsmodus fuer Ausleihfunktion
    this->isSelectionMode = true;
    *selection = NULL;
    this->selection = selection;

    this->setWindowTitle(QString::fromStdString("Person auswählen"));
    ui->neuePerson->hide();
    ui->personenTable->setContextMenuPolicy(Qt::NoContextMenu);
    ui->personenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->personenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->modalButtons->button(QDialogButtonBox::Save)->hide();
}

void VerwaltePersonenDialog::on_personenTable_cellDoubleClicked(int row, int column) {
    if (!this->isSelectionMode) return;

    *(this->selection) = &((*personen)[row]);
    this->accept();
}

void VerwaltePersonenDialog::personenTableContextMenu(const QPoint& pos){
    QTableWidgetItem* selected = ui->personenTable->itemAt(pos);
    if (selected == nullptr) return; // wenn keine Zeilen gerechtsklickt, dann auch kein context menu

    ui->personenTable->selectRow(selected->row()); // die Zeile der gerechtsklickten Zelle auswaehlen

    // context menu
    QMenu menu(ui->personenTable);
    menu.addAction(QIcon::fromTheme("edit-delete"), "Löschen", this, [this, selected] { VerwaltePersonenDialog::deletePerson(selected->row()); });
    menu.exec(ui->personenTable->viewport()->mapToGlobal(pos));
}


void VerwaltePersonenDialog::deletePerson(int row) {
    std::string IDtoDelete = ui->personenTable->getCellText(row,0);

    for (std::vector<Person>::iterator it = this->personen->begin(); it != this->personen->end(); ++it) {
        if (it->getID() == IDtoDelete) {
            this->personen->erase(it);
            break;
        }
    }

    ui->personenTable->removeRow(row);
}
