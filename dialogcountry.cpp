#include "dialogcountry.h"
#include "ui_dialogcountry.h"

DialogCountry::DialogCountry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCountry)
{
    ui->setupUi(this);
}

DialogCountry::~DialogCountry()
{
    delete ui;
}
