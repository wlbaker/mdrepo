/**
 * @file   device_driver_ini_parser.h
 * @author M Szwaja
 *
 * @brief This is a class declaration that defines Load, Save, and
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
 */
//=============================================================================
#ifndef DICES_DEVICE_DRIVER_INI_PARSER_SRC_DEVICE_DRIVER_INI_PARSER_H
#define	DICES_DEVICE_DRIVER_INI_PARSER_SRC_DEVICE_DRIVER_INI_PARSER_H

#include "simple-ini.h"
#include "rc-ini-parser-device-driver.h"

// This is a class that has variables that need to be set from an
// external file. The values are stored in a .ini file.
class DIMParser
{
public:
  DIMParser(std::string file_path);
  ~DIMParser();

  std::string get_udi();
  std::string get_manufacturer();
  std::string get_model();
  std::string get_software_version();
  std::string get_port_name();
  int get_baud_rate();
  int get_data_bits();
  int get_stop_bits();
  int get_handshaking();
  std::string get_parity();
  bool get_enable_hardware_flow_control();
  bool get_enable_software_flow_control();
  int get_domain_id();

  // Database configuration
  std::string get_db_host();
  std::string get_db_port();
  std::string get_db_user();
  std::string get_db_pwd();
  std::string get_db_name();


  DicesRcDeviceDriverIniParser Load(std::string section_name);
  DicesRcDeviceDriverIniParser PrintConfig();

private:
  DIMParser(const DIMParser &src);
  DIMParser &operator=(const DIMParser &rhs);

  std::string _udi;
  std::string _manufacturer;
  std::string _model;
  std::string _software_version;

  std::string _port_name;
  int _baud_rate;
  int _data_bits;
  int _stop_bits;
  int _handshaking;
  std::string _parity;
  bool _enable_hardware_flow_control;
  bool _enable_software_flow_control;

  // Database configuration
  std::string _db_host;
  std::string _db_port;
  std::string _db_user;
  std::string _db_pwd;
  std::string _db_name;

  int _domain_id;

  std::string _ini_file_path;
};

#endif

