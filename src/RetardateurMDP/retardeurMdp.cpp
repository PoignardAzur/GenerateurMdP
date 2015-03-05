
#include <QInputDialog>
#include <QDate>
#include <QClipboard>

#include "editPasswordFile.hpp"
#include "ui_generateurmdp.h"


GenerateurMdP::GenerateurMdP(QWidget *parent) : QMainWindow(parent), ui(new Ui::GenerateurMdP)
{
    ui->setupUi(this);
    m_timerByMinute = new QTimer;
    m_globalTimer = new QTimer;
    QObject::connect(m_timerByMinute, SIGNAL(timeout()), this, SLOT(givingPassword()));
    m_waitingButtonPressed = false;
    QWidget::setWindowTitle("Retardateur de mot de passe 3000");
}

GenerateurMdP::~GenerateurMdP()
{
    delete ui;
    delete m_timerByMinute;
}


int GenerateurMdP::timeToWaitAtStart()
{
    if (QDate::currentDate().dayOfWeek() == 1) //monday
    return MONDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 2) //tuesday
    return TUESDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 3) //wednesday
    return WEDNESDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 4) //thursday
    return THURSDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 5) //friday
    return FRIDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 6) //saturday
    return SATURDAY_WAIT_TIME;

    if (QDate::currentDate().dayOfWeek() == 7) //sunday
    return SUNDAY_WAIT_TIME;

    // not gonna happen
    return DEFAULT_WAIT_TIME; // the day the world ended
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

        m_globalTimer->start(timeToWaitAtStart());
        givingPassword();
    }

    else
    {
        cancelGettingPassword();
    }
}

void GenerateurMdP::on_resetPasswordButton_pressed()
{
    ui->getPasswordButton->setEnabled(true);
    cancelGettingPassword();
    QString str = QInputDialog::getText(this, "Nouveau mot de passe", "Entrez votre nouveau mot de passe :");

    if (str != "")
    createNewPassword(str.toStdString());
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


