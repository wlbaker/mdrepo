
#include "bandrenderer.h"

#include <iostream>
#include <pista.h>


#define COORD_TYPE GL_FLOAT

BandRenderer::BandRenderer()
{

}

void BandRenderer::addWaveform( const char *loc, float range_min, float range_max, const QColor &color ) {
    WaveformSetupDataEx *setup = new WaveformSetupDataEx;

    setup->loc=loc;
    setup->range_min = range_min;
    setup->range_max = range_max;
    setup->insert_vertex_pos = 0;
    setup->code="WF0";
    setup->unit="unit0";
#ifdef USE_RAW_OPENGL
    setup->m_vbo = 0;
#endif
    setup->y_last = 0;
    setup->color = color;

    setups.push_front(*setup);
}

void BandRenderer::initializeGL() {



}

void BandRenderer::resize( int x, int y, int w, int h) {

   this->x = x;
   this->y = y;
   this->w = w;
   this->h = h;

}

float *prepare_data( const pista_data_packet *pkt, const pista_item_desc *desc, bool& created ) {
    float *y_data = NULL;

    void **data = (void **)(pkt->payload + desc->offset);
    int count = desc->count;

    int subtyp = desc->subtyp;
    if (subtyp == FLOAT_ARR_TYP) {
        y_data = (float*)(*data);
    } else if (subtyp == INT_ARR_TYP) {
        int* i_data = (int*)(*data);
        y_data = new float[count];
        created = true;
        int idx = 0;
        while (count--) {
            y_data[idx++] = *(i_data++);
        }
    } else if (subtyp == DOUBLE_ARR_TYP) {
        double* dd_data = (double*)(*data);
        y_data = new float[count];
        created = true;
        int idx = 0;
        while (count--) {
            y_data[idx++] = (float)*(dd_data++);
        }
    }

    return y_data;
}

void BandRenderer::addWaveformPacket( int64_t pkt_tm0, const pista_data_packet *pkt ) {


    for( int idx = 0; idx < pkt->field_cnt ; idx++ ) {
        const pista_item_desc *desc = &pkt->desc[idx];

        for(std::list<WaveformSetupDataEx>::iterator list_iter = setups.begin();
            list_iter != setups.end(); list_iter++)
        {
            WaveformSetupDataEx &setup = *list_iter;

            if ( strcmp(desc->loc, setup.loc) == 0 ) {
                setup.unit = desc->unit;
                setup.code = desc->code;

                float dt = 5;
                if (desc != NULL) {
                    int r = desc->freq;
                    if (r != 0) {
                        dt = 1.0f / r;
                    }
                }
                bool created = false;
                float *y_data = prepare_data( pkt, desc, created);
                addVertices( setup, pkt_tm0, dt, y_data, desc->count);

                if( created ) {
                    delete y_data;
                }
            }
        }

    }

}

#ifdef USE_RAW_OPENGL

// CALL ON GL THREAD ONLY check_vbos

void GLBandPainter::check_vbos( WaveformSetupDataEx &setup) {
    if (setup.m_vbo != 0) {
        return;
    }
    std::cout << "glerror=" << glGetError() << std::endl;
    setup.m_vbo = 22;
    glGenBuffers(1, &setup.m_vbo);
    std::cout << "generated buffer: " << setup.m_vbo << " err=" << glGetError() << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, setup.m_vbo);

    // allocate space, but dont put anything in it
    setup.sz = VBO_VERTEX_COUNT * SIZEOF_COORD * COORDS_PER_VERTEX;

    glBufferData(GL_ARRAY_BUFFER, setup.sz, NULL, GL_DYNAMIC_DRAW);
    std::cout << "allocated vbo: " << setup.m_vbo << " sz=" << setup.sz << std::endl;

}
#else
// do nothing...must be allocated on opengl thread, and alloc is handled on flush
void BandRenderer::check_vbos( WaveformSetupDataEx &setup) {

    if( setup.m_vbo.isCreated() == false || setup.m_vbo.size() == 0 ) {
        setup.m_vbo.create();
        setup.m_vbo.allocate(40000);
        setup.m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    }
}
#endif

void BandRenderer::addVertices(WaveformSetupDataEx &setup, int64_t pkt_tm0, float dt, float *y_data, int count) {

    setup.m_waveform.add( pkt_tm0, dt, count, y_data );

}


