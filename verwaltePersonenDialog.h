#ifndef VERWALTEPERSONENDIALOG_H
#define VERWALTEPERSONENDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include <vector>
#include "Medium.h"
#include "Person.h"

namespace Ui {
class VerwaltePersonenDialog;
}

class VerwaltePersonenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerwaltePersonenDialog(QWidget *parent = nullptr);
    ~VerwaltePersonenDialog();
    void setTableData(std::vector<Person>&);
    std::vector<Person>* personen;

private slots:
    void on_buttonBox_accepted();

    void on_neuePerson_clicked();

    void contextMenuEvent(QContextMenuEvent *event);

    void deleteRow();

private:
    Ui::VerwaltePersonenDialog *ui;
};

#endif // VERWALTEPERSONENDIALOG_H
