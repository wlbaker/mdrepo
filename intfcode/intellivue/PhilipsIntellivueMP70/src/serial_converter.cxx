/**
 * @file serial_converter.cxx
 *
 * Constructs a serial request and checks serial responses
 * Philips IntelliVue MP70.
 *
 * Example 1:
 * If a Computer Client wants to send the data:
 * "0x3a 0x71"
 * The CRC for this data would be:
 * "0xd9 0x64"
 * after building the ones-complement and byte-swapping, this results in:
 * "0x9b 0x26"
 * The whole frame would be:
 * "0xc0 0x3a 0x71 0x9b 0x26 0xc1"
 *
 * Example 2:
 * If a Computer Client wants to send the data:
 * "0x3a 0x91"
 * The CRC for this data would be:
 * "0x3e 0x6a"
 * after building the ones-complement and byte-swapping, this results in:
 * "0x95 0xc1"
 * The whole frame would be:
 * "0xc0 0x3a 0x91 0x95 0x7d 0xe1 0xc1"
 * Note that byte "0xc1" in the CRC is a reserved character and must be escape.
 * This results in "0x7d 0xe1".
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

#include "serial_converter.h"
#include <cstring>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "intellivue_utils.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

#define PPPINITFCS 0xffff // Initial FCS value
#define PPPGOODFCS 0xf0b8 // Good final FCS value
#define P 0x8408

static const uint8_t kProtocolId = 0x11;
static const uint8_t kMessageType = 0x01;
static const int kMaxFCSTableSize = 256;
static uint16_t fcstab[kMaxFCSTableSize] = {0};
static bool created_fcs_table = false;
static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

SerialConverter::SerialConverter()
{
  if (!created_fcs_table)
  {
    CreateFCSTable();
    created_fcs_table = true;
  }
}

SerialConverter::~SerialConverter() { }

DicesRcPhilipsIntellivueMP70 SerialConverter::ConstructSerialMsg(
  uint8_t* buf, unsigned int max_size, unsigned int* numbytes)
{
  static const char* sfn = "SerialConverter::ConstructSerialMsg() ";
  if (!buf)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buf is a "
      "null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!numbytes)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument numbytes is a "
      "null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  std::vector<uint8_t> temp;
  int x7D_counter = 0;
  uint8_t length[2] = { 0 };

  try
  {
    // Add contents of byte array to vector
    temp.insert(temp.begin(), buf, buf + *numbytes);
  }
  catch (std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert buffer into vector. "
      << ex.what());
    return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
  }

  /**
   * Add header
   * Protocol id = 0x11
   * Message type = 0x01
   * Length = numbytes (without the 7D bytes inserted)
   */
  uint16_t new_short = htons(static_cast<uint16_t>(*numbytes));
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(&length[0], pnew_short, sizeof(new_short));

  uint8_t header[] = { kProtocolId, kMessageType, length[0], length[1] };

  try
  {
    temp.insert(temp.begin(), header, header + 4);
  }
  catch (std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert header bytes into "
      "vector. " << ex.what());
    return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
  }

  // Increase the number of bytes from the header
  *numbytes += 4;

  // Make a buffer with header
  uint8_t bufwheader[temp.size()]; // variable length cannot be initialized

  for (std::vector<uint8_t>::size_type ix = 0; ix < temp.size(); ix++)
  {
    bufwheader[ix] = temp.at(ix);
  }

  // Send bytes and initial fcs value
  uint16_t fcsval = 0;
  DicesRcPhilipsIntellivueMP70 status = CalculateNewFCS(
    PPPINITFCS,
    &fcsval,
    bufwheader,
    *numbytes);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  // Take ones compliment of value
  fcsval = ~fcsval;

  // Convert result to bytes and add it to byte array.
  uint8_t fcsbytes[2] = { 0 };

  new_short = htons(fcsval);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(&fcsbytes[0], pnew_short, sizeof(new_short));

  uint8_t bufwfcs[*numbytes + 2];

  // Add FCS to array
  for (int x = 0; x < *numbytes; x++) bufwfcs[x] = bufwheader[x];

  // Byte swap. 1 first
  bufwfcs[*numbytes] = fcsbytes[1];
  bufwfcs[*numbytes + 1] = fcsbytes[0];

  *numbytes += 2;

  // Clear vector
  temp.clear();

  // Add contents of byte array to vector
  for (int x = 0; x < *numbytes; x++)
  { // Check for control characters 0xC0, 0xC1, 0x7D
    if ((bufwfcs[x] == 0xC0 || bufwfcs[x] == 0xC1 || bufwfcs[x] == 0x7D)
      && x > 3)
    {
      // Put 0x7D before character and XOR that character with 0x20.
      // Example: 0xC1 XOR 0x20 = 0xE1
      try
      {
        temp.push_back(0x7D);
      }
      catch (std::exception& ex)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert 0x7D character, "
          "before control character, in vector. " << ex.what());
        return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
      }
      try
      {
        temp.push_back((bufwfcs[x] ^ 0x20));
      }
      catch (std::exception& ex)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert character "
          "XOR with 0x20 into vector. " << ex.what());
        return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
      }
      x7D_counter++;
    }
    else
    {
      try
      {
        temp.push_back(bufwfcs[x]);
      }
      catch (std::exception& ex)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert character, "
          "which is not a control character, into vector. " << ex.what());
        return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
      }
    }
  }

  *numbytes += x7D_counter;

  try
  {
    // Add BOF
    temp.insert(temp.begin(), 0xC0);
  }
  catch (std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert beginning of frame "
      "(BOF) into vector. " << ex.what());
    return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
  }

  try
  {
    // Add EOF
    temp.push_back(0xC1);
  }
  catch (std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back end of frame "
      "(EOF) onto vector. " << ex.what());
    return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
  }
  *numbytes += 2;

  if (*numbytes > max_size)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to store new serial message "
      "containing " << *numbytes << "bytes in vector of max size " << max_size
      << " bytes");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  memset(buf, 0, max_size);

  for (std::vector<uint8_t>::size_type ix = 0; ix < temp.size(); ix++)
  {
    try
    {
      buf[ix] = temp.at(ix);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to access element from "
        "vector. " << ex.what());
      return DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE;
    }
  }
  temp.clear();

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 SerialConverter::CalculateNewFCS(
  const uint16_t fcs,
  uint16_t* return_fcs,
  uint8_t* cp,
  unsigned int len)
{
  static const char* sfn = "SerialConverter::CalculateNewFCS() ";

  if (!return_fcs)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument return_fcs is a "
      "null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!cp)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument cp is a null "
      "pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  uint16_t temp_fcs = fcs;

  while (len--)
  {
    temp_fcs = (temp_fcs >> 8) ^ fcstab[(temp_fcs ^ *cp++) & 0xff];
  }

  *return_fcs = temp_fcs;
  return DicesRcPhilipsIntellivueMP70::OK;
}

