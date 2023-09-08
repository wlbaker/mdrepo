#include "settingsform.h"
#include "ui_settingsform.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkAddressEntry>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>

#include <QStandardPaths>
#include <QProcess>

#include <QScroller>

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    ui->editor->setReadOnly(true);
    connect( ui->bluetooth, SIGNAL(clicked(bool)), this, SIGNAL(bluetoothSignal()) );

    QScroller::grabGesture(ui->editor, QScroller::LeftMouseButtonGesture);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_wifi_clicked()
{

  //  nmcli device wifi list
    // ...better than iwlist scan

    // this will show NM pre-configured connections

    ui->editor->clear();
    ui->editor->appendPlainText("WIFI:\n\n");

    QNetworkConfiguration cfg;
    QNetworkConfigurationManager ncm;

    auto nc = ncm.allConfigurations();

    for(auto &x : nc ) {
         QString s = QObject::tr("Interface: ") + x.bearerType() + "\n";

         // if( x.bearerType() == QNetworkConfiguration::BearerWLAN )
         s += x.name();
         s += "\n";

         ui->editor->appendPlainText( s );
    }

    // auto session = QNetworkSession(cfg,this);
    // session -> open();
}

void SettingsForm::on_ports_clicked()
{
    ui->editor->clear();
    ui->editor->appendPlainText("Serial Ports:\n\n");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            QString s = QObject::tr("Port: ") + info.portName() + "\n"
                        + QObject::tr("Location: ") + info.systemLocation() + "\n"
                        + QObject::tr("Description: ") + info.description() + "\n"
                        + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                        + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                        + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                        + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                        + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
            ui->editor->appendPlainText( s );
    }
}

void SettingsForm::on_network_clicked()
{
    ui->editor->clear();
    ui->editor->appendPlainText("Network:\n\n");

    foreach (const QNetworkInterface &intf,  QNetworkInterface::allInterfaces() ) {
         QString s = QObject::tr("Interface: ") + intf.humanReadableName()+ "\n";
         foreach( const QNetworkAddressEntry &host, intf.addressEntries() ) {
             s += QObject::tr("  Address: ");
             s += host.ip().toString() + " netmask: " + host.netmask().toString();
             s += "\n";
         }

         ui->editor->appendPlainText( s );
    }
}


void append( QString& s, const QStringList &list ) {
    foreach (const QString &str, list) {
            s += QString("\n [%1] ").arg(str);
    }
}

void SettingsForm::on_storage_clicked()
{
    ui->editor->clear();
    ui->editor->appendPlainText("Storage:\n");

    QString s;
    s += "AppLocalDataLocation: ";
    append( s, QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation));
    s += "\nAppDataLocation: ";
     append( s,  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation));
    s += "\nAppConfigLocation: ";
     append( s,  QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation));
    s += "\n\n";

    ui->editor->appendPlainText( s );
    QProcess process;
    process.start("mount");
    process.waitForFinished(-1); // will wait forever until finished

    QString sout = process.readAllStandardOutput();
    // QString serr = process.readAllStandardError();

    ui->editor->appendPlainText( sout );


}
