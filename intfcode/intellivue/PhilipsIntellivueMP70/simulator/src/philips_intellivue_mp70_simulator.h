/**
 * @file philips_intellivue_mp70_simulator.h
 *
 * @brief Declares a class which simulates the philips intellivue mp70. This
 * class listens for commands and sends responses.
 *
 * @author M Szwaja
 */
//=============================================================================

#ifndef PHILIPS_INTELLIVUE_MP70_SIMULATOR_H
#define PHILIPS_INTELLIVUE_MP70_SIMULATOR_H

#include <string>
#include <atomic>
#include <mutex>
#include "intellivue.h"
#include "device_simulator.h"
#include "PhilipsIntellivueMP70SimulatorReturnCodes.h"

class rs_232;
class ThreePinRS232ReadInterface;
class RS232ReadInterface;
class Socket;

class PhilipsIntellivueMP70Simulator : public DeviceSimulator
{
 public:

  enum association_state
  {
    associated = 0,
    unassociated
  };

  enum response_type
  {
    unknown = 0,
    association_response,
    mds_create_event_result,
    mds_result,
    pat_demo_result,
    alarm_result,
    set_rtsa_priority_list,
    numeric_group_static,
    numeric_group_all,
    rtsa_group_static,
    rtsa_group_all
  };

  PhilipsIntellivueMP70Simulator(RS232ReadInterface* interface);
  ~PhilipsIntellivueMP70Simulator();

  /**
   * Runs simulator
   * @param [in] argc Number of arguments in argument vector.
   * @param [in] argv Argument vecotor which contains command line arguments.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 RunSimulator(int argc, char** argv);

 private:
  // Disallow use of implicitly generated member functions:
  PhilipsIntellivueMP70Simulator(const PhilipsIntellivueMP70Simulator& src);
  PhilipsIntellivueMP70Simulator &operator=(const PhilipsIntellivueMP70Simulator& rhs);

  DicesRcPhilipsIntellivueSimulatorMP70 IsSerialOrLanSimulationFile(
    uint8_t* buffer, const ssize_t buffer_length, FILE* fd);

  /**
   * Reads responses from a simulation file, until the requested response is
   * reached. The file pointer is left after the record. This function also
   * writes The responses to the serial port. All linked responses are
   * read together.  
   * @param [in, out] fd File pointer to simulation data file.
   * @param [in] response Type of response that is being searched for in the
   *   simulation file.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 SearchSimulationFileForResponse(
    uint8_t* buffer,
    const ssize_t buffer_length,
    FILE* fd,
    response_type response);

  /**
   * Determines if the response is linked.
   * @param [in] bytes Pointer to byte array containing unsigned characters.
   * @param [in] length Number of elements in bytes array.
   * @param [in, out] torf Pointer to bool
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsLinkedResult(
    uint8_t* bytes,
    ssize_t length,
    bool* torf);

  DicesRcPhilipsIntellivueSimulatorMP70 IsConnectIndicationMessage(
    uint8_t* buffer,
    const ssize_t buffer_length,
    ssize_t length,
    bool* torf);

  /**
   * Determines if buffer contains an association response. The parameter 
   * torf will be set to true if it is an association response.
   * @param [in] bytes Pointer to buffer of bytes which contains response.
   * @param [in] length Number of bytes in buffer.
   * @param [in, out] torf Pointer to bool.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsAssociationResponse(
    uint8_t* bytes,
    ssize_t length,
    bool* torf);

  /**
   * Determines if buffer contains an MDS Create Event Result. The parameter 
   * torf will be set to true if it is an MDS Create Event Result.
   * @param [in] bytes Pointer to buffer of bytes which contains response.
   * @param [in] length Number of bytes in buffer.
   * @param [in, out] torf Pointer to bool.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsMDSCreateEventResult(
    uint8_t* bytes,
    ssize_t length,
    bool* torf);

  /**
   * Determines if buffer contains an Set RTSA priority list result. The
   * parameter torf will be set to true if it is an Set RTSA priority list
   * result. The result must be of a particular response type.
   * @param [in] bytes Pointer to buffer of bytes which contains response.
   * @param [in] length Number of bytes in buffer.
   * @param [in, out] torf Pointer to bool.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsSetRTSAPriorityListResult(
    uint8_t* bytes,
    ssize_t length,
    bool* torf);

  /**
   * Determines if buffer contains an extended poll data result. The
   * parameter torf will be set to true if it is an extended poll data
   * result. The result must be of a particular response type.
   * @param [in] bytes Pointer to buffer of bytes which contains response.
   * @param [in] length Number of bytes in buffer.
   * @param [in, out] torf Pointer to bool.
   * @param [in] response The type of extended poll data result being searched
   *   for.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsSinglePollDataResult(
    uint8_t* bytes,
    ssize_t length,
    bool* torf,
    response_type response);

  /**
   * Determines if buffer contains a single poll data result. The
   * parameter torf will be set to true if it is a single poll data
   * result.
   * @param [in] bytes Pointer to buffer of bytes which contains response.
   * @param [in] length Number of bytes in buffer.
   * @param [in, out] torf Pointer to bool.
   * @param [in] response The type of single poll data result being searched
   *   for.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 IsExtendedPollDataResult(
    uint8_t* bytes,
    ssize_t length,
    bool* torf,
    response_type response);

  /**
   * Writes buffer of bytes to the serial port. This is a thread safe function.
   * @param [in] bytes Pointer to buffer of bytes.
   * @param [in] length Number of bytes in buffer to write to serial port.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 WriteBytes(
    uint8_t* bytes,
    const size_t length);

  /**
   * Sends association response and MDS create event report to the serial port.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 HandleAssociationRequest();

  /**
   * Parses command and sends the appropriate simulation responses to the
   * serial port.
   * @param [in] bytes Pointer to buffer of bytes.
   * @param [in] length Number of bytes in buffer.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 HandleDataExportCommand(
    uint8_t* bytes,
    int length);

  /**
   * Thread function for writing numeric sample data.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ExtendedNumericThreadFunction();

  /**
   * Thread function for writing RTSA sample data.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ExtendedRTSAThreadFunction();

  /**
   * Thread function for writing alarm sample data.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ExtendedAlarmThreadFunction();

  /**
   * Opens simulation data file.
   * @param [in] filename Full path and filename.
   * @param [in, out] pfd Pointer to file pointer. This file pointer is set
   *   upon function return.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 OpenSimulationFile(
    const char* filename,
    FILE** pfd);

  /**
   * Reads simulation file timestamp. The timestamp is the time at which the
   * intellivue data was logged.
   * Precondition: file pointer must be at start of timestamp.
   * @param [in, out] fd File pointer to open simulation data file.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ReadSimulationFileTimestamp(
    FILE* fd);

  /**
   * Reads simulation file data. The data (intellivue response data) follows
   * the timestamp in the log file.
   * Precondition: file pointer must be at start of data.
   * @param [in, out] fd File pointer to open simulation data file.
   * @param [in, out] total_number_of_bytes Pointer to the number of bytes
   *   of data read from simulation data file.
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ReadSimulationFileData(
    uint8_t* buffer,
    const ssize_t buffer_length,
    FILE* fd,
    ssize_t* total_number_of_bytes);

  DicesRcPhilipsIntellivueSimulatorMP70 ReadLanSimulationFileData(
    uint8_t* buffer,
    const ssize_t buffer_length,
    FILE* fd,
    ssize_t* total_number_of_bytes);

  /**
   * Reads record from log file. The record includes both the timestamp and
   * the data recorded at that time. There is one data response per timestamp.
   * Precondition: file pointer must be at start of timestamp.
   * @param [in, out] fd File pointer to simulation data file. 
   * @param [in, out] total_number_of_bytes Number of bytes of data read (not 
   *   including timestamp)
   * @return Returns DicesRcPhilipsIntellivueSimulatorMP70::OK for success.
   */
  DicesRcPhilipsIntellivueSimulatorMP70 ReadSimulationFileRecord(
    uint8_t* buffer,
    const ssize_t buffer_length,
    FILE* fd,
    ssize_t* total_number_of_bytes);

