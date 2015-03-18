
#ifndef PASSWORD_RULE_WIDGET_HPP
#define PASSWORD_RULE_WIDGET_HPP

#include <QFrame>
#include "PasswordSerializer.hpp"


namespace Ui
{
    class PasswordRuleWidget;
}

class PasswordRuleWidget : public QFrame
{
    Q_OBJECT

    public:

    explicit PasswordRuleWidget(QWidget *parent, PasswordSerializer* serializer);
    ~PasswordRuleWidget();

    void deleteThis(bool getInfo);


    private slots:

    void on_min_timeEdit_timeChanged(const QTime &time);
    void on_max_timeEdit_timeChanged(const QTime &time);
    void on_remove_button_clicked();


    private:

    void timeChanged();

    Ui::PasswordRuleWidget *ui; // has-a
    PasswordSerializer* m_serializer; // use-a
};


#endif // PASSWORD_RULE_WIDGET_HPP
