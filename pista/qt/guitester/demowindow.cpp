#include "demowindow.h"
#include "ui_demowindow.h"

#include <QDesktopWidget>
#include <QMessageBox>

#include <iostream>

#include <pista-cl.h>

DemoWindow::DemoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DemoWindow)
{
    ui->setupUi(this);
    ui->devlistPage->setVisible(true);
    ui->viewPage->setVisible(false);

    resize( QDesktopWidget().availableGeometry(this).size() * 0.7);

    try {
        initPista();
    } catch(...) {
            QMessageBox Msgbox;
            Msgbox.setText("Error in init pista");
            Msgbox.exec();
    }

}

void DemoWindow::initPista( ) {

    QListWidget *v = ui->listWidget;

    PistaCl &pista = PistaCl::getInstance();
    for( int i = 0; i < pista.driver_count(); i++ ) {
        PistaDriver *driver = pista.driver(i);
        v->addItem( driver->longname() );
    }
}

DemoWindow::~DemoWindow()
{
    delete ui;
}

void DemoWindow::on_nextButton_clicked()
{
    ui->devlistPage->setVisible(false);
    ui->viewPage->setVisible(true);
    std::cout << "next done" << std::endl;

}


class PISTA_API H2 : public PistaEventHandler {

    GLInstrumentDisplay *instrument;
public:
    H2( GLInstrumentDisplay *instrument) {
        this->instrument = instrument;
    }

    virtual int event( PistaDataPacket *pkt ) {

        // pista_dump_packet( pkt->_packet() );
        // std::cout << "ZZZ pkt: " << pkt->getStreamID() << " --> " << "=" << pkt->getDescriptor(0)->loc << std::endl;

        if( pkt->getStreamID() == PISTA_DF_MEASUREMENT ) {
            instrument->vitals_slot(pkt->_packet());
        } else if ( pkt->getStreamID() == PISTA_DF_WAVEFORM) {
            instrument->waveform_slot(pkt->_packet());
        } else {
            std::cerr << "unexpected packet: " << pkt->getStreamID() << std::endl;
        }
        return PISTA_OK;
    }
};

void DemoWindow::on_simuButton_clicked()
{

    ui->simuButton->setEnabled(false);
    ui->realtime->setChecked(true);

    H2 *qtHandler = new H2( ui->instrument );

    PistaCl &pista = PistaCl::getInstance();
    PistaDriver *dev = pista.driver("simu");

    // SIMU_init( ctx, &drv );
    PistaDev *simu = dev->allocate( );
    // pista_set_event_handler(&simu, qt_eventfunc, this );
    simu->attach(qtHandler);
    // connect( simu, SIGNAL(), this, SLOT(eventSlot()));
    simu->connect();

}

void DemoWindow::on_realtime_clicked()
{
    ui->instrument->setRealtime( ui->realtime->isChecked() );
}

void DemoWindow::on_secCombo_currentTextChanged(const QString &arg1)
{
    QString val(arg1);
    val.chop(4);  // chop [sp]secs

    float secWidth = val.toFloat();
    ui->instrument->setSeconds( secWidth );
}
