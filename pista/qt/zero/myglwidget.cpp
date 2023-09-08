#include <iostream>

#include "myglwidget.h"

#include <QMatrix4x4>>

// http://stackoverflow.com/questions/23732001/how-to-use-vaos-with-instancing-in-qt-5

#define SIZEOF_COORD        (sizeof(float))
#define COORDS_PER_VERTEX   2
#define VBO_VERTEX_COUNT    1000
bool initted = false;


WaveformSetupDataEx::WaveformSetupDataEx() :
    _vbo(QOpenGLBuffer::VertexBuffer)
{
    std::cout << "create wfsetupdataex" << std::endl;

    loc="waveform0";
    range_min = -100;
    range_max = 100;
    insert_vertex_pos = 0;
    code="WF0";
    unit="unit0";

    y_last = 0;

    _vbo.create();
    _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo.bind();
}


MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    initted=false;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

float MyGLWidget::addData( float ts, int count, float *data ) {

    QOpenGLBuffer &_vbo = setup._vbo;

    float dt = 0.1;

    //
    if( !initted ) {
        int vbo_length =  VBO_VERTEX_COUNT * SIZEOF_COORD * COORDS_PER_VERTEX;

        _vbo.allocate(vbo_length);
        _vbo.bind();

        initted = true;

        std::cout << "allocated=" << vbo_length << " dt=" << dt << std::endl;
    }


    // save the last vertexes in case of overrun
    if (count > 1) {
   //     int pos = y_offset + count - 1;
   //     y_t0 = t0 + (int) (dt * pos);
   //     setup.y_last = y_data[pos];
    }


            // float *coord_pairs = (float *)bytebuffer;
    int y_offset = 0;
    int pos = 0;
            for (int i = y_offset; i < y_offset + count; i++) {

                _vbo.write(pos++, &ts, sizeof(ts) );
                _vbo.write(pos++, data++, sizeof(float) );
                ts += dt;
            }

            setup.insert_vertex_pos += count;

    return ts;

}


void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{

    std::cout << "initializeGL" << std::endl;

    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    std::cout <<"p" << std::endl;
    this->makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    matrix.translate(0, 0, -10);
    matrix.rotate(xRot / 16.0, 1.0, 0.0, 0.0);
    matrix.rotate(yRot / 16.0, 0.0, 1.0, 0.0);
    matrix.rotate(zRot / 16.0, 0.0, 0.0, 1.0);

    //glLoadIdentity();
    //glTranslatef(0.0, 0.0, -10.0);
    //glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    //glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    //glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();

    //this->swapBuffers();
    //this->doneCurrent();
}

void MyGLWidget::resizeGL(int width, int height)
{
    std::cout << "resize setting veiwport" << std::endl;

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{
    qglColor(Qt::red);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);

    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}
