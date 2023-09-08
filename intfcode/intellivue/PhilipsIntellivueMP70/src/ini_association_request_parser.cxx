/**
 * @file ini_association_request_parser.cxx
 * 
 * @brief Implementation file for SimpleIni_parser class.
 * 
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 **/

#include "ini_association_request_parser.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

static const char* kSectionCfgAssociationRequest = "cfg_association_request";

// Association Request User Data
static const char* kLengthOfRequest = "length_of_request";
static const char* kLengthOfUserData = "length_of_userdata";
static const char* kProtocolVersion = "protocol_version";
static const char* kNomenclatureVersion = "nomenclature_version";
static const char* kFunctionalUnits = "functional_units";
static const char* kSystemType = "system_type";
static const char* kStartupMode = "startup_mode";
static const char* kOptionListCount = "option_list_count";
static const char* kOptionListLength = "option_list_length";
static const char* kSupportedProfilesCount = "supported_profiles_count";
static const char* kSupportedProfilesLength = "supported_profiles_length";
static const char* kSupportedAttId = "supported_att_id";
static const char* kSupportedAvaLength = "supported_ava_length";
static const char* kPollProfileRevision = "poll_profile_revision";
static const char* kMinPollPeriod = "min_poll_period";
static const char* kMaxMtuRx = "max_mtu_rx";
static const char* kMaxMtuTx = "max_mtu_tx";
static const char* kMaxBwTx = "max_bw_tx";
static const char* kPollProfileOptOptions = "poll_profile_opt_options";
static const char* kOptionalPackagesCount = "optional_packages_count";
static const char* kOptionalPackagesLength = "optional_packages_length";
static const char* kOptAttributeId = "opt_attribute_id";
static const char* kOptLength = "opt_length";
static const char* kPollProfileExtOptOptions = "poll_profile_ext_opt_options";
static const char* kPollExtCount = "poll_ext_count";
static const char* kPollExtLength = "poll_ext_length";

static const unsigned long kDefaultLengthOfRequest = 220;
static const unsigned long kDefaultLengthOfUserData = 72;
static const unsigned long kDefaultProtocolVersion = 0x80000000;
static const unsigned long kDefaultNomenclatureVersion = 0x40000000;
static const unsigned long kDefaultFunctionalUnits = 0;
static const unsigned long kDefaultSystemType = 0x80000000;
static const unsigned long kDefaultStartupMode = 0x20000000;
static const unsigned long kDefaultOptionListCount = 0;
static const unsigned long kDefaultOptionListLength = 0;
static const unsigned long kDefaultSupportedProfilesCount = 1;
static const unsigned long kDefaultSupportedProfilesLength = 44;
static const unsigned long kDefaultSupportedAttId = 1;
static const unsigned long kDefaultSupportedAvaLength = 40;
static const unsigned long kDefaultPollProfileRevision = 0x80000000;
static const unsigned long kDefaultMinPollPeriod = 800000;
static const unsigned long kDefaultMaxMtuRx = 1000;
static const unsigned long kDefaultMaxMtuTx = 1000;
static const unsigned long kDefaultMaxBwTx = 0xffffffff;
static const unsigned long kDefaultPollProfileOptOptions = 0x60000000;
static const unsigned long kDefaultOptionalPackagesCount = 1;
static const unsigned long kDefaultOptionalPackagesLength = 12;
static const unsigned long kDefaultOptAttributeId = 0xf001;
static const unsigned long kDefaultOptLength = 8;
static const unsigned long kDefaultPollProfileExtOptOptions = 0x88000000;
static const unsigned long kDefaultPollExtCount = 0;
static const unsigned long kDefaultPollExtLength = 0;

IniAssociationRequestParser::IniAssociationRequestParser(std::string file_path)
  : IniParser(file_path),
  _length_of_request(kDefaultLengthOfRequest),
  _length_of_userdata(kDefaultLengthOfUserData),
  _protocol_version(kDefaultProtocolVersion),
  _nomenclature_version(kDefaultNomenclatureVersion),
  _functional_units(kDefaultFunctionalUnits),
  _system_type(kDefaultSystemType),
  _startup_mode(kDefaultStartupMode),
  _option_list_count(kDefaultOptionListCount),
  _option_list_length(kDefaultOptionListLength),
  _supported_profiles_count(kDefaultSupportedProfilesCount),
  _supported_profiles_length(kDefaultSupportedProfilesLength),
  _supported_att_id(kDefaultSupportedAttId),
  _supported_ava_length(kDefaultSupportedAvaLength),
  _poll_profile_revision(kDefaultPollProfileRevision),
  _min_poll_period(kDefaultMinPollPeriod),
  _max_mtu_rx(kDefaultMaxMtuRx),
  _max_mtu_tx(kDefaultMaxMtuTx),
  _max_bw_tx(kDefaultMaxBwTx),
  _poll_profile_opt_options(kDefaultPollProfileOptOptions),
  _optional_packages_count(kDefaultOptionalPackagesCount),
  _optional_packages_length(kDefaultOptionalPackagesLength),
  _opt_attribute_id(kDefaultOptAttributeId),
  _opt_length(kDefaultOptLength),
  _poll_profile_ext_opt_options(kDefaultPollProfileExtOptOptions),
  _poll_ext_count(kDefaultPollExtCount),
  _poll_ext_length(kDefaultPollExtLength) { }

IniAssociationRequestParser::~IniAssociationRequestParser() { }

unsigned long IniAssociationRequestParser::get_length_of_request()
{
  return _length_of_request;
}

unsigned long IniAssociationRequestParser::get_length_of_userdata()
{
  return _length_of_userdata;
}

unsigned long IniAssociationRequestParser::get_protocol_version()
{
  return _protocol_version;
}

