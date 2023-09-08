#include "instrumentpanel.h"
#include "ui_instrumentpanel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include "instrumentwidget.h"

#include <iostream>

InstrumentPanel::InstrumentPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstrumentPanel)
{
    ui->setupUi(this);


    /*
    InstrumentWidget *glWidget = new InstrumentWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    // connect(dockBtn, SIGNAL(clicked()), this, SLOT(dockUndock()));
    // mainLayout->addWidget(dockBtn);

    // setLayout(mainLayout);
    ui->tabber->addTab( w, "main" );

    */

}

InstrumentPanel::~InstrumentPanel()
{
    delete ui;
}

void InstrumentPanel::on_undock_clicked()
{

}

void InstrumentPanel::dockUndock()
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        // dockBtn->setText(tr("Dock"));
        show();
    } else {
        /*
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                // dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
        */
    }
}

void InstrumentPanel::setAnimating(bool enabled)
{
    if (enabled) {
        // Animate continuously, throttled by the blocking swapBuffers() call the
        // QOpenGLWindow internally executes after each paint. Once that is done
        // (frameSwapped signal is emitted), we schedule a new update. This
        // obviously assumes that the swap interval (see
        // QSurfaceFormat::setSwapInterval()) is non-zero.
        connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
        update();

    } else {
        disconnect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    }

    std::cout << "set update: " << enabled << std::endl;
}
