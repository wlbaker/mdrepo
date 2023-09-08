/**
 * @file intellivue_connect_indication_message.h
 *
 * @brief Declares a class which parses connect indication message from
 * intellivue.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_CONNECT_INDICATION_MESSAGE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_CONNECT_INDICATION_MESSAGE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

namespace ice
{
class MDS;
};

class IntellivueConnectIndicationMessage
{
 public:
  IntellivueConnectIndicationMessage();
  virtual ~IntellivueConnectIndicationMessage();

  static DicesRcPhilipsIntellivueMP70 IsConnectIndicationMessage(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseConnectIndicationMessage(
    ConnectIndication* connect_indication,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 DeleteConnectIndicationMessage(
    ConnectIndication* connect_indication);

  static DicesRcPhilipsIntellivueMP70 SetMDSWithConnectIndicationMessage(
    std::pair<DicesRcDriver, ice::MDS*>* instance_pair,
    const ConnectIndication& connect_indication);

  static DicesRcPhilipsIntellivueMP70 GetIPAddressString(
    std::string* ip_address,
    const ConnectIndication& connect_indication);

  static DicesRcPhilipsIntellivueMP70 GetDataExportProtocolPortNumber(
    int* port_number,
    const ConnectIndication& connect_indication);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueConnectIndicationMessage(const IntellivueConnectIndicationMessage& src);
  IntellivueConnectIndicationMessage &operator=(const IntellivueConnectIndicationMessage& rhs);
};

#endif
