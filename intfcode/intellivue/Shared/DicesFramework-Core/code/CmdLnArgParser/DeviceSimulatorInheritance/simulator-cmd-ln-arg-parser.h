/* 
 * @file SimulatorCmdLnArgParser.h
 * @author M Szwaja
 *
 */
//=============================================================================

#ifndef SIMULATOR_CMD_LN_ARG_PARSER_H
#define	SIMULATOR_CMD_LN_ARG_PARSER_H

#include <string.h>
#include "../cmd-ln-arg-parser.h"
#include <Common/dices-framework-enum.h>

class SimulatorCmdLnArgParser : public DicesCmdLnArgParser
{
public:
  SimulatorCmdLnArgParser();
  virtual ~SimulatorCmdLnArgParser();

  DicesRcCmdLnArgParser GetModel(std::string* model);
  DicesRcCmdLnArgParser GetPortName(std::string* portName);
  DicesRcCmdLnArgParser GetBaudrate(int* baud);
  DicesRcCmdLnArgParser GetDataBits(int* databits);
  DicesRcCmdLnArgParser GetStopBits(rs232_stopbits* stopbits);
  DicesRcCmdLnArgParser GetParity(rs232_parity* parity);
  DicesRcCmdLnArgParser GetHandShaking(int* handshaking);
  DicesRcCmdLnArgParser GetSwFlowControl(bool* sw_flow_control);
  DicesRcCmdLnArgParser GetHwFlowControl(bool* hw_flow_control);
  DicesRcCmdLnArgParser GetDataFileName(std::string* filename);
  DicesRcCmdLnArgParser GetNetworkInterface(std::string* network_interface);

  SimulatorCmdLnArgParser(const SimulatorCmdLnArgParser& orig) = delete;
  SimulatorCmdLnArgParser &operator=(const SimulatorCmdLnArgParser& orig) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

};

#endif

