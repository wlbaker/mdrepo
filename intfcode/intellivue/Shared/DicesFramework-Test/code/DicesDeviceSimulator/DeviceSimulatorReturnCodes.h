/* 
 * @file DicesRcDeviceSimulator.h
 *
 * @author M Szwaja
 */
//=============================================================================

#ifndef DICES_DEVICE_SIMULATOR_SRC_DEVICE_SIMULATOR_RETURN_CODES_H
#define	DICES_DEVICE_SIMULATOR_SRC_DEVICE_SIMULATOR_RETURN_CODES_H

#include <string>

enum class DicesRcDeviceSimulator
{
  OK = 0,
  FAIL = 1,
  FAILED_NULL_POINTER,
  FAILED_TO_PARSE_CMD_LINE,
  FAILED_TO_OPEN_SERIAL_PORT
};

class DicesRcDeviceSimulatorStatusMessage
{
 public:
  static std::string DicesRcDeviceSimulatorToString(DicesRcDeviceSimulator rc)
  {
    switch (rc)
    {
      case DicesRcDeviceSimulator::OK:
        return "OK";
        break;
      case DicesRcDeviceSimulator::FAIL:
        return "Fail";
        break;
      case DicesRcDeviceSimulator::FAILED_NULL_POINTER:
        return "Failed: Pointer is null";
        break;
      case DicesRcDeviceSimulator::FAILED_TO_PARSE_CMD_LINE:
        return "Failed to parse command line";
        break;
      case DicesRcDeviceSimulator::FAILED_TO_OPEN_SERIAL_PORT:
        return "Failed to open serial port";
        break;
      default:
        return "Generic device simulator fail";
        break;
    }
  }
};

#endif

