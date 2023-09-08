/*
 * @file main.cxx
 *
 * @brief This file demonstrates how to use DocBox quality of service (QoS) for
 * RTI DDS entities. RTI DDS will load the QoS file set in NDDS_QOS_PROFILES.
 * This file demonstrates the use of the “dices_dim_library” QoS library and
 * the “dices_dim_durable_profile” QoS profile. In DocBox QoS.xml file there
 * are several environment variables, and two of them (DOCBOX_RTPS_HOST_ID and
 * DOCBOX_RTPS_APP_ID) are set by the DicesHostIdAndAppId library in this
 * example with the function call DBXHostAppID::SetHostAndAppID(). Using this
 * DocBox algorithm prevents DDS guid collisions better than RTI DDS out of
 * the box algorithm for DDS guids. A DDS guid collision could result in DDS
 * datareaders not receiving new data from DDS datawriters with identical DDS
 * guids.
 *
 * @author M Szwaja
 */
//=============================================================================
#include <iostream>
#include <chrono>
#include <ndds/ndds_cpp.h>
#include <ndds/ndds_namespace_cpp.h>
#include "numericSupport.h"
#include "Nomenclature/iso_ieee_11073_part_10101_nomenclature_general.h"
#include "Nomenclature/x73_nomenclature_medical_scada.h"
#include "Nomenclature/dimension_util.h"
#include "DicesHostIdAndAppId/host-app-id.h"
#include "DicesHostIdAndAppId/rc-host-app-id.h"

#include "pista.h"
#include "protobuf-c.h"

#include <argp.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

static int inf_measurement_id_to_mdc[] {
	-1,
        MDC_PRESS_BLD_NONINV_SYS, // Sint32 nibp_sys = 1; 
        MDC_PRESS_BLD_NONINV_DIA, // int32 nibp_dia = 2; 
        MDC_PRESS_BLD_NONINV_MEAN, //int32 nibp_mean = 3; 
        MDC_PULS_OXIM_PULS_RATE, //int32 spo2_hr = 4; 
        MDC_PRESS_BLD_VEN_CENT, //int32 cvp_mean = 5; 
        MDC_PRESS_BLD_ART_PULM_WEDGE, //int32 pa_pwp = 6; 
        MDC_PRESS_BLD_ART_PULM_MEAN, //int32 pa_mean = 7; 
        MDC_PRESS_BLD_ART_PULM_SYS, //int32 pa_sys = 8; 
        MDC_PRESS_BLD_ART_PULM_DIA, //int32 pa_dia = 9; 
        MDC_PRESS_BLD_ART_ABP_MEAN, //int32 art_mean = 10; 
        MDC_PRESS_BLD_ART_ABP_SYS, //int32 art_sys = 11; 
        MDC_PRESS_BLD_ART_ABP_DIA, //int32 art_dia = 12; 
        MDC_PRESS_BLD_ART_PULM_WEDGE, //int32 art_pwp = 13; 
        MDC_PRESS_BLD_ART_ABP_SYS, //int32 art_hr = 14; 
        0, //int32 ecg_pp = 15; 
        0, //int32 ecg_arr = 16; 
        0, //int32 ecg_pvc = 17; 
        MDC_ECG_HEART_RATE, //int32 ecg_hr = 18; 
        MDC_PULS_OXIM_SAT_O2, //int32 spo2_sat = 19; 
        MDC_PULS_OXIM_PULS_RATE, //int32 spo2_pr = 20; 
        MDC_BLD_PULS_RATE_INV, //int32 art_pr = 21; 
        MDC_TEMP_CORE, //int32 tbasic_a = 22; 
        MDC_TEMP_SKIN, //int32 tbasic_b = 23; 
        MDC_TEMP_DELTA_BODY, //int32 tbasic_delta = 24; 
        MDC_TEMP_CORE, //int32 temp1_a = 25; 
        MDC_TEMP_SKIN, //int32 temp1_b = 26; 
        MDC_PRESS_GEN_1_SYS, //int32 gp1_sys = 27; 
        MDC_PRESS_GEN_1_DIA, //int32 gp1_dia = 28; 
        MDC_PRESS_GEN_1_MEAN, //int32 gp1_mean = 29; 
        MDC_PRESS_GEN_2_SYS, //int32 gp2_sys = 30; 
        MDC_PRESS_GEN_2_DIA, //int32 gp2_dia = 31; 
        MDC_PRESS_GEN_2_MEAN, //int32 gp2_mean = 32;
};


