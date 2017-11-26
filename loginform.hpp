#ifndef LOGINFORM_HPP
#define LOGINFORM_HPP

#include <QDialog>

namespace Ui
{
    class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void showError(const QString &errorMessage);
signals:
    void adminLoggedIn();

private slots:
    void on_btnLogin_clicked();
    void on_btnClose_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_HPP
