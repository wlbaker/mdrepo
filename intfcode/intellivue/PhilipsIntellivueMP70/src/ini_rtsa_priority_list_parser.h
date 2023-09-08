/**
 * @file   ini_rtsa_priority_list_parser.h
 * @author M Szwaja
 *
 * @brief SimpleIni_parser is an example class that defines Load, Save, and
 * functions which utilize SimpleIni.h. This class has variables that need
 * to be set outside of its own scope, the desired values for these
 * variables are located within an ini file, this class holds two functions 
 * for accessing these values.
 *
 * @section license MIT LICENCE
 * http://www.opensource.org/licenses/mit-license.php
 * and applies to SimpleIni.h
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 *
 * Created on May 6, 2014, 3:37 PM
 **/

#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INI_RTSA_PRIORITY_LIST_PARSER_H_
#define	PHILIPS_INTELLIVUE_MP70_SRC_INI_RTSA_PRIORITY_LIST_PARSER_H_

#include "ini_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IniRTSAPriorityListParser : public IniParser
{
 public:
  friend class IniRTSAPriorityListParserUnitTest;

  IniRTSAPriorityListParser(std::string file_path);
  ~IniRTSAPriorityListParser();

  DicesRcPhilipsIntellivueMP70 Load(std::string section_name);

  unsigned int get_waveform_1();
  unsigned int get_waveform_2();
  unsigned int get_waveform_3();
  unsigned int get_waveform_4();
  unsigned int get_waveform_5();
  unsigned int get_waveform_6();
  unsigned int get_waveform_7();
  unsigned int get_waveform_8();
  unsigned int get_waveform_9();
  unsigned int get_waveform_10();
  unsigned int get_waveform_11();

 private:
  IniRTSAPriorityListParser(const IniRTSAPriorityListParser &src);
  IniRTSAPriorityListParser &operator=(const IniRTSAPriorityListParser &rhs);

  // All RTSA priority list waveforms read from ini file
  unsigned int _waveform_1;
  unsigned int _waveform_2;
  unsigned int _waveform_3;
  unsigned int _waveform_4;
  unsigned int _waveform_5;
  unsigned int _waveform_6;
  unsigned int _waveform_7;
  unsigned int _waveform_8;
  unsigned int _waveform_9;
  unsigned int _waveform_10;
  unsigned int _waveform_11;
};

#endif