// This is the only QoS library and Qos Profile that DocBox systems uses.
// They are defined in DocBox QoS.xml file.
static const char* kQosLibrary = "dices_dim_library";
static const char* kQosProfile = "dices_dim_durable_profile";

// Pointers to DDS participant, datawriter, datareader, and instance. These
// pointers are accessed in multiple functions so that's why they are declared
// at the file scope.
static DDS::DomainParticipant* participant = nullptr;
static ice::NumericObservedValueDataWriter* numeric_meas_obs_val_data_writer = nullptr;
static ice::NumericObservedValue::DataReader* numeric_meas_obs_val_reader = nullptr;
static ice::NumericObservedValue* instance = nullptr;

// NOTE: GetTimeOfDayUtc was originally a library function, but it has
// a dependency on our IDL for ice::Timespec, so that's why it's implemented
// here.
static int GetTimeOfDayUtc(ice::Timespec *ts)
{
  // NOTE std::chrono::system_clock is the only clock required to have epoch of
  // the system time as its internal epoch.

  int iret = 1;

  if (!ts)
  {
    std::cerr << "Function argument ts is a null pointer" << std::endl;
    return iret;
  }

  typedef intmax_t Chron_seconds;
  typedef unsigned long Chron_nanoseconds;

  struct Chron_Timespec
  {
    Chron_seconds seconds;
    Chron_nanoseconds nanoseconds;
  };

  if (ts)
  {
    Chron_Timespec cts;
    
    std::chrono::system_clock::time_point tpnow =
        std::chrono::system_clock::now();

    std::chrono::system_clock::duration dura = tpnow.time_since_epoch();
    cts.seconds =
        dura.count() * std::chrono::system_clock::period::num
        / std::chrono::system_clock::period::den;
    cts.nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(dura).count()
        % std::giga::num;
    ts->seconds = static_cast<ice::TIME_T>(cts.seconds);
    ts->nanoseconds = static_cast<ice::INT32>(cts.nanoseconds);
    iret = 0;
  }

  return iret;
}

