#ifndef SHORTCUTICONAREA_H
#define SHORTCUTICONAREA_H

#include <QIcon>
#include <QWidget>
#include <QStringList>
#include <QVector>
#include <QLabel>


class ShortcutIconArea : public QWidget
{
    Q_OBJECT

public:
    explicit ShortcutIconArea(QWidget *parent = 0);
    ~ShortcutIconArea();

    void updateIcon(int row, const QIcon &icon);

private:
    QLabel *pixmapLabels[4];

    QLabel *createPixmapLabel();

};

#endif // SHORTCUTICONAREA_H
