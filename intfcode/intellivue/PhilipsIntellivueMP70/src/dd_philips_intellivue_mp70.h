#ifndef PHILIPS_INTELLIVUE_MP70_SRC_DD_PHILIPS_INTELLIVUE_MP70_H_
#define	PHILIPS_INTELLIVUE_MP70_SRC_DD_PHILIPS_INTELLIVUE_MP70_H_

#include <string>

enum class DicesRcPhilipsIntellivueMP70;

class DDPhilipsIntellivueMP70
{
 public:
  friend class DDPhilipsIntellivueMP70UnitTest;

  DDPhilipsIntellivueMP70();
  ~DDPhilipsIntellivueMP70();

  DicesRcPhilipsIntellivueMP70 RunDriver(int argc, char** argv);

 private:
  DDPhilipsIntellivueMP70(const DDPhilipsIntellivueMP70 &src);
  DDPhilipsIntellivueMP70 &operator=(const DDPhilipsIntellivueMP70 &rhs);

  DicesRcPhilipsIntellivueMP70 ParseIniCfgFile(const std::string& file_path);
  DicesRcPhilipsIntellivueMP70 ParseCommandLine(int argc, char** argv);

  std::string _udi;
  std::string _manufacturer;
  std::string _model;
  std::string _software_version;

  std::string _database_name;
  std::string _database_user;
  std::string _database_password;
  std::string _database_host;

  std::string _portname;
  int _baudrate;
  int _databits;
  int _stopbits;
  int _handshaking;
  std::string _parity;
  bool _enable_hardware_flow_control;
  bool _enable_software_flow_control;
  int _connect_indication_receive_port_number;
  int _upd_receive_port_number;
  std::string _local_ip_address;
  std::string _broadcast_address;
  std::string _device_ip_address;
};

#endif