static int InitDDS( const char *my_ice_udi )
{
  // DocBox has implemented a unique algorithm for setting a DDS GUID. The
  // DDS GUID is broken up into two parts, the rtps_host_id and rtps_app_id.
  // This function sets environment variables, which will then be used to set
  // the DDS GUID in DocBox's Qos.xml file. The environment variables can be
  // found under the <wire_protocol> tag in the QoS.xml file, which sets
  // DDS_WireProtocolQosPolicy. The environment variabaes are
  // DOCBOX_RTPS_HOST_ID and DOCBOX_RTPS_APP_ID.
  const unsigned int kmax_retries = 0;
  const unsigned int kmax_timeout_millis = 1000;
  DicesRcHostAndAppId hostappid_status = DBXHostAppID::SetHostAndAppID(
        kmax_retries,
        kmax_timeout_millis);
  if (hostappid_status != DicesRcHostAndAppId::OK)
  {
    std::cerr << DicesRcHostAndAppIdStatusMessage::
                 DicesRcHostAndAppIdToString(hostappid_status) <<  std::endl;
    return 1;
  }

  // ice::DDS_DOMAIN_ID_MANAGER is defined in common.idl, and it is currently domain id 2.
  participant = DDSTheParticipantFactory->
      create_participant_with_profile(
        ice::DDS_DOMAIN_ID_MANAGER,
        kQosLibrary,
        kQosProfile,
        nullptr,
        DDS_STATUS_MASK_NONE);
  if(!participant)
  {
    std::cerr << "Failed to create participant" << std::endl;
    return 1;
  }

  DDS::Publisher* publisher = participant->create_publisher_with_profile(
        kQosLibrary,
        kQosProfile,
        nullptr,
        DDS_STATUS_MASK_NONE);
  if(!publisher)
  {
    std::cerr << "Failed to create publisher" << std::endl;
    return 1;
  }

  DDS::Subscriber* subscriber = participant->create_subscriber_with_profile(
        kQosLibrary,
        kQosProfile,
        nullptr,
        DDS_STATUS_MASK_NONE);
  if(!subscriber)
  {
    std::cerr << "Failed to create subscriber" << std::endl;
    return 1;
  }

  DDS::ReturnCode_t retcode = ice::NumericObservedValue::TypeSupport::
      register_type(
        participant,
        ice::NumericObservedValue::TypeSupport::get_type_name());
  if (retcode != DDS_RETCODE_OK)
  {
    std::cerr << "Failed to register type, retcode =" << retcode << std::endl;
    return 1;
  }

  DDS::Topic* topic = participant->create_topic(
        ice::NumericMeasObservedValueTopic,
        ice::NumericObservedValue::TypeSupport::get_type_name(),
        DDS_TOPIC_QOS_DEFAULT,
        nullptr,
        DDS_STATUS_MASK_NONE);
  if(!topic)
  {
    std::cerr << "Failed to create DDS Topic for numeric measurement observed "
                 "value" << std::endl;
    return 1;
  }

  DDS::DataWriter* data_writer = publisher->create_datawriter_with_profile(
        topic,
        kQosLibrary,
        kQosProfile,
        nullptr,
        DDS::STATUS_MASK_NONE);
  if(!data_writer)
  {
    std::cerr << "Failed to create DDS data writer" << std::endl;
    return 1;
  }

  numeric_meas_obs_val_data_writer = ice::NumericObservedValueDataWriter::
      narrow(data_writer);
  if(!numeric_meas_obs_val_data_writer)
  {
    std::cerr << "Failed to narrow numeric measurement observed value data "
                 "writer" << std::endl;
    return 1;
  }

  DDS::DataReader* reader = subscriber->create_datareader_with_profile(
        topic,
        kQosLibrary,
        kQosProfile,
        nullptr,
        DDS_STATUS_MASK_ALL);
  if (!reader)
  {
    std::cerr << "Failed to create DDS DataReader with profile" << std::endl;
    return 1;
  }

  numeric_meas_obs_val_reader = ice::NumericObservedValue::DataReader::narrow(
        reader);
  if (!numeric_meas_obs_val_reader)
  {
    std::cerr << "DataReader narrow error" << std::endl;
    return 1;
  }

  instance = ice::NumericObservedValue::TypeSupport::create_data();
  if(!instance)
  {
    std::cerr << "Failed to create numeric observed value instance"
              << std::endl;
    return 1;
  }

  // Populate numeric measurement observed value with static data
  strncpy(instance->ice_id, my_ice_udi, ice::MAX_LEN_ICE_ID);
  // NOTE: this is not a bug, RTI DDS allocates extra character for null
  // terminator.
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = 1;

  // No parent object in this example
  instance->parent_handle = 0;

  // ice::nom_part_metric is an enumerator defined in common.idl.
  // It means metric [supervisory control and data acquisition
  // (SCADA)] partition.
  instance->type.partition = ice::nom_part_metric;

  // MDC_PART_SCADA is a numeric constant defined in header file
  // iso_ieee_11073_part_10101_nomenclature_general.h.
  // It means SCADA (Physio IDs)
  instance->type.code = MDC_PART_SCADA;

  // No context object in this example.
  instance->context_seq_number = 0;

  // ice::nom_part_metric is an enumerator defined in common.idl.
  // It means the metric [supervisory control and data acquisition (SCADA)]
  // partition.
  instance->metric_id_partition = ice::nom_part_metric;

  // Optional fields device_timestamp and device_relative_timestamp are not
  // really relevant in this example. They will be null.

  // MDC_PULS_OXIM_SAT_O2 is a nemeric constant defined in header
  // file x73_nomenclature_medical_scada.h. It means SpO2.
  instance->nu_observed_value.metric_id = MDC_PULS_OXIM_SAT_O2;

  // MDC_DIM_PERCENT is a numeric constant defined in header file
  // dimension_util.h. It means percent (%).
  instance->nu_observed_value.unit_code = MDC_DIM_PERCENT;

  // In the metric.idl ice::MeasurementStatus is a bit mask, that can be
  // set with a combination of ice::MeasurementStatusBits values. In this
  // example, we'll set the bits for demo data, so that this data cannot
  // be mistaken for a live patient SpO2 value.
  instance->nu_observed_value.state = ice::MeasurementStatusBits::demo_data;

  return 0;
}

