/* 
 * @file SimulatorCmdLnArgParser.cxx
 * @author M Szwaja
 *
 */
//=============================================================================

#include "../simulator-cmd-ln-arg-parser.h"
#include <string.h>
#include <limits.h>
#include "common.h"

static const char* kDefaultPortname = "ttyUSB0";
static const int kDefaultBaudrate = 9600;
static const int kDefaultDataBits = 0;
static const rs232_stopbits kDefaultStopBits = one_stopbit;
static const rs232_parity kDefaultParity = parity_none;
static const int kDefaultHandshaking = 0;

struct SimulatorCmdLnArgParser::impl
{
  impl() = default;
  ~impl() = default;

  DicesRcCmdLnArgParser GetModel(
      SimulatorCmdLnArgParser& src,
      std::string* model)
  {
    if (!model)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument model is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-model";
    std::map<std::string, std::string> options_map = src.get_options();
    auto model_opt = options_map.find(soption);
    *model = "";

    // '-model' was not a given argument
    if (model_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args.");
      return DicesRcCmdLnArgParser::NO_MODEL_OPTION;
    }
    else if (model_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_MODEL_ARGUMENT;
    }
    // we got '-model', return it
    else
    {
      *model = model_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "model being used: " << *model);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetPortName(
      SimulatorCmdLnArgParser& src,
      std::string* portName)
  {
    if (!portName)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument portName is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-portname";
    std::map<std::string, std::string> options_map = src.get_options();
    auto portname_opt = options_map.find(soption);
    *portName = kDefaultPortname;

    if (portname_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                     << "args. Using default " << kDefaultPortname);
      return DicesRcCmdLnArgParser::NO_PORT_NAME_OPTION;
    }
    else if (portname_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << kDefaultPortname);
      return DicesRcCmdLnArgParser::NO_PORT_NAME_ARGUMENT;
    }
    else
    {
      *portName = portname_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "port name being used: " << *portName);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetBaudrate(
      SimulatorCmdLnArgParser& src, int* baud)
  {
    if (!baud)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument baud is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-baud";
    std::map<std::string, std::string> options_map = src.get_options();
    auto baud_opt = options_map.find(soption);
    *baud = kDefaultBaudrate;

    // '-baud' was not a given argument
    if (baud_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args. Using default " << kDefaultBaudrate);
      return DicesRcCmdLnArgParser::NO_BAUD_RATE_OPTION;
    }
    else if (baud_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << kDefaultBaudrate);
      return DicesRcCmdLnArgParser::NO_BAUD_RATE_ARGUMENT;
    }
    // we got '-baud', return it
    else
    {
      char* endptr = 0;
      long baud_value = strtol(baud_opt->second.c_str(), &endptr, 10);
      if (baud_value == LONG_MAX || baud_value == LONG_MIN)
      {
        if (errno == ERANGE)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "String value cannot be represented as "
                                                       "long. Using default " << kDefaultBaudrate);
          return DicesRcCmdLnArgParser::LONG_LIMIT_EXCEEDED;
        }
      }

      if (baud_value > INT_MAX || baud_value < INT_MIN)
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unable to cast baud rate from long to "
                                                     "int. The integer limit was exceeded. Using default "
                       << kDefaultBaudrate);
        return DicesRcCmdLnArgParser::INT_LIMIT_EXCEEDED;
      }

      if (!baud_value)
      {
        if (endptr == baud_opt->second.c_str())
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "strtol error: no valid conversion could "
                                                       "be made. Using default " << kDefaultBaudrate);
          return DicesRcCmdLnArgParser::NO_VALID_CONVERSION;
        }
      }

      *baud = static_cast<int>(baud_value);
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "baud being used: " << *baud);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDataBits(
      SimulatorCmdLnArgParser& src,
      int* databits)
  {
    if (!databits)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument databits is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-databits";
    std::map<std::string, std::string> options_map = src.get_options();
    auto databits_opt = options_map.find(soption);
    *databits = kDefaultDataBits;

    // '-databits' was not a given argument
    if (databits_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args. Using default " << kDefaultDataBits);
      return DicesRcCmdLnArgParser::NO_DATA_BITS_OPTION;
    }
    else if (databits_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << kDefaultDataBits);
      return DicesRcCmdLnArgParser::NO_DATA_BITS_ARGUMENT;
    }
    // we got '-databits', return it
    else
    {
      char* endptr = 0;
      long databits_value = strtol(databits_opt->second.c_str(), &endptr, 10);
      if (databits_value == LONG_MAX || databits_value == LONG_MIN)
      {
        if (errno == ERANGE)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "String value cannot be represented as "
                                                       "long. Using default " << kDefaultDataBits);
          return DicesRcCmdLnArgParser::LONG_LIMIT_EXCEEDED;
        }
      }

      if (databits_value > INT_MAX || databits_value < INT_MIN)
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unable to cast databits from long to "
                                                     "int. The integer limit was exceeded. Using default "
                       << kDefaultDataBits);
        return DicesRcCmdLnArgParser::INT_LIMIT_EXCEEDED;
      }

      if (!databits_value)
      {
        if (databits_opt->second.c_str() == endptr)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "strtol error: no valid conversion could "
                                                       "be made. Using default " << kDefaultDataBits);
          return DicesRcCmdLnArgParser::NO_VALID_CONVERSION;
        }
      }

      *databits = static_cast<int>(databits_value);
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "databits being used: " << *databits);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetStopBits(
      SimulatorCmdLnArgParser& src,
      rs232_stopbits* stopbits)
  {
    if (!stopbits)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument stopbits is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-stopbits";
    std::map<std::string, std::string> options_map = src.get_options();
    auto stopbits_opt = options_map.find(soption);
    *stopbits = kDefaultStopBits;

    // '-stopbits' was not a given argument
    if (stopbits_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args. Using default " << kDefaultStopBits << " (one stopbit)");
      return DicesRcCmdLnArgParser::NO_STOP_BITS_OPTION;
    }
    else if (stopbits_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << kDefaultStopBits
                     << " (one stopbit)");
      return DicesRcCmdLnArgParser::NO_STOP_BITS_ARGUMENT;
    }
    // we got '-stopbits', return it
    else
    {
      std::string stopbits_str = stopbits_opt->second;
      if (!strcmp(stopbits_str.c_str(), "1"))
        *stopbits = one_stopbit;
      else if (!strcmp(stopbits_str.c_str(), "1.5"))
        *stopbits = one_point_five_stopbits;
      else if (!strcmp(stopbits_str.c_str(), "2"))
        *stopbits = two_stopbits;
      else
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unknown stopbits string \"" << stopbits_str
                       << "\". Using default " << kDefaultStopBits << " (one stopbit)");
      }

      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "stopbits being used: " << *stopbits);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetParity(
      SimulatorCmdLnArgParser& src,
      rs232_parity* parity)
  {
    if (!parity)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument parity is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-parity";
    const char* snone = "none";
    const char* seven = "even";
    const char* sodd = "odd";
    const char* sspace = "space";
    std::map<std::string, std::string> options_map = src.get_options();
    auto parity_opt = options_map.find(soption);
    *parity = kDefaultParity;

    // '-parity' was not a given argument
    if (parity_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args. Using default parity " << kDefaultParity << " (none)");
      return DicesRcCmdLnArgParser::NO_PARITY_OPTION;
    }
    else if (parity_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default parity "
                     << kDefaultParity << " (none)");
      return DicesRcCmdLnArgParser::NO_PARITY_ARGUMENT;
    }
    // we got '-parity'
    else
    {
      std::string parity_str = parity_opt->second;

      if (!strcasecmp(parity_str.c_str(), snone))
        *parity = parity_none;
      else if (!strcasecmp(parity_str.c_str(), seven))
        *parity = parity_even;
      else if (!strcasecmp(parity_str.c_str(), sodd))
        *parity = parity_odd;
      else if (!strcasecmp(parity_str.c_str(), sspace))
        *parity = parity_space;
      else
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unknown parity \"" << parity_str
                       << "\". Using default parity " << kDefaultParity << " (none).");
      }

      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "parity being used: " << *parity);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetHandShaking(
      SimulatorCmdLnArgParser& src,
      int* handshaking)
  {
    if (!handshaking)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument handshaking is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-handshaking";
    std::map<std::string, std::string> options_map = src.get_options();
    auto handshaking_opt = options_map.find(soption);
    *handshaking = kDefaultHandshaking;

    // '-handshaking' was not a given argument
    if (handshaking_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                                                              "args; Using default " << kDefaultHandshaking);
      return DicesRcCmdLnArgParser::NO_HANDSHAKING_OPTION;
    }
    else if (handshaking_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args; Using default " << kDefaultHandshaking);
      return DicesRcCmdLnArgParser::NO_HANDSHAKING_ARGUMENT;
    }
    // we got '-handshaking', return it
    else
    {
      char* endptr = 0;
      long handshaking_value = strtol(handshaking_opt->second.c_str(), &endptr,
                                      10);
      if (handshaking_value == LONG_MAX || handshaking_value == LONG_MIN)
      {
        if (errno == ERANGE)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "String value cannot be represented as "
                                                       "long. Using default " << kDefaultHandshaking);
          return DicesRcCmdLnArgParser::LONG_LIMIT_EXCEEDED;
        }
      }

      if (handshaking_value > INT_MAX || handshaking_value < INT_MIN)
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unable to cast handshaking from long to "
                                                     "int. The integer limit was exceeded. Using default "
                       << kDefaultHandshaking);
        return DicesRcCmdLnArgParser::INT_LIMIT_EXCEEDED;
      }

      if (!handshaking_value)
      {
        if (handshaking_opt->second.c_str() == endptr)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "strtol error: no valid conversion could "
                                                       "be made. Using default " << kDefaultHandshaking);
          return DicesRcCmdLnArgParser::NO_VALID_CONVERSION;
        }
      }

      *handshaking = static_cast<int>(handshaking_value);
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "handshaking being used: " << *handshaking);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetSwFlowControl(
      SimulatorCmdLnArgParser& src,
      bool* enable_sw_flow_ctrl)
  {
    if (!enable_sw_flow_ctrl)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument enable_sw_flow_ctrl is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-enableSwFlowControl";
    std::map<std::string, std::string> options_map = src.get_options();
    auto flow_ctrl_opt = options_map.find(soption);
    *enable_sw_flow_ctrl = false;

    // '-enableSwFlowControl' was not a given argument
    if (flow_ctrl_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line args."
                     << " SW Flow control is diabled");
      return DicesRcCmdLnArgParser::NO_SW_FLOW_CONTROL_OPTION;
    }
    // we got '-enableSwFlowControl', return true
    else
    {
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "enabled sw flow control");
      *enable_sw_flow_ctrl = true;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetHwFlowControl(
      SimulatorCmdLnArgParser& src,
      bool* enable_hw_flow_ctrl)
  {
    if (!enable_hw_flow_ctrl)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument enable_hw_flow_ctrl is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-enableHwFlowControl";
    std::map<std::string, std::string> options_map = src.get_options();
    auto flow_ctrl_opt = options_map.find(soption);
    *enable_hw_flow_ctrl = false;

    // '-enableHwFlowControl' was not a given argument
    if (flow_ctrl_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line args."
                     << " HW Flow control is disabled");
      return DicesRcCmdLnArgParser::NO_HW_FLOW_CONTROL_OPTION;
    }
    // we got '-enableHwFlowControl', return true
    else
    {
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "enabled hw flow control");
      *enable_hw_flow_ctrl = true;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDataFileName(
      SimulatorCmdLnArgParser& src,
      std::string* filename)
  {
    if (!filename)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument filename is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-datafilename";
    std::map<std::string, std::string> options_map = src.get_options();
    auto filename_opt = options_map.find(soption);
    *filename = "";

    if (filename_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                     << "args. Using default " << "\"\"");
      return DicesRcCmdLnArgParser::NO_DATA_FILE_NAME_OPTION;
    }
    else if (filename_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << "\"\"");
      return DicesRcCmdLnArgParser::NO_DATA_FILE_NAME_ARGUMENT;
    }
    else
    {
      *filename = filename_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "file name being used: " << *filename);
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetNetworkInterface(
      SimulatorCmdLnArgParser& src,
      std::string* network_interface)
  {
    if (!network_interface)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument network_interface is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    const char* soption = "-networkinterface";
    std::map<std::string, std::string> options_map = src.get_options();
    auto network_interface_opt = options_map.find(soption);
    *network_interface = "";

    if (network_interface_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line "
                     << "args. Using default " << "\"\"");
      return DicesRcCmdLnArgParser::NO_NETWORK_INTERFACE_OPTION;
    }
    else if (network_interface_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default " << "\"\"");
      return DicesRcCmdLnArgParser::NO_NETWORK_INTERFACE_ARGUMENT;
    }
    else
    {
      *network_interface = network_interface_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "network interface being used: " << *network_interface);
    }

    return DicesRcCmdLnArgParser::OK;
  }
};

