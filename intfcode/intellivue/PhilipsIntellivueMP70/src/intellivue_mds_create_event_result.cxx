/**
 * @file intellivue_mds_create_event_result.cxx
 *
 * @brief Defines a class which creates an MDS create event result message.
 *
 * @author M Szwaja
 */
//=============================================================================

#include "intellivue_mds_create_event_result.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"

static uint8_t kMDSCreateEventResult [] = { 0xE1, 0x00, 0x00, 0x02, 0x00, 0x02,
  0x00, 0x14, 0x00, 0x01, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x21, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x48, 0x47, 0x00, 0x0d, 0x06, 0x00, 0x00 };

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueMDSCreateEventResult::IntellivueMDSCreateEventResult() { }

IntellivueMDSCreateEventResult::~IntellivueMDSCreateEventResult() { }

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventResult::
CreateMDSCreateEventResult(
  uint8_t* mds_create_event_result,
  unsigned int size_of_buffer,
  unsigned int* size_of_request)
{
  static const char* sfn = "IntellivueMDSCreateEventResult::"
    "CreateMDSCreateEventResult() ";
  if (!mds_create_event_result)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "mds_create_event_result is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!size_of_request)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument size_of_request "
      "is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *size_of_request = 0;

  if (size_of_buffer < sizeof(kMDSCreateEventResult))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "MDS create event result buffer "
      "length (" << size_of_buffer << ") is too small to contain result "
      "size (" << sizeof(kMDSCreateEventResult) << ")");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  memmove(
    mds_create_event_result,
    kMDSCreateEventResult,
    sizeof(kMDSCreateEventResult));
  *size_of_request = sizeof(kMDSCreateEventResult);

  return DicesRcPhilipsIntellivueMP70::OK;
}