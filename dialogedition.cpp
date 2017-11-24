#include "dialogedition.h"
#include "ui_dialogedition.h"

DialogEdition::DialogEdition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEdition)
{
    ui->setupUi(this);
}

DialogEdition::~DialogEdition()
{
    delete ui;
}
