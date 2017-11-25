#pragma once

#include <QMainWindow>
#include "database.hpp"

namespace Ui 
{
    class MainWindow;
}

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class ComboBoxSqlModel;
class DialogAuthor;
class DialogEdition;
class DialogCountry;
class DialogGenre;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_close_triggered();
    void on_action_edit_authors_triggered();
    void on_action_manage_editions_triggered();
    void on_action_edit_genres_triggered();
    void on_action_edit_countries_triggered();

    void on_action_insert_book_triggered();
    void on_action_remove_book_triggered();
    void on_action_search_book_triggered();

    void on_btnSearchBook_clicked();
    void on_btnResetForm_clicked();

private:
    Ui::MainWindow *ui;
    Database mDB;
    QSqlRelationalTableModel *mModel;
    QSqlRelationalDelegate *mDelegate;
    DialogAuthor *mDialogAuthor;
    DialogEdition *mDialogEdition;
    DialogCountry *mDialogCountry;
    DialogGenre *mDialogGenre;

    ComboBoxSqlModel *mComboModelAuthor;
    ComboBoxSqlModel *mComboModelCountry;
    ComboBoxSqlModel *mComboModelGenre;
    ComboBoxSqlModel *mComboModelEdition;
    void fillComboBoxes();
};
