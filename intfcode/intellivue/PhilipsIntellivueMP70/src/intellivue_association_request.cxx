/**
 * @file intellivue_association_request.cxx
 *
 * Create association request using the data in an XML configuration file.
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================

#include "intellivue_association_request.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "intellivue_utils.h"
#include "ini_parser.h"
#include "ini_association_request_parser.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();
static const char* KFilenameAssociationRequestCfg = "association_request_cfg.ini";
static const char* kCfgAssociationRequestSectionName = "cfg_association_request";

// Session Header and size
static uint8_t association_response_session_header[] = {
  0x0D, 0xEC
};

// Session data and size
static uint8_t association_request_session_data[] = {
  0x05, 0x08, 0x13, 0x01, 0x00, 0x16, 0x01,
  0x02, 0x80, 0x00, 0x14, 0x02, 0x00, 0x02
};

// Presentation header and size
static uint8_t association_request_presentation_header[] = {
  0xC1, 0x00 /*Filled with length of request*/,
  0x31, 0x80, 0xA0, 0x80, 0x80, 0x01, 0x01, 0x00,
  0x00, 0xA2, 0x80, 0xA0, 0x03, 0x00, 0x00, 0x01,
  0xA4, 0x80, 0x30, 0x80, 0x02, 0x01, 0x01, 0x06,
  0x04, 0x52, 0x01, 0x00, 0x01, 0x30, 0x80, 0x06,
  0x02, 0x51, 0x01, 0x00, 0x00, 0x00, 0x00, 0x30,
  0x80, 0x02, 0x01, 0x02, 0x06, 0x0C, 0x2A, 0x86,
  0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x30, 0x80, 0x06, 0x0C, 0x2A, 0x86,
  0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x61, 0x80, 0x30, 0x80, 0x02, 0x01, 0x01, 0xA0,
  0x80, 0x60, 0x80, 0xA1, 0x80, 0x06, 0x0C, 0x2A,
  0x86, 0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00,
  0x00, 0x03, 0x01, 0x00, 0x00, 0xBE, 0x80, 0x28,
  0x80, 0x06, 0x0C, 0x2A, 0x86, 0x48, 0xCE, 0x14,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02,
  0x01, 0x02, 0x81
};

// Presentation trailer and size
static uint8_t association_request_presentation_trailer[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

/* Association Release Request */
static uint8_t association_release_request[] = {
  0x09, 0x18 /* ReleaseReqSessionHeader */,
  0xC1, 0x16, 0x61, 0x80, 0x30, 0x80, 0x02, 0x01,
  0x01, 0xA0, 0x80, 0x62, 0x80, 0x80, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationHeader */,
  0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationTrailer */
};

IntellivueAssociationRequest::IntellivueAssociationRequest(
  const char* filename)
{
  const char* sfn = "IntellivueAssociationRequest::IntellivueAssociationRequest() ";
  if (!filename)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument filename is a null pointer.");
    return;
  }
  _cfg_filename = filename;
}

IntellivueAssociationRequest::IntellivueAssociationRequest()
  : _cfg_filename(KFilenameAssociationRequestCfg) { }

IntellivueAssociationRequest::~IntellivueAssociationRequest() { }

DicesRcPhilipsIntellivueMP70 IntellivueAssociationRequest::
CreateAssociationRequest(
  uint8_t* association_request_buffer,
  unsigned int size_of_buffer,
  unsigned int* size_of_request)
{
  static const char* sfn = "IntellivueAssociationRequest::"
    "CreateAssociationRequest() ";

  if (!association_request_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "association_request_buffer is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!size_of_request)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument size_of_request "
      "is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *size_of_request = 0;

  IniAssociationRequestParser ini_parser(_cfg_filename);
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  status = ini_parser.Load(kCfgAssociationRequestSectionName);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  // Get number of bytes in each array
  size_t size_of_header = sizeof(association_response_session_header)
    / sizeof(uint8_t);
  size_t size_of_session_data = sizeof(association_request_session_data)
    / sizeof(uint8_t);
  size_t size_of_presentation_header =
    sizeof(association_request_presentation_header) / sizeof(uint8_t);
  size_t size_of_association_request_presentation_trailer =
    sizeof(association_request_presentation_trailer) / sizeof(uint8_t);

  // Store length of request in presentation header
  association_request_presentation_header[1] = static_cast<uint8_t>(220);
  uint8_t length_of_user_data[] = { static_cast<uint8_t>(72) };

  size_t size_of_length_of_user_data =
    sizeof(length_of_user_data) / sizeof(uint8_t);

  size_t calc_size = size_of_header + size_of_session_data
    + size_of_presentation_header + size_of_length_of_user_data
    + (12 * sizeof(int)) + (12 * sizeof(uint16_t))
    + size_of_association_request_presentation_trailer;
  if (size_of_buffer < calc_size)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Buffer is too small to hold "
      "store association request.");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  memmove(
    &association_request_buffer[*size_of_request],
    association_response_session_header,
    size_of_header);
  *size_of_request += size_of_header;

  memmove(
    &association_request_buffer[*size_of_request],
    association_request_session_data,
    size_of_session_data);
  *size_of_request += size_of_session_data;

  memmove(
    &association_request_buffer[*size_of_request],
    association_request_presentation_header,
    size_of_presentation_header);
  *size_of_request += size_of_presentation_header;

  memmove(
    &association_request_buffer[*size_of_request],
    length_of_user_data,
    size_of_length_of_user_data);
  *size_of_request += size_of_length_of_user_data;

  int new_int = htonl(static_cast<int>(ini_parser.get_protocol_version()));
  uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_nomenclature_version()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_functional_units()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_system_type()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_startup_mode()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  uint16_t new_short = htons(static_cast<uint16_t>(
    ini_parser.get_option_list_count()));
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_option_list_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_supported_profiles_count()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_supported_profiles_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(ini_parser.get_supported_att_id()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_supported_ava_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_int = htonl(static_cast<int>(ini_parser.get_poll_profile_revision()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_min_poll_period()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_max_mtu_rx()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_max_mtu_tx()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(ini_parser.get_max_bw_tx()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_int = htonl(static_cast<int>(0x60000000));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_optional_packages_count()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(
    ini_parser.get_optional_packages_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(ini_parser.get_opt_attribute_id()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(ini_parser.get_opt_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_int = htonl(static_cast<int>(ini_parser.get_poll_profile_ext_opt_options()));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_short = htons(static_cast<uint16_t>(ini_parser.get_poll_ext_count()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(static_cast<uint16_t>(ini_parser.get_poll_ext_length()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &association_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  memmove(
    &association_request_buffer[*size_of_request],
    association_request_presentation_trailer,
    size_of_association_request_presentation_trailer);
  *size_of_request += size_of_association_request_presentation_trailer;

  return DicesRcPhilipsIntellivueMP70::OK;
}
