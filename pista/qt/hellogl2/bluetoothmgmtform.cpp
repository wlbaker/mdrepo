#include "bluetoothmgmtform.h"
#include "ui_bluetoothmgmtform.h"


#include <QMenu>

#include <QtBluetooth/qbluetoothaddress.h>
#include <QtBluetooth/qbluetoothdevicediscoveryagent.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>


BluetoothMgmtForm::BluetoothMgmtForm(QWidget *parent) :
    QWidget(parent),
    localDevice(new QBluetoothLocalDevice),
    ui(new Ui::BluetoothMgmtForm)
{
    ui->setupUi(this);

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

       connect(ui->inquiryType, SIGNAL(toggled(bool)), this, SLOT(setGeneralUnlimited(bool)));
       connect(ui->scan, SIGNAL(clicked()), this, SLOT(startScan()));

       connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
               this, SLOT(addDevice(QBluetoothDeviceInfo)));
       connect(discoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

       connect(ui->list, SIGNAL(itemActivated(QListWidgetItem*)),
               this, SLOT(itemActivated(QListWidgetItem*)));

       connect(localDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
               this, SLOT(hostModeStateChanged(QBluetoothLocalDevice::HostMode)));

       hostModeStateChanged(localDevice->hostMode());
       // add context menu for devices to be able to pair device
       ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayPairingMenu(QPoint)));
       connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing))
           , this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));

}

BluetoothMgmtForm::~BluetoothMgmtForm()
{
    delete ui;
     delete discoveryAgent;
}


void BluetoothMgmtForm::addDevice(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::green));
        else
            item->setTextColor(QColor(Qt::black));

        ui->list->addItem(item);
    }

}

void BluetoothMgmtForm::startScan()
{
    discoveryAgent->start();
    ui->scan->setEnabled(false);
    ui->inquiryType->setEnabled(false);
}

void BluetoothMgmtForm::scanFinished()
{
    ui->scan->setEnabled(true);
    ui->inquiryType->setEnabled(true);
}

void BluetoothMgmtForm::setGeneralUnlimited(bool unlimited)
{
    if (unlimited)
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    else
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
}

void BluetoothMgmtForm::itemActivated(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));

    qDebug("ServiceDiscoveryDialog d(name, address);");
    qDebug("d.exec();");
}

void BluetoothMgmtForm::on_discoverable_clicked(bool clicked)
{
    if (clicked)
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
}

void BluetoothMgmtForm::on_power_clicked(bool clicked)
{
    if (clicked)
        localDevice->powerOn();
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
}

void BluetoothMgmtForm::hostModeStateChanged(QBluetoothLocalDevice::HostMode mode)
{
    if (mode != QBluetoothLocalDevice::HostPoweredOff)
        ui->power->setChecked(true);
    else
       ui->power->setChecked( false);

    if (mode == QBluetoothLocalDevice::HostDiscoverable)
        ui->discoverable->setChecked(true);
    else
        ui->discoverable->setChecked(false);

    bool on = !(mode == QBluetoothLocalDevice::HostPoweredOff);

    ui->scan->setEnabled(on);
    ui->discoverable->setEnabled(on);
}

void BluetoothMgmtForm::displayPairingMenu(const QPoint &pos)
{
    QMenu menu(this);
    QAction *pairAction = menu.addAction("Pair");
    QAction *removePairAction = menu.addAction("Remove Pairing");
    QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
    QListWidgetItem *currentItem = ui->list->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if (index == -1)
        return;

    QBluetoothAddress address (text.left(index));
    if (chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if (chosenAction == removePairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
}

void BluetoothMgmtForm::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::green));
        }
    } else {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::red));
        }
    }
}
