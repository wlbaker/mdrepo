#ifndef PATIENTFORM_H
#define PATIENTFORM_H

#include <QWidget>

class QAbstractButton;

namespace Ui {
class PatientForm;
}

class PatientForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientForm(QWidget *parent = 0);
    ~PatientForm();

signals:
    void deviceDetail(const QChar *devName );

private slots:
    void deviceClick();

private:
    Ui::PatientForm *ui;

    void addDevice(QLayout *layout, const char *devName, const char *resourceName );

};

#endif // PATIENTFORM_H