  DicesRcPhilipsIntellivueSimulatorMP70 ReadLanSimulationFileRecord(
    uint8_t* buffer,
    const ssize_t buffer_length,
    FILE* fd,
    ssize_t* total_number_of_bytes);

  /**
   * Converts bytes to terminal in hexadecimal format. Line numbers in hex are
   * added.
   * @param [in] bytes Pointer to buffer of bytes which will be converted.
   * @param [in] length Number of bytes in buffer to convert.
   * @return Returns a string containing the bytes in hexadecimal format.
   */
  std::string convert_data_to_hex_string(uint8_t* bytes, int length);

  DicesRcPhilipsIntellivueSimulatorMP70 RunSerialSimulator();
  DicesRcPhilipsIntellivueSimulatorMP70 RunLanSimulator();
  DicesRcPhilipsIntellivueSimulatorMP70 LookUpIpAddrInfo(
    const std::string& iface_name,
    std::string* ip_addr,
    std::string* bcast_addr);
  DicesRcPhilipsIntellivueSimulatorMP70 ConvertStringIpAddrToIntellivueIPAddress(
    const std::string& ip_addr,
    intellivue::IPAddress* intellivue_ip_addr);
  DicesRcPhilipsIntellivueSimulatorMP70 FindPositionOfAttributeInAttributeList(
    uint8_t* bytes,
    int length,
    intellivue::OIDType attribute_id,
    int* position);

  void BroadcastConnectIndicationMessage();

  Socket* _socket;
  ThreePinRS232ReadInterface* _rs232_read_impl;
  FILE** _simulation_pfds;
  bool _is_lan_simulator;
  std::mutex _write_mutex;
  std::atomic<long long> _numeric_seconds_since_epoch;
  std::atomic<long long> _rtsa_seconds_since_epoch;
  std::atomic<long long> _alarm_seconds_since_epoch;
  std::atomic<bool> _ext_nu_done;
  std::atomic<bool> _ext_rtsa_done;
  std::atomic<bool> _ext_alarm_done;
  std::atomic<int> _simulator_state;
};

#endif