void SerialConverter::CreateFCSTable()
{
  for (unsigned int b = 0; b < kMaxFCSTableSize; b++)
  {
    unsigned int v = b;

    for (int i = 8; i--;)
      v = v & 1 ? (v >> 1) ^ P : v >> 1;

    fcstab[b] = (v & 0xFFFF);
  }
}

DicesRcPhilipsIntellivueMP70 SerialConverter::UnwrapSerialMsg(
  uint8_t* buf,
  unsigned int* numbytes)
{
  static const char* sfn = "SerialConverter::UnwrapSerialMsg() ";

  if (!buf)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buf is a "
      "null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!numbytes)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument numbytes is a "
      "null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  std::vector<uint8_t> temp;
  uint8_t fcstemp[2] = { 0 };

  // Get rid of 0x7D's and XOR 0x20 to the following byte
  for (int ix = 0; ix < *numbytes; ix++)
  {
    if (buf[ix] == 0x7D)
    {
      if ((ix + 1) < *numbytes)
      {
        try
        {
          temp.push_back(buf[ix + 1] ^ 0x20);
        }
        catch (std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back character, "
            "which is a control character after 0x7D, onto vector. "
            << ex.what());
          return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
        }
        ix++;
      }
    }
    else
    {
      if (ix == 0 && buf[ix] == 0xC0)
      {
        // Don't add BOF to vector
      }
      else if (ix == (*numbytes - 1) && buf[ix] == 0xC1)
      {
        // Don't add EOF to vector
      }
      else
      {
        try
        {
          temp.push_back(buf[ix]);
        }
        catch (std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back character, "
            "which is not a control character, onto vector. " << ex.what());
          return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
        }
      }
    }
  }

  if (temp.size() > 2)
  {
    // Save FCS value
    try
    {
      fcstemp[1] = temp.at(temp.size() - 1);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to access character, "
        "second byte in FCS, in vector. " << ex.what());
      return DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE;
    }
    try
    {
      fcstemp[0] = temp.at(temp.size() - 2);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to access character, "
        "first byte in FCS, in vector. " << ex.what());
      return DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE;
    }

    // Remove the FCS from bytes
    temp.pop_back();
    temp.pop_back();
  }

  for (int ix = 0; ix < temp.size(); ix++)
  {
    try
    {
      buf[ix] = temp.at(ix);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to access character "
        "in vector while copying bytes to array. " << ex.what());
      return DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE;
    }
  }

  // Get the actual FCS value and take ones compliment of value
  uint16_t fcsval = 0;
  DicesRcPhilipsIntellivueMP70 status = CalculateNewFCS(
    PPPINITFCS,
    &fcsval,
    buf,
    temp.size());
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }
  fcsval = ~fcsval;

  // Turn fcsval into bytes
  uint8_t fcsbytes[2] = { 0 };

  uint16_t new_short = htons(fcsval);
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
  memmove(&fcsbytes[0], pnew_short, sizeof(new_short));

  // Check to make sure both FCS's match.
  if (fcsbytes[1] != fcstemp[0] || fcsbytes[0] != fcstemp[1])
  {
    // Bad message
    LOG4CPLUS_WARN(root_logger, sfn << "Incorrect frame check sequence "
      << "values: New FCS byte[0] = " << static_cast<int>(fcsbytes[0])
      << ", byte[1] = " << static_cast<int>(fcsbytes[1]) << std::endl
      << "Original FCS byte[0] = " << static_cast<int>(fcstemp[0])
      << ", byte[1] = " << static_cast<int>(fcstemp[1]) << std::endl);
    return DicesRcPhilipsIntellivueMP70::FRAME_CHECK_SEQUENCE_INCORRECT_FAILURE;
  }

  // Parse header for error checking and save number of bytes
  uint8_t protocol_id = buf[0];
  uint8_t msg_type = buf[1];
  *numbytes = ntohs(*(reinterpret_cast<uint16_t*>(&buf[2])));

  // Check for bad protocol id
  if (protocol_id != kProtocolId)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Found incorrect protocol_id "
      << protocol_id << " in response");
    return DicesRcPhilipsIntellivueMP70::INCORRECT_PROTOCOL_ID_FAILURE;
  }

  // Check for bad message type
  if (msg_type != kMessageType)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Found incorrect msg_type "
      << msg_type << " in response");
    return DicesRcPhilipsIntellivueMP70::INCORRECT_MESSAGE_TYPE_FAILURE;
  }

  // Remove header
  for (int x = 4; x < temp.size(); x++)
  {
    try
    {
      buf[x - 4] = temp.at(x);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to access character "
        "in vector while removing header. " << ex.what());
      return DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE;
    }
  }

  temp.clear();
  return DicesRcPhilipsIntellivueMP70::OK;
}
