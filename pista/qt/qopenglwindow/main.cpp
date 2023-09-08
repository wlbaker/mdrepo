
#include <QOpenGLWindow>
#include <QScreen>
#include <QPainter>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QStaticText>
#include <QKeyEvent>

#include "background_renderer.h"

#include <iostream>

static QPainterPath painterPathForTriangle()
{
    static const QPointF bottomLeft(-1.0, -1.0);
    static const QPointF top(0.0, 1.0);
    static const QPointF bottomRight(1.0, -1.0);

    QPainterPath path(bottomLeft);
    path.lineTo(top);
    path.lineTo(bottomRight);
    path.closeSubpath();
    return path;
}

class OpenGLWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    OpenGLWindow();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;

private:
    void setAnimating(bool enabled);

    QMatrix4x4 m_window_normalised_matrix;
    QMatrix4x4 m_window_painter_matrix;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model_triangle;
    QMatrix4x4 m_model_text;
    QBrush m_brush;

    FragmentToy m_fragment_toy;
    QStaticText m_text_layout;
    bool m_animate;

    QOpenGLContext *_context;
};

// Use NoPartialUpdate. This means that all the rendering goes directly to
// the window surface, no additional framebuffer object stands in the
// middle. This is fine since we will clear the entire framebuffer on each
// paint. Under the hood this means that the behavior is equivalent to the
// manual makeCurrent - perform OpenGL calls - swapBuffers loop that is
// typical in pure QWindow-based applications.
OpenGLWindow::OpenGLWindow()
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
    , m_fragment_toy("./background.frag")
    , m_text_layout("The triangle and this text is rendered with QPainter")
    , m_animate(true)
    , _context(0)
{
    m_view.lookAt(QVector3D(0,0,10),
                  QVector3D(0,0,0),
                  QVector3D(0,1,0));

    m_brush = QBrush( Qt::blue ); // gradient);

    setAnimating(m_animate);
}

void OpenGLWindow::initializeGL()
{
}

void OpenGLWindow::paintGL()
{
    //glDisable(GL_STENCIL_TEST);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    this->makeCurrent();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // m_fragment_toy.draw(size());

    QPainter p(this);
    p.setWorldTransform(m_window_normalised_matrix.toTransform());

    QMatrix4x4 mvp = m_projection * m_view * m_model_triangle;
    p.setTransform(mvp.toTransform(), true);

    // p.fillPath(painterPathForTriangle(), m_brush);

    p.setBrush(m_brush);
    p.drawPath(painterPathForTriangle());

    QTransform text_transform = (m_window_painter_matrix * m_view * m_model_text).toTransform();
    p.setTransform(text_transform, false);
    p.setPen(QPen(Qt::white));
    m_text_layout.prepare(text_transform);
    qreal x = - (m_text_layout.size().width() / 2);
    qreal y = 0;
    p.drawStaticText(x, y, m_text_layout);

    m_model_triangle.translate(-0.01, 0, 0 );
    // m_model_text.rotate(1, 0, 1, 0);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);

    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-5, -5, -10);
    glVertex3f( 5, -5, -10);
    glVertex3f( 0,  5, -10);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-5, -5, 10);
    glVertex3f( 5, -5, 10);
    glVertex3f( 0,  5, 10);
    glEnd();

    glFlush();
    // glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();
    // this->swapBuffers();
    // this->doneCurrent();

}

void OpenGLWindow::resizeGL(int w, int h)
{
    std::cout << "resize!!" << std::endl;

    m_window_normalised_matrix.setToIdentity();
    m_window_normalised_matrix.translate(w / 2.0, h / 2.0);
    m_window_normalised_matrix.scale(w / 2.0, -h / 2.0);

    m_window_painter_matrix.setToIdentity();
    m_window_painter_matrix.translate(w / 2.0, h / 2.0);

    m_text_layout.setTextWidth(std::max(w * 0.2, 80.0));

    m_projection.setToIdentity();
    m_projection.perspective(45.f, qreal(w) / qreal(h), 0.1f, 100.f);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, +20, -20, +20, 1.0, 15.0);
}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_P) { // pause
        m_animate = !m_animate;
        setAnimating(m_animate);
    }
}

void OpenGLWindow::setAnimating(bool enabled)
{
    if (enabled) {
        // Animate continuously, throttled by the blocking swapBuffers() call the
        // QOpenGLWindow internally executes after each paint. Once that is done
        // (frameSwapped signal is emitted), we schedule a new update. This
        // obviously assumes that the swap interval (see
        // QSurfaceFormat::setSwapInterval()) is non-zero.
        connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
        update();
    } else {
        disconnect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    }
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    OpenGLWindow window;
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window.setFormat(fmt);
    window.showMaximized();

    return app.exec();
}

#include "main.moc"
