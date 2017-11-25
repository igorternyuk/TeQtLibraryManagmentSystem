#pragma once

#include <QDialog>

namespace Ui
{
    class DialogAuthor;
}

class QSqlTableModel;

class DialogAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAuthor(QWidget *parent = nullptr);
    ~DialogAuthor();

private slots:
    void on_action_insert_new_author_triggered();
    void on_action_remove_selected_author_triggered();
    void on_action_reload_list_of_authors_triggered();

private:
    Ui::DialogAuthor *ui;
    QSqlTableModel *mModel;
};
