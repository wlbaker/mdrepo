#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DemoWindow;
}

class DemoWindow : public QMainWindow
{
    Q_OBJECT

    // PistaDev *simu;

public:
    explicit DemoWindow(QWidget *parent = 0);
    ~DemoWindow();

    Ui::DemoWindow *getUI() { return ui; }

private slots:
    void on_nextButton_clicked();

    void on_simuButton_clicked();

    void on_realtime_clicked();

    void on_secCombo_currentTextChanged(const QString &arg1);

private:
    void initPista( );
    Ui::DemoWindow *ui;
};

#endif // MAINWINDOW_H
