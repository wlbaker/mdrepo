/**
 * @file intellivue_association_response.cxx
 *
 * @brief Defines class which parses association responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_association_response.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "intellivue.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueAssociationResponse::IntellivueAssociationResponse() { }

IntellivueAssociationResponse::~IntellivueAssociationResponse() { }

DicesRcPhilipsIntellivueMP70 IntellivueAssociationResponse::
IsAssociationResponse(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueAssociationResponse::"
    "IsAssociationResponse() ";

  if (!is_msg)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument is_msg is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  *is_msg = false;

  if (numbytes < 1) return DicesRcPhilipsIntellivueMP70::OK;

  switch (buffer[0])
  {
    case CN_SPDU_SI:
    case AC_SPDU_SI:
    case RF_SPDU_SI:
    case FN_SPDU_SI:
    case DN_SPDU_SI:
    case AB_SPDU_SI:
      *is_msg = true;
      break;
    default:
      break;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueAssociationResponse::
ParseAssociationResponse(
  AssociationResponse* association_response,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueAssociationResponse::"
    "ParseAssociationResponse() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  if (!association_response)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "association_response is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  uint32_t iu32x = 0;
  uint8_t iu8x = 0;
  int iindex = 0;
  int iuserdataindex = -1;
  int ibytecount = 0;
  uint16_t session_header_length = 0;

  // NOTE: The size of SessionHeader should be 2 bytes, but because LI length
  // is a pointer, sizeof(SessionHeader) returns 9 (1 + 8 byte pointer). We
  // only parse 2 bytes here (one for type and one for first byte of LI length).
  // This works out because we need to parse the first byte of LI
  // length first to determine the number of bytes needed for length.
  // Using constant here instead of sizeof call.
  const int ksize_of_session_header = 2;
  if ((numbytes - iindex) < ksize_of_session_header)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Corrupt association response. Not enough bytes ("
                    << (numbytes - iindex) << ") left to parse SessionHeader bytes ("
                    << ksize_of_session_header << ")");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // Session Header
  association_response->sessionHeader.type = buffer[iindex];
  uint8_t li_length = buffer[iindex + 1];
  iindex += 2;

  if (li_length == 0xFF)
  {
    // L = 256 is encoded as {0xFF,0x01,0x00}
    const int knum_li_bytes = 3;
    association_response->sessionHeader.length =
      new (std::nothrow) uint8_t[knum_li_bytes]();
    if (!association_response->sessionHeader.length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
        "sessionHeader length size " << knum_li_bytes << " bytes");
      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
    }
    if ((numbytes - iindex) < (knum_li_bytes - 1))
    {
      LOG4CPLUS_ERROR(root_logger, sfn
                      << "Corrupt association response. Not enough bytes ("
                      << (numbytes - iindex) << ") left to parse remaining LI length bytes ("
                      << (knum_li_bytes - 1) << ")");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }
    association_response->sessionHeader.length[0] = li_length;
    association_response->sessionHeader.length[1] = buffer[iindex];
    association_response->sessionHeader.length[2] = buffer[iindex + 1];

    session_header_length = ntohs(*(reinterpret_cast<uint16_t*>(
      &buffer[iindex])));
    iindex += 2;
  }
  else
  {
    // L = 15 is encoded as 0x0f
    const int knum_li_bytes = 1;
    association_response->sessionHeader.length =
      new (std::nothrow) uint8_t[knum_li_bytes]();
    if (!association_response->sessionHeader.length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
        "sessionHeader length size " << knum_li_bytes << " bytes");
      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
    }
    association_response->sessionHeader.length[0] = li_length;
    session_header_length = static_cast<uint16_t>(
      association_response->sessionHeader.length[0]);
  }

  if ((numbytes - iindex) < static_cast<int>(session_header_length))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt association response. "
      "Session header length is greater than the size of the message");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  if ((numbytes - iindex) < sizeof(intellivue::SPpdu))
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Corrupt association response. Not enough bytes ("
                    << (numbytes - iindex) << ") left to parse remaining SPpdu bytes ("
                    << sizeof(intellivue::SPpdu) << ")");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  association_response->spdh.session_id = ntohs(*(reinterpret_cast<uint16_t*>(
    &buffer[iindex])));
  iindex += 2;

  association_response->spdh.p_context_id = ntohs(
    *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  switch (association_response->sessionHeader.type)
  {
    case AC_SPDU_SI: // Accepted
      // Continue on to parsing the UserData
      // TODO
      break;
    case RF_SPDU_SI: // Refused
      // Something is wrong with the association request message,
      // or another client is already associated with the Intellivue.
      // The UserData section is empty
      LOG4CPLUS_WARN(root_logger, sfn << "Received session refuse header "
        "RF_SPDU_SI. Something is wrong with the association request message, "
        "or another client is already associated with the Intellivue. "
        "The UserData section is empty.");
      return DicesRcPhilipsIntellivueMP70::ASSOCIATION_REFUSED;
      break;
    case AB_SPDU_SI: // Aborted
      // A timeout occurred. Client must try to associate again.
      // The UserData section is empty
      LOG4CPLUS_WARN(root_logger, sfn << "Received session abort header "
        "AB_SPDU_SI. Indicates immediate termination of the association. "
        "The UserData section is empty.");
      return DicesRcPhilipsIntellivueMP70::ASSOCIATION_ABORTED;
      break;
    case DN_SPDU_SI: // Session Disconnect
      // A Session Disconnect header. The message contains a Release Response,
      // indicating that the association has been terminated.
      LOG4CPLUS_WARN(root_logger, sfn << "Received session disconnect header "
        "DN_SPDU_SI. Indicates the immediate termination of the association. "
        "The UserData section is empty.");
      return DicesRcPhilipsIntellivueMP70::ASSOCIATION_DISCONNECT;
      break;
    default:
      LOG4CPLUS_WARN(root_logger, sfn << "Received unknown session abort header ("
                     << static_cast<int>(association_response->sessionHeader.type) << ")");
      break;
  }

  // Locate start of user data
  status = FindAssociationResponseUserDataStart(
    &iuserdataindex,
    buffer,
    numbytes,
    iindex);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }
  if (iuserdataindex < 0)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to locate start of user data");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  iindex = iuserdataindex;

  // ASNLength
  iu8x = buffer[iindex];
  iindex++;

  if (iu8x < 128)
  {
    // ASNLength is one byte and represents actual length value.
    // Show decimal value
    iu32x = static_cast<uint32_t>(iu8x);
  }
  else
  {

    /**
     * ASNLength is > one byte. Bits 0 - 6 indicate the number of bytes
     * appended to encode the actual length.
     * Show values
     */
    ibytecount = (iu8x & 0x7F);
    iu32x = buffer[iindex];
    iindex++;

    for (int ix = 1; ix < ibytecount; ix++)
    {
      iu8x = buffer[iindex];
      iindex++;
      iu32x = (iu32x << 8);
      iu32x += static_cast<uint32_t>(iu8x);
    }
  }

  // Check ANSLength
  if ((numbytes - iindex) < iu32x)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Corrupt association response. ASNLength ("
                    << iu32x << ") is greater than the number of bytes left "
                                "in message (" << (numbytes - iindex)  << ").");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  const int kfirst_mdseuserinfostd_bytes = 24;
  if ((numbytes - iindex) < kfirst_mdseuserinfostd_bytes)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Unable to parse the first "
                    << kfirst_mdseuserinfostd_bytes
                    << " bytes of MDSEUserInfoStd from the number of bytes "
                       "left in message (" << (numbytes - iindex) << ")");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // ProtocolVersion
  association_response->msdseUserInfo.protocol_version = ntohl(
    *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // NomenclatureVersion
  association_response->msdseUserInfo.nomenclature_version = ntohl(
    *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // FunctionalUnits
  association_response->msdseUserInfo.functional_units = ntohl(
    *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // SystemType
  association_response->msdseUserInfo.system_type = ntohl(
    *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // StartupMode
  association_response->msdseUserInfo.startup_mode = ntohl(
    *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // AttributeList (option_list)
  association_response->msdseUserInfo.option_list.count = ntohs(
    *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  association_response->msdseUserInfo.option_list.length = ntohs(
    *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex)
    < association_response->msdseUserInfo.option_list.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt association response. "
      "AttributeList option_list length is greater than the number of bytes "
      "in message");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  association_response->msdseUserInfo.option_list.value =
    new (std::nothrow) intellivue::AVAType[
    association_response->msdseUserInfo.option_list.count]();
  if (!association_response->msdseUserInfo.option_list.value)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
      "option_list attribute list");
    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
  }

  for (
    int ix = 0;
    ix < association_response->msdseUserInfo.option_list.count;
    ix++)
  {
    const int ksizeof_attr_id_and_len = 4;
    if ((numbytes - iindex) < ksizeof_attr_id_and_len)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
                      << "Unable to parse option_list AVAType attribute_id and "
                         "length bytes (" << ksizeof_attr_id_and_len
                      << ") from the number of bytes left in message ("
                      << (numbytes - iindex) << ").");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    association_response->msdseUserInfo.option_list.value[ix].attribute_id =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    association_response->msdseUserInfo.option_list.value[ix].length =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    if ((numbytes - iindex)
      < association_response->msdseUserInfo.option_list.value[ix].length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt association response. "
        "option_list attribute length is greater than the number of bytes "
        "in message");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    iindex += association_response->msdseUserInfo.option_list.value[ix].length;
  }

  const int ksizeof_count_and_len = 4;
  if ((numbytes - iindex) < ksizeof_count_and_len)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Unable to parse supported_aprofiles count and length "
                       "bytes (" << ksizeof_count_and_len
                    << ") from the number of bytes left in message ("
                    << (numbytes - iindex) << ")");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // AttributeList (supported_aprofiles)
  association_response->msdseUserInfo.supported_aprofiles.count =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  association_response->msdseUserInfo.supported_aprofiles.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex)
    < association_response->msdseUserInfo.supported_aprofiles.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt association response. "
      "AttributeList supported_aprofiles length is greater than the number "
      "of bytes in message");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  association_response->msdseUserInfo.supported_aprofiles.value =
    new (std::nothrow) intellivue::AVAType[
    association_response->msdseUserInfo.supported_aprofiles.count]();
  if (!association_response->msdseUserInfo.supported_aprofiles.value)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
      "supported_aprofiles attribute list");
    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
  }

  for (
    int ix = 0;
    ix < association_response->msdseUserInfo.supported_aprofiles.count;
    ix++)
  {
    const int ksizeof_attr_id_and_len = 4;
    if ((numbytes - iindex) < ksizeof_attr_id_and_len)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
                      << "Unable to parse supported_aprofiles AVAType "
                         "attribute_id and length bytes ("
                      << ksizeof_attr_id_and_len << ") from the number "
                         "of bytes left in message (" << (numbytes - iindex)
                      << ")");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    association_response->msdseUserInfo.supported_aprofiles.value[ix].
      attribute_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    association_response->msdseUserInfo.supported_aprofiles.value[ix].
      length = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    if ((numbytes - iindex)
      < association_response->msdseUserInfo.supported_aprofiles.value[ix].
      length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt association response. "
        "supported_aprofiles attribute length is greater than the number of "
        "bytes in message");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    bool is_valid = false;
    status = IntellivueUtils::IsValidAssociationResponseAttribute(
      association_response->msdseUserInfo.supported_aprofiles.value[ix].
      attribute_id,
      &is_valid);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
    if (is_valid)
    {
      status = IntellivueUtils::ParseAttribute(
        &association_response->msdseUserInfo.supported_aprofiles.value[ix],
        buffer,
        iindex);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return status;
      }
    }

    iindex += association_response->msdseUserInfo.supported_aprofiles.value[ix].
      length;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueAssociationResponse::
