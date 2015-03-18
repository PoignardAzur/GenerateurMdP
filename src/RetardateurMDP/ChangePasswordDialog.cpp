
#include "ChangePasswordDialog.hpp"
#include "ui_ChangePasswordDialog.h"
#include "PasswordRuleWidget.hpp"

#include <QSizePolicy>


ChangePasswordDialog::ChangePasswordDialog(QWidget* parent, QString* oldMasterkey, QString newMasterkey, bool createFile, PasswordSerializer* serializer) :
QDialog(parent), ui(new Ui::ChangePasswordDialog), m_serializer(serializer), m_masterkey(oldMasterkey)
{
    ui->setupUi(this);

    bool changeMasterkey = *oldMasterkey != newMasterkey;

    ui->changeMasterkey_box->setChecked(changeMasterkey);

    if ((changeMasterkey && *oldMasterkey == "") || createFile)
    {
        ui->changeMasterkey_box->setTitle("Ajouter clé maître");
    }

    if (createFile)
    {
        QDialog::setWindowTitle("Créer fichier mot de passe");
    }

    ui->masterkey_lineEdit->setText(newMasterkey);

    changePassword(false);  // no password is entered yet

    drawMasterkey(false);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;

    if (m_spacer)
    {
        delete m_spacer;
    }
}

void ChangePasswordDialog::changePassword(bool validPassword)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(validPassword);
}

void ChangePasswordDialog::addRule()
{
    PasswordRuleWidget* w = new PasswordRuleWidget(ui->rulesAreaContents, m_serializer);
    ui->ruleArea_layout->addWidget(w);

    QObject::connect(this, &ChangePasswordDialog::deleteRuleWidgets, w, &PasswordRuleWidget::deleteThis);

    if (m_spacer)
    {
        ui->ruleArea_layout->removeItem(m_spacer);
        delete m_spacer;
    }

    m_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->ruleArea_layout->addItem(m_spacer);
}

void ChangePasswordDialog::drawMasterkey(bool draw)
{
    ui->masterkey_lineEdit->setEchoMode(draw ? QLineEdit::Normal : QLineEdit::Password);
}

void ChangePasswordDialog::okPressed()
{
    m_serializer->reset();

    deleteRuleWidgets(true);
    m_serializer->setPasswordStr(ui->password_lineEdit->text());

    if (ui->changeMasterkey_box->isChecked())
    {
        *m_masterkey = ui->masterkey_lineEdit->text();
    }
}


void ChangePasswordDialog::on_addRule_button_clicked()
{
    addRule();
}

void ChangePasswordDialog::on_deleteRules_button_clicked()
{
    deleteRuleWidgets(false);
}

void ChangePasswordDialog::on_drawMasterkey_checkbox_toggled(bool checked)
{
    drawMasterkey(checked);
}

void ChangePasswordDialog::on_buttonBox_accepted()
{
    okPressed();
    accept();
}

void ChangePasswordDialog::on_buttonBox_rejected()
{
    reject();
}

void ChangePasswordDialog::on_password_lineEdit_textChanged(const QString &str)
{
    changePassword(str != "");
}

