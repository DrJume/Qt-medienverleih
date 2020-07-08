#ifndef VERWALTEMEDIENDIALOG_H
#define VERWALTEMEDIENDIALOG_H

#include <QDialog>
#include <QTableWidget>

#include <vector>

#include "Medium.h"

namespace Ui {
class VerwalteMedienDialog;
}

class VerwalteMedienDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerwalteMedienDialog(QWidget *parent = nullptr);
    ~VerwalteMedienDialog();
    void setTab(char mediumType);
    void setTableData(std::vector<Medium*>* medien);
    std::vector<Medium*> *medien;
    void selectionMode(Medium **selection);

private slots:
    void on_tabWidget_currentChanged();

    void on_modalButtons_accepted();

    void on_createButton_clicked();

    void on_buecherTable_cellDoubleClicked(int row, int column);

    void on_filmeTable_cellDoubleClicked(int row, int column);

    void handleCellChange(int row, int col);


    void buecherTableContextMenu(const QPoint& pos);
    void filmeTableContextMenu(const QPoint& pos);

private:
    Ui::VerwalteMedienDialog *ui;
    char currentMedium;
    bool isSelectionMode;
    Medium **selection;

    void deleteBuch(int row);
    void deleteFilm(int row);
};

#endif // VERWALTEMEDIENDIALOG_H
