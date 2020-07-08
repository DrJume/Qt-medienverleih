#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Person.h"
#include "Medium.h"
#include "Ausleihe.h"

#include <AusleihVerwaltung.h>

#include "verwalteDatenTabelle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionPersonen_verwalten_triggered();

    void on_actionSpeichern_triggered();

    void on_neueAusleihe_clicked();

    void on_actionBuecher_verwalten_triggered();

    void on_actionFilme_verwalten_triggered();

    void ausleihContextMenu(const QPoint& pos);

    void updateAusleihTable();

    void on_actionOeffnen_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Person> personen;
    std::vector<Medium*> medien;
    AusleihVerwaltung ausleihenVerwaltung;

    void ausleiheZurueckgeben(int row);

};
#endif // MAINWINDOW_H
