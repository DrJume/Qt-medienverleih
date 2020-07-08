#include "verwalteDatenTabelle.h"

#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>

#include <iostream>
#include <vector>

void VerwalteDatenTabelle::setHeaderCells(std::initializer_list<QString> headerCells) {
    QStringList tableHeader(headerCells);
    this->setColumnCount(tableHeader.length());
    this->setHorizontalHeaderLabels(tableHeader);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    this->verticalHeader()->setVisible(false);

    std::vector<int> defaultWeights (headerCells.size(),1);
    this->setColumnWidthWeights(defaultWeights);
    this->horizontalHeader()->setStretchLastSection(true);
}

void VerwalteDatenTabelle::setColumnWidthWeights(std::vector<int> columnWidths) {
    int weightSum = 0;
    for (int i = 0; i < this->columnCount(); i++) {
        weightSum += columnWidths[i];
    }

    for (int i = 0; i < this->columnCount(); i++) {
        this->setColumnWidth(i, (double)columnWidths[i]/weightSum * (this->horizontalHeader()->width()));
    }
}

void VerwalteDatenTabelle::addNewEmptyRow() {
    // neue Zeile am Ende hinzufuegen und initialisieren
    int newRow = this->rowCount();
    this->insertRow(newRow);

    for (int col=0; col < this->columnCount(); col++) {
        this->setItem(newRow, col, new QTableWidgetItem());
    }
}

std::string VerwalteDatenTabelle::getCellText(int row, int col) {
    return this->item(row,col)->text().toStdString();
}

int VerwalteDatenTabelle::getCellInt(int row, int col) { // Tabelleneintrag gleich in int konvertieren
    int value;
    try {
        value = std::stoi(this->getCellText(row, col));
    } catch (std::invalid_argument) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setWindowTitle("Ungültige Eingabe");
        msgBox.setText("'" + this->horizontalHeaderItem(col)->text() + "' muss eine Zahl sein!");
        msgBox.exec();
        throw;
    }
    return value;
}

void VerwalteDatenTabelle::setCellText(int row, int col, std::string text) {
    this->setItem(row, col, new QTableWidgetItem(QString::fromStdString(text)));
}
