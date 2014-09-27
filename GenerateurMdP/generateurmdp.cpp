#include "generateurmdp.h"
#include "ui_generateurmdp.h"





GenerateurMdP::GenerateurMdP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateurMdP)
{
    ui->setupUi(this);
    m_timer = new QTimer;
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(givingPassword()));
    m_waitingButtonPressed = false;
}

int GenerateurMdP::minutesToWaitAtStart()
{
	return MINUTES_TO_WAIT_BY_DEFAULT;
}


GenerateurMdP::~GenerateurMdP()
{
    delete ui;
	delete m_timer;
}




void GenerateurMdP::givingPassword()
{
    if (m_minutesToWait == 0)
    {
        ui->mainLine->setText(getPassword().c_str());
        ui->getPasswordButton->setEnabled(false);
    }

    else
    {
        if (m_minutesToWait == 1)
        ui->mainLine->setText(DEFAULT_WAITING_TEXT_1 + QString::number(m_minutesToWait) + DEFAULT_WAITING_TEXT_2);
        else
        ui->mainLine->setText(DEFAULT_WAITING_TEXT_1 + QString::number(m_minutesToWait) + DEFAULT_WAITING_TEXT_3);

		m_minutesToWait--;
		m_timer->start(MINUTE_DURATION);
    }
}





void GenerateurMdP::on_getPasswordButton_pressed()
{
    if(!m_waitingButtonPressed)
    {
        m_waitingButtonPressed = true;
        ui->getPasswordButton->setText(PRESSED_PASSWORD_BUTTON_TEXT);
		m_minutesToWait = minutesToWaitAtStart();
        givingPassword();
    }

    else
    {
        m_waitingButtonPressed = false;
        ui->getPasswordButton->setText(DEFAULT_PASSWORD_BUTTON_TEXT);
        ui->mainLine->setText("");
		m_minutesToWait = 1;
		m_timer->stop();
    }
}




void GenerateurMdP::on_resetPasswordButton_pressed()
{
    ui->getPasswordButton->setEnabled(true);
    on_getPasswordButton_pressed();
    ui->mainLine->setText(createNewPassword().c_str());
}

void GenerateurMdP::on_resetListButton_pressed()
{
    resetLists();
}
