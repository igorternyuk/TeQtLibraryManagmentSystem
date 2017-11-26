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
#include "comboboxsqlmodel.hpp"
#include "dialogbooksearch.hpp"
#ifdef DEBUG
#include <QDebug>
#endif

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
    ui(new Ui::MainWindow)
    //mDB("library", "igorternyuk", "1319", "127.0.0.1", 3306)
{
    ui->setupUi(this);
    this->setWindowTitle("TeQtLibraryManagmentSystem");


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

    configureComboBoxes();
}

MainWindow::~MainWindow()
{
    //mDB.closeConnection();
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
    mDialogAuthor->exec();
}

void MainWindow::on_action_manage_editions_triggered()
{
    mDialogEdition->exec();
}

void MainWindow::on_action_edit_countries_triggered()
{
    mDialogCountry->exec();
}

void MainWindow::on_action_edit_genres_triggered()
{
    mDialogGenre->exec();
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

void MainWindow::on_btnSearchBook_clicked()
{
    QString sql {"SELECT book.id AS ID, book.title AS Title, genre.name AS Genre," \
                 " author.name AS Author, edition.name AS Edition, book.pages AS Pages," \
                 " country.name AS Country, book.DOP AS DateOfPublication, book.price"
                 " AS Price, book.available AS NumberOfExamples FROM book" \
                 " INNER JOIN genre, author, edition, country WHERE book.idGenre = genre.id AND" \
                 " book.idAuthor = author.id AND book.idEdition = edition.id AND"\
                 " edition.idCountry = country.id AND book.title LIKE '%"};
    QString regExp { ui->txtSearch->text() };
    sql += regExp + "%' ";

    if(ui->checkBoxPages->isChecked())
    {
        auto pagesMin = ui->spinBoxPagesMin->value();
        auto pagesMax = ui->spinBoxPagesMax->value();
        sql += QString(" AND book.pages > %1  AND book.pages < %2").arg(pagesMin).arg(pagesMax);
    }

    if(ui->checkBoxPrice->isChecked())
    {
        auto priceMin = ui->spinBoxPriceMin->value();
        auto priceMax = ui->spinBoxPriceMax->value();
        sql += QString(" AND book.price > %1  AND book.price < %2").arg(priceMin).arg(priceMax);
    }

    if(ui->checkBoxDate->isChecked())
    {
        auto dateMin = ui->dateEditMIn->date().toString(Qt::ISODate);
        auto dateMax = ui->dateEditMax->date().toString(Qt::ISODate);

        sql += QString(" AND book.DOP > '%1'  AND book.DOP < '%2'").arg(dateMin).arg(dateMax);
    }

    if(ui->comboAuthores->currentIndex() > 0)
    {
        bool ok { false };
        auto id = ui->comboAuthores->itemData(ui->comboAuthores->currentIndex(),
                                              Qt::UserRole).toInt(&ok);
        if(ok)
            sql += QString(" AND author.id = %1").arg(id);
    }

    if(ui->comboCountries->currentIndex() > 0)
    {
        bool ok { false };
        auto id = ui->comboCountries->itemData(ui->comboCountries->currentIndex(),
                                               Qt::UserRole).toInt(&ok);
        if(ok)
            sql += QString(" AND country.id = %1").arg(id);
    }

    if(ui->comboGenres->currentIndex() > 0)
    {
        bool ok { false };
        auto id = ui->comboGenres->itemData(ui->comboGenres->currentIndex(),
                                            Qt::UserRole).toInt(&ok);
        if(ok)
            sql += QString(" AND genre.id = %1").arg(id);
    }

    if(ui->comboEditions->currentIndex() > 0)
    {
        bool ok { false };
        auto id = ui->comboEditions->itemData(ui->comboEditions->currentIndex(),
                                              Qt::UserRole).toInt(&ok);
        if(ok)
            sql += QString(" AND edition.id = %1").arg(id);
    }

    if(ui->checkBoxOnlyAvailables->isChecked())
    {
        sql += QString(" AND book.available > 0 ");
    }
#ifdef DEBUG
    qDebug() << "SQL = " << sql;
#endif
    DialogBookSearch dialog(sql, this);
    dialog.exec();
}

void MainWindow::on_btnResetForm_clicked()
{

}

void MainWindow::configureComboBoxes()
{
    //Authors

    mDialogAuthor = new DialogAuthor(this);
    mComboModelAuthor = new ComboBoxSqlModel("name", "author", this);
    ui->comboAuthores->setModel(mComboModelAuthor);
    connect(mDialogAuthor, &DialogAuthor::reloadData, [this](){
            mComboModelAuthor->reload();
            ui->comboAuthores->setCurrentIndex(0);
    });

    //Countries

    mDialogCountry = new DialogCountry(this);
    mComboModelCountry = new ComboBoxSqlModel("name", "country", this);
    ui->comboCountries->setModel(mComboModelCountry);
    connect(mDialogCountry, &DialogCountry::reloadData, [this](){
            mComboModelCountry->reload();
            ui->comboCountries->setCurrentIndex(0);
    });

    //Genres

    mDialogGenre = new DialogGenre(this);
    mComboModelGenre = new ComboBoxSqlModel("name", "genre", this);
    ui->comboGenres->setModel(mComboModelGenre);
    connect(mDialogGenre, &DialogGenre::reloadData,[this](){
            mComboModelGenre->reload();
            ui->comboGenres->setCurrentIndex(0);
    });

    //Editions

    mDialogEdition = new DialogEdition(this);
    mComboModelEdition = new ComboBoxSqlModel("name", "edition", this);
    ui->comboEditions->setModel(mComboModelEdition);
    connect(mDialogEdition, &DialogEdition::reloadData,[this](){
            mComboModelEdition->reload();
            ui->comboEditions->setCurrentIndex(0);
    });
}
