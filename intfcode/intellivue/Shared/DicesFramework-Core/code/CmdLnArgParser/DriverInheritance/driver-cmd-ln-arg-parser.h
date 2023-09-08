/*
 * File:   DriverCmdLnArgParser.h
 * Author: rfries
 *
 * Created on June 11, 2014, 4:03 PM
 */

#ifndef DRIVERCMDLNARGPARSER_H
#define	DRIVERCMDLNARGPARSER_H

#include <string.h>
#include "../cmd-ln-arg-parser.h"

class DriverCmdLnArgParser : public DicesCmdLnArgParser
{
public:
  DriverCmdLnArgParser();
  virtual ~DriverCmdLnArgParser();

  DicesRcCmdLnArgParser GetUdi(std::string* udi);
  DicesRcCmdLnArgParser GetPortName(std::string* port_name);
  DicesRcCmdLnArgParser GetLocalIp(std::string* ip_address);
  DicesRcCmdLnArgParser GetBroadcastAddress(std::string* bcast_address);
  DicesRcCmdLnArgParser GetDeviceIp(std::string* ip_address);
  DicesRcCmdLnArgParser GetDisableSerialIo(bool* disable_serial_io);
  DicesRcCmdLnArgParser GetDisableLanIo(bool* disable_lan_io);
  DicesRcCmdLnArgParser GetIniPath(std::string* ini_path);

  // Disallow use of implicitly generated member functions:
  DriverCmdLnArgParser(const DriverCmdLnArgParser& src) = delete;
  DriverCmdLnArgParser &operator=(const DriverCmdLnArgParser& rhs) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;
};

#endif	/* DRIVERCMDLNARGPARSER_H */