void handle_pista_long( long *src, int count ) {
    while( count-- > 0 ) {
        long val = *(src++);
        printf( "%lxL ", val );
    }
}

void handle_pista_int( int *src, int count ) {
    while( count-- > 0 ) {
        int val = *(src++);
        printf( "%d, ", val );
    }
}

void handle_pista_float( float *src, int count ) {
    while( count-- > 0 ) {
        float val = *(src++);
        printf( "%f, ", val );
    }
}

void handle_pista_field( const ProtobufCFieldDescriptor *fd, void *payload ) {

    void *base = payload;

        int id = fd->id; // pista_get_field_id( fd );
	int mdc = -1;
	if( id < sizeof( inf_measurement_id_to_mdc) ) {
		mdc = inf_measurement_id_to_mdc[id];
	}

        const char *loc  = pista_get_field_loc( fd );
        const char *code = pista_get_field_loc( fd );
        const char *desc = pista_get_field_loc( fd );
        int offset = pista_get_field_offset( fd );
        int count = pista_get_field_spp( fd );
        int subtyp = pista_get_field_subtyp( fd );

		payload = base + offset;

        // printf("%lx{%d}", (unsigned long)payload, ndesc);
        printf("@%d %s:%s:%s [%d]: ", offset, loc, code, desc, count);
        switch( subtyp ) {
        case LONG_TYP:
            handle_pista_long( (long *)payload, 1 );
            break;
        case INT_TYP:
            handle_pista_int( (int *)payload, 1 );
            break;
        case FLOAT_TYP:
            handle_pista_float( (float *)payload, 1 );
            break;
        case INT_ARR_TYP:
		{
			// we skipped the COUNT field right before payload
			/// int *pi = (int *)payload;
			// int f_n = *(pi++);
			int **ppi = (int **)payload;
            	handle_pista_int( *ppi, count );
		}
            break;
        case FLOAT_ARR_TYP:
		{
			// we skipped the COUNT field right before payload
			// int *pi = (int *)payload;
			// int f_n = *(pi++);
			float **ppf = (float **)payload;
            	handle_pista_float( *ppf, count );
		}
            break;
        case BYTE_ARR_TYP:
            // handle_pista_byte_array( (char **)payload, count );
            // break;
        case STRING_TYP:
            // handle_pista_byte_array( (char **)payload, count );
            // break;
	default:
        	printf("BROKEN TYPE!");
		break;
        }

}

static int handle_drager_packet( const struct pista_data_packet *pkt ) {
    const ProtobufCMessageDescriptor *mdesc = pista_get_message_descriptor( pkt );

    std::cout << "DUMPING PACKET: " << pkt->source_name << " sid: " <<  pkt->stream_id << std::endl;
    int tot = pista_get_field_count( pkt );
    for( int i =0 ; i < tot; i++ ) {
        const ProtobufCFieldDescriptor *fdesc = pista_get_field_descriptor( pkt, i );
        // handle_pista_desc( fdesc, pkt->payload );
        instance->nu_observed_value.value = rand() % 20 + 80;

        // Source timestamp should be set just before the write call.
        if (GetTimeOfDayUtc(&instance->source_timestamp))
        {
          std::cerr << "Failed to set source_timestamp of the instance."
                    << std::endl;
        }

        // Write numeric meas observed value
        DDS::ReturnCode_t retcode = numeric_meas_obs_val_data_writer->write(
              *instance,
              DDS::HANDLE_NIL);
        if (retcode != DDS_RETCODE_OK)
        {
          std::cerr << "Failed to write Numeric Meas Observed Value, retcode = "
                    << retcode << std::endl;
          continue;
        }

        std::cout << "HANDLE_DRAGER_PACKET Wrote Numeric Meas Observed Value instance" << std::endl;
    }
  return 0;
}

