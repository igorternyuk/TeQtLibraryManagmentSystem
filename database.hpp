#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
/*
USE library;
SELECT book.id AS ID, book.title AS Title, genre.name AS Genre, author.name AS Author,
edition.name AS Edition, book.pages AS Pages, country.name AS Country, book.DOP AS DateOfPublication FROM book
INNER JOIN genre, author, edition, country WHERE book.idGenre = genre.id AND
book.idAuthor = author.id AND book.idEdition = edition.id AND edition.idCountry = country.id
AND book.title LIKE '%Papel%' AND book.DOP > '2005-05-17' AND book.pages < 3000
ORDER BY book.title DESC LIMIT 3;
*/

/*
Поиск по имени, автору, жанру, изданию, стране, диапазону дат и количеству страниц
с выводом результата в одлельное диалоговое окно с нередактируемой таблицей
Стратегия - QSqlQueryModel
*/
class Database
{
public:
    explicit Database(const QString &databaseName,
                      const QString &userName,
                      const QString &userPassword,
                      const QString &server,
                      int port,
                      const QString &driver = "QMYSQL");
    bool openConnection(QString &error);
    inline bool isOpened() const noexcept { return mDB.isOpen(); }
    void closeConnection();
private:
    QSqlDatabase mDB;
};