void BandRenderer::renderOverlayText() {
    //    instrument.monospaced.beginRendering(w, h);
    //    instrument.monospaced.setColor(1.0f, 1.0f, 0.6f, 0.8f);
    //    // optionally set the color
    //    int idx = 0;
    //    for (WaveformSetupDataEx setup : setups) {
    //        int xoff = 20 + 80 * idx;
    //        Color color = setup.getColor();
    //        if (color != null) {
    //            instrument.monospaced.setColor(color.brighter().brighter());
    //        }
    //        RpUnit unit = setup.getUnit();

    //        String unitName = "";
    //        double rangeMax = setup.getRangeMax();
    //        double rangeMin = setup.getRangeMin();
    //        if (unit != null) {
    //            rangeMax = unit.transform((int) rangeMax);
    //            rangeMin = unit.transform((int) rangeMin);
    //            unitName = " [" + unit.getUnitName() + "]";
    //        }
    //        instrument.monospaced.draw(df0.format(rangeMax), xoff, h - 20);
    //        instrument.monospaced.draw(setup.getCode(), xoff + 40, h - 20);
    //        instrument.monospaced.draw(df0.format(rangeMin) + unitName, xoff, 10);
    //        idx++;
    //    }
    //    instrument.monospaced.endRendering();

}

void BandRenderer::renderSignals( QOpenGLShaderProgram &m_program, int vertexAttr, int colorUniform ) {


    glLineWidth(2);

//    // gl.glBlendFunc(GL2.GL_SRC_ALPHA, GL2.GL_ONE_MINUS_SRC_COLOR);
    for(std::list<WaveformSetupDataEx>::iterator list_iter = setups.begin();
        list_iter != setups.end(); list_iter++) {

        WaveformSetupDataEx &setup = *list_iter;
        check_vbos(setup);

        // WARNING: alloc size...dubious
        setup.insert_vertex_pos = setup.m_waveform.flush( setup.m_vbo, setup.insert_vertex_pos );

        // glVertexPointer(COORDS_PER_VERTEX, COORD_TYPE, 0, 0);

        setup.m_vbo.bind();

        m_program.enableAttributeArray(vertexAttr);

        m_program.setAttributeBuffer( vertexAttr, GL_FLOAT, 0, 2);
        m_program.setUniformValue( colorUniform, setup.color );



        glDrawArrays(GL_LINE_STRIP, 0, setup.insert_vertex_pos / COORDS_PER_VERTEX - 1 );

        m_program.disableAttributeArray(vertexAttr);

    }


//    // disable arrays once we're done
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glDisableClientState(GL_VERTEX_ARRAY);

    /*
     * for overlaying the signal labels...should be done in the instrument...it has global font resources
     * */
}

void BandRenderer::renderIndicators( ) {

    /*
    glColor4f(1,0,0,1);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.1-1, -0.1, 1);
        glVertex3f( 0.1-1, -0.1, 1);
        glVertex3f( 0-1,  0.1, 1);
    glEnd();
    */
}

void BandRenderer::readVertices( float * arr, int count) {
     std::list<WaveformSetupDataEx>::iterator it = setups.begin();
     std::advance(it, count);
     WaveformSetupDataEx &setupref = *it;

     // glBindBuffer(GL_ARRAY_BUFFER, setupref.m_vbo );
     setupref.m_vbo.bind();

     // void *bytebuffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, SIZEOF_COORD * count * COORDS_PER_VERTEX, GL_MAP_READ_BIT); // |
    void *bytebuffer = setupref.m_vbo.mapRange( 0, SIZEOF_COORD * count * COORDS_PER_VERTEX, QOpenGLBuffer::RangeRead ); // |
    if (bytebuffer == NULL) {
        int err = glGetError();
        std::cout << "READ MAP RANGE ERROR: " << err << " ?= {}  MESSAGE=" << GL_INVALID_OPERATION << std::endl;
        return;
    }
    float *buf = (float *)bytebuffer;
    int ii = 0;
    while (count > 0 ) {
        float v_x = *(buf++); // ignore the x for now
        float v_y = *(buf++);
        arr[ii++] = v_y;
        count--;
    }
    // glUnmapBuffer(GL_ARRAY_BUFFER);
    setupref.m_vbo.unmap();

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    setupref.m_vbo.release();

}

