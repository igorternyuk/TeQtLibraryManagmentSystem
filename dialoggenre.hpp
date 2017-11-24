#ifndef DIALOGGENRE_H
#define DIALOGGENRE_H

#include <QDialog>

namespace Ui {
class DialogGenre;
}

class DialogGenre : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGenre(QWidget *parent = 0);
    ~DialogGenre();

private:
    Ui::DialogGenre *ui;
};

#endif // DIALOGGENRE_H
