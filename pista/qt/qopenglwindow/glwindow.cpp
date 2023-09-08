#include "glwindow.h"

#include <QColor>
#include <QMatrix4x4>
#include <QVector>
#include <QVector3D>
#include <QVector4D>

#include <QDebug>

#include <iostream>

GLWindow::GLWindow(QWindow *parent)
  : QWindow(parent)
  , _vbo(QOpenGLBuffer::VertexBuffer)
  , _context(0)
{
  setSurfaceType(QWindow::OpenGLSurface);
}

GLWindow::~GLWindow()
{}

void GLWindow::initGL()
{
  QVector<QVector3D> triangles;
  triangles << QVector3D(-0.5, 0.5, 1) << QVector3D(-0.5, -0.5, 1) << QVector3D(0.5, -0.5, 1);
  triangles << QVector3D(0.5, 0.5, 0.5) << QVector3D(-0.5, -0.5, 0.5) << QVector3D(0.5, -0.5, 0.5);

  _vbo.create();
  _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  _vbo.bind();

  size_t positionSize = triangles.size() * sizeof(QVector3D);
  _vbo.allocate(positionSize );
  _vbo.bind();
  _vbo.write(0, triangles.constData(), positionSize);

//  _program->release();
  resizeGL(width(), height());

  std::cout << "initGL done" << std::endl;
}

void GLWindow::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void GLWindow::paintGL()
{
    std::cout << "a";
  if (! _context) // not yet initialized
    return;

  std::cout << "d";
  std::cout.flush();

  _context->makeCurrent(this);
  QColor background(Qt::black);

  glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 matrix;
  matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
  matrix.translate(0, 0, -2);

//  _program->bind();
//  _vao.bind();

//  _matbo.bind();
//  _matbo.write(0, matrix.constData(), 4 * sizeof(QVector4D));


  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
  if( !_vbo.bind() ) {
      std::cout << "COULD NOT BIND VBO" << std::endl;
  }
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3f(1.0, 1.0, 1.0 );
  // _func330->glDrawArraysInstanced(GL_LINES, 0, 6, 1);
  glDrawArrays(GL_LINES, 0, 6);

  _vbo.release();

  glColor3f(1,0,0);
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5, -0.5, 1);
  glVertex3f( 0.5, -0.5, 1);
  glVertex3f( 0.0,  0.5, 1);
  glEnd();
  glColor3f(0,1,0);
  glBegin(GL_TRIANGLES);
  glVertex3f(-100, -100, 1);
  glVertex3f( 100, -100, 1);
  glVertex3f( 100,  100, 1);
  glEnd();


//  _program->release();

  _context->swapBuffers(this);
  _context->doneCurrent();

}


void GLWindow::exposeEvent(QExposeEvent *event)
{
  Q_UNUSED(event);

  if (isExposed())
  {
    if (! _context)
    {
      _context = new QOpenGLContext(this);
      QSurfaceFormat format(requestedFormat());
      format.setVersion(3,3);
      format.setDepthBufferSize(24);

      _context->setFormat(format);
      _context->create();

      _context->makeCurrent(this);
      initializeOpenGLFunctions();

      _func330 = _context->versionFunctions<QOpenGLFunctions_3_3_Core>();
      if (_func330)
        _func330->initializeOpenGLFunctions();
      else
      {
        qWarning() << "Could not obtain required OpenGL context version";
        exit(1);
      }

      initGL();
    }

    paintGL();
  }
}
