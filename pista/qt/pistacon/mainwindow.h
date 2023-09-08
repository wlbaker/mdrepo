#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "propaqdriver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void timerEvent(QTimerEvent *) override;

private slots:
    void on_getPista_clicked();

    void on_exitButton_clicked();

    void on_test0_clicked();

private:
    Ui::MainWindow *ui;
    PropaqDriver *client = nullptr;
};

#endif // MAINWINDOW_H
