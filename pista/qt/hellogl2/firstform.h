#ifndef FIRSTFORM_H
#define FIRSTFORM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class FirstForm;
}

class MainWindow;

class FirstForm : public QWidget
{
    Q_OBJECT

    MainWindow *wiz;
public:
    explicit FirstForm(MainWindow *wiz = 0, QWidget *parent = 0);
    ~FirstForm();

signals:
    void patientSignal();
    void dataSignal();
    void settingsSignal();

private slots:
    void on_patient_clicked();

private:
    Ui::FirstForm *ui;

};

#endif // FIRSTFORM_H
