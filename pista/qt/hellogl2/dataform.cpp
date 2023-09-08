#include "dataform.h"
#include "ui_dataform.h"

#include <QStandardPaths>
#include <QFile>

#include <QMessageBox>

DataForm::DataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataForm)
{
    ui->setupUi(this);

    // connect( ui->generateData, SIGNAL(clicked(bool)),  )
}

DataForm::~DataForm()
{
    delete ui;
}

void DataForm::on_generateData_clicked()
{
    QString appDataDir =  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();

    QFile f(appDataDir + "/out.dat");

    f.open( QFile::ReadWrite);
    f.write( "once upon a midnight dreary.\n" );
    f.write( "while i pondered weak and weary.\n" );
    f.close();

    QMessageBox mbox(this);
    mbox.setText("wrote text");
    mbox.exec();
}

void DataForm::on_readData_clicked()
{
    QString appDataDir =  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();

    QFile f(appDataDir + "/out.dat");
    f.open( QFile::ReadOnly );
    QString dat = f.readAll();
    f.close();

    QMessageBox mbox(this);
    mbox.setText(dat);
    mbox.exec();

}
