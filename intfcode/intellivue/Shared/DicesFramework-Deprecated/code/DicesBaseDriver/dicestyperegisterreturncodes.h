#ifndef PARTICIPANT_DIRECTOR_RETURN_CODES_H_
#define PARTICIPANT_DIRECTOR_RETURN_CODES_H_

#include <string>

enum class DICESTypeRegisterRC
{
  OK = 0,
  FAIL = 1,
  BAD_FUNCTION_ARGUMENT,
  FAILED_TO_REGISTER_TYPES,
  FAILED_TO_UNREGISTER_TYPES
};

class DICESTypeRegisterRCStatusMessage
{
 public:

  const static std::string DICESTypeRegisterToString(const DICESTypeRegisterRC error_code)
  {
    std::string error_message;
    switch (error_code)
    {
      case DICESTypeRegisterRC::OK:
        error_message = "Ok";
        break;
      case DICESTypeRegisterRC::FAIL:
        error_message = "Fail";
        break;
      case DICESTypeRegisterRC::BAD_FUNCTION_ARGUMENT:
        error_message = "Failed to use bad function argument. The argument "
          "is a null pointer.";
        break;
      case DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES:
        error_message = "Failed to register dynamic type";
        break;
      case DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES:
        error_message = "Failed to unregister dynamic type";
        break;
      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }
    return error_message;
  }
 private:
  // Disallow use of implicitly generated member functions:
  DICESTypeRegisterRCStatusMessage(const DICESTypeRegisterRCStatusMessage &statusMsg);
  DICESTypeRegisterRCStatusMessage &operator=(const DICESTypeRegisterRCStatusMessage &statusMsg);
};

#endif
