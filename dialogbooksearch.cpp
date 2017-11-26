#include "dialogbooksearch.hpp"
#include "ui_dialogbooksearch.h"
#include <QSqlQueryModel>

DialogBookSearch::DialogBookSearch(const QString &sqlCmd,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBookSearch),
    mSqlCmd{ sqlCmd }
{
    ui->setupUi(this);
    this->setWindowTitle("Search results");
    mModel = new QSqlQueryModel(this);
    mModel->setQuery(mSqlCmd);
    if(mModel->rowCount() > 0)
    {
        ui->lblResults->setText("<span style =\" font-weight:600;color:green;\">" +
                                QString::number(mModel->rowCount()) +
                                " results found </span>");
    }
    else
    {
        ui->lblResults->setText("<span style =\" font-weight:600;color:red;\">"
                                "No results found </span>");
    }
    ui->tableView->setModel(mModel);
    ui->tableView->resizeColumnsToContents();
    connect(ui->checkBox, &QCheckBox::clicked, [this](){
        sortBy(ui->comboOrderBooks->currentIndex());
    });
    ui->comboOrderBooks->addItems({"ID", "Title", "Pages", "Date of publicaton",
                                   "Genre", "Author", "Edition", "Price",
                                   "Number of examples"});
    auto signal = static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged);
    connect(ui->comboOrderBooks, signal, this,
            &DialogBookSearch::sortBy);
    connect(ui->btnClose, &QPushButton::clicked, this, &DialogBookSearch::close);
}

DialogBookSearch::~DialogBookSearch()
{
    delete ui;
}

void DialogBookSearch::sortBy(int index)
{
    mModel->setQuery(mSqlCmd + this->getSortCommandTail(index) +
                     (ui->checkBox->isChecked() ? " DESC;" : ";"));
}

QString DialogBookSearch::getSortCommandTail(int index)
{
    switch(index)
    {
    case 1:
        return " ORDER BY book.title";
    case 2:
        return " ORDER BY book.pages";
    case 3:
        return " ORDER BY book.DOP";
    case 4:
        return " ORDER BY book.genre";
    case 5:
        return " ORDER BY book.author";
    case 6:
        return " ORDER BY book.edition";
    case 7:
        return " ORDER BY book.price";
    case 8:
        return " ORDER BY book.available";
    case 0:
    default:
        return " ORDER BY book.id";
    }
}
