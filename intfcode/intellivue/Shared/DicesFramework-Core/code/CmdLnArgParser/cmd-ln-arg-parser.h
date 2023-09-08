/* 
 * File:   DicesCmdLnArgParser.h
 * Author: rfries
 *
 * Created on June 9, 2014, 8:38 AM
 */

#ifndef DICESCMDLNARGPARSER_H
#define	DICESCMDLNARGPARSER_H

#include "rc-cmd-ln-arg-parser.h"
#include <string>
#include <map>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>

class DicesCmdLnArgParser
{
public:
  DicesCmdLnArgParser();
  virtual ~DicesCmdLnArgParser();
  
  // simply stores all opions and corresponding arguments into a map
  DicesRcCmdLnArgParser Parse(int argc, char** argv);
  DicesRcCmdLnArgParser GetDomainId(int* domain_id);

  std::map<std::string, std::string> get_options();

  DicesCmdLnArgParser(const DicesCmdLnArgParser& orig) = delete;
  DicesCmdLnArgParser &operator=(const DicesCmdLnArgParser& orig) = delete;
  
protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

};

#endif	/* DICESCMDLNARGPARSER_H */

