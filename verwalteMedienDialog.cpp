#include "verwalteMedienDialog.h"
#include "ui_verwalteMedienDialog.h"

#include "Medium.h"
#include "Buch.h"
#include "Film.h"
#include "AusleihVerwaltung.h"

#include <QTabBar>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QMenu>

#include <iostream>

VerwalteMedienDialog::VerwalteMedienDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerwalteMedienDialog)
{
    ui->setupUi(this);

    this->isSelectionMode=false;

    ui->buecherTable->setHeaderCells({"Inv-Nr", "Titel", "Wert", "Author", "Verlag", "Seiten"});
    ui->buecherTable->setColumnWidthWeights({1, 2, 1, 2, 2, 1});
    ui->filmeTable->setHeaderCells({"Inv-Nr", "Titel", "Wert", "Regisseur", "Dauer", "Altersfreigabe"});
    ui->filmeTable->setColumnWidthWeights({1, 3, 1, 3, 1, 2});

    ui->buecherTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->buecherTable,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(buecherTableContextMenu(const QPoint&)));

    ui->filmeTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->filmeTable,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(filmeTableContextMenu(const QPoint&)));
}

VerwalteMedienDialog::~VerwalteMedienDialog()
{
    delete ui;
}

void VerwalteMedienDialog::handleCellChange(int row, int col) {
    // Ueberpruefen ob bei einem Editieren der Medien eine bestehende Inventar-Nr eingefuegt  wird
    if (col != 0) return;

    QTableWidget *activeTable;
    switch (currentMedium) {
    case MediumTypes::BUCH:
        activeTable=ui->buecherTable;
        break;
    case MediumTypes::FILM:
        activeTable=ui->filmeTable;
        break;
    default:
        return;
        break;
    }

    QTableWidgetItem *cell = activeTable->item(row, col);
    if (cell == NULL) return;
    if (Medium::findMedium(this->medien, cell->text().toStdString()) == NULL) return;

    cell->setText("");

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setWindowTitle("Ungültige Eingabe");
    msgBox.setText("'Inventar-Nr' muss eindeutig bleiben!");
    msgBox.exec();

    return;
}

void VerwalteMedienDialog::setTab(char mediumType) {
    currentMedium=mediumType;

    switch (mediumType) {
    case MediumTypes::BUCH:
        ui->tabWidget->setCurrentWidget(ui->buecher);
        ui->createButton->setText(QString("Buch hinzufügen"));
        break;

    case MediumTypes::FILM:
        ui->tabWidget->setCurrentWidget(ui->filme);
        ui->createButton->setText(QString("Film hinzufügen"));
        break;
    default:
        break;
    }
}

void VerwalteMedienDialog::setTableData(std::vector<Medium*>* medien) {
    ui->buecherTable->setRowCount(0);
    ui->filmeTable->setRowCount(0);

    int buecherRow=0 , filmeRow=0;
    // durch den Medienvektor iterieren und anhand getType() die Eintraege entsprechend casten und die Tabelle fuellen
    for (int index=0; index < medien->size(); index++) {
        QTableWidgetItem *inventarNrItem = new QTableWidgetItem(QString::fromStdString((*medien)[index]->getInventarNr()));
        inventarNrItem->setFlags(inventarNrItem->flags() ^ Qt::ItemIsEditable); // inventarNr uneditierbar machen (in der normalen Auflistung)

        switch ((*medien)[index]->getType()) {
        case MediumTypes::BUCH: {
            ui->buecherTable->insertRow(ui->buecherTable->rowCount());

            Buch *buch = dynamic_cast<Buch*>((*medien)[index]);

            ui->buecherTable->setItem(buecherRow, 0, inventarNrItem);
            ui->buecherTable->setCellText(buecherRow, 1, (*medien)[index]->getTitel());
            ui->buecherTable->setCellText(buecherRow, 2, std::to_string((*medien)[index]->getWert()));
            ui->buecherTable->setCellText(buecherRow, 3, buch->getAuthor());
            ui->buecherTable->setCellText(buecherRow, 4, buch->getVerlag());
            ui->buecherTable->setCellText(buecherRow, 5, std::to_string(buch->getSeiten()));

            buecherRow++;
            break;
        }

        case MediumTypes::FILM: {
            ui->filmeTable->insertRow(ui->filmeTable->rowCount());

            Film *film = dynamic_cast<Film*>((*medien)[index]);

            ui->filmeTable->setItem(filmeRow, 0, inventarNrItem);
            ui->filmeTable->setCellText(filmeRow, 1, (*medien)[index]->getTitel());
            ui->filmeTable->setCellText(filmeRow, 2, std::to_string((*medien)[index]->getWert()));
            ui->filmeTable->setCellText(filmeRow, 3, film->getRegisseur());
            ui->filmeTable->setCellText(filmeRow, 4, std::to_string(film->getDauer()));
            ui->filmeTable->setCellText(filmeRow, 5, std::to_string(film->getAltersfreigabe()));

            filmeRow++;
            break;
        }

        default:
            break;
        }
    }

    // interne referenz behalten
    this->medien=medien;

    connect(ui->buecherTable,
            SIGNAL(cellChanged(int,int)),
            SLOT(handleCellChange(int,int)));

    connect(ui->filmeTable,
            SIGNAL(cellChanged(int,int)),
            SLOT(handleCellChange(int,int)));
}

