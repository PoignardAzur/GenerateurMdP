
#include "PasswordRuleWidget.hpp"
#include "ui_PasswordRuleWidget.h"


PasswordRuleWidget::PasswordRuleWidget(QWidget *parent, PasswordSerializer* serializer) :
QFrame(parent), ui(new Ui::PasswordRuleWidget), m_serializer(serializer)
{
    ui->setupUi(this);
    QFrame::setFrameShadow(QFrame::Raised);
    //QFrame::setFrameShape(QFrame::Box);
    QFrame::setFrameShape(QFrame::Panel);
}

PasswordRuleWidget::~PasswordRuleWidget()
{
    delete ui;
}

void PasswordRuleWidget::deleteThis(bool getInfo)
{
    if (getInfo)
    {
        Rule r;

        r.minTime = ui->min_timeEdit->time().msecsSinceStartOfDay();
        r.maxTime = ui->max_timeEdit->time().msecsSinceStartOfDay();

        int day = ui->day_comboBox->currentIndex();

        switch (day)
        {
            case 0:
                r.monday = true;
                r.tuesday = true;
                r.wednesday = true;
                r.thursday = true;
                r.fryday = true;
                r.saturday = true;
                r.sunday = true;
            break;

            case 1:
                r.monday = true;
            break;

            case 2:
                r.tuesday = true;
            break;

            case 3:
                r.wednesday = true;
            break;

            case 4:
                r.thursday = true;
            break;

            case 5:
                r.fryday = true;
            break;

            case 6:
                r.saturday = true;
            break;

            case 7:
                r.sunday = true;
            break;
        }

        r.delay = ui->delay_timeEdit->time().msecsSinceStartOfDay();

        m_serializer->addRule(r);
    }

    deleteLater();
}

void PasswordRuleWidget::timeChanged()
{
    ui->min_timeEdit->setMaximumTime(ui->max_timeEdit->time());
    ui->max_timeEdit->setMinimumTime(ui->min_timeEdit->time());
}


void PasswordRuleWidget::on_min_timeEdit_timeChanged(const QTime &time)
{
    (void) time;
    timeChanged();
}

void PasswordRuleWidget::on_max_timeEdit_timeChanged(const QTime &time)
{
    (void) time;
    timeChanged();
}

void PasswordRuleWidget::on_remove_button_clicked()
{
    deleteLater();
}

