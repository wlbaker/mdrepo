#include "firstform.h"
#include "ui_firstform.h"

#include "mainwindow.h"

FirstForm::FirstForm(MainWindow *wiz, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstForm)
{
    ui->setupUi(this);

    this->wiz = wiz;

    connect( ui->data, SIGNAL(clicked()), this, SIGNAL(dataSignal()) );
    connect( ui->settings, SIGNAL(clicked()), this, SIGNAL(settingsSignal()) );

    wiz->registerKeyboardShortcut( Qt::Key_Right, SIGNAL(patientSignal()), 0 );
}

FirstForm::~FirstForm()
{
    delete ui;
}

void FirstForm::on_patient_clicked()
{
    emit patientSignal();
}
