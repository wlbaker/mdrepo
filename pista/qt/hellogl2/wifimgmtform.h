#ifndef WIFIMGMTFORM_H
#define WIFIMGMTFORM_H

#include <QWidget>

namespace Ui {
class wifimgmtform;
}

class wifimgmtform : public QWidget
{
    Q_OBJECT

public:
    explicit wifimgmtform(QWidget *parent = 0);
    ~wifimgmtform();

private:
    Ui::wifimgmtform *ui;
};

#endif // WIFIMGMTFORM_H
