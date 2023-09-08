/**
 * @file   ini_dim_parser.h
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

#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INI_DIM_PARSER_H_
#define	PHILIPS_INTELLIVUE_MP70_SRC_INI_DIM_PARSER_H_

#include "Core/IniParser/simple-ini.h"
#include "ini_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class DIMParser : public IniParser
{
 public:
  friend class DIMParserUnitTest;

  DIMParser(std::string file_path);
  ~DIMParser();

  std::string get_manufacturer();
  std::string get_model();
  std::string get_software_version();
  std::string get_database_name();
  std::string get_database_user();
  std::string get_database_password();
  std::string get_database_host();
  std::string get_port_name();
  int get_baud_rate();
  int get_data_bits();
  int get_stop_bits();
  int get_handshaking();
  std::string get_parity();
  bool get_enable_hardware_flow_control();
  bool get_enable_software_flow_control();
  int get_connect_indication_port();
  int get_protocol_udp_port();

  DicesRcPhilipsIntellivueMP70 Load(std::string section_name);

 private:
  DIMParser(const DIMParser &src);
  DIMParser &operator=(const DIMParser &rhs);

  // Variables that require externally defined values.
  std::string _manufacturer;
  std::string _model;
  std::string _software_version;

  std::string _database_name;
  std::string _database_user;
  std::string _database_password;
  std::string _database_host;

  std::string _port_name;
  int _baud_rate;
  int _data_bits;
  int _stop_bits;
  int _handshaking;
  std::string _parity;
  bool _enable_hardware_flow_control;
  bool _enable_software_flow_control;

  int _connect_indication_port;
  int _protocol_udp_port;
};

#endif
