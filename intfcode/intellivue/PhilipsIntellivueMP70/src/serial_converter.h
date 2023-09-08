/**
 * @file serial_converter.h
 *
 * Constructs a serial request and checks serial responses
 * Philips IntelliVue MP70.
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
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_SERIAL_CONVERTER_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_SERIAL_CONVERTER_H_

#include <cstdint>
enum class DicesRcPhilipsIntellivueMP70;

class SerialConverter
{
 public:
  friend class SerialConverterUnitTest;

  SerialConverter();
  ~SerialConverter();

  /**
   * Given a buffer of bytes, construct a serial message.
   */
  DicesRcPhilipsIntellivueMP70 ConstructSerialMsg(
    uint8_t* buf,
    unsigned int max_size,
    unsigned int* numbytes);

  /**
   * Remove header, FCS, BOF, EOF, inserted 0x7D's. Uses FCS to check message.
   * Result should be the same as a UDP response.
   */
  static DicesRcPhilipsIntellivueMP70 UnwrapSerialMsg(
    uint8_t* buf,
    unsigned int* numbytes);

 private:
  // Disallow use of implicitly generated member functions:
  SerialConverter(const SerialConverter& src);
  SerialConverter &operator=(const SerialConverter& rhs);

  /**
   * Generate a FCS table for the HDLC FCS.
   * The HDLC polynomial: x**0 + x**5 + x**12 + x**16 (0x8408).
   */
  static void CreateFCSTable();

  /**
   * Calculate a new FCS given the current FCS and the new data.
   */
  static DicesRcPhilipsIntellivueMP70 CalculateNewFCS(
    const uint16_t fcs,
    uint16_t* return_fcs,
    uint8_t* cp,
    unsigned int len);
};

#endif
