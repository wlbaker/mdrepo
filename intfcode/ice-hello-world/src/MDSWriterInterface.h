/**
 * @file  MDSWriterInterface.h
 * @brief Manage DDS entities for writing the MDS type.
 */
//=============================================================================
#ifndef MDS_WRITER_INTERFACE_H
#define MDS_WRITER_INTERFACE_H

#include <sstream>
#include <iostream>

namespace ice
{
class MDS;
class MDSDataWriter;
}

class DDSCommunicator;
template<typename T> class DdsAutoType;

class MDSWriterInterface
{
private:
  //  Disallow use of implicitly generated member functions:
  MDSWriterInterface(const MDSWriterInterface &src);
  MDSWriterInterface &operator=(const MDSWriterInterface &rhs);

	// Communicator manages basic DDS entities DomainParticipant, Pub, Sub
	DDSCommunicator *_communicator;

	// Data writer
	ice::MDSDataWriter *_writer;

public:
  // CREATORS

	MDSWriterInterface();
	~MDSWriterInterface();

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
	int Write(DdsAutoType<ice::MDS> data);
	int Delete(DdsAutoType<ice::MDS> data);

  // ACCESSORS

	DDSCommunicator *get_communicator() const { return _communicator; }
	ice::MDSDataWriter *get_writer() const { return _writer; }

};

#endif
