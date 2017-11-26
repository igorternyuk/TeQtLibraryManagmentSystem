#include "loginform.hpp"
#include "ui_loginform.h"
#include <QSqlQuery>
#include <QSqlRecord>
#ifdef DEBUG
#include <QDebug>
#endif

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::showError(const QString &errorMessage)
{
    ui->lblStatus->setText("<span style =\" font-weight:600;color:red;\">"
                           + errorMessage + " </span>");
}

void LoginForm::on_btnLogin_clicked()
{
    QString username { ui->txtUserName->text() };
    QString password { ui->txtPassword->text() };
    QString cmd = QString("SELECT COUNT(*) AS number FROM library.admin WHERE"
                  " username = '%1' AND pass = '%2';").arg(username).arg(password);
#ifdef DEBUG
    qDebug() << "SQL = " << cmd;
#endif
    QSqlQuery query { cmd};
    QSqlRecord rec { query.record() };
    int nameCol { rec.indexOf("number") };
    if(query.next())
    {
        int numberOfResults { query.value(nameCol).toInt() };
#ifdef DEBUG
        qDebug() << "numberOfResults = " << numberOfResults;
#endif
        if(numberOfResults == 1)
        {
            emit adminLoggedIn();
        }
        else if(numberOfResults > 1)
        {
            ui->lblStatus->setText("<span style =\" font-weight:600;color:red;\">"
                                   "User data is duplicated </span>");
        }
        else
        {
            ui->lblStatus->setText("<span style =\" font-weight:600;color:red;\">"
                                   "Incorrect data </span>");
        }
    }
}

void LoginForm::on_btnClose_clicked()
{
    close();
}
