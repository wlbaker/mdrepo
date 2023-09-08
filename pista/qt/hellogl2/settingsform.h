#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

signals:
    void bluetoothSignal();
    void wifiSignal();

private slots:
    void on_ports_clicked();

    void on_network_clicked();

    void on_storage_clicked();
    void on_wifi_clicked();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
