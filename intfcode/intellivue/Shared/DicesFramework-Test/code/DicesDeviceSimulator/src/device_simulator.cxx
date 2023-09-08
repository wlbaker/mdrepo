/**
 * @file device_simulator.cxx
 *
 * @brief Defines a base class for device simulators. This class opens serial
 * port and parses command line arguments.
 *
 * @author M Szwaja
 */
//=============================================================================

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "Communication/RS232/rs232.h"
#include "Communication/RS232/rs232-read-interface.h"
#include "device_simulator.h"
#include "Core/CmdLnArgParser/DeviceSimulatorInheritance/simulator-cmd-ln-arg-parser.h"
#include "Communication/rc-base-communication.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

DeviceSimulator::DeviceSimulator(RS232ReadInterface* serial_impl)
  : _baud(9600),
    _databits(8),
    _stopbits(one_stopbit),
    _parity(parity_none),
    _sw_flow_control(true),
    _hw_flow_control(false),
    _rs232(0)
{
  _rs232 = new (std::nothrow) RS232(serial_impl);
}

DeviceSimulator::~DeviceSimulator()
{
  delete _rs232;
}

DicesRcDeviceSimulator DeviceSimulator::OpenRS232Port()
{
  static const char* sfn = "DeviceSimulator::OpenRS232Port()";

  if (!_rs232)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " _rs232 is a null pointer.");
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;
  }

  // Set port settings
  _rs232->set_portname(_portname);
  _rs232->set_baudrate(_baud);
  _rs232->set_databits(_databits);
  _rs232->set_stopbits(_stopbits);
  _rs232->set_handshaking(_handshaking);
  _rs232->set_parity(_parity);
  _rs232->set_enable_hardware_flow_control(_hw_flow_control);
  _rs232->set_enable_software_flow_control(_sw_flow_control);

  // Open port
  DicesRcBaseComm rs232_status = _rs232->Open();
  if (rs232_status != DicesRcBaseComm::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Unable to open serial port "
      << _portname << ". " << DicesRcBaseCommStatusMessage::
      DicesRcBaseCommToString(rs232_status));
    return DicesRcDeviceSimulator::FAILED_TO_OPEN_SERIAL_PORT;
  }

  return DicesRcDeviceSimulator::OK;
}

DicesRcDeviceSimulator DeviceSimulator::ParseCommandLine(int argc, char** argv)
{
  static const char* sfn = "DeviceSimulator::ParseCommandLine()";
  SimulatorCmdLnArgParser parser;
  DicesRcCmdLnArgParser status = DicesRcCmdLnArgParser::OK;

  status = parser.Parse(argc, argv);
  if (status != DicesRcCmdLnArgParser::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Unable to parse command line "
      "arguments.");
    return DicesRcDeviceSimulator::FAILED_TO_PARSE_CMD_LINE;
  }

  status = parser.GetModel(&_model);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetPortName(&_portname);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetBaudrate(&_baud);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetDataBits(&_databits);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetStopBits(&_stopbits);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetParity(&_parity);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetHandShaking(&_handshaking);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetSwFlowControl(&_sw_flow_control);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;
  
  status = parser.GetHwFlowControl(&_hw_flow_control);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetDataFileName(&_data_file_name);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  status = parser.GetNetworkInterface(&_network_interface);
  if (status == DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER)
    return DicesRcDeviceSimulator::FAILED_NULL_POINTER;

  return DicesRcDeviceSimulator::OK;
}

