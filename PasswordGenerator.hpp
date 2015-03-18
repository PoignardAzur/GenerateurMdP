
#ifndef PASSWORD_GENERATOR_HPP
#define PASSWORD_GENERATOR_HPP

#include <QMainWindow>


namespace Ui
{
    class PasswordGenerator;
}


class PasswordGenerator : public QWidget
{
    Q_OBJECT

    public:

    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

    void resetPassword();
    QString getPasswordStr() const;


    signals:

    void passwordChanged(const QString& str);


    private slots:

    void on_password_lineEdit_textChanged(const QString &str);
    void on_generatePassword_button_pressed();
    void on_drawPassword_checkbox_clicked();
    void on_copyToClipboard_button_pressed();


    private:

    char generateLetter();
    QString generateStr(size_t size);

    Ui::PasswordGenerator *ui;
    std::default_random_engine m_generator;
};


#endif // PASSWORD_GENERATOR_HPP
