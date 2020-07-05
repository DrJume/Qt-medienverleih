#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltePersonenDialog.h"
#include "verwalteMedienDialog.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList spalten({"Inventar-Nummer", "Typ", "Titel", "Ausleiher", "ausgeliehen am"});
    ui->tableWidget->setColumnCount(spalten.length());
    ui->tableWidget->setHorizontalHeaderLabels(spalten);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



    QTableWidgetItem *test = new QTableWidgetItem("Hello");
    ui->tableWidget->setItem(0, 0, test);

    this->personen  = {Person("111", "Olaf", "Scholz", 1980)};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPersonen_verwalten_triggered()
{
    VerwaltePersonenDialog verwaltePersonen;
    verwaltePersonen.setTableData(this->personen);
    verwaltePersonen.exec();
}

void MainWindow::on_actionSpeichern_triggered()
{

}

void MainWindow::on_neueAusleihe_clicked()
{

}

void MainWindow::on_actionBuecher_verwalten_triggered()
{
    VerwalteMedienDialog verwalteMedien;
//    verwalten.setTableData(this->personen);
    verwalteMedien.exec();
}

void MainWindow::on_actionFilme_verwalten_triggered()
{
    VerwalteMedienDialog verwalteMedien;
//    verwalten.setTableData(this->personen);
    verwalteMedien.exec();
}
