#ifndef VERWALTEPERSONENDIALOG_H
#define VERWALTEPERSONENDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include <vector>
#include "Medium.h"
#include "Person.h"
#include "verwalteDatenTabelle.h"

namespace Ui {
class VerwaltePersonenDialog;
}

class VerwaltePersonenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerwaltePersonenDialog(QWidget *parent = nullptr);
    ~VerwaltePersonenDialog();
    void setTableData(std::vector<Person>* personen);
    std::vector<Person>* personen;
    void selectionMode(Person **selection);

private slots:
    void on_modalButtons_accepted();

    void on_neuePerson_clicked();

    void on_personenTable_cellDoubleClicked(int row, int column);

    void handleCellChange(int row, int col);


    void personenTableContextMenu(const QPoint& pos);

private:
    Ui::VerwaltePersonenDialog *ui;
    bool isSelectionMode;
    Person** selection;

    void deletePerson(int row);

};

#endif // VERWALTEPERSONENDIALOG_H
