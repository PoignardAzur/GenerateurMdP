
#include <QMessageBox>
#include <QDate>

#include "ui_PasswordDelayer.h"
#include "PasswordDelayer.hpp"
#include "ChangePasswordDialog.hpp"


PasswordDelayer::PasswordDelayer(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::PasswordDelayer),
m_fileBox(new PasswordDelayer_Filebox(this)),
m_mainBox(new PasswordDelayer_MainBox(this))
{
    ui->setupUi(this);

    ui->boxes_layout->addWidget(m_fileBox);
    ui->boxes_layout->addWidget(m_mainBox);

    QWidget::setWindowTitle("Retardateur de mot de passe");
    connectSignals();
    changeMode(false);
}

void PasswordDelayer::connectSignals()
{
    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::openPasswordFile, this, &PasswordDelayer::openPasswordFile);
    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::createPasswordFile, this, &PasswordDelayer::createPasswordFile);
    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::closeFile, this, &PasswordDelayer::closeFile);

    auto f1 = [this]()
    {
        m_mainBox->givePassword(m_serializer.getPasswordStr(), m_serializer.waitingTime());
    };

    auto f2 = [this]()
    {
        changePassword(ui->masterKey_lineEdit->text(), false);
    };

    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::givePassword, f1);
    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::changePassword, f2);

    QObject::connect(m_fileBox, &PasswordDelayer_Filebox::cancelGettingPassword, m_mainBox, &PasswordDelayer_MainBox::cancelGettingPassword);
    QObject::connect(m_mainBox, &PasswordDelayer_MainBox::stateUpdated, m_fileBox, &PasswordDelayer_Filebox::waitingPassword);
}

PasswordDelayer::~PasswordDelayer()
{
    delete ui;
}


void PasswordDelayer::openPasswordFile(const QString& filename)
{
    m_file.setFileName(filename);
    m_file.open(QFile::ReadWrite);

    QString contents = m_file.readAll();
    QString masterkey = ui->masterKey_lineEdit->text();

    if (!m_serializer.load(contents, masterkey))
    {
        QMessageBox::warning(this, "Fichier illisible", "Le fichier ou la clé maître entrée est invalide.");
        m_file.close();
        return;
    }

    // else

    m_fileMasterkey = masterkey;
    changeMode(true);
}

void PasswordDelayer::createPasswordFile(const QString& filename)
{
    m_file.setFileName(filename);

    if (QFile::exists(filename))
    {
        QString str = QString("Le fichier %1 existe déjà, écraser le fichier ?").arg(filename);

        if (QMessageBox::question(this, "Ecraser fichier ?", str) == QMessageBox::No)
        {
            return;
        }
    }

    // else

    m_file.open(QFile::ReadWrite);
    m_isFileOpen = true;

    changePassword(ui->masterKey_lineEdit->text(), true);
    changeMode(true);
}

void PasswordDelayer::closeFile()
{
    m_file.close();
    changeMode(false);          // disables the password box, enables the file line, changes the button shown
    m_fileMasterkey = "";
}


bool PasswordDelayer::checkFile()
{
    bool fileOpen = m_file.isOpen();

    if (m_isFileOpen && !fileOpen)
    {
        QMessageBox::critical(this, "Fichier fermé", "Le fichier utilisé par ce programme s'est fermé durant son exécution.");
        closeFile();
        return false;
    }

    if (!m_isFileOpen && fileOpen) // should not happen
    {
        QMessageBox::warning(this, "Fichier ouvert", "Une erreur s'est produite. Un fichier n'a pas été fermé par ce programme.");
        closeFile();
        return false;
    }

    return true;
}


void PasswordDelayer::changePassword(QString newMasterkey, bool createFile)
{
    m_mainBox->cancelGettingPassword();

    if (!checkFile())
    {
        return;
    }

    if (newMasterkey != m_fileMasterkey && m_fileMasterkey != "")
    {
        QMessageBox::warning(this, "Mauvaise clé maître", "La clé maître entrée est invalide");
        return;
    }

    // else

    ChangePasswordDialog* d = new ChangePasswordDialog(this, &m_fileMasterkey, newMasterkey, createFile, &m_serializer);
    bool passwordChanged = d->exec();

    if (passwordChanged || createFile)
    {
        if (!passwordChanged)
        {
            m_serializer.setPasswordStr("DEFAULT_PASSWORD");
        }

        QString contents = m_serializer.serialize(m_fileMasterkey);

        m_file.resize(0);
        m_file.write(contents.toLatin1());
    }
}


void PasswordDelayer::changeMode(bool fileOpen)
{
    m_fileBox->changeMode(fileOpen);
    m_mainBox->changeMode(fileOpen);

    m_isFileOpen = fileOpen;
}


void PasswordDelayer::masterkeyChanged(const QString& masterkey)
{
    if (m_isFileOpen)
    {
        m_mainBox->masterkeyChanged(masterkey == m_fileMasterkey || m_fileMasterkey == "");
    }
}

void PasswordDelayer::on_masterKey_lineEdit_textChanged(const QString &str)
{
    masterkeyChanged(str);
}


