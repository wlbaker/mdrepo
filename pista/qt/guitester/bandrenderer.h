#ifndef GLBANDPAINTER_H
#define GLBANDPAINTER_H

#include <QWidget>
// #include <QGLWidget>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <pista.h>

#include <list>
#include "qtwaveformbuffer.h"

class pista_data_packet;

struct WaveformSetupDataEx {

public:
    WaveformSetupDataEx() : m_vbo(QOpenGLBuffer::VertexBuffer) {

    }

    QtWaveformBuffer m_waveform;

    const char *loc;
    const char *unit;
    const char *code;

    QColor color;

#ifdef USE_RAW_OPENGL
    GLuint m_vbo;
#else
    QOpenGLBuffer m_vbo;
#endif
    int insert_vertex_pos;
    int sz;  // setup size
    int y_last;

    int range_min = -100;
    int range_max = 100;
};

class BandRenderer
{
private:
    const static int SIZEOF_COORD = 4;
    const static int VBO_VERTEX_COUNT = 100000;
    // const static int COORD_TYPE = GL_FLOAT;
    const static int COORDS_PER_VERTEX = 2;

    std::list<WaveformSetupDataEx> setups;
    /**
     * Ratio of world-space units to screen pixels. Increasing this zooms the
     * display out, decreasing it zooms the display in.
     */
    double width_in_msec = 15000;

    int y_t0;
    float *y_last;

    // std::list<WaveformSetupDataEx> setups;
    // std::list<TimedNote> annos;

    /*
     * viewport
     */
    int x;
    int y;
    int w;
    int h;
    // int debug_idx;
    // boolean visible;
    // boolean did_missing_error;

    void check_vbos(WaveformSetupDataEx &setup);
    // int _addVertices(WaveformSetupDataEx &setup, int64_t t0, float dt, int vbo_offset, float *y_data, int y_offset, int y_length);

public:
    explicit BandRenderer();

    void initializeGL();
    void renderSignals( QOpenGLShaderProgram &m_program, int vertexAttr, int colorAttr  );
    void renderIndicators( );
    void renderOverlayText( );
    void resize(int x, int y, int w, int h);

    void addWaveform( const char *loc, float range_min, float range_max, const QColor &color );
    void addWaveformPacket( int64_t tm, const pista_data_packet *pkt );
    void addVertices(WaveformSetupDataEx &setup, int64_t t0, float dt, float *y_data, int count );
    void readVertices( float * arr, int count);

    int get_x() { return x; }
    int get_y() { return y; }
    int view_w() { return w; }
    int view_h() { return h; }

signals:

public slots:
};

#endif // GLBANDPAINTER_H
