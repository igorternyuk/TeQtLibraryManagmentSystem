#include "dialogauthor.h"
#include "ui_dialogauthor.h"

DialogAuthor::DialogAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAuthor)
{
    ui->setupUi(this);
}

DialogAuthor::~DialogAuthor()
{
    delete ui;
}
