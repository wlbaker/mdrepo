/**
 * @file intellivue_association_release_request.cxx
 *
 * @brief Defines a class which creates an association release request.
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

#include "intellivue_association_release_request.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <cstring>
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

// Association Release Request
static const uint8_t kAssociationReleaseRequest[] = {
  0x09, 0x18 /* ReleaseReqSessionHeader */,
  0xC1, 0x16, 0x61, 0x80, 0x30, 0x80, 0x02, 0x01,
  0x01, 0xA0, 0x80, 0x62, 0x80, 0x80, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationHeader */,
  0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationTrailer */
};

IntellivueAssociationReleaseRequest::IntellivueAssociationReleaseRequest() { }

IntellivueAssociationReleaseRequest::~IntellivueAssociationReleaseRequest() { }

DicesRcPhilipsIntellivueMP70 IntellivueAssociationReleaseRequest::
CreateAssociationReleaseRequest(
  uint8_t* association_release_request_buffer,
  unsigned int size_of_buffer,
  unsigned int* size_of_request)
{
  static const char* sfn = "IntellivueAssociationRequest::"
    "CreateAssociationReleaseRequest() ";

  if (!association_release_request_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "association_release_request_buffer is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!size_of_request)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument size_of_request "
      "is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *size_of_request = 0;

  // Make sure the buffer has enough bytes for the new association release
  // request
  if (size_of_buffer < sizeof(kAssociationReleaseRequest))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Association release request buffer "
      "length (" << size_of_buffer << ") is too small to contain request "
      "size (" << sizeof(kAssociationReleaseRequest) << ")");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  memmove(
    association_release_request_buffer,
    kAssociationReleaseRequest,
    sizeof(kAssociationReleaseRequest));
  *size_of_request = sizeof(kAssociationReleaseRequest);

  return DicesRcPhilipsIntellivueMP70::OK;
}
