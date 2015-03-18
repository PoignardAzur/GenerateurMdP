
#include "PasswordDelayer.hpp"
#include <QApplication>
#include "ChangePasswordDialog.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PasswordDelayer w;
    w.show();

//    QString masterkey;
//    PasswordSerializer serializer;

//    ChangePasswordDialog d(nullptr, &masterkey, false, &serializer);
//    d.show();

    return a.exec();
}


