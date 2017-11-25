#include "dialogbooksearch.hpp"
#include "ui_dialogbooksearch.h"

DialogBookSearch::DialogBookSearch(const QString &sqlCmd,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBookSearch),
    mSqlCmd{ sqlCmd }
{
    ui->setupUi(this);
}

DialogBookSearch::~DialogBookSearch()
{
    delete ui;
}

void DialogBookSearch::sortBy(int index)
{

}

void DialogBookSearch::toggleDescOrder(bool isDesc)
{

}
