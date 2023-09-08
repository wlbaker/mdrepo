#include "wifimgmtform.h"
#include "ui_wifimgmtform.h"

wifimgmtform::wifimgmtform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wifimgmtform)
{
    ui->setupUi(this);
}

wifimgmtform::~wifimgmtform()
{
    delete ui;
}