void VerwalteMedienDialog::on_tabWidget_currentChanged() {
    const std::string currentTabName = ui->tabWidget->currentWidget()->objectName().toStdString();

    if (currentTabName == "buecher") {
        currentMedium = MediumTypes::BUCH;
    } else if (currentTabName == "filme") {
        currentMedium = MediumTypes::FILM;
    }

    // aktualisiere den Text des Erstellen-Buttons
    switch (currentMedium) {
    case MediumTypes::BUCH:
        ui->createButton->setText(QString("Buch hinzufügen"));
        break;
    case MediumTypes::FILM:
        ui->createButton->setText(QString("Film hinzufügen"));
        break;
    default:
        break;
    }
}

void VerwalteMedienDialog::on_modalButtons_accepted() { // Bei druecken von "Save"
    std::vector<Medium*> *medien = this->medien;

    // Daten aus der Tabelle in die Datenstruktur schreiben
    for (int i=0; i < ui->tabWidget->count(); i++) {
        const std::string tabName = ui->tabWidget->widget(i)->objectName().toStdString();

        char mediumType;
        if (tabName == "buecher") {
            mediumType = MediumTypes::BUCH;
        } else if (tabName == "filme") {
            mediumType = MediumTypes::FILM;
        }

        switch (mediumType) {
        case MediumTypes::BUCH: {
            // durch alle Zeilen iterieren
            for (int row = 0; row < ui->buecherTable->rowCount(); row++) {
                // Daten rauslesen
                std::string inventarNr = ui->buecherTable->getCellText(row, 0);
                if (inventarNr == "") {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setStandardButtons(QMessageBox::Close);
                    msgBox.setWindowTitle("Ungültige Eingabe");
                    msgBox.setText("'Inventar-Nr' darf nicht leer sein!");
                    msgBox.exec();
                    return;
                }

                std::string titel = ui->buecherTable->getCellText(row, 1);

                int wert;
                try {
                    wert = ui->buecherTable->getCellInt(row, 2);
                } catch (...) {
                    return;
                }

                std::string author = ui->buecherTable->getCellText(row, 3);
                std::string verlag = ui->buecherTable->getCellText(row, 4);

                int seiten;
                try {
                    seiten = ui->buecherTable->getCellInt(row, 5);
                } catch (...) {
                    return;
                }

                Medium* existMedium = Medium::findMedium(medien, inventarNr);
                if (existMedium == NULL) { // (neues) Medium mit neuer inventarNr
                    medien->push_back(new Buch(inventarNr, titel, wert, author, verlag, seiten));
                    continue;
                }

                // in den Vector einfuegen
                Buch *buch = dynamic_cast<Buch*>(existMedium);
                buch->setTitel(titel);
                buch->setWert(wert);
                buch->setAuthor(author);
                buch->setVerlag(verlag);
                buch->setSeiten(seiten);
            }
            break;
        }

        case MediumTypes::FILM: {
            // durch alle Zeilen iterieren
            for (int row = 0; row < ui->filmeTable->rowCount(); row++) {
                // Daten rauslesen
                std::string inventarNr = ui->filmeTable->getCellText(row, 0);
                if (inventarNr == "") {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setStandardButtons(QMessageBox::Close);
                    msgBox.setWindowTitle("Ungültige Eingabe");
                    msgBox.setText("'Inventar-Nr' darf nicht leer sein!");
                    msgBox.exec();
                    return;
                }

                std::string titel = ui->filmeTable->getCellText(row, 1);

                int wert;
                try {
                    wert = ui->filmeTable->getCellInt(row, 2);
                } catch (...) {
                    return;
                }

                std::string regisseur = ui->filmeTable->getCellText(row, 3);

                int dauer;
                try {
                    dauer = ui->filmeTable->getCellInt(row, 4);
                } catch (...) {
                    return;
                }


                int altersfreigabe;
                try {
                    altersfreigabe = ui->filmeTable->getCellInt(row, 5);
                } catch (...) {
                    return;
                }

                Medium* existMedium = Medium::findMedium(medien, inventarNr);
                if (existMedium == NULL) { // (neues) Medium mit neuer inventarNr
                    medien->push_back(new Film(inventarNr, titel, wert, regisseur, dauer, altersfreigabe));
                    continue;
                }

                // in den Vector einfuegen
                Film *film = dynamic_cast<Film*>(existMedium);
                film->setTitel(titel);
                film->setWert(wert);
                film->setRegisseur(regisseur);
                film->setDauer(dauer);
                film->setAltersfreigabe(altersfreigabe);
            }
            break;
        }

        default:
            break;
        }
    }

    // wenn alles ok ist, Dialog schliessen
    this->accept();
}

