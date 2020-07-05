#include "verwalteMedienDialog.h"
#include "ui_verwalteMedienDialog.h"

#include <QTabBar>

VerwalteMedienDialog::VerwalteMedienDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerwalteMedienDialog)
{
    ui->setupUi(this);

    QStringList buecherTableSpalten({"Inv-Nr", "Titel", "Wert", "Author", "Verlag", "Seiten"});
    ui->buecherTable->setColumnCount(buecherTableSpalten.length());
    ui->buecherTable->setHorizontalHeaderLabels(buecherTableSpalten);
    ui->buecherTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList filmeTableSpalten({"Inv-Nr", "Titel", "Wert", "Regisseur", "Dauer", "Altersfreigabe"});
    ui->filmeTable->setColumnCount(filmeTableSpalten.length());
    ui->filmeTable->setHorizontalHeaderLabels(filmeTableSpalten);
    ui->filmeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setCurrentWidget(ui->filme);
}

VerwalteMedienDialog::~VerwalteMedienDialog()
{
    delete ui;
}
