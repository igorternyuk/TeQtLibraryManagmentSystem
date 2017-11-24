#include "dialoggenre.h"
#include "ui_dialoggenre.h"

DialogGenre::DialogGenre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenre)
{
    ui->setupUi(this);
}

DialogGenre::~DialogGenre()
{
    delete ui;
}
