
#include "qtwaveformbuffer.h"

#include <iostream>

const static int SIZEOF_COORD = sizeof(GLfloat);
const static int COORDS_PER_VERTEX = 2;

QtWaveformBuffer::QtWaveformBuffer()
{
    m_data.resize( m_maxcount * SIZEOF_COORD );

}


float QtWaveformBuffer::add( int64_t ttm, float dt, int count, float* farr )
{
    if( ttm > 0 ) {
        tm = ttm/1000.0f;
    }

    GLfloat *p = m_data.data() + m_count;

    bool first = true;

    // std::cout << "adding tm=" << tm << " dt=" << dt;
    m_count += count*COORDS_PER_VERTEX*2;
    while( count-- > 0 ) {
        if( first ) {
            *p++ = prev_tm;
            *p++ = prev_y;
            first = false;
        } else {
            *p++ = tm;
            *p++ = (*farr++);
        }
        tm += dt;
        *p++ = tm;
        *p++ = (*farr);
        // std::cout << p[-4] << "," << p[-3] << " --> " << p[-2] << "," << p[-1] << std::endl;
    }
    prev_tm = tm;
    prev_y = (*farr);

    // std::cout << std::endl;

    return tm;
}

/*
 * should only be called by the OpenGL thread
 */

int QtWaveformBuffer::flush( QOpenGLBuffer &vbo, int insert_pos )
{
    if( !m_count ) {
        return insert_pos;
    }

    int sz = m_count * SIZEOF_COORD;

    // std::cout << std::dec << "flushing from: " << insert_pos << " count=" << m_count << " sz=" << sz << " vbosz=" << vbo.size() << ": ";

    if( !vbo.bind() ) {
        std::cerr << "ERROR: could not bind buffer" << std::endl;
    }

    float *dat = (float *)m_data.constData();
    /*
    float *coord = dat;
    for (int i = 0; i < 12; ) {

        std::cout << *(coord++) ;
        std::cout << ",";
        std::cout << *(coord++);
        std::cout << " --> ";
        std::cout << *(coord++);
        std::cout << ",";
        std::cout << *(coord++);
        std::cout << "  ";
        i+= 4;
    }
    std::cout << "..." << std::endl;
    */

    if( insert_pos + m_count < maxCount() ) {
        // this will drop part of a frame...anything past maxCount();
        vbo.write( insert_pos * SIZEOF_COORD, dat, sz);
    } else {
        insert_pos = 0;
        vbo.write( insert_pos * SIZEOF_COORD, dat, sz);
    }

    insert_pos += m_count;
    m_count = 0; // ERROR FIXME: Thread race condition

    vbo.release();

    return insert_pos;
}

#ifdef USE_RAW_OPENGL
static void _write( int vbo_offset, const float *y_data, int y_offset, int y_length) {
    int vbo_length = y_length * SIZEOF_COORD * COORDS_PER_VERTEX;

    void *bytebuffer = glMapBufferRange(GL_ARRAY_BUFFER, vbo_offset, vbo_length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
    if (bytebuffer == NULL) {
        int err = glGetError();
        std::cout << "WRITE MAP RANGE ERROR: " << err << " ?= " << GL_INVALID_OPERATION << " for vbo_offset="
                << vbo_offset << " vbo_len=" << vbo_length << std::endl;
    } else {

            float *coord_pairs = (float *)bytebuffer;
            for (int i = y_offset; i < y_offset + y_length; ) {

                // *(coord_pairs++) = t0;
                *(coord_pairs++) = y_data[i++];
                *(coord_pairs++) = y_data[i++];

            }
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    return;
}

int QtWaveformBuffer::flush( GLuint vbo, int insert_pos )
{
    if( !m_count ) {
        return insert_pos;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    int vbo_offset = insert_pos * SIZEOF_COORD;

    _write( vbo_offset, m_data.constData(), 0, m_count);
    insert_pos += m_count;
    m_count = 0; // ERROR FIXME: Thread race condition

    glBindBuffer( GL_ARRAY_BUFFER, 0);

    return insert_pos;
}

#endif
