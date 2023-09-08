#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *e);

private slots:
    // void on_xRotSlider_valueChanged(int value);

    void on_manual_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
