#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define STR_SIZE 12


namespace Ui {
class MainWindow;
}

std::string generateStr(int size = STR_SIZE);


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetMdp();

private slots:
    void on_pushButton_pressed();

    void on_drawPasswordCheckbox_clicked();

    void on_copyButton_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
