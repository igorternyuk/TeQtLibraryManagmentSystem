#include "dialogbooksearch.hpp"
#include "ui_dialogbooksearch.h"

DialogBookSearch::DialogBookSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBookSearch)
{
    ui->setupUi(this);
}

DialogBookSearch::~DialogBookSearch()
{
    delete ui;
}
