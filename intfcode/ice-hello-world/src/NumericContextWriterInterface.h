/**
 * @file  NumericContextWriterInterface.h
 * @brief Manage DDS entities for writing the NumericContext type.
 */
//=============================================================================
#ifndef NUMERIC_CONTEXT_WRITER_INTERFACE_H
#define NUMERIC_CONTEXT_WRITER_INTERFACE_H

#include <sstream>
#include <iostream>

namespace ice
{
class NumericContext;
class NumericContextDataWriter;
}

class DDSCommunicator;
template<typename T> class DdsAutoType;

class NumericContextWriterInterface
{
private:
  //  Disallow use of implicitly generated member functions:
  NumericContextWriterInterface(const NumericContextWriterInterface &src);
  NumericContextWriterInterface &operator=(const NumericContextWriterInterface &rhs);

	// Communicator manages basic DDS entities DomainParticipant, Pub, Sub
	DDSCommunicator *_communicator;

	// Data writer
	ice::NumericContextDataWriter *_writer;

public:
  // CREATORS

	NumericContextWriterInterface();
	~NumericContextWriterInterface();

  // MANIPULATORS

	/*
   * Initialize
   * Create Domain Participant, Publisher, Topic and Writer
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
	int Write(DdsAutoType<ice::NumericContext> data);
	int Delete(DdsAutoType<ice::NumericContext> data);

  // ACCESSORS

	DDSCommunicator *get_communicator() { return _communicator; }
	ice::NumericContextDataWriter *get_writer() { return _writer; }

};

#endif
