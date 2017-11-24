#ifndef DIALOGEDITION_H
#define DIALOGEDITION_H

#include <QDialog>

namespace Ui {
class DialogEdition;
}

class DialogEdition : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEdition(QWidget *parent = 0);
    ~DialogEdition();

private:
    Ui::DialogEdition *ui;
};

#endif // DIALOGEDITION_H
