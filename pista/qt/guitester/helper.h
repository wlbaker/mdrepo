#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

//! [0]
class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};
//! [0]

#endif // HELPER_H
