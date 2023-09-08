#ifndef DATAFORM_H
#define DATAFORM_H

#include <QWidget>

namespace Ui {
class DataForm;
}

class DataForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataForm(QWidget *parent = 0);
    ~DataForm();

private slots:
    void on_generateData_clicked();

    void on_readData_clicked();

private:
    Ui::DataForm *ui;
};

#endif // DATAFORM_H
