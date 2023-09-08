#ifndef GLINSTRUMENTDISPLAY_H
#define GLINSTRUMENTDISPLAY_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QPainter>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <QPen>
#include <QFont>

class BandRenderer;
class pista_data_packet;

class GLInstrumentDisplay : public QOpenGLWidget, protected QOpenGLFunctions
{
    int64_t tm0 = 0;
    QMatrix4x4 modelview;

    bool realtime;
    float dsec;
    float secs = 30.0f;

public:
    GLInstrumentDisplay(QWidget *parent);


    void setRealtime( bool tf ) { realtime = tf; }
    void setSeconds( float secs ) { this->secs = secs; }

    // void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE {} ;

    void waveform_slot( const pista_data_packet *pkt );
    void vitals_slot( const pista_data_packet *pkt );

private:

    void initializeGL()  Q_DECL_OVERRIDE;
    void paintGL()  Q_DECL_OVERRIDE;
    void resizeGL(int w, int h)  Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;

    void drawOutlines( );
    void drawBands();
    void drawLegend( QPainter *painter);

    QFont textFont;
    QPen textPen;

    QOpenGLShaderProgram m_program;
    QOpenGLVertexArrayObject m_vao;

    int vertexAttr;
    int colorUniform;
    int matrixUniform;

    std::list<BandRenderer*> bands;
};

#endif // GLINSTRUMENTDISPLAY_H
