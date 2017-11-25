#include "dialoggenre.hpp"
#include "ui_dialoggenre.h"
#include <QSqlTableModel>
#include <QMessageBox>

DialogGenre::DialogGenre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenre)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage genres");
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->addActions({ ui->action_insert_new_genre,
                                ui->action_remove_selected_genre,
                                ui->action_reload_list_of_genres});

    connect(ui->btnNewGenre, &QPushButton::clicked, this,
            &DialogGenre::on_action_insert_new_genre_triggered);
    connect(ui->btnRemoveGenre, &QPushButton::clicked, this,
            &DialogGenre::on_action_remove_selected_genre_triggered);
    connect(ui->btnReloadGenres, &QPushButton::clicked, this,
            &DialogGenre::on_action_reload_list_of_genres_triggered);

    mModel = new QSqlTableModel(this);
    mModel->setTable("genre");
    ui->tableView->setModel(mModel);
    mModel->select();
}

DialogGenre::~DialogGenre()
{
    delete ui;
}

void DialogGenre::on_action_insert_new_genre_triggered()
{
    mModel->insertRow(mModel->rowCount());
    //mModel->select();
}

void DialogGenre::on_action_remove_selected_genre_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm deleting",
                                        "Do you really want to delete"
                                        " selected genre?",
                                        QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        mModel->removeRow(ui->tableView->currentIndex().row());
        mModel->select();
    }
}

void DialogGenre::on_action_reload_list_of_genres_triggered()
{
    mModel->select();
}