static int ShutdownDDS()
{
  int iret = 0;

  DDS::ReturnCode_t retcode = ice::NumericObservedValue::TypeSupport::
      delete_data(instance);
  if (retcode != DDS::RETCODE_OK)
  {
    std::cerr << "Failed to delete instance error, retcode = "
              << retcode << std::endl;
    iret = 1;
  }
  instance = nullptr;

  if (!participant) return iret;

  retcode = participant->delete_contained_entities();
  if (retcode != DDS::RETCODE_OK)
  {
    std::cerr << "Failed to delete contained entities from participant, "
                 "retcode = " << retcode << std::endl;
    iret = 1;
  }
  numeric_meas_obs_val_data_writer = nullptr;
  numeric_meas_obs_val_reader = nullptr;

  retcode = DDSTheParticipantFactory->delete_participant(participant);
  if (retcode != DDS::RETCODE_OK)
  {
    std::cerr << "Failed to delete participant error, retcode = "
              << retcode << std::endl;
    iret = 1;
  }
  participant = nullptr;

  retcode = DDSDomainParticipantFactory::finalize_instance();
  if (retcode != DDS::RETCODE_OK)
  {
    std::cerr << "Failed to finalize instance error, retcode = "
              << retcode << std::endl;
    iret = 1;
  }

  return iret;
}

static int init_receiver(char *s_if, char *s_mcast) {
	int ret;
	int fd;

	struct in_addr my_if_addr;
	struct in_addr my_mcast_addr;

	ret = inet_pton( AF_INET, s_if, &my_if_addr );
	if( ret != 1 ) {
		printf("error in s_if: %s, %d\n", s_if, ret );
		return ret;
	}
	ret = inet_pton( AF_INET, s_mcast, &my_mcast_addr );
	if( ret != 1 ) {
		printf("error in s_mcast: %s, %d\n", s_if, ret );
		return ret;
	}

	// create socket
	fd = socket( AF_INET, SOCK_DGRAM, 0);
	if( fd == -1) {
		perror("socket creation failed");
		return fd;
	}

	// bind to local address
	struct sockaddr_in bind_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(2050),
		.sin_addr = {
			.s_addr = INADDR_ANY
		}
	};

	ret = bind( fd, (const struct sockaddr *)(&bind_addr), sizeof(bind_addr));
	if( ret == -1 ) {
		perror("socket bind failed");
		return ret;
	}

	// set multicast interface on server
	/* 
	struct in_addr if_ip;
	if_ip.s_addr = ...;
	
	ret = setsockopt( fd, IPPROTO_IP, IP_MULTICAST_IF, (const void *)(&if_ip), sizeof(if_ip));
	if( ret == -1 ) {
		return ret;
	}
	*/


	struct ip_mreq group;
	memcpy( &group.imr_interface.s_addr, &my_if_addr, sizeof(my_if_addr) );
	memcpy( &group.imr_multiaddr.s_addr, &my_mcast_addr, sizeof(my_mcast_addr) );

	ret = setsockopt( fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)(&group), sizeof(group));
	if( ret == -1 ) {
		printf("socket group membership failed\n");
		return ret;
	}

	int one = 1;
	ret = setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, (const void *)(&one), sizeof(one));
	if( ret == -1 ) {
		printf("socket reuse failed\n");
		return ret;
	}

	return fd;
}


const char *argp_program_version = "docbox-infinity 0.1";
const char *argp_program_bug_address = "<william.l.baker2.civ@mail.mil>";
static char doc[] = "Drager Infinity network driver for DocBox.";
// static char args_doc[] = NULL;
static struct argp_option options[] = {
    { "udi", 'U', "STRING", 0, "UDI for DocBox"},
    { "portname", 'p', "TTY", 0, "Serial port device to be used by the driver."},
    { "localIp", 'i', "IP", 0, "Local IP address for network communication."},
    { "bcast", 'b', "IP", 0, "Broadcast address for network communication."},
    { "deviceIp", 'd', "IP", 0, "Address that will be assigned to the medical device via the Cube's DHCP server."},
    { 0 }
};

