#include "connection-utilities.h"

#include <unistd.h>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

std::string exec(const char* cmd)
{
  static const char* sfn = "exec(const char* cmd)";

  char buffer[128];
  std::string result = "";

  if(!cmd)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << " Empty function argument");
    return "ERROR";
  }

  FILE* pipe = popen(cmd, "r");

  if (!pipe)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << " Failed to open file: " << cmd);
    return "ERROR";
  }

  while (!feof(pipe)) {
    if (fgets(buffer, 128, pipe) != NULL)
    {
      result += buffer;
    }
  }
  pclose(pipe);
  return result;
}

bool IsPostgresServiceUp()
{
  static const char* sfn = "IsPostgresServiceUp()";

  // use script to determine if postgres service is up
  std::string result = "";
  try
  {
    result = exec("service postgresql status");
  }
  catch (const std::exception& e)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << " Exception creating database: " << e.what());
    result = "ERROR";
  }

  std::size_t found = result.find("online");

  return found != std::string::npos;
}

void WaitForPostgresServiceUp()
{
  while(!IsPostgresServiceUp())
  {
    sleep(1);
  }
}
