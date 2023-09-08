// WLB: see doc:
//
// http://doc.qt.io/qt-5/qtbluetooth-overview.html

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QBluetoothServer>
#include <QBluetoothAddress>
#include <QBluetoothSocket>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QBluetoothServiceInfo>
#include <QBluetoothTransferManager>
#include <QBluetoothTransferRequest>
#include <QBluetoothTransferReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_getPista_clicked()
{
    QMessageBox Msgbox;
        Msgbox.setText("ready to init pista");
        Msgbox.exec();

        Msgbox.setText("done");
        Msgbox.exec();
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::startDeviceDiscovery()
{

    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // Start a discovery
    discoveryAgent->start();

    //...
}

// In your local slot, read information about the found devices
void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
}

void MainWindow::pushFile() {
    // Create a transfer manager
    QBluetoothTransferManager *transferManager = new QBluetoothTransferManager(this);

    // Create the transfer request and file to be sent
    QBluetoothAddress remoteAddress("00:11:22:33:44:55:66");
    QBluetoothTransferRequest request(remoteAddress);
    QFile *file = new QFile("testfile.txt");

    // Ask the transfer manager to send it
    QBluetoothTransferReply *reply = transferManager->put(request, file);
    if (reply->error() == QBluetoothTransferReply::NoError) {

        // Connect to the reply's signals to be informed about the status and do cleanups when done
        QObject::connect(reply, SIGNAL(finished(QBluetoothTransferReply*)),
                         this, SLOT(transferFinished(QBluetoothTransferReply*)));
        QObject::connect(reply, SIGNAL(error(QBluetoothTransferReply::TransferError)),
                         this, SLOT(error(QBluetoothTransferReply::TransferError)));
    } else {
        qWarning() << "Cannot push testfile.txt:" << reply->errorString();
    }
}

void ChatClient::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void MainWindow::on_test0_clicked()
{

    try {
        QBluetoothLocalDevice localDevice;
        QString localDeviceName;
        QList<QBluetoothAddress> remotes;

        if (localDevice.isValid()) {

            // Turn Bluetooth on
            localDevice.powerOn();

            // Read local device name
            localDeviceName = localDevice.name();

            // Make it visible to others
            localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

            // Get connected devices
            QList<QBluetoothAddress> remotes;
            remotes = localDevice.connectedDevices();
        }

        Iterator<BluetoothDevice> iterator=remotes.Iterator();
        while (iterator.hasNext()) {
            BluetoothDevice device=iterator.next();
            Log.w(this.getClass().getSimpleName(),"Found "+device.getAddress()+" = "+device.getName());
            if (device.getName().equals("HC-06")) {

                    // connect
                    BluetoothSocket socket=device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                    socket.connect();
                    InputStream istream=socket.getInputStream();
                    OutputStream ostream=socket.getOutputStream();

                    // send
                    ostream.write("whatever\n".getBytes());

                    // receive
                    Thread.sleep(1000);
                    int avail=istream.available();
                    Log.w(this.getClass().getSimpleName(),"Received "+avail+" bytes");
                    BufferedReader br = new BufferedReader(new InputStreamReader(istream));
                    String s=br.readLine();
                    Log.w(this.getClass().getSimpleName(),"Received: "+s);
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }




}

void  MainWindow::timerEvent(QTimerEvent *event) {
    client->dev_tick();
}
