#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLContext>


// http://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php
struct WaveformSetupDataEx {
public:
    WaveformSetupDataEx();

    const char *loc;
    const char *unit;
    const char *code;

    int insert_vertex_pos;
    int y_last;

    int range_min = -100;
    int range_max = 100;

    QOpenGLBuffer _vbo;
};


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

signals:

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    float addData( float ts, int count, float *data );

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);

private:
     void draw();

    int xRot;
    int yRot;
    int zRot;

    WaveformSetupDataEx setup;

    QPoint lastPos;
    // QOpenGLContext *_context;
};

#endif // MYGLWIDGET_H
