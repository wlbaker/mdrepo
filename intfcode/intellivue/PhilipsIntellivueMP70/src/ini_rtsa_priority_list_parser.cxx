/**
 * @file ini_rtsa_priority_list_parser.cxx
 * 
 * @brief Defines a class which parses the rtsa priority list ini file.
 * 
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 **/

#include "ini_rtsa_priority_list_parser.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

static const char* kSectionCfgRTSAPriorityList = "cfg_rtsa_priority_list";
static const char* kWaveform1 = "waveform1";
static const char* kWaveform2 = "waveform2";
static const char* kWaveform3 = "waveform3";
static const char* kWaveform4 = "waveform4";
static const char* kWaveform5 = "waveform5";
static const char* kWaveform6 = "waveform6";
static const char* kWaveform7 = "waveform7";
static const char* kWaveform8 = "waveform8";
static const char* kWaveform9 = "waveform9";
static const char* kWaveform10 = "waveform10";
static const char* kWaveform11 = "waveform11";
static const unsigned int kDefaultWaveformValue = 0;

IniRTSAPriorityListParser::IniRTSAPriorityListParser(std::string file_path)
  : IniParser(file_path),
  _waveform_1(kDefaultWaveformValue),
  _waveform_2(kDefaultWaveformValue),
  _waveform_3(kDefaultWaveformValue),
  _waveform_4(kDefaultWaveformValue),
  _waveform_5(kDefaultWaveformValue),
  _waveform_6(kDefaultWaveformValue),
  _waveform_7(kDefaultWaveformValue),
  _waveform_8(kDefaultWaveformValue),
  _waveform_9(kDefaultWaveformValue),
  _waveform_10(kDefaultWaveformValue),
  _waveform_11(kDefaultWaveformValue) { }

IniRTSAPriorityListParser::~IniRTSAPriorityListParser() { }

unsigned int IniRTSAPriorityListParser::get_waveform_1()
{
  return _waveform_1;
}

unsigned int IniRTSAPriorityListParser::get_waveform_2()
{
  return _waveform_2;
}

unsigned int IniRTSAPriorityListParser::get_waveform_3()
{
  return _waveform_3;
}

unsigned int IniRTSAPriorityListParser::get_waveform_4()
{
  return _waveform_4;
}

unsigned int IniRTSAPriorityListParser::get_waveform_5()
{
  return _waveform_5;
}

unsigned int IniRTSAPriorityListParser::get_waveform_6()
{
  return _waveform_6;
}

unsigned int IniRTSAPriorityListParser::get_waveform_7()
{
  return _waveform_7;
}

unsigned int IniRTSAPriorityListParser::get_waveform_8()
{
  return _waveform_8;
}

unsigned int IniRTSAPriorityListParser::get_waveform_9()
{
  return _waveform_9;
}

unsigned int IniRTSAPriorityListParser::get_waveform_10()
{
  return _waveform_10;
}

unsigned int IniRTSAPriorityListParser::get_waveform_11()
{
  return _waveform_11;
}

DicesRcPhilipsIntellivueMP70 IniRTSAPriorityListParser::Load(
  std::string section_name)
{
  static const char* sfn = "IniRTSAPriorityListParser::Load() ";

  if (!_ini_parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "_ini_parser is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::
      INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE;
  }

  static const int kmax_string_size = 256;
  if (_ini_file_path.length() > kmax_string_size)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "File path " << _ini_file_path
      << " exceeds max string size " << kmax_string_size;);
    return DicesRcPhilipsIntellivueMP70::
      PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE;
  }

  if (_ini_parser->LoadFile(_ini_file_path.c_str()))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to load ini file "
      << _ini_file_path);
    return DicesRcPhilipsIntellivueMP70::
      PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE;
  }

  if (!strcmp(section_name.c_str(), kSectionCfgRTSAPriorityList))
  {
    _waveform_1 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform1,
      kDefaultWaveformValue);

    _waveform_2 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform2,
      kDefaultWaveformValue);

    _waveform_3 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform3,
      kDefaultWaveformValue);

    _waveform_4 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform4,
      kDefaultWaveformValue);

    _waveform_5 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform5,
      kDefaultWaveformValue);

    _waveform_6 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform6,
      kDefaultWaveformValue);

    _waveform_7 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform7,
      kDefaultWaveformValue);

    _waveform_8 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform8,
      kDefaultWaveformValue);

    _waveform_9 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform9,
      kDefaultWaveformValue);

    _waveform_10 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform10,
      kDefaultWaveformValue);

    _waveform_11 = _ini_parser->GetUnsignedLongValue(
      kSectionCfgRTSAPriorityList,
      kWaveform11,
      kDefaultWaveformValue);
  }
  else
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Unknown section name "
      << section_name);
    return DicesRcPhilipsIntellivueMP70::
      PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE;
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}
