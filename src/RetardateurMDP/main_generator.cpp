
#include "PasswordGenerator.hpp"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PasswordGenerator w;
    w.show();

    return a.exec();
}

