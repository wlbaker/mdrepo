/*
 * File:   DicesRcCmdLnArgParser.h
 * Author: rfries & Brendan J. Murphy
 *
 * Created on June 9, 2014, 8:57 AM
 */

#ifndef CMDLNARGPARSERRETURNCODES_H
#define	CMDLNARGPARSERRETURNCODES_H

#include <string>

enum class DicesRcCmdLnArgParser
{
  OK = 0,
  FAIL = 1,
  FUNCTION_ARGUMENT_NULL_POINTER,
  NO_UDI_OPTION,
  NO_UDI_ARGUMENT,
  NO_DOMAIN_ID_OPTION,
  NO_DOMAIN_ID_ARGUMENT,
  NO_MODEL_OPTION,
  NO_MODEL_ARGUMENT,
  NO_PORT_NAME_OPTION,
  NO_PORT_NAME_ARGUMENT,
  NO_BAUD_RATE_OPTION,
  NO_BAUD_RATE_ARGUMENT,
  NO_DATA_BITS_OPTION,
  NO_DATA_BITS_ARGUMENT,
  NO_STOP_BITS_OPTION,
  NO_STOP_BITS_ARGUMENT,
  NO_PARITY_OPTION,
  NO_PARITY_ARGUMENT,
  NO_HANDSHAKING_OPTION,
  NO_HANDSHAKING_ARGUMENT,
  NO_SW_FLOW_CONTROL_OPTION,
  NO_HW_FLOW_CONTROL_OPTION,
  NO_DATA_FILE_NAME_OPTION,
  NO_DATA_FILE_NAME_ARGUMENT,
  NO_MODULE_ID_OPTION,
  NO_MODULE_ID_ARGUMENT,
  NO_DISABLE_SERIAL_IO_OPTION,
  NO_DISABLE_LAN_IO_OPTION,
  NO_LOCAL_IP_OPTION,
  NO_LOCAL_IP_ARGUMENT,
  NO_BROADCAST_ADDRESS_OPTION,
  NO_BROADCAST_ADDRESS_ARGUMENT,
  NO_DEVICE_IP_OPTION,
  NO_DEVICE_IP_ARGUMENT,
  NO_INI_OPTION,
  NO_INI_ARGUMENT,
  NO_MAX_TIMEOUT_OPTION,
  NO_MAX_TIMEOUT_ARGUMENT,
  NO_NETWORK_INTERFACE_OPTION,
  NO_NETWORK_INTERFACE_ARGUMENT,
  INT_LIMIT_EXCEEDED,
  LONG_LIMIT_EXCEEDED,
  NO_VALID_CONVERSION
};

class DicesRcCmdLnArgParserStatusMessage
{
public:

  static std::string DicesRcCmdLnArgParserToString(DicesRcCmdLnArgParser rc)
  {
    switch (rc)
    {
      case DicesRcCmdLnArgParser::OK:
        return "OK";
        break;
      case DicesRcCmdLnArgParser::FAIL:
        return "Fail";
        break;
      case DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER:
        return "Function argument is a null pointer.";
        break;
      case DicesRcCmdLnArgParser::NO_UDI_OPTION:
        return "'-udi' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_UDI_ARGUMENT:
        return "The argument for '-udi' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_DOMAIN_ID_OPTION:
        return "'-domainId' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DOMAIN_ID_ARGUMENT:
        return "The argument for '-domainId' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_MODEL_OPTION:
        return "'-model' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_MODEL_ARGUMENT:
        return "The argument for '-model' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_PORT_NAME_OPTION:
        return "'-portname' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_PORT_NAME_ARGUMENT:
        return "The argument for '-portname' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_BAUD_RATE_OPTION:
        return "'-baud' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_BAUD_RATE_ARGUMENT:
        return "The argument for '-baud' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_DATA_BITS_OPTION:
        return "'-databits' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DATA_BITS_ARGUMENT:
        return "The argument for '-databits' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_STOP_BITS_OPTION:
        return "'-stopbits' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_STOP_BITS_ARGUMENT:
        return "The argument for '-stopbits' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_PARITY_OPTION:
        return "'-parity' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_PARITY_ARGUMENT:
        return "The argument for '-parity' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_HANDSHAKING_OPTION:
        return "'-handshaking' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_HANDSHAKING_ARGUMENT:
        return "The argument for '-handshaking' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_SW_FLOW_CONTROL_OPTION:
        return "'-enableSwFlowControl' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_HW_FLOW_CONTROL_OPTION:
        return "'-enableHwFlowControl' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DATA_FILE_NAME_OPTION:
        return "'-datafilename' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DATA_FILE_NAME_ARGUMENT:
        return "The argument for '-datafilename' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_MODULE_ID_OPTION:
        return "'-moduleId' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_MODULE_ID_ARGUMENT:
        return "The argument for '-moduleId' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_DISABLE_SERIAL_IO_OPTION:
        return "'-disableSerialIo' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DISABLE_LAN_IO_OPTION:
        return "'-disableLanIo' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_LOCAL_IP_OPTION:
        return "'-localIp' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_LOCAL_IP_ARGUMENT:
        return "The argument for '-localIp' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_OPTION:
        return "'-bcast' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_ARGUMENT:
        return "The argument for '-bcast' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_DEVICE_IP_OPTION:
        return "'-deviceIp' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_DEVICE_IP_ARGUMENT:
        return "The argument for '-deviceIp' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_INI_OPTION:
        return "'-ini' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_INI_ARGUMENT:
        return "The argument for '-ini' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_MAX_TIMEOUT_OPTION:
        return "'-maxtimeout' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_MAX_TIMEOUT_ARGUMENT:
        return "The argument for '-maxtimeout' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::NO_NETWORK_INTERFACE_OPTION:
        return "'-networkinterface' was never included in the command line options";
        break;
      case DicesRcCmdLnArgParser::NO_NETWORK_INTERFACE_ARGUMENT:
        return "The argument for '-networkinterface' was never stated in the command line";
        break;
      case DicesRcCmdLnArgParser::LONG_LIMIT_EXCEEDED:
        return "The maximum or minimum size of an long was exceeded.";
        break;
      case DicesRcCmdLnArgParser::INT_LIMIT_EXCEEDED:
        return "The maximum or minimum size of an integer was exceeded.";
        break;
      case DicesRcCmdLnArgParser::NO_VALID_CONVERSION:
        return "Unable to convert value.";
        break;
      default:
        return "Generic Command Line Argument Parser Fail";
        break;
    }
  }
};

#endif	/* CMDLNARGPARSERRETURNCODES_H */

