/**
 * @file DicesRS232ReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the DICES
 * RS232 tool.
 *
 */
//=============================================================================
#ifndef SIMULATOR_SRC_PHILIPS_INTELLIVUE_MP70_SIMULATOR_RETURN_CODES_H_
#define SIMULATOR_SRC_PHILIPS_INTELLIVUE_MP70_SIMULATOR_RETURN_CODES_H_

#include <string>

enum class DicesRcPhilipsIntellivueSimulatorMP70
{
  OK = 0,
  FAIL = 1,
  PARSE_CMD_LINE_FAIL,
  FUNCTION_ARGUMENT_IS_NULL,
  SERIAL_PORT_OPEN_FAIL,
  SERIAL_PORT_WRITE_FAIL,
  CORRUPT_DATA,
  OPEN_FILE_FAIL,
  CLOSE_FILE_FAIL,
  END_OF_FILE,
  FILE_READ_FAIL,
  IS_SERIAL_SIM_DATA_FILE,
  IS_LAN_SIM_DATA_FILE,
  IP_ADDR_INFO_NOT_FOUND,
  IP_ADDR_INFO_FOUND
};

class DicesRcPhilipsIntellivueSimulatorMP70StatusMessage
{
 public:

  const static std::string DicesRcPhilipsIntellivueSimulatorMP70ToString(
    const DicesRcPhilipsIntellivueSimulatorMP70 error_code)
  {
    std::string error_message;
    switch (error_code)
    {
      case DicesRcPhilipsIntellivueSimulatorMP70::OK:
        error_message = "Ok";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::FAIL:
        error_message = "Fail";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::PARSE_CMD_LINE_FAIL:
        error_message = "Failed to parse command line arguments";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::SERIAL_PORT_OPEN_FAIL:
        error_message = "Failed to open serial port";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::SERIAL_PORT_WRITE_FAIL:
        error_message = "Failed to write to serial port";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::CORRUPT_DATA:
        error_message = "Failed to parse data due to corruption";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::FUNCTION_ARGUMENT_IS_NULL:
        error_message = "Function argument is null";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::END_OF_FILE:
        error_message = "End of file reached";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::FILE_READ_FAIL:
        error_message = "Failed to read from file";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::OPEN_FILE_FAIL:
        error_message = "Failed to open file";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::CLOSE_FILE_FAIL:
        error_message = "Failed to close file";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::IS_SERIAL_SIM_DATA_FILE:
        error_message = "Simulation data file contains serial protocol data";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::IS_LAN_SIM_DATA_FILE:
        error_message = "Simulation data file contains lan protocol data";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::IP_ADDR_INFO_NOT_FOUND:
        error_message = "Unable to find network interface ip address information";
        break;
      case DicesRcPhilipsIntellivueSimulatorMP70::IP_ADDR_INFO_FOUND:
        error_message = "found network interface ip address information";
        break;
      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }
    return error_message;
  }
 private:
  // Disallow use of implicitly generated member functions:
  DicesRcPhilipsIntellivueSimulatorMP70StatusMessage(const DicesRcPhilipsIntellivueSimulatorMP70StatusMessage &src);
  DicesRcPhilipsIntellivueSimulatorMP70StatusMessage &operator=(const DicesRcPhilipsIntellivueSimulatorMP70StatusMessage &rhs);
};

#endif
