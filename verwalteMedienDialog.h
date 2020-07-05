#ifndef VERWALTEMEDIENDIALOG_H
#define VERWALTEMEDIENDIALOG_H

#include <QDialog>

namespace Ui {
class VerwalteMedienDialog;
}

class VerwalteMedienDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerwalteMedienDialog(QWidget *parent = nullptr);
    ~VerwalteMedienDialog();

private:
    Ui::VerwalteMedienDialog *ui;
};

#endif // VERWALTEMEDIENDIALOG_H
