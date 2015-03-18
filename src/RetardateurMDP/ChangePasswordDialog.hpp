
#ifndef CHANGE_PASSWORD_DIALOG_HPP
#define CHANGE_PASSWORD_DIALOG_HPP

#include <QDialog>
#include <QSpacerItem>
#include "PasswordSerializer.hpp"


namespace Ui
{
    class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

    public:

    explicit ChangePasswordDialog(QWidget* parent, QString* oldMasterkey, QString newMasterkey, bool createFile, PasswordSerializer* serializer);
    ~ChangePasswordDialog();


    signals :

    void deleteRuleWidgets(bool getInfo);


    private slots:

    void on_password_lineEdit_textChanged(const QString &str);

    void on_addRule_button_clicked();
    void on_deleteRules_button_clicked();

    void on_drawMasterkey_checkbox_toggled(bool checked);

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


    private:

    void changePassword(bool validPassword);
    void addRule();
    void drawMasterkey(bool draw);
    void okPressed();

    Ui::ChangePasswordDialog *ui; // has-a
    QSpacerItem* m_spacer = nullptr;

    PasswordSerializer* m_serializer; // use-a
    QString* m_masterkey;
};


#endif // CHANGE_PASSWORD_DIALOG_HPP
