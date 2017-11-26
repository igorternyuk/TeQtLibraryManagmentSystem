#include "program.hpp"
#include "loginform.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <QDesktopWidget>
#ifdef DEBUG
#include <QDebug>
#endif

Program::Program(QObject *parent):
    QObject(parent),
    mDB("library", "igorternyuk", "1319", "127.0.0.1", 3306)
{
    QString error;
    mLoginForm = new LoginForm;
    mMainWindow = new MainWindow;
    connect(mLoginForm, &LoginForm::adminLoggedIn, this, &Program::showMainWindow);
    if(!mDB.openConnection(error))
    {
        mLoginForm->showError(error);
    }
}

Program::~Program()
{
    mDB.closeConnection();

    delete mMainWindow;
    delete mLoginForm;
}

void Program::validateUser()
{
    centralizeWidget(mLoginForm);
    mLoginForm->show();
}

void Program::showMainWindow()
{
    qDebug() << "Successfully logged in";
    centralizeWidget(mMainWindow);
    mMainWindow->show();
    mLoginForm->hide();
}

void Program::centralizeWidget(QWidget *widget)
{
    QRect desktop = QApplication::desktop()->geometry();
    auto dx = (desktop.width() - widget->width()) / 2;
    auto dy = (desktop.height() - widget->height()) / 2;
    widget->move(dx, dy);
    widget->show();
}
