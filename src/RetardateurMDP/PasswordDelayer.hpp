
#ifndef PASSWORD_DELAYER_HPP
#define PASSWORD_DELAYER_HPP

#include <QMainWindow>
#include <QString>
#include <QFile>

#include "PasswordSerializer.hpp"
#include "PasswordDelayer_Filebox.hpp"
#include "PasswordDelayer_MainBox.hpp"


namespace Ui
{
    class PasswordDelayer;
}

class PasswordDelayer : public QMainWindow
{
    Q_OBJECT

    public:

    explicit PasswordDelayer(QWidget *parent = nullptr);
    void connectSignals();
    ~PasswordDelayer();


    public slots:

    void openPasswordFile(const QString& filename);
    void createPasswordFile(const QString& filename);
    void closeFile();

    void changePassword(QString newMasterkey, bool createFile);


private slots:
    void on_masterKey_lineEdit_textChanged(const QString &arg1);

private:

    Ui::PasswordDelayer *ui;
    PasswordDelayer_Filebox* m_fileBox;
    PasswordDelayer_MainBox* m_mainBox;

    PasswordSerializer m_serializer;

    QFile m_file;
    bool m_isFileOpen = false;
    bool checkFile();

    void changeMode(bool fileOpen);

    void masterkeyChanged(const QString& masterkey);
    QString m_fileMasterkey;
};


#endif // PASSWORD_DELAYER_HPP
