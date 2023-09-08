
#include "glinstrumentdisplay.h"
#include <iostream>

#include <pista.h>
#include "bandrenderer.h"

#include <QDateTime>
#include <QTextDocument>
#include <QWheelEvent>

GLInstrumentDisplay::GLInstrumentDisplay(QWidget *parent) : QOpenGLWidget(parent)
{
    // this is one method to update the display using a QTimer
    // connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL() ));
    // timer.start(16);

    BandRenderer *band0 = new BandRenderer();
    BandRenderer *band1 = new BandRenderer();

    band0->addWaveform("waveform0", -30.0, 36.0, Qt::red );
    band1->addWaveform("waveform2", -20.0, 26.0, Qt::green );

    bands.push_back( band0 );
    bands.push_back( band1 );

    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

}

void GLInstrumentDisplay::wheelEvent(QWheelEvent *event)
{

    if (realtime )
    {
        // ignore
    } else {
        dsec += secs * (event->delta() / 1000.0f);
    }
}

void GLInstrumentDisplay::initializeGL() {
    initializeOpenGLFunctions();

    // QMutexLocker initLock(initMutex());
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "\n"
        "uniform mediump mat4 matrix;\n"
        "uniform int currentTime;\n"
        "uniform mediump float relTime;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "uniform vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_program.addShader(vshader);
    m_program.addShader(fshader);
    m_program.link();

    colorUniform = m_program.uniformLocation("color");
    vertexAttr = m_program.attributeLocation("vertex");
    matrixUniform = m_program.uniformLocation("matrix");

    /*
    createGeometry();

    vbo.create();
    vbo.bind();
    const int verticesSize = vertices.count() * 3 * sizeof(GLfloat);
    vbo.allocate(verticesSize * 2);
    vbo.write(0, vertices.constData(), verticesSize);
    vbo.write(verticesSize, normals.constData(), verticesSize);
    */
}

void GLInstrumentDisplay::resizeGL(int w, int h) {


    int hh = h/2;
    int y = 0;
    for ( std::list<BandRenderer*>::const_iterator iterator = bands.begin(); iterator != bands.end(); ++iterator) {
        BandRenderer *band = *iterator;
        band->resize( 0, y, w, hh);
        y += hh;
    }
}

void GLInstrumentDisplay::paintGL() { // Event(QPaintEvent *) {

//    QPainter painter( this );

    glClearColor( 0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // glEnableClientState(GL_VERTEX_ARRAY);


    drawBands( );
    // glDrawArrays(GL_TRIANGLES, 0, vertices.size());


//    drawOutlines();

//    drawLegend( &painter);

//    painter.setPen(textPen);
//    painter.setFont(textFont);
//    painter.drawText(QRect(1, 1, 20, 20), Qt::AlignCenter, QStringLiteral("Qt"));

//    painter.end();

    update();  // another method to update the display...schedule another repaint after flush
}

void GLInstrumentDisplay::drawLegend(QPainter *painter) {
    const int Margin = 11;
     const int Padding = 6;

     QTextDocument textDocument;
     textDocument.setDefaultStyleSheet("* { color: #FFEFEF }");
     textDocument.setHtml("<h4 align=\"center\">Vowel Categories</h4>"
                          "<p align=\"center\"><table width=\"100%\">"
                          "<tr><td>Open:<td>a<td>e<td>o<td>&ouml"
                          "</table>");
     textDocument.setTextWidth(textDocument.size().width());

     QRect rect(QPoint(0, 0), textDocument.size().toSize()
                              + QSize(2 * Padding, 2 * Padding));
     painter->translate(width() - rect.width() - Margin,
                        height() - rect.height() - Margin);
     painter->setPen(QColor(255, 239, 239));
     painter->setBrush(QColor(255, 0, 0, 31));
     painter->drawRect(rect);

     painter->translate(Padding, Padding);
     textDocument.drawContents(painter);
}

void GLInstrumentDisplay::drawBands() {
    int64_t tm = QDateTime::currentDateTime().toMSecsSinceEpoch(); // pista_get_current_time_with_ms();
    if( tm0 == 0 ) {
        tm0 = tm;  // well...ok...maybe...but no data has been received
    }

    if( realtime ) {
        dsec = (tm - tm0)/1000.0f;
    }
    m_program.setUniformValue("currentTime", (uint)tm );
    m_program.setUniformValue("relTime", (GLfloat)dsec );

    std::list<BandRenderer*>::const_iterator iterator;
    for (iterator = bands.begin(); iterator != bands.end(); ++iterator) {
        BandRenderer *band = *iterator;

        glViewport(band->get_x(), band->get_y(), band->view_w(), band->view_h() );

        //
        //        set the y-scale
        //
                // glOrtho(-60, 10,  setup.range_min,  setup.range_max,  -1,  1);
                // glOrtho(-60, 10,  -20,  20,  -1,  1);

        modelview.setToIdentity();

        float dh = 70.0f;
        float y_scale = 4.0f / dh;
        float x_scale = 2.0f / secs;
        // modelview.translate(band->get_w()/4, 0, 0);
        // modelview.translate( band->view_w() / 2, 0, 0 );
        modelview.scale( x_scale, 1.0, 1.0 );
        modelview.translate(-dsec + secs/2, 0.0f, 0.0f);
        modelview.scale( 1.0, y_scale, 1.0 );

        // std::cout << dsec << " w,h=" << band->view_w() << "," << band->view_h() << std::endl;

        m_program.bind();
        m_program.setUniformValue(matrixUniform, modelview);
        band->renderSignals( m_program, vertexAttr, colorUniform );
        m_program.release();

        band->renderIndicators();


    }



}


void GLInstrumentDisplay::drawOutlines( ) {
    //
    // draw dividing lines between the bands
    //
    glViewport(0, 0, width(), height() );
/*
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // gluOrtho2D( 0, width(), 0, height());
    glOrtho(0, width(),  0,  height(),  -1,  1);

    glPopMatrix();
*/
}

void GLInstrumentDisplay::waveform_slot( const pista_data_packet *pkt ) {

    if( tm0 == 0 ) {
        tm0 = pkt->tm;
    }
    for ( std::list<BandRenderer*>::const_iterator iterator = bands.begin(); iterator != bands.end(); ++iterator) {
        BandRenderer *band = *iterator;
        band->addWaveformPacket( pkt->tm - tm0, pkt );
    }
}

void GLInstrumentDisplay::vitals_slot( const pista_data_packet *pkt ) {

}
