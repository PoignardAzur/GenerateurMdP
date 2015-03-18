
#include "PasswordDelayer_Filebox.hpp"
#include "ui_PasswordDelayer_Filebox.h"

#include <QFile>
#include <QFileDialog>


PasswordDelayer_Filebox::PasswordDelayer_Filebox(QWidget *parent) :
QWidget(parent), ui(new Ui::PasswordDelayer_Filebox)
{
    ui->setupUi(this);

    changeMode(false);
}

PasswordDelayer_Filebox::~PasswordDelayer_Filebox()
{
    delete ui;
}


void PasswordDelayer_Filebox::changeMode(bool fileOpen)
{
    // enable/disable File bar
    ui->path_button->setEnabled(!fileOpen);
    ui->path_lineEdit->setReadOnly(fileOpen);

    // show/hide File Mode buttons
    ui->openFile_button->setVisible(!fileOpen);
    ui->openFile_button->setEnabled(!fileOpen);
    ui->createFile_button->setVisible(!fileOpen);
    ui->createFile_button->setEnabled(!fileOpen);

    // show/hide Password Mode buttons
    ui->getPassword_button->setVisible(fileOpen);
    ui->getPassword_button->setEnabled(fileOpen);
    ui->resetPassword_button->setVisible(fileOpen);
    ui->resetPassword_button->setEnabled(fileOpen);
    ui->closeFile_button->setVisible(fileOpen);
    ui->closeFile_button->setEnabled(fileOpen);

    if (!fileOpen)
    {
        updateButtons(getWrittenFilePath());
    }
}

void PasswordDelayer_Filebox::waitingPassword(bool b)
{
    m_waitingPassword = b;

    if (m_waitingPassword)
    {
        ui->getPassword_button->setText("Annuler mot de passe");
    }

    else
    {
        ui->getPassword_button->setText("Donner mot de passe");
    }
}


void PasswordDelayer_Filebox::updateButtons(const QString& filename)
{
    if (filename.isEmpty())
    {
        ui->createFile_button->setEnabled(false);
        ui->openFile_button->setEnabled(false);
    }

    else
    {
        ui->createFile_button->setEnabled(true);
        ui->openFile_button->setEnabled(isThereFile(filename));
    }
}

bool PasswordDelayer_Filebox::isThereFile(const QString& filename)
{
    return QFile::exists(filename);
}

QString PasswordDelayer_Filebox::getWrittenFilePath() const
{
    return ui->path_lineEdit->text();
}


void PasswordDelayer_Filebox::on_path_lineEdit_textChanged(const QString &str)
{
    updateButtons(str);
}

void PasswordDelayer_Filebox::on_path_button_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Ouvrir fichier de Mot de Passe", getWrittenFilePath(), "*.mdp");
    //QString path = QFileDialog::getSaveFileName(this, "Ouvrir fichier de Mot de Passe", getWrittenFilePath(), "*.mdp");

    if (!path.isEmpty())
    {
        ui->path_lineEdit->setText(path);
    }
}


void PasswordDelayer_Filebox::on_openFile_button_clicked()
{
    if (isThereFile(getWrittenFilePath()))
    {
        openPasswordFile(getWrittenFilePath());
    }
}

void PasswordDelayer_Filebox::on_createFile_button_clicked()
{
    if (!getWrittenFilePath().isEmpty())
    {
        createPasswordFile(getWrittenFilePath());
    }
}


void PasswordDelayer_Filebox::on_getPassword_button_clicked()
{
    if (!m_waitingPassword)
    {
        givePassword();
    }

    else
    {
        cancelGettingPassword();
    }
}

void PasswordDelayer_Filebox::on_resetPassword_button_clicked()
{
    changePassword();
}

void PasswordDelayer_Filebox::on_closeFile_button_clicked()
{
    closeFile();
}

