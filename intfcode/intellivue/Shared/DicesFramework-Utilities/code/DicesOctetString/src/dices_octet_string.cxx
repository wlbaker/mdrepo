#ifndef DICES_OCTET_STRING_H
#define DICES_OCTET_STRING_H

#include "dices_octet_string.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "common.h"

std::string OctetArrayToHexString(ice::OCTET* array, int length)
{
// TODO rengland 30 JUN 2017
// This really should log on null, but I don't know how we want
// to set said log up.  None of our utils log properly.
  if (array == nullptr) return "";

  std::stringstream ss;
  for (int ix = 0; ix < length; ix++)
  {
    // Setting zero fill and two character width to make sure each hex byte is
    // two characters.
    ss << std::hex << std::setfill('0') << std::setw(2)
       << static_cast<int>(array[ix]);
  }
  return ss.str();
}

#endif	/* DICES_OCTET_STRING_H */
