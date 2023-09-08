#ifndef INSTRUMENTPANEL_H
#define INSTRUMENTPANEL_H

#include <QDialog>

namespace Ui {
class InstrumentPanel;
}

class InstrumentPanel : public QDialog
{
    Q_OBJECT

public:
    explicit InstrumentPanel(QWidget *parent = 0);
    ~InstrumentPanel();

    void setAnimating(bool enabled);

private slots:
    void on_undock_clicked();
    void dockUndock();

private:
    Ui::InstrumentPanel *ui;
};

#endif // INSTRUMENTPANEL_H
