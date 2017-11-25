#include "database.hpp"

Database::Database(const QString &databaseName, const QString &userName,
                   const QString &userPassword, const QString &server, int port,
                   const QString &driver)
{
    mDB = QSqlDatabase::addDatabase(driver);
    mDB.setDatabaseName(databaseName);
    mDB.setUserName(userName);
    mDB.setPassword(userPassword);
    mDB.setHostName(server);
    mDB.setPort(port);
}

bool Database::openConnection(QString &error)
{
    if(!mDB.open())
    {
        error = mDB.lastError().text();
        return false;
    }
    return true;
}

void Database::closeConnection()
{
    mDB.close();
}
