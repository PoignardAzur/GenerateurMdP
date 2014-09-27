#ifndef GENERATEURMDP_H
#define GENERATEURMDP_H

#include <QMainWindow>
#include <string>
#include <QTimer>

#define MINUTES_TO_WAIT_BY_DEFAULT 30
#define MINUTE_DURATION 60*1000
//#define MINUTE_DURATION 60
#define DEFAULT_PASSWORD_BUTTON_TEXT "Donner mot de passe"
#define PRESSED_PASSWORD_BUTTON_TEXT "Annuler mot de passe"
#define DEFAULT_WAITING_TEXT_1 "Temps restant : "
#define DEFAULT_WAITING_TEXT_2 " minute"
#define DEFAULT_WAITING_TEXT_3 " minutes"




namespace Ui {
class GenerateurMdP;
}

class GenerateurMdP : public QMainWindow
{
    Q_OBJECT

	public:
		explicit GenerateurMdP(QWidget *parent = 0);
		~GenerateurMdP();

        int minutesToWaitAtStart();

private slots:
        void on_getPasswordButton_pressed();
        void givingPassword();


        void on_resetPasswordButton_pressed();

        void on_resetListButton_pressed();

private:

        Ui::GenerateurMdP *ui;
        int m_minutesToWait;
        bool m_waitingButtonPressed;
		QTimer *m_timer;
};

std::string generateStr();
char generateLetter();
const std::string& getPassword();
std::string createNewPassword();
std::string shiftString(const std::string& copie, signed char decalage);

void resetLists();

#endif // GENERATEURMDP_H

