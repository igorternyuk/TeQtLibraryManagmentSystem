#include "dialogauthor.hpp"
#include "ui_dialogauthor.h"
#include <QSqlTableModel>
#include <QMessageBox>

DialogAuthor::DialogAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAuthor)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage authors");
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->addActions({ ui->action_insert_new_author,
                                ui->action_remove_selected_author,
                                ui->action_reload_list_of_authors});

    connect(ui->btnNewAuthor, &QPushButton::clicked, this,
            &DialogAuthor::on_action_insert_new_author_triggered);
    connect(ui->btnRemoveAuthor, &QPushButton::clicked, this,
            &DialogAuthor::on_action_remove_selected_author_triggered);
    connect(ui->btnReloadAuthors, &QPushButton::clicked, this,
            &DialogAuthor::on_action_reload_list_of_authors_triggered);

    mModel = new QSqlTableModel(this);
    mModel->setTable("author");
    ui->tableView->setModel(mModel);
    mModel->select();
}

DialogAuthor::~DialogAuthor()
{
    delete ui;
}

void DialogAuthor::on_action_insert_new_author_triggered()
{
    mModel->insertRow(mModel->rowCount());
    //mModel->select();
}

void DialogAuthor::on_action_remove_selected_author_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm deleting",
                                        "Do you really want to delete"
                                        " selected author?",
                                        QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        mModel->removeRow(ui->tableView->currentIndex().row());
        mModel->select();
    }
}

void DialogAuthor::on_action_reload_list_of_authors_triggered()
{
    mModel->select();
}
