/**
 * @file   ini_association_request_parser.h
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

#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INI_ASSOCIATION_REQUEST_PARSER_H_
#define	PHILIPS_INTELLIVUE_MP70_SRC_INI_ASSOCIATION_REQUEST_PARSER_H_

#include "ini_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IniAssociationRequestParser : public IniParser
{
 public:
  friend class IniAssociationRequestParserUnitTest;

  IniAssociationRequestParser(std::string file_path);
  ~IniAssociationRequestParser();

  unsigned long get_length_of_request();
  unsigned long get_length_of_userdata();
  unsigned long get_protocol_version();
  unsigned long get_nomenclature_version();
  unsigned long get_functional_units();
  unsigned long get_system_type();
  unsigned long get_startup_mode();
  unsigned long get_option_list_count();
  unsigned long get_option_list_length();
  unsigned long get_supported_profiles_count();
  unsigned long get_supported_profiles_length();
  unsigned long get_supported_att_id();
  unsigned long get_supported_ava_length();
  unsigned long get_poll_profile_revision();
  unsigned long get_min_poll_period();
  unsigned long get_max_mtu_rx();
  unsigned long get_max_mtu_tx();
  unsigned long get_max_bw_tx();
  unsigned long get_poll_profile_opt_options();
  unsigned long get_optional_packages_count();
  unsigned long get_optional_packages_length();
  unsigned long get_opt_attribute_id();
  unsigned long get_opt_length();
  unsigned long get_poll_profile_ext_opt_options();
  unsigned long get_poll_ext_count();
  unsigned long get_poll_ext_length();

  DicesRcPhilipsIntellivueMP70 Load(std::string section_name);

 private:
  IniAssociationRequestParser(const IniAssociationRequestParser &src);
  IniAssociationRequestParser &operator=(const IniAssociationRequestParser &rhs);

  // All association request user data read from ini file
  unsigned long _length_of_request;
  unsigned long _length_of_userdata;
  unsigned long _protocol_version;
  unsigned long _nomenclature_version;
  unsigned long _functional_units;
  unsigned long _system_type;
  unsigned long _startup_mode;
  unsigned long _option_list_count;
  unsigned long _option_list_length;
  unsigned long _supported_profiles_count;
  unsigned long _supported_profiles_length;
  unsigned long _supported_att_id;
  unsigned long _supported_ava_length;
  unsigned long _poll_profile_revision;
  unsigned long _min_poll_period;
  unsigned long _max_mtu_rx;
  unsigned long _max_mtu_tx;
  unsigned long _max_bw_tx;
  unsigned long _poll_profile_opt_options;
  unsigned long _optional_packages_count;
  unsigned long _optional_packages_length;
  unsigned long _opt_attribute_id;
  unsigned long _opt_length;
  unsigned long _poll_profile_ext_opt_options;
  unsigned long _poll_ext_count;
  unsigned long _poll_ext_length;
};

#endif
