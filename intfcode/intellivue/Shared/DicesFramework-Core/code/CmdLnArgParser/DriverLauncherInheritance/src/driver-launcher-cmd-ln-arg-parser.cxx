/* 
 * File:   DriverLauncherCmdLnArgParser.cxx
 * Author: rfries & Brendan J. Murphy
 *
 * Created on July 29, 2014, 11:40 am
 */

#include <string.h>
#include <limits.h>
#include "../driver-launcher-cmd-ln-arg-parser.h"
#include "../../cmd-ln-arg-parser.h"

struct DriverLauncherCmdLnArgParser::impl
{
  impl() = default;

  ~impl() = default;

  DicesRcCmdLnArgParser GetModuleId(DriverLauncherCmdLnArgParser& src, std::string* module_id)
  {
    if (!module_id)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument module_id is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-moduleId";
    std::map<std::string, std::string> options_map = src.get_options();
    auto moduleId_opt = options_map.find(soption);
    module_id->assign("");

    // '-moduleId' was not a given argument
    if (moduleId_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_MODULE_ID_OPTION;
    }
    else if (moduleId_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "No argument provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_MODULE_ID_ARGUMENT;
    }
    // we got '-moduleId', return it
    else
    {
      module_id->assign(moduleId_opt->second);
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "ModuleId: " << *module_id);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }
};

DriverLauncherCmdLnArgParser::DriverLauncherCmdLnArgParser()
  :_pimpl(nullptr)
{
  static const char* sfn = "DriverLauncherCmdLnArgParser::DriverLauncherCmdLnArgParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}

DicesRcCmdLnArgParser DriverLauncherCmdLnArgParser::GetModuleId(std::string* module_id)
{
  static const char* sfn = "DriverLauncherCmdLnArgParser::GetModuleId() ";
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "_pimpl is a null pointer");
    return DicesRcCmdLnArgParser::FAIL;
  }
  return _pimpl->GetModuleId(*this, module_id);
}
