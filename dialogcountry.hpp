#ifndef DIALOGCOUNTRY_H
#define DIALOGCOUNTRY_H

#include <QDialog>

namespace Ui {
class DialogCountry;
}

class DialogCountry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCountry(QWidget *parent = 0);
    ~DialogCountry();

private:
    Ui::DialogCountry *ui;
};

#endif // DIALOGCOUNTRY_H
