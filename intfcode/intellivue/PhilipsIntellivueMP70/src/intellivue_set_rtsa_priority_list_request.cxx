/**
 * @file intellivue_set_rtsa_priority_list_request.cxx
 *
 * @brief Defines a class which creates a set rtsa priority list request.
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author M Szwaja
 */
//=============================================================================

#include "intellivue_set_rtsa_priority_list_request.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <netinet/in.h>
#include <cstring>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "ini_rtsa_priority_list_parser.h"
#include "intellivue.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();
static const char* kIniCfgFileName = "rtsa_priority_list.ini";
static const char* kCfgPriorityListSectionName = "cfg_rtsa_priority_list";

IntellivueSetRTSAPriorityListRequest::IntellivueSetRTSAPriorityListRequest() { }

IntellivueSetRTSAPriorityListRequest::~IntellivueSetRTSAPriorityListRequest() { }

DicesRcPhilipsIntellivueMP70 IntellivueSetRTSAPriorityListRequest::
CreateSetRTSAPriorityListRequest(
  uint8_t* set_rtsa_priority_list_request_buffer,
  unsigned int size_of_buffer,
  unsigned int* size_of_request)
{
  static const char* sfn = "IntellivueSetRTSAPriorityListRequest::"
    "CreateSetRTSAPriorityListRequest() ";

  if (!set_rtsa_priority_list_request_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "set_rtsa_priority_list_request_buffer is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!size_of_request)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument size_of_request "
      "is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *size_of_request = 0;

  std::vector<unsigned int> wave_vector;
  IniRTSAPriorityListParser ini(kIniCfgFileName);

  if (ini.Load(kCfgPriorityListSectionName) != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Failed to load section "
      << kCfgPriorityListSectionName << " from file " << kIniCfgFileName);
    return DicesRcPhilipsIntellivueMP70::FAIL;
  }

  try
  {
    // Fill vector with waves from ini file
    if (ini.get_waveform_1()) wave_vector.push_back(ini.get_waveform_1());
    if (ini.get_waveform_2()) wave_vector.push_back(ini.get_waveform_2());
    if (ini.get_waveform_3()) wave_vector.push_back(ini.get_waveform_3());
    if (ini.get_waveform_4()) wave_vector.push_back(ini.get_waveform_4());
    if (ini.get_waveform_5()) wave_vector.push_back(ini.get_waveform_5());
    if (ini.get_waveform_6()) wave_vector.push_back(ini.get_waveform_6());
    if (ini.get_waveform_7()) wave_vector.push_back(ini.get_waveform_7());
    if (ini.get_waveform_8()) wave_vector.push_back(ini.get_waveform_8());
    if (ini.get_waveform_9()) wave_vector.push_back(ini.get_waveform_9());
    if (ini.get_waveform_10()) wave_vector.push_back(ini.get_waveform_10());
    if (ini.get_waveform_11()) wave_vector.push_back(ini.get_waveform_11());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Unable to push_back waveform "
      "number. " << ex.what());
    return DicesRcPhilipsIntellivueMP70::FAIL;
  }

  int waveform_data_size = wave_vector.size() * sizeof (int);

  const int kuint16_t_count_per_req = 16;
  // Make sure the buffer has enough bytes for the new set RTSA priority list
  // request.
  if (size_of_buffer
    <  kuint16_t_count_per_req * sizeof (uint16_t) + sizeof (int) + waveform_data_size)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Buffer is too small to hold "
      "set RTSA priority list request");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  uint16_t session_id = 0xE100;
  uint16_t p_context_id = 2;
  uint16_t ro_type = 1;
  uint16_t length_1 = 30 + waveform_data_size;
  uint16_t invoke_id = 0;
  uint16_t command_type = 5;
  uint16_t length_2 = 24 + waveform_data_size;
  uint16_t m_obj_class = 0x21;
  uint16_t context_id = 0;
  uint16_t handle = 0;
  int scope = 0;
  uint16_t mod_list_count = 1;
  uint16_t mod_list_length = 10 + waveform_data_size;
  uint16_t mod_operator = REPLACE;
  uint16_t attribute_id = 0xf23a;
  uint16_t attribute_length = 4 + waveform_data_size;
  uint16_t priority_list_length = waveform_data_size;

  // Piece together request
  int current_size = 0;

  uint16_t new_short = htons(static_cast<uint16_t>(session_id));
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(p_context_id));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(ro_type));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(length_1));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(invoke_id));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(command_type));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(length_2));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(m_obj_class));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(context_id));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(handle));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  int new_int = htonl(static_cast<int>(scope));
  uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_int,
    sizeof (int));
  current_size += sizeof (int);

  new_short = htons(static_cast<uint16_t>(mod_list_count));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(mod_list_length));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(mod_operator));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(attribute_id));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(attribute_length));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(wave_vector.size()));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  new_short = htons(static_cast<uint16_t>(priority_list_length));
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(
    &set_rtsa_priority_list_request_buffer[current_size],
    pnew_short,
    sizeof (uint16_t));
  current_size += sizeof (uint16_t);

  // Fill priority list with wave TextIds
  for (int ix = 0; ix < wave_vector.size(); ix++)
  {
    int new_int = htonl(static_cast<int>(wave_vector.at(ix)));
    uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
    memmove(
      &set_rtsa_priority_list_request_buffer[current_size],
      pnew_int,
      sizeof (int));
    current_size += sizeof (int);
  }

  // Clear vector
  wave_vector.clear();

  *size_of_request = current_size;

  return DicesRcPhilipsIntellivueMP70::OK;
}
