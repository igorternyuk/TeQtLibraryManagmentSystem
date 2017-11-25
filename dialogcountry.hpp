#pragma once

#include <QDialog>

namespace Ui
{
    class DialogCountry;
}

class QSqlTableModel;

class DialogCountry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCountry(QWidget *parent = nullptr);
    ~DialogCountry();

private slots:
    void on_action_insert_new_country_triggered();
    void on_action_remove_selected_country_triggered();
    void on_action_reload_list_of_countries_triggered();

private:
    Ui::DialogCountry *ui;
    QSqlTableModel *mModel;
};

