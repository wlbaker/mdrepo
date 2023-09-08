#include "dd_philips_intellivue_mp70.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "Core/CmdLnArgParser/DriverInheritance/driver-cmd-ln-arg-parser.h"
#include "dd_philips_intellivue_mp70_parser.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "ini_parser.h"
#include "ini_dim_parser.h"
#include "Communication/rc-base-communication.h"
#include "Communication/RS232/rs232.h"
#include "Communication/RS232/rs232-read-interface-three-pin.h"
#include "Communication/RS232/rc-rs232.h"
#include "Communication/Socket/socket.h"
#include "Communication/Socket/socket-read-interface-impl.h"
#include "driver.h"
#include "dices_rc_driver.h"

static const char* kini_file_path = "dd_philips_intellivue_mp70.ini";
static const char* kini_cfg_general = "cfg_general";
static const char* kini_cfg_database = "cfg_database";
static const char* kini_cfg_serial_comm = "cfg_serial_comm";
static const char* kini_cfg_lan_comm = "cfg_lan_comm";
static const char* kparity_none = "none";
static const char* kparity_even = "even";
static const char* kparity_odd = "odd";
static const char* kparity_space = "space";
static const char* kDefaultParity = "none";
static const int kDefaultBaudRate = 115200;
static const int kDefaultDataBits = 8;
static const int kDefaultStopBits = 0;
static const int kDefaultHandshaking = 0;
static const int kConnectIndicationPort = 24005;
static const int kProtocolUdpPort = 24105;
static const uint8_t kSerialMessageTerminator = 0xC1;
static const timeval kRecvTimeout = {0, 10000};
static const timeval kSendTimeout = {0, 10000};
static const log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

DDPhilipsIntellivueMP70::DDPhilipsIntellivueMP70()
  : _baudrate(kDefaultBaudRate),
  _databits(kDefaultDataBits),
  _stopbits(kDefaultStopBits),
  _handshaking(kDefaultHandshaking),
  _enable_hardware_flow_control(false),
  _enable_software_flow_control(false),
  _connect_indication_receive_port_number(kConnectIndicationPort),
  _upd_receive_port_number(kProtocolUdpPort)
{
}

