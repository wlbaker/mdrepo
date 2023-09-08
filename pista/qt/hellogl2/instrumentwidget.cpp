/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "instrumentwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

#include <iostream>

#include <cstdlib>
#include <sys/timeb.h>

long initial_tm = 0;

long getMilliCount(){
    timeb tb;
    ftime(&tb);
    return (long) tb.millitm + (tb.time & 0xfffff) * 1000;
}

InstrumentWidget::InstrumentWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(0)
{
    m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
    m_core = false;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent.
    m_transparent = QCoreApplication::arguments().contains(QStringLiteral("--transparent"));
    if (m_transparent)
        setAttribute(Qt::WA_TranslucentBackground);
}

InstrumentWidget::~InstrumentWidget()
{
    cleanup();
}

QSize InstrumentWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize InstrumentWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void InstrumentWidget::cleanup()
{
    makeCurrent();
    m_waveformVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "void main() {\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   gl_FragColor = vec4(color, 1.0);\n"
    "}\n";

void InstrumentWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &InstrumentWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    //m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.

    m_waveformVbo.create();
    m_waveformVbo.bind();
    m_waveformVbo.allocate(m_waveform.constData(), m_waveform.count() * sizeof(GLfloat));
    m_waveformVbo.release();

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void InstrumentWidget::setupVertexAttribs()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    m_waveformVbo.bind();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    m_waveformVbo.release();
}

void InstrumentWidget::paintGL()
{
//     std::cout << "zero-paint sz=" << m_waveform.count() << " verts=" << m_waveform.vertexCount() << std::endl;
//    this->makeCurrent();

    if( initial_tm == 0 ) {
        initial_tm = getMilliCount();
    }

    float delta_tm = getMilliCount() - initial_tm;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.translate(-delta_tm / 5000.0, 0, 0 );

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);

    m_waveformVbo.bind();
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_LINES, 0, m_waveform.vertexCount());
    m_waveformVbo.release();

    m_program->release();

    // hmmm...no make current...done current...single threaded?
//    this->doneCurrent();
    update();  // i dont really like this approach...!
}

void InstrumentWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    // m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    m_proj.ortho( -2, 2, -2, 2, 0, 20 );
}

void InstrumentWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void InstrumentWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    m_lastPos = event->pos();
}
