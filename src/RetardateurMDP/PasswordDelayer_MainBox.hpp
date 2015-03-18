#ifndef PASSWORD_DELAYER_MAINBOX_H
#define PASSWORD_DELAYER_MAINBOX_H

#include <QWidget>
#include <QTimer>


namespace Ui
{
    class PasswordDelayer_MainBox;
}

class PasswordDelayer_MainBox : public QWidget
{
    Q_OBJECT

    public:

    explicit PasswordDelayer_MainBox(QWidget *parent = nullptr);
    ~PasswordDelayer_MainBox();


    signals:

    void stateUpdated(bool gettingPassword);


    public slots :

    void givePassword(const QString& password, int timeToWait);
    void cancelGettingPassword();

    void changeMode(bool fileOpen);
    void masterkeyChanged(bool valid);


    private slots:

    void on_copyToClipboard_button_clicked();
    void on_drawPassword_checkBox_toggled(bool checked);


    private:

    Ui::PasswordDelayer_MainBox *ui;

    void updateDisplay();
    void updateTimerDisplay();
    int timeToWait();

    QString m_password;

    QTimer m_passwordTimer;
    QTimer m_updateDisplayTimer;

    bool m_isWaitingForPassword = false;
    bool m_isWaitOver = false;
    bool m_isMasterkeyValid = true;

    void drawPassword(bool);
    bool isPasswordDrawn();
    void copyToClipboard();
};


#endif // PASSWORD_DELAYER_MAINBOX_H
