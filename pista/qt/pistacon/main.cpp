#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QCoreApplication a(argc, argv);

//    Q_UNUSED(client);

    MainWindow w;
    w.show();

    return a.exec();
}
