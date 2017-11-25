#include "dialogedition.hpp"
#include "ui_dialogedition.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QMessageBox>

enum Columns
{
    ID,
    NAME,
    COUNTRY
};

DialogEdition::DialogEdition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEdition)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage editions");
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->addActions({ ui->action_insert_new_edition,
                                ui->action_remove_selected_edition,
                                ui->action_reload_list_of_editions});

    connect(ui->btnNewEdition, &QPushButton::clicked, this,
            &DialogEdition::on_action_insert_new_edition_triggered);
    connect(ui->btnRemoveEdition, &QPushButton::clicked, this,
            &DialogEdition::on_action_remove_selected_edition_triggered);
    connect(ui->btnReloadEditions, &QPushButton::clicked, this,
            &DialogEdition::on_action_reload_list_of_editions_triggered);

    mModel = new QSqlRelationalTableModel(this);

    mModel->setTable("edition");
    mModel->setHeaderData(ID, Qt::Horizontal, tr("ID"));
    mModel->setHeaderData(NAME, Qt::Horizontal, tr("Name"));
    mModel->setHeaderData(COUNTRY, Qt::Horizontal, tr("Country"));
    mModel->setRelation(COUNTRY, QSqlRelation("country", "id", "name"));
    ui->tableView->setModel(mModel);
    mDelegate = new QSqlRelationalDelegate(this);
    ui->tableView->setItemDelegate(mDelegate);
    mModel->select();
    ui->tableView->resizeColumnsToContents();
}

DialogEdition::~DialogEdition()
{
    delete ui;
}

void DialogEdition::on_action_insert_new_edition_triggered()
{
    mModel->insertRow(mModel->rowCount());
    //mModel->select();
}

void DialogEdition::on_action_remove_selected_edition_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm deleting",
                                        "Do you really want to delete"
                                        " selected edition?",
                                        QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        mModel->removeRow(ui->tableView->currentIndex().row());
        mModel->select();
    }
}

void DialogEdition::on_action_reload_list_of_editions_triggered()
{
    mModel->select();
}