DeleteAssociationResponse(
  AssociationResponse* association_response)
{
  static const char* sfn = "IntellivueAssociationResponse::"
    "DeleteAssociationResponse() ";
  if (!association_response)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "association_response is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  delete [] association_response->sessionHeader.length;
  association_response->sessionHeader.length = nullptr;

  for (
    int ix = 0;
    ix < association_response->msdseUserInfo.option_list.count;
    ix++)
  {
    if (!association_response->msdseUserInfo.option_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "AttributeList (option_list) "
        "AVAType list is a null pointer.");
      break;
    }
    DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::DeleteAttribute(
      &association_response->msdseUserInfo.option_list.value[ix]);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  delete [] association_response->msdseUserInfo.option_list.value;
  association_response->msdseUserInfo.option_list.value = nullptr;

  for (
    int ix = 0;
    ix < association_response->msdseUserInfo.supported_aprofiles.count;
    ix++)
  {
    if (!association_response->msdseUserInfo.supported_aprofiles.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "AttributeList (supported_aprofiles) "
        "AVAType list is a null pointer.");
      break;
    }
    DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::DeleteAttribute(
      &association_response->msdseUserInfo.supported_aprofiles.value[ix]);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  delete [] association_response->msdseUserInfo.supported_aprofiles.value;
  association_response->msdseUserInfo.supported_aprofiles.value = nullptr;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueAssociationResponse::
FindAssociationResponseUserDataStart(
  int* iuserdataindex,
  uint8_t* buffer,
  int numbytes,
  int iindex)
{
  static const char* sfn = "IntellivueAssociationResponse::"
    "FindAssociationResponseUserDataStart() ";

  if (!iuserdataindex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "iuserdataindex is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "buffer is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  int ix = 0;
  *iuserdataindex = -1;
  uint32_t user_data_start1[] = { 0xBE, 0x80, 0x28, 0x80, 0x81 };
  uint32_t user_data_start2[] = { 0xBE, 0x80, 0x28, 0x80, 0x02, 0x01,
    0x02, 0x81 };

  int lstart1 = sizeof(user_data_start1) / sizeof(user_data_start1[0]);
  int lstart2 = sizeof(user_data_start2) / sizeof(user_data_start2[0]);

  // Locate start of user data
  while ((iindex < numbytes) && (ix < (lstart1 - 1)))
  {
    if (buffer[iindex] != user_data_start1[ix]) ix = 0;
    else ix++;

    iindex++;
  }

  if ((ix > 0) && (iindex < numbytes))
  {
    if (buffer[iindex] == user_data_start1[ix])
    { // Located start of data
      *iuserdataindex = iindex + 1;
    }
    else
    {
      while ((iindex < numbytes) && (ix < lstart2))
      {
        if (buffer[iindex] != user_data_start2[ix])
        {
          ix = 0;
          break;
        }
        else
        {
          ix++;
        }
        iindex++;
      }

      // Determine if start of data has been located
      if (ix > 0) *iuserdataindex = iindex;
    }
  }

  if (*iuserdataindex >= numbytes)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "User data index ("
                    << *iuserdataindex << ") is out of bounds of buffer ("
                    << numbytes << ")");
    *iuserdataindex = -1; // Set back to -1 for failure.
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}
