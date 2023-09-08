#include "patientform.h"
#include "ui_patientform.h"

#include <QToolButton>
#include <QDebug>
#include <QAbstractButton>

#include "flowlayout.h"

PatientForm::PatientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientForm)
{
    ui->setupUi(this);

    FlowLayout *flowLayout = new FlowLayout;

    addDevice(flowLayout, "Impact 731", ":/images/impact.jpg");
    addDevice(flowLayout, "Simulated Monitor", ":/images/meddev.png");

    ui->widget->setLayout(flowLayout);
}

void PatientForm::addDevice(QLayout *layout, const char *devName, const char *resourceName ) {
    QIcon icon(resourceName);

    QToolButton *button = new QToolButton();
    button->setText(devName);
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    button->setIcon(icon);
    button->setIconSize(QSize(60,60));

    button->setProperty("dev", devName);

    connect( button, SIGNAL(clicked(bool)), this, SLOT(deviceClick()) );
    // connect( vent, &QAction::triggered, this, [this]{ deviceClick(); } );
    layout->addWidget(button);
}

void PatientForm::deviceClick( ) {
    QAbstractButton *button = (QAbstractButton *)sender();
    QVariant prop = button->property("dev");

    QString s = prop.toString();
    emit deviceDetail( s.constData() );
}

PatientForm::~PatientForm()
{
    delete ui;
}
