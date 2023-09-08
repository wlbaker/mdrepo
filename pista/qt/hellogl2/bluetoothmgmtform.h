#ifndef BLUETOOTHMGMTFORM_H
#define BLUETOOTHMGMTFORM_H

#include <QWidget>

#include <QListWidgetItem>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

// QT_USE_NAMESPACE



namespace Ui {
class BluetoothMgmtForm;
}

class BluetoothMgmtForm : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothMgmtForm(QWidget *parent = 0);
    ~BluetoothMgmtForm();

public slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void on_power_clicked(bool clicked);
    void on_discoverable_clicked(bool clicked);
    void displayPairingMenu(const QPoint &pos);
    void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);
private slots:
    void startScan();
    void scanFinished();
    void setGeneralUnlimited(bool unlimited);
    void itemActivated(QListWidgetItem *item);
    void hostModeStateChanged(QBluetoothLocalDevice::HostMode);

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    Ui::BluetoothMgmtForm *ui;
};

#endif // BLUETOOTHMGMTFORM_H
