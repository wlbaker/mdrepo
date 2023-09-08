/**
 * @file test.cxx
 *
 * @brief Tool for consistently casting primitive values.
 *
 * @author Robert England
 */

#include <cstdint>

// Casts a signed 16-bit integer field from two 8-bit unsigned ints.
int16_t CastInt16(uint8_t msb, uint8_t lsb)
{
  bool msb_sign = msb >= 0x80;
  bool lsb_sign = lsb >= 0x80;
  uint8_t msb_val = msb;
  uint8_t lsb_val = lsb;
  if (msb_sign) msb_val -= 0x80;
  if (lsb_sign) lsb_val -= 0x80;
  int16_t retval = static_cast<int16_t>(msb_val) * 256 + static_cast<int16_t>(lsb_val);
  if (lsb_sign) retval += 0x80;
  if (msb_sign) retval -= 0x8000;
  return retval;
}

uint8_t CastInt16ToUint8MSB(int16_t value)
{
  bool sign = value < 0;
  int16_t val = value;
  if (sign) val += 0x8000;
  uint16_t uval = static_cast<uint16_t>(val);
  if (sign) uval += 0x8000;
  uint16_t msb = uval / 256;
  return static_cast<uint8_t>(msb);
}

uint8_t CastInt16ToUint8LSB(int16_t value)
{
  bool sign = value < 0;
  int16_t val = value;
  if (sign) val += 0x8000;
  uint16_t uval = static_cast<uint16_t>(val);
  if (sign) uval += 0x8000;
  uint16_t lsb = uval % 256;
  return static_cast<uint8_t>(lsb);
}