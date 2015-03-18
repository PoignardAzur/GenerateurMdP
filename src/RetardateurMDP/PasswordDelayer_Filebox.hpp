
#ifndef PASSWORD_DELAYER_FILEBOX_HPP
#define PASSWORD_DELAYER_FILEBOX_HPP

#include <QWidget>


namespace Ui
{
    class PasswordDelayer_Filebox;
}

class PasswordDelayer_Filebox : public QWidget
{
    Q_OBJECT

    public:

    explicit PasswordDelayer_Filebox(QWidget *parent = nullptr);
    ~PasswordDelayer_Filebox();

    void changeMode(bool fileOpen);
    void waitingPassword(bool b);


    signals:

    void openPasswordFile(const QString& filename);
    void createPasswordFile(const QString& filename);
    void closeFile();

    void givePassword();
    void changePassword();
    void cancelGettingPassword();


    private slots:

    void on_path_lineEdit_textChanged(const QString &str);
    void on_path_button_clicked();

    void on_openFile_button_clicked();
    void on_createFile_button_clicked();

    void on_getPassword_button_clicked();
    void on_resetPassword_button_clicked();
    void on_closeFile_button_clicked();


    private:

    void updateButtons(const QString& filename);
    bool isThereFile(const QString& filename);
    QString getWrittenFilePath() const;

    Ui::PasswordDelayer_Filebox *ui;
    bool m_waitingPassword = false;
};


#endif // PASSWORD_DELAYER_FILEBOX_HPP
