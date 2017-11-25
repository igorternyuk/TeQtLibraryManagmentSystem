#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "dialogauthor.hpp"
#include "dialogcountry.hpp"
#include "dialoggenre.hpp"
#include "dialogedition.hpp"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QDate>
#include <QMessageBox>

enum Columns
{
    ID,
    TITLE,
    PAGES,
    DOP,
    GENRE,
    AUTHOR,
    EDITION,
    PRICE,
    AVAILABLE
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDB("library", "igorternyuk", "1319", "127.0.0.1", 3306)
{
    ui->setupUi(this);
    this->setWindowTitle("TeQtLibraryManagmentSystem");
    QString error;
    if(!mDB.openConnection(error))
    {
        QMessageBox::critical(this, "Database error", error);
        close();
    }

    mModel = new QSqlRelationalTableModel(this);
    mModel->setTable("book");
    mModel->setHeaderData(ID, Qt::Horizontal, tr("ID"));
    mModel->setHeaderData(TITLE, Qt::Horizontal, tr("Title"));
    mModel->setHeaderData(PAGES, Qt::Horizontal, tr("Number of pages"));
    mModel->setHeaderData(DOP, Qt::Horizontal, tr("Date of publication"));
    mModel->setHeaderData(GENRE, Qt::Horizontal, tr("Genre"));
    mModel->setHeaderData(AUTHOR, Qt::Horizontal, tr("Author"));
    mModel->setHeaderData(EDITION, Qt::Horizontal, tr("Edition"));
    mModel->setHeaderData(PRICE, Qt::Horizontal, tr("Price"));
    mModel->setHeaderData(AVAILABLE, Qt::Horizontal, tr("Number of examples"));
    mModel->setRelation(GENRE, QSqlRelation("genre", "id", "name"));
    mModel->setRelation(AUTHOR, QSqlRelation("author", "id", "name"));
    mModel->setRelation(EDITION, QSqlRelation("edition", "id", "name"));
    ui->tableView->setModel(mModel);
    mDelegate = new QSqlRelationalDelegate(this);
    ui->tableView->setItemDelegate(mDelegate);
    mModel->select();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({
                                  ui->action_insert_book,
                                  ui->action_remove_book,
                                  ui->action_search_book
                              });
    ui->dateEditMax->setDate(QDate::currentDate());
    ui->dateEditMIn->setDate(QDate::currentDate());
    /*

CREATE TABLE book (
    id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    title TEXT,
    pages INTEGER,
    DOP DATE,
    idGenre INTEGER,
    idAthor INTEGER,
    idEdition INTEGER,
    price DOUBLE,
    isAvailable BIT,
    FOREIGN KEY (idGenre) REFERENCES genre(id),
    FOREIGN KEY (idAthor) REFERENCES author(id),
    FOREIGN KEY (idEdition) REFERENCES edition(id)
);
*/
    /*QSqlTableModel *model = new QSqlTableModel;
     model->setTable("employee");
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();
     model->removeColumn(0); // don't show the ID
     model->setHeaderData(0, Qt::Horizontal, tr("Name"));
     model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

     QTableView *view = new QTableView;
     view->setModel(model);
     view->show();*/


}

MainWindow::~MainWindow()
{
    mDB.closeConnection();
    delete ui;
}

void MainWindow::on_action_close_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm exit",
                                        "Do you really want to exit?",
                                         QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
        this->close();
}

void MainWindow::on_action_edit_authors_triggered()
{
    DialogAuthor dialog(this);
    dialog.exec();
}

void MainWindow::on_action_manage_editions_triggered()
{
    DialogEdition dialog(this);
    dialog.exec();
}

void MainWindow::on_action_edit_countries_triggered()
{
    DialogCountry dialog(this);
    dialog.exec();
}

void MainWindow::on_action_edit_genres_triggered()
{
    DialogGenre dialog(this);
    dialog.exec();
}

void MainWindow::on_action_insert_book_triggered()
{
    mModel->insertRow(mModel->rowCount());
}

void MainWindow::on_action_remove_book_triggered()
{
    auto answer = QMessageBox::question(this, "Confirm deleting",
                                        "Do you really want to delete"
                                        " selected book?",
                                        QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        mModel->removeRow(ui->tableView->currentIndex().row());
        mModel->select();
    }
}

void MainWindow::on_action_search_book_triggered()
{
    mModel->select();
}


