/**
 * @file  ice_hello_world.cxx
 * @brief Run the publisher OR subscriber part of an example DocBox DDS app.
 */
//=============================================================================
#include <iostream>
#include <string>
#include "HelloIceApp.h"

int main(int argc, char *argv[])
{
  int iret = 1;
  HelloIceApp *app = new HelloIceApp();

  while(app)
  {
    app->CmdLineHelp(argv[0], 0);

    iret = app->ParseCommandLineArgs(argc, argv);
    if (iret)
    {
      std::cout << std::endl << app->get_statusmsg() << std::endl;
      break;
    }

    iret = app->RunApp(argv[0]);
    if (iret)
    {
      std::cout << std::endl << app->get_statusmsg() << std::endl;
      break;
    }
    break;
  }
  if (app) delete app;
  std::cout << "\nGoodbye." << std::endl;
  return iret;
}
