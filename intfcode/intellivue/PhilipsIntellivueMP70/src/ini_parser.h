/**
 * @file   ini_parser.h
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

#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INI_PARSER_H_
#define	PHILIPS_INTELLIVUE_MP70_SRC_INI_PARSER_H_

#include "Core/IniParser/simple-ini.h"

enum class DicesRcPhilipsIntellivueMP70;

// This is an example class that has variables that need to be set from an
// external file. The values are stored in a .ini file referred to as file_name.

class IniParser
{
 public:
  IniParser(std::string file_path);
  ~IniParser();

  // file_name is a .ini file which holds the desired external values.
  virtual DicesRcPhilipsIntellivueMP70 Load(std::string section_name) = 0;

 protected:
  std::string _ini_file_path;

  // CSimpleIniTempl (the primary class in SimpleIni.h) is templated. For 
  // convenience there are 4 typedef'd versions.
  // CSimpleIniA is a typedef for the CSimpleIniTempl class that is not 
  // (upper/lower) case specific when reading the keys in an ini file 
  // (ie. Example_String and example_string are considered the same)
  // CSimpleIniCaseA would be used if the user wanted to specify keys by case.

  // This class contains 
  CSimpleIniA *_ini_parser;

  // Function replacement for IS_OPTION macro
  bool is_option(std::string str, std::string option);

  // Converts strings to bool
  bool to_bool(std::string str);

 private:
  IniParser(const IniParser &src);
  IniParser &operator=(const IniParser &rhs);
};

#endif
