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
    explicit DialogBookSearch(QWidget *parent = nullptr);
    ~DialogBookSearch();

private:
    Ui::DialogBookSearch *ui;
};

