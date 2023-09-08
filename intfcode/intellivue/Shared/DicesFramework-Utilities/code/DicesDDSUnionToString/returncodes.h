/*
 * File:   returncodes.h
 * Author: M Szwaja
 *
 * Return codes for DDS union to string tool
 */

#ifndef DICES_RC_DDS_UNION_TO_STRING_H_
#define	DICES_RC_DDS_UNION_TO_STRING_H_

#include <string>

enum class DicesRcDDSUnionToString
{
  OK = 0,
  FAIL = 1,
};

class DicesRcDDSUnionToStringStatusMessage
{
 public:

  const static std::string DicesRcDDSUnionToStringToString(const DicesRcDDSUnionToString error_code)
  {
    std::string code_message;
    switch (error_code)
    {
      case DicesRcDDSUnionToString::OK:
        code_message = "Ok";
        break;
      case DicesRcDDSUnionToString::FAIL:
        code_message = "Fail";
        break;
      default: // should not be reached
        code_message = "Unknown Status Code: ";
        code_message.append(std::to_string(static_cast<int>(error_code)));
        break;
    }
    return code_message;
  }
 private:
  // Disallow use of implicitly generated member functions:
  DicesRcDDSUnionToStringStatusMessage(const DicesRcDDSUnionToStringStatusMessage &src);
  DicesRcDDSUnionToStringStatusMessage &operator=(const DicesRcDDSUnionToStringStatusMessage &rhs);
};

#endif	// DICES_RC_DDS_UNION_TO_STRING_H_

