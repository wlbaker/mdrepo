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

#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"

#include "pista-cl.h"

#include <iostream>

void loadStylesheet() {

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
//    if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
//        fmt.setSamples(4);
//    if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
//        fmt.setVersion(3, 2);
//        fmt.setProfile(QSurfaceFormat::CoreProfile);
//    }
    QSurfaceFormat::setDefaultFormat(fmt);
#endif

//    pista_context *ctx;
//    pista_init(&ctx);
    PistaCl &pista = PistaCl::getInstance();
    for( int i = 0; i < pista.driver_count(); i++ ) {
        PistaDriver *driver = pista.driver(i);
        std::cout << "pista driver: " << i << " " << driver->longname() << std::endl;
    }
    pista.run();

    loadStylesheet();

    MainWindow mainWindow;
    mainWindow.resize(mainWindow.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();

    int widgetArea = mainWindow.width() * mainWindow.height();

#if !defined(DESKTOP_APP )
    mainWindow.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    widgetArea = desktopArea;  // maximize
#endif
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        mainWindow.show();
    else
        mainWindow.showMaximized();
    return app.exec();
}
