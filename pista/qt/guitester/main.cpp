#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QMessageBox>

#include "demowindow.h"

/*
class OpenGL: public QOpenGLWidget, protected QOpenGLFunctions {
protected:
    void initializeGL(){
        glClearColor(0,1,1,0);
    }

    void resizeGL(int w, int h){
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,w,0,h,-1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void paintGL(){
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1,0,0);
        glBegin(GL_POLYGON);{
            glVertex2f(0,0);
            glVertex2f(100,500);
            glVertex2f(500,100);
        }glEnd();
    }
};
*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

      DemoWindow w;

//    QDesktopWidget dw;
//    int x=dw.width()*0.7;
//    int y=dw.height()*0.7;
//    w.setFixedSize(x,y);

    w.show();

    return a.exec();
}
