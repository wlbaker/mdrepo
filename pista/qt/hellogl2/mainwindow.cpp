/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>

#include "patientform.h"
#include "dataform.h"
#include "bluetoothmgmtform.h"

#include "glinstrumentdisplay.h"

#include <iostream>

MainWindow::MainWindow()
{
#if defined( DESKTOP_APP )
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));
    setMenuBar(menuBar);
#endif

    /*
     * Create an action to handle ESCAPE
     */
    {
        QAction *foo = new QAction(this);
        foo->setShortcut(Qt::Key_Escape ); // Qt::Key_Q | Qt::CTRL);

        connect(foo, SIGNAL(triggered()), this, SLOT(close()));
        this->addAction(foo);
    }

    /*
     * Create an action to handle LEFT
     */
    {
        QAction *left = new QAction(this);
        left->setShortcut(Qt::Key_Left ); // Qt::Key_Q | Qt::CTRL);

        connect(left, SIGNAL(triggered()), this, SLOT(leftKey()));
        this->addAction(left);
    }

    onAddNew();
}

void MainWindow::onAddNew()
{
    stackedLayout = new QStackedLayout;
    if (!centralWidget()) {
        /*
        instrument = new InstrumentDisplay(this );
        setCentralWidget( instrument );

        instrument->setAnimating(true);
        */
        QWidget *c = new QWidget();
        first = new FirstForm(this );

        stackedLayout->addWidget( first );

        c->setLayout( stackedLayout );
        setCentralWidget( c );

        connect( first, SIGNAL(patientSignal()), this, SLOT(patientSlot() ));
        connect( first, SIGNAL(dataSignal()), this, SLOT(dataSlot() ));
        connect( first, SIGNAL(settingsSignal()), this, SLOT(settingsSlot() ));
    } else {
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));
    }

    qDebug("onAddNew()");
}

void MainWindow::deviceDetailSlot( const QChar *devName )
{
    std::cout << "DEVICE DETAIL: " << devName << std::endl;

    GLInstrumentDisplay *display = new GLInstrumentDisplay( this );
    stackedLayout->addWidget( display );
    stackedLayout->setCurrentIndex( stackedLayout->currentIndex() + 1);

}

void MainWindow::clearKeyboardShortcuts() {

}

void MainWindow::registerKeyboardShortcut( int key, const char *action, int icon ) {

}

void MainWindow::leftKey() {
    close();
}

void MainWindow::rightKey() {

}

void MainWindow::upKey() {

}

void MainWindow::downKey() {

}

void MainWindow::enterKey() {

}

void MainWindow::patientSlot() {

    PatientForm *patient = new PatientForm(this );
    connect( patient, SIGNAL(deviceDetail(const QChar *)), this, SLOT(deviceDetailSlot(const QChar *) ));
    stackedLayout->addWidget( patient );
    stackedLayout->setCurrentIndex( stackedLayout->currentIndex() + 1);

     return;
}

void MainWindow::bluetoothSlot() {

    BluetoothMgmtForm *bt = new BluetoothMgmtForm(this );
    stackedLayout->addWidget( bt );
    stackedLayout->setCurrentIndex( stackedLayout->currentIndex() + 1);

     return;
}

void MainWindow::dataSlot() {
    DataForm *form = new DataForm(this );
    stackedLayout->addWidget( form );
    stackedLayout->setCurrentIndex( stackedLayout->currentIndex() + 1);

    return;
}

void MainWindow::settingsSlot() {
    SettingsForm *settings = new SettingsForm(this );
    stackedLayout->addWidget( settings );
    stackedLayout->setCurrentIndex( stackedLayout->currentIndex() + 1);

    connect( settings, SIGNAL(bluetoothSignal()), this, SLOT(bluetoothSlot() ));

    return;
}

void MainWindow::closeEvent(QCloseEvent *event) {
     // do some data saves or something else
    // dont close

    if( stackedLayout->currentIndex() > 0 ) {
        QWidget *top = stackedLayout->currentWidget();
        stackedLayout->removeWidget( top );
        delete top;

        event->ignore();
    }
}
