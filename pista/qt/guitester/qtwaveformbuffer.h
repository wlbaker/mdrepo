#ifndef QTWAVEFORMBUFFER_H
#define QTWAVEFORMBUFFER_H

#define GL_GLEXT_PROTOTYPES

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

#include <QOpenGLBuffer>

class QtWaveformBuffer
{
public:
    QtWaveformBuffer();
    const GLfloat *constData() const { return m_data.constData(); }
    int maxCount() const { return 2*m_maxcount; }
    int count() const { return 2*m_count; }
    int vertexCount() const { return m_count / 2; }

    float add( int64_t ttm, float dt, int count, float* farr );
    int flush( QOpenGLBuffer &vbo, int insert_pos );

#ifdef USE_RAW_OPENGL
    int flush( GLuint vbo, int insert_pos );
#endif

private:

    float tm = 0;
    float prev_tm = 0;
    float prev_y = 0;

    QVector<GLfloat> m_data;
    int m_count = 0;
    int m_maxcount = 2500;
};

#endif // QTWAVEFORMBUFFER_H
