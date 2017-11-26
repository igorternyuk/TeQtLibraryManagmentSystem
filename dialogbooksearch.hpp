#pragma once

#include <QDialog>

namespace Ui
{
    class DialogBookSearch;
}

class QSqlQueryModel;

class DialogBookSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookSearch(const QString &sqlCmd,
                              QWidget *parent = nullptr);
    ~DialogBookSearch();

private:
    Ui::DialogBookSearch *ui;
    QString mSqlCmd;
    QSqlQueryModel *mModel;
private slots:
    void sortBy(int index);
    QString getSortCommandTail(int index);
};