void VerwalteMedienDialog::on_createButton_clicked() {
    switch (currentMedium) {
    case MediumTypes::BUCH:
        ui->buecherTable->addNewEmptyRow();
        break;
    case MediumTypes::FILM:
        ui->filmeTable->addNewEmptyRow();
        break;
    default:
        break;
    }
}

void VerwalteMedienDialog::selectionMode(Medium **selection) { // Selektionsmodus fuer Ausleihfunktion
    this->isSelectionMode = true;
    *selection = NULL;
    this->selection = selection;

    this->setWindowTitle(QString("Medium auswählen"));
    ui->createButton->hide();
    for (int i=0; i < ui->tabWidget->count(); i++) {
        QTableWidget *table = qobject_cast<QTableWidget*>(ui->tabWidget->widget(i)->children()[0]);

        table->setContextMenuPolicy(Qt::NoContextMenu);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    ui->modalButtons->button(QDialogButtonBox::Save)->hide();
}


void VerwalteMedienDialog::on_buecherTable_cellDoubleClicked(int row, int column) {
    if (!this->isSelectionMode) return;

    (*this->selection) = Medium::findMedium(this->medien, ui->buecherTable->getCellText(row,0));

    this->accept();
}

void VerwalteMedienDialog::on_filmeTable_cellDoubleClicked(int row, int column) {
    if (!this->isSelectionMode) return;

    (*this->selection) = Medium::findMedium(this->medien, ui->filmeTable->getCellText(row,0));

    this->accept();
}

void VerwalteMedienDialog::buecherTableContextMenu(const QPoint& pos){
    QTableWidgetItem* selected = ui->buecherTable->itemAt(pos);
    if (selected == nullptr) return; // wenn keine Zeilen gerechtsklickt, dann auch kein context menu

    ui->buecherTable->selectRow(selected->row()); // die Zeile der gerechtsklickten Zelle auswaehlen

    // context menu
    QMenu menu(ui->buecherTable);
    menu.addAction(QIcon::fromTheme("edit-delete"), "Löschen", this, [this, selected] { VerwalteMedienDialog::deleteBuch(selected->row()); });
    menu.exec(ui->buecherTable->viewport()->mapToGlobal(pos));
}


void VerwalteMedienDialog::deleteBuch(int row) {
    std::string IDtoDelete = ui->buecherTable->getCellText(row,0);

    if (AusleihVerwaltung().istAusgeliehen(IDtoDelete)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setWindowTitle("Fehler beim Löschen");
        msgBox.setText("Dieses Buch ist noch ausgeliehen!");
        msgBox.exec();
        return;
    }

    for (std::vector<Medium*>::iterator it = this->medien->begin(); it != this->medien->end(); ++it) {
        if ((*it)->getID() == IDtoDelete) {
            delete (*it);
            this->medien->erase(it);
            break;
        }
    }

    ui->buecherTable->removeRow(row);
}

void VerwalteMedienDialog::filmeTableContextMenu(const QPoint& pos){
    QTableWidgetItem* selected = ui->filmeTable->itemAt(pos);
    if (selected == nullptr) return; // wenn keine Zeilen gerechtsklickt, dann auch kein context menu

    ui->filmeTable->selectRow(selected->row()); // die Zeile der gerechtsklickten Zelle auswaehlen

    // context menu
    QMenu menu(ui->filmeTable);
    menu.addAction(QIcon::fromTheme("edit-delete"), "Löschen", this, [this, selected] { VerwalteMedienDialog::deleteFilm(selected->row()); });
    menu.exec(ui->filmeTable->viewport()->mapToGlobal(pos));
}


void VerwalteMedienDialog::deleteFilm(int row) {
    std::string IDtoDelete = ui->filmeTable->getCellText(row,0);

    if (AusleihVerwaltung().istAusgeliehen(IDtoDelete)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setWindowTitle("Fehler beim Löschen");
        msgBox.setText("Dieser Film ist noch ausgeliehen!");
        msgBox.exec();
        return;
    }

    for (std::vector<Medium*>::iterator it = this->medien->begin(); it != this->medien->end(); ++it) {
        if ((*it)->getID() == IDtoDelete) {
            delete (*it);
            this->medien->erase(it);
            break;
        }
    }

    ui->filmeTable->removeRow(row);
}
