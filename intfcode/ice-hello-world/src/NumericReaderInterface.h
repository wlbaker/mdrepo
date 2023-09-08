/**
 * @file  NumericReaderInterface.h
 * @brief Manage DDS entities for reading the NumericObservedValue type.
 */
//=============================================================================
#ifndef NUMERIC_READER_INTERFACE_H
#define NUMERIC_READER_INTERFACE_H

#include <sstream>
#include <iostream>

namespace ice
{
class NumericObservedValue;
class NumericObservedValueDataReader;
}

class DDSWaitSet;
class DDSStatusCondition;
class DDSCommunicator;
class DDSReadCondition;

class NumericReaderInterface 
{
private:
  //  Disallow use of implicitly generated member functions:
  NumericReaderInterface(const NumericReaderInterface &src);
  NumericReaderInterface &operator=(const NumericReaderInterface &rhs);

	// Communicator manages basic DDS entities DomainParticipant, Pub, Sub
	DDSCommunicator *_communicator;

	// Data reader
	ice::NumericObservedValueDataReader *_reader;

	// Objects to block a thread until sample data arrive
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
  DDSReadCondition *_instance_alive;
  DDSReadCondition *_instance_disposed;
  DDSReadCondition *_instance_no_writers;

public:
  // CREATORS

	NumericReaderInterface();
	~NumericReaderInterface();

  // MANIPULATORS

	/*
   * Initialize
   * Create Domain Participant, Subscriber, Topic and Reader
   *
   * Parameters:
   *  domain_id [in] DDS domain ID.
   *  topicname [in] DDS topic name.
   *  qoslibraryname [in] Library name containing the XML QoS profile.
   *      If qoslibraryname is null RTI Data Distribution Service will use the
   *      default library (see DDSSubscriber::set_default_library).
   *  qosprofileame [in] XML QoS Profile name.
   *      If qosprofilename is null RTI Data Distribution Service will use the
   *      default profile (see DDSSubscriber::set_default_profile).
   */
  int Initialize(
    const long domain_id,
    const char *topicname,
    const char *qoslibraryname,
    const char *qosprofilename);

  int Destroy();

  // Receive and handle sample data.
  // Use DDS Waitset to continuously wait (block) for sample data.
  // Write them to the console when they arrive.
  void WaitForData();

  // ACCESSORS

	DDSCommunicator *get_communicator() const { return _communicator; }
  ice::NumericObservedValueDataReader *get_reader() const { return _reader; }

  // One-shot get data, block only for timeout duration
  bool GetData(
    const DDS_Duration_t &timeout,
    ice::NumericObservedValue *data_sample);

};

#endif