unsigned long IniAssociationRequestParser::get_nomenclature_version()
{
  return _nomenclature_version;
}

unsigned long IniAssociationRequestParser::get_functional_units()
{
  return _functional_units;
}

unsigned long IniAssociationRequestParser::get_system_type()
{
  return _system_type;
}

unsigned long IniAssociationRequestParser::get_startup_mode()
{
  return _startup_mode;
}

unsigned long IniAssociationRequestParser::get_option_list_count()
{
  return _option_list_count;
}

unsigned long IniAssociationRequestParser::get_option_list_length()
{
  return _option_list_length;
}

unsigned long IniAssociationRequestParser::get_supported_profiles_count()
{
  return _supported_profiles_count;
}

unsigned long IniAssociationRequestParser::get_supported_profiles_length()
{
  return _supported_profiles_length;
}

unsigned long IniAssociationRequestParser::get_supported_att_id()
{
  return _supported_att_id;
}

unsigned long IniAssociationRequestParser::get_supported_ava_length()
{
  return _supported_ava_length;
}

unsigned long IniAssociationRequestParser::get_poll_profile_revision()
{
  return _poll_profile_revision;
}

unsigned long IniAssociationRequestParser::get_min_poll_period()
{
  return _min_poll_period;
}

unsigned long IniAssociationRequestParser::get_max_mtu_rx()
{
  return _max_mtu_rx;
}

unsigned long IniAssociationRequestParser::get_max_mtu_tx()
{
  return _max_mtu_tx;
}

unsigned long IniAssociationRequestParser::get_max_bw_tx()
{
  return _max_bw_tx;
}

unsigned long IniAssociationRequestParser::get_poll_profile_opt_options()
{
  return _poll_profile_opt_options;
}

unsigned long IniAssociationRequestParser::get_optional_packages_count()
{
  return _optional_packages_count;
}

unsigned long IniAssociationRequestParser::get_optional_packages_length()
{
  return _optional_packages_length;
}

unsigned long IniAssociationRequestParser::get_opt_attribute_id()
{
  return _opt_attribute_id;
}

unsigned long IniAssociationRequestParser::get_opt_length()
{
  return _opt_length;
}

unsigned long IniAssociationRequestParser::get_poll_profile_ext_opt_options()
{
  return _poll_profile_ext_opt_options;
}

unsigned long IniAssociationRequestParser::get_poll_ext_count()
{
  return _poll_ext_count;
}

unsigned long IniAssociationRequestParser::get_poll_ext_length()
{
  return _poll_ext_length;
}

DicesRcPhilipsIntellivueMP70 IniAssociationRequestParser::Load(std::string section_name)
{
  static const char* sfn = "IniAssociationRequestParser::Load() ";

  if (!_ini_parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "_ini_parser is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE;
  }

  if (_ini_file_path.length() > 256)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "File path " << _ini_file_path
      << " exceeds max string size");
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE;
  }

  if (_ini_parser->LoadFile(_ini_file_path.c_str()))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to load ini file "
      << _ini_file_path);
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE;
  }

  if (!strcmp(section_name.c_str(), kSectionCfgAssociationRequest))
  {
    _length_of_request = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kLengthOfRequest,
      kDefaultLengthOfRequest);

    _length_of_userdata = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kLengthOfUserData,
      kDefaultLengthOfUserData);

    _protocol_version = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kProtocolVersion,
      kDefaultProtocolVersion);

    _nomenclature_version = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kNomenclatureVersion,
      kDefaultNomenclatureVersion);

    _functional_units = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kFunctionalUnits,
      kDefaultFunctionalUnits);

    _system_type = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kSystemType,
      kDefaultSystemType);

    _startup_mode = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kStartupMode,
      kDefaultStartupMode);

    _option_list_count = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptionListCount,
      kDefaultOptionListCount);

    _option_list_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptionListLength,
      kDefaultOptionListLength);

    _supported_profiles_count = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kSupportedProfilesCount,
      kDefaultSupportedProfilesCount);

    _supported_profiles_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kSupportedProfilesLength,
      kDefaultSupportedProfilesLength);

    _supported_att_id = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kSupportedAttId,
      kDefaultSupportedAttId);

    _supported_ava_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kSupportedAvaLength,
      kDefaultSupportedAvaLength);

    _poll_profile_revision = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kPollProfileRevision,
      kDefaultPollProfileRevision);

    _min_poll_period = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kMinPollPeriod,
      kDefaultMinPollPeriod);

    _max_mtu_rx = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kMaxMtuRx,
      kDefaultMaxMtuRx);

    _max_mtu_tx = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kMaxMtuTx,
      kDefaultMaxMtuTx);

    _max_bw_tx = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kMaxBwTx,
      kDefaultMaxBwTx);

    _poll_profile_opt_options = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kPollProfileOptOptions,
      kDefaultPollProfileOptOptions);

    _optional_packages_count = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptionalPackagesCount,
      kDefaultOptionalPackagesCount);

    _optional_packages_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptionalPackagesLength,
      kDefaultOptionalPackagesLength);

    _opt_attribute_id = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptAttributeId,
      kDefaultOptAttributeId);

    _opt_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kOptLength,
      kDefaultOptLength);

    _poll_profile_ext_opt_options = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kPollProfileExtOptOptions,
      kDefaultPollProfileExtOptOptions);

    _poll_ext_count = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kPollExtCount,
      kDefaultPollExtCount);

    _poll_ext_length = _ini_parser->GetUnsignedLongValue(
      kSectionCfgAssociationRequest,
      kPollExtLength,
      kDefaultPollExtLength);
  }
  else
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Unknown section name "
      << section_name);
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE;
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}
