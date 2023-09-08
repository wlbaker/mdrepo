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

#include "glwidget.h"
#include "instrumentdisplay.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include <iostream>

InstrumentDisplay::InstrumentDisplay(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    mainLayout->setMargin( 2 );

    dockBtn = new QPushButton(tr("Undock"), this);
    connect(dockBtn, SIGNAL(clicked()), this, SLOT(dockUndock()));

    buttonLayout->addWidget(dockBtn);

    addData = new QPushButton(tr("Add Data"), this);
    connect(addData, SIGNAL(clicked()), this, SLOT(data_packet()));
    buttonLayout->addWidget(addData);

    dumpData = new QPushButton(tr("Dump"), this);
    connect(dumpData, SIGNAL(clicked()), this, SLOT(diag_dump()));
    buttonLayout->addWidget(dumpData);

    QWidget *w = new QWidget;
    w->setLayout( buttonLayout );

    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(w);

    setLayout(mainLayout);

    setWindowTitle(tr("Instrument"));
}

void InstrumentDisplay::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void InstrumentDisplay::dockUndock()
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}

void InstrumentDisplay::diag_dump()
{
    glWidget->diag_dump( );  // pista_data_packet
}

void InstrumentDisplay::data_packet()
{
    glWidget-> data_packet( NULL );  // pista_data_packet
}

void InstrumentDisplay::setAnimating(bool enabled)
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
