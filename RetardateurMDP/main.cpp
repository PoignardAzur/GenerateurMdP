#include "retardeurMdp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenerateurMdP w;
    w.show();

    return a.exec();
}


