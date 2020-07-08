#ifndef VERWALTEDATENTABELLE_H
#define VERWALTEDATENTABELLE_H

#include <QTableWidget>

#include <string>

#include "Daten.h"

class VerwalteDatenTabelle : public QTableWidget
{

public:
    VerwalteDatenTabelle();
    VerwalteDatenTabelle(QWidget *parent) : QTableWidget(parent) {}

    void setHeaderCells(std::initializer_list<QString> headerCells);
    void setColumnWidthWeights(std::vector<int> columnWidths);
    void addNewEmptyRow();
    std::string getCellText(int row, int col);
    int getCellInt(int row, int col);
    void setCellText(int row, int col, std::string text);

};

#endif // VERWALTEDATENTABELLE_H
