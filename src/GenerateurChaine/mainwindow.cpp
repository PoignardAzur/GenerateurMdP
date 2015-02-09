#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <cstdlib>
#include <QClipboard>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setValue(STR_SIZE);
    srand(time(0));
    resetMdp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetMdp()
{
    ui->lineEdit->setText(generateStr(ui->spinBox->value()).c_str());
}



void MainWindow::on_pushButton_pressed()
{
    resetMdp();
}


void MainWindow::on_drawPasswordCheckbox_clicked()
{
    if (ui->drawPasswordCheckbox->isChecked())
    ui->lineEdit->setEchoMode(QLineEdit::Normal);

    else
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_copyButton_pressed()
{
    QApplication::clipboard()->setText( ui->lineEdit->text() );
}
