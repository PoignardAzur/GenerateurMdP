
#include "PasswordGenerator.hpp"
#include "ui_PasswordGenerator.h"

#include <random>

#include <QClipboard>
#include <QString>

const int STR_DEFAULT_SIZE = 12;


PasswordGenerator::PasswordGenerator(QWidget *parent) : QWidget(parent), ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);

    ui->passwordSize_spinbox->setValue(STR_DEFAULT_SIZE);
    resetPassword();

    ui->copyToClipboard_button->setVisible(!parent);
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}


char PasswordGenerator::generateLetter()
{
    char nombre = std::uniform_int_distribution<int>(0, 35)(m_generator);

    if (nombre < 26)
    return nombre + 'a';

//	else
    return nombre - 26 + '0';
}

QString PasswordGenerator::generateStr(size_t size)
{
    QString str(size, ' ');

    for(size_t i = 0; i < size; ++i)
    {
        str[i] = generateLetter();
    }

    return str;
}

void PasswordGenerator::resetPassword()
{
    int size = ui->passwordSize_spinbox->value();
    ui->password_lineEdit->setText(generateStr(size));
}

QString PasswordGenerator::getPasswordStr() const
{
    return ui->password_lineEdit->text();
}


void PasswordGenerator::on_password_lineEdit_textChanged(const QString &str)
{
    passwordChanged(str);
}

void PasswordGenerator::on_generatePassword_button_pressed()
{
    resetPassword();
}

void PasswordGenerator::on_drawPassword_checkbox_clicked()
{
    bool draw = ui->drawPassword_checkbox->isChecked();
    ui->password_lineEdit->setEchoMode(draw ? QLineEdit::Normal : QLineEdit::Password);
}

void PasswordGenerator::on_copyToClipboard_button_pressed()
{
    QApplication::clipboard()->setText(ui->password_lineEdit->text());
}

