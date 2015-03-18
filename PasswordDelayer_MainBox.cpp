
#include <QMessageBox>
#include <QClipboard>

#include "PasswordDelayer_MainBox.hpp"
#include "ui_PasswordDelayer_MainBox.h"

#include "predefinedValues.hpp"


PasswordDelayer_MainBox::PasswordDelayer_MainBox(QWidget *parent) :
QWidget(parent), ui(new Ui::PasswordDelayer_MainBox)
{
    ui->setupUi(this);

    QObject::connect(&m_updateDisplayTimer, &QTimer::timeout, this, &PasswordDelayer_MainBox::updateDisplay);

    changeMode(false);
}

PasswordDelayer_MainBox::~PasswordDelayer_MainBox()
{
    delete ui;
}


void PasswordDelayer_MainBox::givePassword(const QString& password, int timeToWait)
{
    m_password = password;
    m_passwordTimer.start(timeToWait);

    m_isWaitingForPassword = true;
    m_isMasterkeyValid = true;
    updateDisplay();

    stateUpdated(true);
}

void PasswordDelayer_MainBox::cancelGettingPassword()
{
    m_passwordTimer.stop();
    m_updateDisplayTimer.stop();

    m_password = "NO PASSWORD";

    m_isWaitingForPassword = false;
    m_isWaitOver = false;
    updateDisplay();

    stateUpdated(false);

    ui->copyToClipboard_button->setEnabled(false);
}


void PasswordDelayer_MainBox::changeMode(bool fileOpen)
{
    // enable/disable Password box
    ui->password_groupBox->setEnabled(fileOpen);

    if (!fileOpen)
    {
        cancelGettingPassword();
    }
}

void PasswordDelayer_MainBox::masterkeyChanged(bool valid)
{
    m_isMasterkeyValid = valid;
    ui->password_groupBox->setEnabled(m_isMasterkeyValid);

    if (!valid)
    {
        ui->drawPassword_checkBox->setChecked(false);
    }
}


void PasswordDelayer_MainBox::updateDisplay()
{
    if (m_isWaitingForPassword && timeToWait() == 0)
    {
        m_isWaitingForPassword = false;
        m_isWaitOver = true;

        ui->copyToClipboard_button->setEnabled(true);
    }

    if (m_isWaitingForPassword)
    {
        updateTimerDisplay();
    }

    else if (m_isWaitOver)
    {
        ui->mainLine->setEchoMode(isPasswordDrawn() ? QLineEdit::Normal : QLineEdit::Password);
        ui->mainLine->setText(m_password);
    }

    else
    {
        ui->mainLine->setEchoMode(QLineEdit::Normal);
        ui->mainLine->setText("");
    }
}

void PasswordDelayer_MainBox::updateTimerDisplay()
{
    if (timeToWait() / MINUTE_DURATION >= 2)
    {
        QString str = QString("Il reste %1 minutes").arg(timeToWait() / MINUTE_DURATION);
        ui->mainLine->setText(str);
        m_updateDisplayTimer.start((timeToWait() - 1) % MINUTE_DURATION);
    }

    else
    {
        if (timeToWait() / SECOND_DURATION > 1)
        {
            QString str = QString("Il reste %1 secondes").arg(timeToWait() / SECOND_DURATION);
            ui->mainLine->setText(str);
        }

        else
        {
            ui->mainLine->setText("Il reste une seconde");
        }

        m_updateDisplayTimer.start(SECOND_DURATION);
    }
}

int PasswordDelayer_MainBox::timeToWait()
{
    return m_passwordTimer.remainingTime();
}


void PasswordDelayer_MainBox::drawPassword(bool)
{
    if (m_isWaitOver)
    {
        updateDisplay();
    }
}

bool PasswordDelayer_MainBox::isPasswordDrawn()
{
    return ui->drawPassword_checkBox->isChecked();
}

void PasswordDelayer_MainBox::copyToClipboard()
{
    if (!m_isWaitOver)
    {
        QMessageBox::warning(this, "Opération impossible", "Le mot de passe n'est pas encore disponible.");
    }

    else
    {
        QApplication::clipboard()->setText(m_password);
    }
}


void PasswordDelayer_MainBox::on_copyToClipboard_button_clicked()
{
    copyToClipboard();
}

void PasswordDelayer_MainBox::on_drawPassword_checkBox_toggled(bool checked)
{
    drawPassword(checked);
}