SimulatorCmdLnArgParser::SimulatorCmdLnArgParser()
  :_pimpl(nullptr)
{
  static const char* sfn = "SimulatorCmdLnArgParser::SimulatorCmdLnArgParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}

SimulatorCmdLnArgParser::~SimulatorCmdLnArgParser()
{
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetModel(std::string* model)
{
  return _pimpl->GetModel(*this, model);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetPortName(std::string* portName)
{
  return _pimpl->GetPortName(*this, portName);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetBaudrate(int* baud)
{
  return _pimpl->GetBaudrate(*this, baud);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetDataBits(int* databits)
{
  return _pimpl->GetDataBits(*this, databits);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetStopBits(rs232_stopbits* stopbits)
{
  return _pimpl->GetStopBits(*this, stopbits);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetParity(rs232_parity* parity)
{
  return _pimpl->GetParity(*this, parity);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetHandShaking(int* handshaking)
{
  return _pimpl->GetHandShaking(*this, handshaking);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetSwFlowControl(bool* sw_flow_control)
{
  return _pimpl->GetSwFlowControl(*this, sw_flow_control);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetHwFlowControl(bool* hw_flow_control)
{
  return _pimpl->GetHwFlowControl(*this, hw_flow_control);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetDataFileName(std::string* filename)
{
  return _pimpl->GetDataFileName(*this, filename);
}

DicesRcCmdLnArgParser SimulatorCmdLnArgParser::GetNetworkInterface(std::string* network_interface)
{
  return _pimpl->GetNetworkInterface(*this, network_interface);
}
