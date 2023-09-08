/* 
 * File:   dices_rc_driver_status.h
 * Author: Robert England
 *
 * Return codes for Device Driver Status tool
 *
 * Created on June 26, 2014
 * Last Modified on June 26, 2014
 */

#ifndef DICES_RC_DRIVER_STATUS_H_
#define	DICES_RC_DRIVER_STATUS_H_

#include <string>

enum class DicesRcDriverStatus
{
  OK = 0,
  FAIL = 1,
  
  NULL_PUBLISHER_PARAMETER,
  
  DRIVER_STATE_WRITER_LOOKUP_FAILURE,
  DRIVER_STATE_WRITER_NARROW_FAILURE,
  DRIVER_STATE_WRITER_NULL_FAILURE,

  STATE_INSTANCE_CREATE_FAILURE,
  DRIVER_STATUS_UPDATE_FAILURE,
  STATE_INSTANCE_DELETE_FAILURE
};

class DicesRcDriverStatusStatusMessage
{
public:
  const static std::string DicesRcDriverStatusToString(const DicesRcDriverStatus error_code)
  {
    std::string error_message;
    switch(error_code)
    {
      case DicesRcDriverStatus::OK:
        error_message = "Ok";
      break;
      case DicesRcDriverStatus::FAIL:
        error_message = "Fail";
      break;
      
      case DicesRcDriverStatus::NULL_PUBLISHER_PARAMETER:
        error_message = "Null value provided for required parameter publisher";
      break;
      
      case DicesRcDriverStatus::DRIVER_STATE_WRITER_LOOKUP_FAILURE:
        error_message = "Failed to look up base DDS Data Writer for Device Driver State Topic when initializing DDS objects";
      break;
      case DicesRcDriverStatus::DRIVER_STATE_WRITER_NARROW_FAILURE:
        error_message = "Failed to narrow base DDS Data Writer into Device Driver State Data Writer";
      break;
      case DicesRcDriverStatus::DRIVER_STATE_WRITER_NULL_FAILURE:
        error_message = "Device Driver State Topic Writer is a null pointer";
      break;

      case DicesRcDriverStatus::STATE_INSTANCE_CREATE_FAILURE:
        error_message = "Failed to create an empty Device Driver Status instance";
      break;
      case DicesRcDriverStatus::DRIVER_STATUS_UPDATE_FAILURE:
        error_message = "Failed to update Device Driver Status instance";
      break;
      case DicesRcDriverStatus::STATE_INSTANCE_DELETE_FAILURE:
        error_message = "Failed to properly delete Device Driver Status instance";
      break;
      default: // should not be reached
        error_message = "Unknown status code";
      break;
    }
    return error_message;
  }
private:
  // Disallow use of implicitly generated member functions:
  DicesRcDriverStatusStatusMessage(const DicesRcDriverStatusStatusMessage &src);
  DicesRcDriverStatusStatusMessage &operator=(const DicesRcDriverStatusStatusMessage &rhs);
};

#endif	// DICES_RC_DRIVER_STATUS_H_

