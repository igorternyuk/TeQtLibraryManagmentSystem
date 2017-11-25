#include "dialogcountry.hpp"
#include "ui_dialogcountry.h"
#include <QSqlTableModel>
#include <QMessageBox>

DialogCountry::DialogCountry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCountry)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage countries");
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->addActions({ ui->action_insert_new_country,
                                ui->action_remove_selected_country,
                                ui->action_reload_list_of_countries});

    connect(ui->btnNewCountry, &QPushButton::clicked, this,
            &DialogCountry::on_action_insert_new_country_triggered);
    connect(ui->btnRemoveCountry, &QPushButton::clicked, this,
            &DialogCountry::on_action_remove_selected_country_triggered);
    connect(ui->btnReloadCountries, &QPushButton::clicked, this,
            &DialogCountry::on_action_reload_list_of_countries_triggered);

    mModel = new QSqlTableModel(this);
    mModel->setTable("country");
    ui->tableView->setModel(mModel);
    mModel->select();
}

DialogCountry::~DialogCountry()
{
    delete ui;
}

void DialogCountry::on_action_insert_new_country_triggered()
{
    mModel->insertRow(mModel->rowCount());
    //mModel->select();
}

void DialogCountry::on_action_remove_selected_country_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm deleting",
                                        "Do you really want to delete"
                                        " selected country?",
                                        QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        mModel->removeRow(ui->tableView->currentIndex().row());
        mModel->select();
    }
}

void DialogCountry::on_action_reload_list_of_countries_triggered()
{
    mModel->select();
}
