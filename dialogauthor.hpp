#ifndef DIALOGAUTHOR_H
#define DIALOGAUTHOR_H

#include <QDialog>

namespace Ui {
class DialogAuthor;
}

class DialogAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAuthor(QWidget *parent = 0);
    ~DialogAuthor();

private:
    Ui::DialogAuthor *ui;
};

#endif // DIALOGAUTHOR_H
