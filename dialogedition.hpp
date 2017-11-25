#pragma once

#include <QDialog>

namespace Ui
{
    class DialogEdition;
}

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;

class DialogEdition : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEdition(QWidget *parent = nullptr);
    ~DialogEdition();
    QSqlRelationalTableModel *model() const;
signals:
    void reloadData();
private slots:
    void on_action_insert_new_edition_triggered();
    void on_action_remove_selected_edition_triggered();
    void on_action_reload_list_of_editions_triggered();

private:
    Ui::DialogEdition *ui;
    QSqlRelationalTableModel *mModel;
    QSqlRelationalDelegate *mDelegate;
};
