#include "editPasswordFile.hpp"
#include "ui_generateurmdp.h"
#include <QInputDialog>
#include <QDate>
#include <QClipboard>


GenerateurMdP::GenerateurMdP(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::GenerateurMdP)
{
    ui->setupUi(this);
    m_timerByMinute = new QTimer;
    m_globalTimer = new QTimer;
    QObject::connect(m_timerByMinute, SIGNAL(timeout()), this, SLOT(givingPassword()));
    m_waitingButtonPressed = false;
    QWidget::setWindowTitle("Retardateur de mot de passe 3000");
}


long long GenerateurMdP::minutesToWaitAtStart()
{
    if (QDate::currentDate().dayOfWeek() == 1) //monday
    return MINUTES_TO_WAIT_MONDAY;

    if (QDate::currentDate().dayOfWeek() == 2) //tuesday
    return MINUTES_TO_WAIT_TUESDAY;

    if (QDate::currentDate().dayOfWeek() == 3) //wednesday
    return MINUTES_TO_WAIT_WEDNESDAY;

    if (QDate::currentDate().dayOfWeek() == 4) //thursday
    return MINUTES_TO_WAIT_THURSDAY;

    if (QDate::currentDate().dayOfWeek() == 5) //friday
    return MINUTES_TO_WAIT_FRIDAY;

    if (QDate::currentDate().dayOfWeek() == 6) //saturday
    return MINUTES_TO_WAIT_SATURDAY;

    if (QDate::currentDate().dayOfWeek() == 7) //sunday
    return MINUTES_TO_WAIT_SUNDAY;

    return MINUTES_TO_WAIT_BY_DEFAULT; // the day the world ended
}


GenerateurMdP::~GenerateurMdP()
{
    delete ui;
    delete m_timerByMinute;
}




void GenerateurMdP::givingPassword()
{
    if (m_globalTimer->remainingTime() == 0)
    {
        ui->mainLine->setText(getPassword().c_str());
        ui->getPasswordButton->setEnabled(false);

        if (ui->drawPasswordCheckBox->isChecked())
        ui->mainLine->setEchoMode(QLineEdit::Normal);

        else
        ui->mainLine->setEchoMode(QLineEdit::Password);

        ui->copyToClipboardButton->setEnabled(true);
    }

    else
    {
        m_minutesToWait = (m_globalTimer->remainingTime() - 1) / MINUTE_DURATION + 1;

        if (m_minutesToWait == 1)
        ui->mainLine->setText(DEFAULT_WAITING_TEXT_1 + QString::number(m_minutesToWait) + DEFAULT_WAITING_TEXT_2);
        else
        ui->mainLine->setText(DEFAULT_WAITING_TEXT_1 + QString::number(m_minutesToWait) + DEFAULT_WAITING_TEXT_3);

        m_timerByMinute->start(MINUTE_DURATION);
    }
}


void GenerateurMdP::on_copyToClipboardButton_pressed()
{
    QApplication::clipboard()->setText(ui->mainLine->text());
}


void GenerateurMdP::on_getPasswordButton_pressed()
{
    if(!m_waitingButtonPressed)
    {
        m_waitingButtonPressed = true;
        ui->getPasswordButton->setText(PRESSED_PASSWORD_BUTTON_TEXT);

        m_globalTimer->start(minutesToWaitAtStart() * MINUTE_DURATION);
        givingPassword();
    }

    else
    {
        cancelGettingPassword();
    }
}

void GenerateurMdP::cancelGettingPassword()
{
    m_waitingButtonPressed = false;
    ui->getPasswordButton->setText(DEFAULT_PASSWORD_BUTTON_TEXT);
    ui->mainLine->setEchoMode(QLineEdit::Normal);
    ui->copyToClipboardButton->setEnabled(false);
    ui->mainLine->setText("");
    m_minutesToWait = 1;
    m_timerByMinute->stop();
}


void GenerateurMdP::on_resetPasswordButton_pressed()
{
    ui->getPasswordButton->setEnabled(true);
    cancelGettingPassword();
    QString str = QInputDialog::getText(this, "Nouveau mot de passe", "Entrez votre nouveau mot de passe :");

    if (str != "")
    createNewPassword(str.toStdString());
}








