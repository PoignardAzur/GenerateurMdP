
#ifndef GENERATEURMDP_H
#define GENERATEURMDP_H

#include <QMainWindow>
#include <string>
#include <QTimer>

#include "SQLite/statement.hpp"
#include "predefinedValues.hpp"


namespace Ui
{
    class GenerateurMdP;
}

class GenerateurMdP : public QMainWindow
{
    Q_OBJECT

    public:

    explicit GenerateurMdP(QWidget *parent = 0);
    ~GenerateurMdP();

    int timeToWaitAtStart();
    void cancelGettingPassword();


    private slots:

    void on_getPasswordButton_pressed();
    void givingPassword();

    void on_resetPasswordButton_pressed();
    void on_copyToClipboardButton_pressed();


    private:

    Ui::GenerateurMdP *ui;
    int m_minutesToWait;
    bool m_waitingButtonPressed;
    QTimer *m_timerByMinute;
    QTimer *m_globalTimer;
};


#endif // GENERATEURMDP_H
