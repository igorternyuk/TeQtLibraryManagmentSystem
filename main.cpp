#include <QApplication>
#include "program.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    Program program;
    program.validateUser();
    return app.exec();
}
