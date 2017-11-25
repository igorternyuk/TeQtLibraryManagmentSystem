#pragma once

#include <QDialog>

namespace Ui
{
    class DialogGenre;
}

class QSqlTableModel;

class DialogGenre : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGenre(QWidget *parent = nullptr);
    ~DialogGenre();
    QSqlTableModel *model() const;

signals:
    void reloadData();

private slots:
    void on_action_insert_new_genre_triggered();
    void on_action_remove_selected_genre_triggered();
    void on_action_reload_list_of_genres_triggered();

private:
    Ui::DialogGenre *ui;
    QSqlTableModel *mModel;
};
