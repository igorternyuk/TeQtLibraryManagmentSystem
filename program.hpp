#pragma once

#include <QObject>
#include "database.hpp"

class QWidget;
class LoginForm;
class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    ~Program();
    void validateUser();
private slots:
    void showMainWindow();
private:
    LoginForm *mLoginForm;
    MainWindow *mMainWindow;
    Database mDB;
    void centralizeWidget(QWidget *widget);
};
