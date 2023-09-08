/* 
 * File:   DriverLauncherCmdLnArgParser.h
 * Author: rfries & Brendan J. Murphy
 *
 * Created on July 29, 2014, 11:37 am
 */

#ifndef DRIVERLAUNCHERCMDLNARGPARSER_H
#define	DRIVERLAUNCHERCMDLNARGPARSER_H

#include <string.h>
#include "../cmd-ln-arg-parser.h"

//struct DicesCmdLnArgParser::impl;

class DriverLauncherCmdLnArgParser : public DicesCmdLnArgParser
{
public:
  DriverLauncherCmdLnArgParser();
  virtual ~DriverLauncherCmdLnArgParser() = default;

  DicesRcCmdLnArgParser GetModuleId(std::string* module_id);

  // Disallow use of implicitly generated member functions:
  DriverLauncherCmdLnArgParser(const DriverLauncherCmdLnArgParser& src) = delete;
  DriverLauncherCmdLnArgParser &operator=(const DriverLauncherCmdLnArgParser& rhs) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;
};

#endif	/* DRIVERCMDLNARGPARSER_H */

