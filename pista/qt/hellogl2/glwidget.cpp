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

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

#include <iostream>

#include <cstdlib>
#include <sys/timeb.h>

static long initial_tm = 0;

static long getMilliCount(){
    timeb tb;
    ftime(&tb);
    return (long) tb.millitm + (tb.time & 0xfffff) * 1000;
}

GLWidget::GLWidget(QWidget *parent)
    : QT_PARENT_GLWIDGET(parent),
      m_waveformVbo( QOpenGLBuffer::VertexBuffer),
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

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(800, 1000);
}

void GLWidget::cleanup()
{
    // makeCurrent();
    m_waveformVbo.destroy();
    delete m_program;
    m_program = 0;
    // doneCurrent();
}

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "void main() {\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "highp vec4 color = vec4(0.39, 1.0, 0.0, 1.0);\n"
    "void main() {\n"
    "   gl_FragColor = color;\n"
    "}\n";

void GLWidget::initializeGL()
{
    std::cout << "initializeGL" << std::endl;

    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
#endif

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.

    m_waveformVbo.create();
    m_waveformVbo.setUsagePattern( QOpenGLBuffer::DynamicDraw );
    m_waveformVbo.bind();

    vbo_alloc_sz = 2048 * 4 * sizeof(GLfloat);
    vbo_insert_pos = 0;

    std::cout << "allocating count=" << vbo_alloc_sz << std::endl;
    m_waveformVbo.allocate(m_waveform.constData(), vbo_alloc_sz);
    m_waveformVbo.release();

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    m_program->release();
}

void GLWidget::setupVertexAttribs()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    m_waveformVbo.bind();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    m_waveformVbo.release();
}

int debug_c = 0;
void GLWidget::paintGL()
{
//     std::cout << "zero-paint sz=" << m_waveform.count() << " verts=" << m_waveform.vertexCount() << std::endl;
//    this->makeCurrent();
    vbo_insert_pos = m_waveform.flush( m_waveformVbo, vbo_insert_pos );

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

    // qglColor( Qt::red );
    // ::glColor3f( 1,0,0 );

    int vertex_count = vbo_insert_pos / sizeof(GLfloat) / 2;
    glDrawArrays(GL_LINES, 0, vertex_count );
    m_waveformVbo.release();

    m_program->release();

    // hmmm...no make current...done current...single threaded?
//    this->doneCurrent();
    update();  // i dont really like this approach...!

    debug_c++;
    if( debug_c == 300 ) {
        data_packet(NULL);
        debug_c = 0;
    }

    /*
    if( dump_flag ) {
        _diag_dump();
        dump_flag = false;
    }
    */
}

void GLWidget::resizeGL(int w, int h)
{
    ::glViewport(0,0,w,h);
    m_proj.setToIdentity();
    // m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    m_proj.ortho( -2, 2, -2, 2, 0, 20 );
}

void GLWidget::data_packet( void *pkt )
{
    float dat[] = { 5.0, 5.0, 3.0, 2.0, 1.0, 0.0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -7.0 };
    m_waveform.add( -1, 0.01, 14, dat );
}

void GLWidget::diag_dump( ) {
    // this->makeCurrent();

    int count = vbo_insert_pos / sizeof(GLfloat) / 4;

    m_waveformVbo.bind();
    float *src = (float *)m_waveformVbo.map( QOpenGLBuffer::ReadOnly );

    std::cout << std::dec << "dumping vertex count=" << count << " loc= 0x" << std::hex << src << std::dec << std::endl;

    for( int i = 0; i < count; i++ ) {
        std::cout << i << " (" << *src++; std::cout << "," << *src++ << ")";
        std::cout << " -> (" << *src++; std::cout << "," << *src++ << ")";
        std::cout << std::endl;
    }

    m_waveformVbo.unmap();
    m_waveformVbo.release();

    // this->doneCurrent();
}
