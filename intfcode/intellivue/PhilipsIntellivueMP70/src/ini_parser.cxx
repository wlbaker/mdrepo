/**
 * @file ini_parser.cxx
 * 
 * @brief Implementation file for SimpleIni_parser class.
 * 
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 **/

#include "ini_parser.h"

IniParser::IniParser(std::string file_path)
  : _ini_file_path(file_path)
{
  _ini_parser = new (std::nothrow) CSimpleIniA;
}

IniParser::~IniParser()
{
  delete _ini_parser;
  _ini_parser = nullptr;
}

bool IniParser::is_option(std::string str, std::string option)
{
  return (!strcasecmp(str.c_str(), option.c_str()));
}

bool IniParser::to_bool(std::string str)
{
  return (!str.compare("true"));
}

