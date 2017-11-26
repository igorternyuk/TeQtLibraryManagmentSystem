#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>

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
