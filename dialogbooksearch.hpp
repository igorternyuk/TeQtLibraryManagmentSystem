#pragma once

#include <QDialog>

namespace Ui
{
    class DialogBookSearch;
}

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
private slots:
    void sortBy(int index);
    void toggleDescOrder(bool isDesc = false);
};

