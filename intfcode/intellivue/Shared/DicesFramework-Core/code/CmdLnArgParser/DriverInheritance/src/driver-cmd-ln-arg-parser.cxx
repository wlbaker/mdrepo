/*
 * File:   DriverCmdLnArgParser.cxx
 * Author: rfries
 *
 * Created on June 11, 2014, 4:03 PM
 */

#include "../driver-cmd-ln-arg-parser.h"

struct DriverCmdLnArgParser::impl
{
  impl() = default;

  ~impl() = default;

  DicesRcCmdLnArgParser GetUdi(DicesCmdLnArgParser& src, std::string* udi)
  {
    if (!udi)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument udi is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-udi";
    std::map<std::string, std::string> options_map = src.get_options();
    auto udi_opt = options_map.find(soption);
    *udi = "";

    // '-udi' was not a given argument
    if (udi_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_UDI_OPTION;
    }
    else if (udi_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_UDI_ARGUMENT;
    }
    // we got '-udi', return it
    else
    {
      *udi = udi_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "udi being used: " << *udi);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetPortName(
      DicesCmdLnArgParser& src,
      std::string* port_name)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetPortName()";
    if (!port_name)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument port_name is a null "
                                                           "pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-portname";
    std::map<std::string, std::string> options_map = src.get_options();
    auto port_name_opt = options_map.find(soption);
    *port_name = "";

    if (port_name_opt == options_map.end())
    {
      // '-portname' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_PORT_NAME_OPTION;
    }
    else if (port_name_opt->second.empty())
    {
      // '-portname' was has no argument
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_PORT_NAME_ARGUMENT;
    }
    else
    {
      // we got '-portname', return it
      *port_name = port_name_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "portname being used: " << *port_name);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetLocalIp(
      DicesCmdLnArgParser& src,
      std::string* ip_address)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetLocalIp()";
    if (!ip_address)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument ip_address is a null "
                                                           "pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-localIp";
    std::map<std::string, std::string> options_map = src.get_options();
    auto local_ip_opt = options_map.find(soption);
    *ip_address = "";

    if (local_ip_opt == options_map.end())
    {
      // '-localIp' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_LOCAL_IP_OPTION;
    }
    else if (local_ip_opt->second.empty())
    {
      // '-localIp' was has no argument
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_LOCAL_IP_ARGUMENT;
    }
    else
    {
      // we got '-localIp', return it
      *ip_address = local_ip_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), " local ip address being used: " << *ip_address);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetBroadcastAddress(
      DicesCmdLnArgParser& src,
      std::string* bcast_address)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetBroadcastAddress()";
    if (!bcast_address)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument bcast_address is a "
                                                           "null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-bcast";
    std::map<std::string, std::string> options_map = src.get_options();
    auto bcast_opt = options_map.find(soption);
    *bcast_address = "";

    if (bcast_opt == options_map.end())
    {
      // '-bcast' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_OPTION;
    }
    else if (bcast_opt->second.empty())
    {
      // '-bcast' was has no argument
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_ARGUMENT;
    }
    else
    {
      // we got '-bcast', return it
      *bcast_address = bcast_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), " broadcast address being used: " << *bcast_address);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDeviceIp(
      DicesCmdLnArgParser& src,
      std::string* ip_address)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetDeviceIp()";
    if (!ip_address)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument ip_address is a null "
                                                           "pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-deviceIp";
    std::map<std::string, std::string> options_map = src.get_options();
    auto device_ip_opt = options_map.find(soption);
    *ip_address = "";

    if (device_ip_opt == options_map.end())
    {
      // '-deviceIp' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_DEVICE_IP_OPTION;
    }
    else if (device_ip_opt->second.empty())
    {
      // '-deviceIp' was has no argument
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_DEVICE_IP_ARGUMENT;
    }
    else
    {
      // we got '-deviceIp', return it
      *ip_address = device_ip_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), " device ip address being used: " << *ip_address);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDisableSerialIo(
      DicesCmdLnArgParser& src,
      bool* disable_serial_io)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetDisableSerialIo()";
    if (!disable_serial_io)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument disable_serial_io "
                                                           "is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-disableSerialIo";
    std::map<std::string, std::string> options_map = src.get_options();
    auto disable_serial_io_opt = options_map.find(soption);
    *disable_serial_io = false;

    if (disable_serial_io_opt == options_map.end())
    {
      // '-disableSerialIo' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_DISABLE_SERIAL_IO_OPTION;
    }
    else
    {
      // we got '-disableSerialIo', return it
      *disable_serial_io = true;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "Serial I/O disabled");
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDisableLanIo(
      DriverCmdLnArgParser& src,
      bool* disable_lan_io)
  {
    static const char* sfn = "DriverCmdLnArgParser::GetDisableLanIo()";
    if (!disable_lan_io)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), sfn << " function argument disable_lan_io "
                                                           "is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-disableLanIo";
    std::map<std::string, std::string> options_map = src.get_options();
    auto disable_lan_io_opt = options_map.find(soption);
    *disable_lan_io = false;

    if (disable_lan_io_opt == options_map.end())
    {
      // '-disableLanIo' was not a given option
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), sfn << " " << soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_DISABLE_LAN_IO_OPTION;
    }
    else
    {
      // we got '-disableLanIo', return it
      *disable_lan_io = true;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "LAN I/O disabled");
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetIniPath(DriverCmdLnArgParser& src, std::string* ini_path)
  {
    if (!ini_path)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument ini_path is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-ini";
    std::map<std::string, std::string> options_map = src.get_options();
    auto ini_path_opt = options_map.find(soption);
    *ini_path = "";

    // '-ini' was not a given argument
    if (ini_path_opt == options_map.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption
                     << " was not found in command line args.");
      return DicesRcCmdLnArgParser::NO_INI_OPTION;
    }
    else if (ini_path_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args.");
      return DicesRcCmdLnArgParser::NO_INI_ARGUMENT;
    }
    // we got '-ini', return it
    else
    {
      *ini_path = ini_path_opt->second;
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "ini path being used: " << *ini_path);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }
};

DriverCmdLnArgParser::DriverCmdLnArgParser()
  :_pimpl(nullptr)
{
  static const char* sfn = "DriverCmdLnArgParser::DriverCmdLnArgParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}

DriverCmdLnArgParser::~DriverCmdLnArgParser()
{
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetUdi(std::string* udi)
{
  return _pimpl->GetUdi(*this, udi);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetPortName(std::string* port_name)
{
  return _pimpl->GetPortName(*this, port_name);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetLocalIp(std::string* ip_address)
{
  return _pimpl->GetLocalIp(*this, ip_address);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetBroadcastAddress(std::string* bcast_address)
{
  return _pimpl->GetBroadcastAddress(*this, bcast_address);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetDeviceIp(std::string* ip_address)
{
  return _pimpl->GetDeviceIp(*this, ip_address);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetDisableSerialIo(bool* disable_serial_io)
{
  return _pimpl->GetDisableSerialIo(*this, disable_serial_io);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetDisableLanIo(bool* disable_lan_io)
{
  return _pimpl->GetDisableLanIo(*this, disable_lan_io);
}

DicesRcCmdLnArgParser DriverCmdLnArgParser::GetIniPath(std::string* ini_path)
{
  return _pimpl->GetIniPath(*this, ini_path);
}