DDPhilipsIntellivueMP70::~DDPhilipsIntellivueMP70()
{
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70::ParseIniCfgFile(const std::string& file_path)
{
  static const char* sfn = "DDPhilipsIntellivueMP70::ParseIniCfgFile() ";
  DIMParser ini_cfg_parser(file_path);

  DicesRcPhilipsIntellivueMP70 status = ini_cfg_parser.Load(kini_cfg_general);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  status = ini_cfg_parser.Load(kini_cfg_database);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  status = ini_cfg_parser.Load(kini_cfg_serial_comm);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  status = ini_cfg_parser.Load(kini_cfg_lan_comm);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  _manufacturer = ini_cfg_parser.get_manufacturer();
  _model = ini_cfg_parser.get_model();
  _software_version = ini_cfg_parser.get_software_version();

  _database_name = ini_cfg_parser.get_database_name();
  _database_user = ini_cfg_parser.get_database_user();
  _database_password = ini_cfg_parser.get_database_password();
  _database_host = ini_cfg_parser.get_database_host();

  _portname = ini_cfg_parser.get_port_name();
  _baudrate = ini_cfg_parser.get_baud_rate();
  _databits = ini_cfg_parser.get_data_bits();
  _stopbits = ini_cfg_parser.get_stop_bits();
  _handshaking = ini_cfg_parser.get_handshaking();
  _parity = ini_cfg_parser.get_parity();
  _enable_hardware_flow_control = ini_cfg_parser.get_enable_hardware_flow_control();
  _enable_software_flow_control = ini_cfg_parser.get_enable_software_flow_control();

  _connect_indication_receive_port_number = ini_cfg_parser.get_connect_indication_port();
  _upd_receive_port_number = ini_cfg_parser.get_protocol_udp_port();

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70::ParseCommandLine(
  int argc,
  char** argv)
{
  static const char* sfn = "DDPhilipsIntellivueMP70::ParseCommandLine() ";
  if (!argv)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument argv is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  // Parse command line arguments
  DriverCmdLnArgParser clp;
  DicesRcCmdLnArgParser clp_status = clp.Parse(argc, argv);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcCmdLnArgParserStatusMessage::
      DicesRcCmdLnArgParserToString(clp_status));
    return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_FAILURE;
  }

  std::string cmd_line_port_name;
  clp_status = clp.GetPortName(&cmd_line_port_name);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    switch (clp_status)
    {
      case DicesRcCmdLnArgParser::NO_PORT_NAME_OPTION:
      case DicesRcCmdLnArgParser::NO_PORT_NAME_ARGUMENT:
        LOG4CPLUS_WARN(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        clp_status = DicesRcCmdLnArgParser::OK;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_SERIAL_PORT_NAME_FAILURE;
        break;
    }
  }
  else
  {
    _portname = cmd_line_port_name;
  }

  std::string local_ip_address;
  clp_status = clp.GetLocalIp(&local_ip_address);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    switch (clp_status)
    {
      case DicesRcCmdLnArgParser::NO_LOCAL_IP_OPTION:
      case DicesRcCmdLnArgParser::NO_LOCAL_IP_ARGUMENT:
        LOG4CPLUS_WARN(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        clp_status = DicesRcCmdLnArgParser::OK;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_LOCAL_IP_ADDRESS_FAILURE;
        break;
    }
  }
  else
  {
    _local_ip_address = local_ip_address;
  }

  std::string broadcast_address;
  clp_status = clp.GetBroadcastAddress(&broadcast_address);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    switch (clp_status)
    {
      case DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_OPTION:
      case DicesRcCmdLnArgParser::NO_BROADCAST_ADDRESS_ARGUMENT:
        LOG4CPLUS_WARN(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        clp_status = DicesRcCmdLnArgParser::OK;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_BROADCAST_ADDRESS_FAILURE;
        break;
    }
  }
  else
  {
    _broadcast_address = broadcast_address;
  }

  std::string device_ip_address;
  clp_status = clp.GetDeviceIp(&device_ip_address);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    switch (clp_status)
    {
      case DicesRcCmdLnArgParser::NO_DEVICE_IP_OPTION:
      case DicesRcCmdLnArgParser::NO_DEVICE_IP_ARGUMENT:
        LOG4CPLUS_WARN(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        clp_status = DicesRcCmdLnArgParser::OK;
        break;
      default:
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcCmdLnArgParserStatusMessage::
          DicesRcCmdLnArgParserToString(clp_status));
        return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_DEVICE_IP_ADDRESS_FAILURE;
        break;
    }
  }
  else
  {
    _device_ip_address = device_ip_address;
  }

  std::string udi;
  clp_status = clp.GetUdi(&udi);
  if (clp_status != DicesRcCmdLnArgParser::OK)
  {
    // A udi option and argument is required from the manager
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcCmdLnArgParserStatusMessage::
      DicesRcCmdLnArgParserToString(clp_status));
    return DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_UDI_FAILURE;
  }
  else
  {
    _udi = udi;
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70::RunDriver(
  int argc,
  char** argv)
{
  static const char* sfn = "DDPhilipsIntellivueMP70::RunDriver() ";
  DicesRcPhilipsIntellivueMP70 driver_status = ParseIniCfgFile(kini_file_path);
  if (driver_status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(driver_status));
    return driver_status;
  }

  driver_status = ParseCommandLine(argc, argv);
  if (driver_status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(driver_status));
    return driver_status;
  }

  BaseComm* base_comm = nullptr;
  ThreePinRS232ReadInterface _rs232_read_impl;
  RS232 rs232(&_rs232_read_impl);
  SocketReadImplInterface socket_read_impl;
  Socket socket(&socket_read_impl);

  // Serial reader should stop reading when a 0xC1 character is read
  DicesRcrs232 rs232_status = _rs232_read_impl.
    set_terminating_character_sequence(
    &kSerialMessageTerminator,
    sizeof (kSerialMessageTerminator));
  if (rs232_status != DicesRcrs232::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to set terminating sequence "
      << _rs232_read_impl.get_statusmsg(rs232_status));
    return DicesRcPhilipsIntellivueMP70::RS232_SET_TERMINATING_SEQUENCE_FAILURE;
  }

  // TODO Find a good balance for timeouts and disconnection.
  const int kmax_serial_timeout_limit_exceeded = 3;
  _rs232_read_impl.set_max_serial_timeout_limit_exceeded(kmax_serial_timeout_limit_exceeded);

  // Set serial port settings loaded from the ini file.
  rs232.set_portname(_portname);
  rs232.set_baudrate(_baudrate);
  rs232.set_databits(_databits);
  rs232.set_stopbits(static_cast<rs232_stopbits>(_stopbits));
  rs232.set_handshaking(_handshaking);
  rs232.set_enable_hardware_flow_control(_enable_hardware_flow_control);
  rs232.set_enable_software_flow_control(_enable_software_flow_control);

  if (!strcasecmp(_parity.c_str(), kparity_none))
    rs232.set_parity(rs232_parity::parity_none);
  else if (!strcasecmp(_parity.c_str(), kparity_even))
    rs232.set_parity(rs232_parity::parity_even);
  else if (!strcasecmp(_parity.c_str(), kparity_odd))
    rs232.set_parity(rs232_parity::parity_odd);
  else if (!strcasecmp(_parity.c_str(), kparity_space))
    rs232.set_parity(rs232_parity::parity_space);
  else
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Unknown parity (\""
      << _parity << "\") loaded from file " << kini_file_path
      << ". Using default none parity.");
    rs232.set_parity(rs232_parity::parity_none);
  }

  // Set the broadcast address (read from command line arguments)
  // Set port number 24005 (specified in interface programming guide)
  socket.set_ip_address(_broadcast_address);
  socket.set_port_number(_connect_indication_receive_port_number);
  socket.set_enable_bind_socket(true);
  socket_read_impl.set_max_socket_timeout_limit(100);
  socket_read_impl.set_max_socket_timeout_limit_exceeded(65);
  socket.set_enable_blocking_io(true);
  socket.set_recv_timeout(&kRecvTimeout);
  socket.set_send_timeout(&kSendTimeout);

  LOG4CPLUS_INFO(root_logger, sfn << "Opening serial port ("
    << _portname << ")...");


  // Found the following on page 71 of the manual
  // (IntellivueDataExportInterfaceProgrammingGuide_Rel_H.0_2013.pdf)
  // "The largest negotiable MTU is 1364 bytes for the LAN interface and 1000
  // Bytes for the MIB/RS232 interface. The resulting size of the data packets
  // may be larger than the MTU, because the MTU covers only the size of the
  // Command Header and the Command Specific Data."
  //
  // Reducing the maximum sizes of command and response buffers to 5000 should
  // provide plenty of memory space for device protocol buffers. It should
  // also reduce weight of memory operations on unused space like memset.
  static const int kmax_command_length = 5000;
  static const int kmax_response_length = 5000;
  Driver driver;
  DDPhilipsIntellivueMP70Parser parser(
    kmax_command_length,
    kmax_response_length);

  parser.set_database_name(_database_name);
  parser.set_database_user(_database_user);
  parser.set_database_password(_database_password);
  parser.set_database_host(_database_host);

  // Set up serial connection first.
  base_comm = &rs232;
  parser.set_is_serial_driver(true);

  parser.set_ice_id(_udi);

  DicesRcDriver status = driver.InitDDS(&parser);
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return DicesRcPhilipsIntellivueMP70::FAIL;
  }

  status = driver.RunDriver(&parser, base_comm);
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DEVICE_DISCONNECTION)
    {
      LOG4CPLUS_WARN(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      return DicesRcPhilipsIntellivueMP70::BASE_DRIVER_RUN_DRIVER_FAILURE;
    }
  }

  // Attempt to communicate via LAN protocol if serial failed.
  if (status == DicesRcDriver::DEVICE_DISCONNECTION)
  {
    // Set LAN connection first.
    base_comm = &socket;
    parser.set_is_serial_driver(false);

    status = DicesRcDriver::OK;
    for(int ix = 0; ix < 2 && status == DicesRcDriver::OK; ix++)
    {
      status = driver.RunDriver(&parser, base_comm);
      if (status != DicesRcDriver::OK)
      {
        if (status == DicesRcDriver::RECONFIGURE_PORT_SETTINGS)
        {
          LOG4CPLUS_INFO(root_logger, sfn << "intellivue ip address: "
            << parser.get_intellivue_ip_address());
          LOG4CPLUS_INFO(root_logger, sfn << "intellivue data export number: "
            << parser.get_intellivue_data_export_port_number());
          // Set port settings parsed from the connect indication message
          socket.set_ip_address(parser.get_intellivue_ip_address());
          socket.set_port_number(parser.get_intellivue_data_export_port_number());
          socket.set_enable_bind_socket(false);
          socket_read_impl.set_max_socket_timeout_limit_exceeded(10);
          socket_read_impl.ResetCounters();
          status = DicesRcDriver::OK; // Ignore this status
        }
        else
        {
          LOG4CPLUS_ERROR(root_logger, sfn
            << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
          return DicesRcPhilipsIntellivueMP70::BASE_DRIVER_RUN_DRIVER_FAILURE;
        }
      }
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}