struct arguments {
    char * deviceIp;
    char * localIp;
    char * portname;
    char * udi;
    char * bcast;
    char *args[3];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = (struct arguments *)state->input;
    switch (key) {
    case 'U': arguments->udi = strdup(arg); break;
    case 'p': arguments->portname = strdup(arg); break;
    case 'i': arguments->localIp = strdup(arg); break;
    case 'b': arguments->bcast = strdup(arg); break;
    case 'd': arguments->deviceIp = strdup(arg); break;
    case ARGP_KEY_ARG:
	// Too many arguments
	//if( state->arg_num > 1 ) {
	      //argp_usage(state);
	//}
	//arguments->args[state->arg_num] = arg;
	break;
    case ARGP_KEY_END:
	// Not enough arguments
	//if( state->arg_num < 1 ) {
	      //argp_usage(state);
	//}
	break;
    case ARGP_KEY_NO_ARGS:
    case ARGP_KEY_INIT:
    case ARGP_KEY_SUCCESS:
    case ARGP_KEY_FINI:
    	// std::cerr << "Ignoring argument:" << key << std::endl;
	break;

    default: 
    	std::cerr << "ERROR Unknown argument:" << key << std::endl;
	return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

int main(int argc, char *argv[])
{
   struct arguments params;

    params.deviceIp = NULL;
    params.localIp = NULL;
    params.portname = NULL;
    params.udi = "TEMP UDI";
    params.bcast = NULL;

    int rc = argp_parse(&argp, argc, argv, 0, 0, &params );
    if( rc) {
    	std::cerr << "Could not parse arguments.  ERROR=" << rc << std::endl;
    	return 1;
    }

    int fd = init_receiver("192.168.50.1", "224.0.1.2");

    struct timeval timeout={2,0};
    rc = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof( timeout ) );
    if( rc) {
    	std::cerr << "sock timeout ERROR=" << rc << " on sock: " << fd << std::endl;
    	return 1;
    }

    for( int i = 0; i < 10; i++ ) {
	char buf[4096];
	int rc = recv( fd, buf, sizeof(buf), 0);
    	std::cout << "PACKET: " << rc << std::endl;
    }
    exit(0);
	    

  if (InitDDS(params.udi))
  {
    std::cerr << "Failed to initialize DDS" << std::endl;
    ShutdownDDS();
    return 1;
  }

  // Run loop
  int seq = 0;
  while(true)
  {
    // Simulates some change in the value with random number between 80 and 100
    instance->nu_observed_value.value = rand() % 20 + 80;

    // Source timestamp should be set just before the write call.
    if (GetTimeOfDayUtc(&instance->source_timestamp))
    {
      std::cerr << "Failed to set source_timestamp of the instance."
                << std::endl;
    }

    // Write numeric meas observed value
    DDS::ReturnCode_t retcode = numeric_meas_obs_val_data_writer->write(
          *instance,
          DDS::HANDLE_NIL);
    if (retcode != DDS_RETCODE_OK)
    {
      std::cerr << "Failed to write Numeric Meas Observed Value, retcode = "
                << retcode << std::endl;
      continue;
    }

    // Wait 1 second for it to send. Not reading any samples is ok though.
    sleep(1);
    seq++;
    if( seq < 10 ) {
	    continue;
    }
    seq = 0;

    // Read numeric meas observed value
    ice::NumericObservedValue::Seq data_seq;
    DDS_SampleInfoSeq info_seq;

    retcode = numeric_meas_obs_val_reader->read(
          data_seq,
          info_seq,
          DDS_LENGTH_UNLIMITED,
          DDS_ANY_SAMPLE_STATE,
          DDS_ANY_VIEW_STATE,
          DDS_ALIVE_INSTANCE_STATE);
    if (retcode == DDS_RETCODE_NO_DATA)
    {
      continue;
    }
    else if (retcode != DDS_RETCODE_OK)
    {
      std::cerr << "read error, retcode = " << retcode << std::endl;
      continue;
    }

    for (int ix = 0; ix < data_seq.length(); ++ix)
    {
      if (info_seq[ix].valid_data)
      {
        std::cout << "Read from Topic " << ice::NumericMeasObservedValueTopic << ":" << ix << std::endl;
        // ice::NumericObservedValue::TypeSupport::print_data(&data_seq[ix]);
      }
    }
    retcode = numeric_meas_obs_val_reader->return_loan(data_seq, info_seq);
    if (retcode != DDS_RETCODE_OK)
    {
      std::cerr << "return loan error, retcode = " << retcode << std::endl;
    }
  }

  if (ShutdownDDS())
  {
    std::cerr << "Failed to shutdown DDS" << std::endl;
    return 1;
  }

  return 0;
}
