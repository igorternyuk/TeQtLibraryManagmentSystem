#ifndef DIALOGBOOKSEARCH_H
#define DIALOGBOOKSEARCH_H

#include <QDialog>

namespace Ui {
class DialogBookSearch;
}

class DialogBookSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBookSearch(QWidget *parent = 0);
    ~DialogBookSearch();

private:
    Ui::DialogBookSearch *ui;
};

#endif // DIALOGBOOKSEARCH_H
