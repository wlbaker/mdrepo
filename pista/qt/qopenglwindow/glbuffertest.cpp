#include <QGuiApplication>
#include <QSurfaceFormat>

#include "glwindow.h"



int main(int argc, char **argv)
{

  QGuiApplication app(argc, argv);

  GLWindow window;
  window.resize(400, 400);
  window.show();

  return app.exec();

}
