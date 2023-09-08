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

static int init_receiver(char *s_if, char *s_mcast) {
	int ret;
	int fd;

	struct in_addr my_if_addr;
	struct in_addr my_mcast_addr;

	printf("SOCK IF: %s\n", s_if );
	printf("SOCK MCAST: %s\n", s_mcast );

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
	if( s_if != NULL ) {
		bind_addr.sin_addr.s_addr = inet_addr( s_if );
	}

	ret = bind( fd, (const struct sockaddr *)(&bind_addr), sizeof(bind_addr));
	if( ret == -1 ) {
	    perror("socket bind failed");
	    return ret;
	}
	printf("bound successful to: %s\n", s_if );

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
		char s0[128];
		char s1[128];
		char buff[128];
		sprintf(buff, "socket group membersip ffaild for group: %s/%s", 
			inet_ntop( AF_INET, &my_if_addr, s0, 32 ),
			inet_ntop( AF_INET, &my_mcast_addr, s1, 32 )
		       );
		perror(buff);
		return ret;
	}

	int one = 1;
	ret = setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, (const void *)(&one), sizeof(one));
	if( ret == -1 ) {
		perror("socket reuse failed");
		// not fatal
		// return ret;
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
    { "multicastIp", 'm', "IP", 0, "Multicast listening address."},
    { 0 }
};

struct arguments {
    char * deviceIp;
    char * localIp;
    char * portname;
    char * udi;
    char * bcast;
    char * multicastIp;
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
    case 'm': arguments->multicastIp = strdup(arg); break;
    // case 'm': arguments->multicastIp = strdup(arg); break;
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
    	// std::cerr << "ERROR Unknown argument:" << key << std::endl;
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
    params.multicastIp = NULL;

    int rc = argp_parse(&argp, argc, argv, 0, 0, &params );
    if( rc) {
    	fprintf(stderr, "Could not parse arguments.  ERROR=%d\n", rc );
    	return 1;
    }

    if( params.localIp == NULL || params.multicastIp == NULL ) {
	argp_usage(NULL);
    	return 2;
    }

    // int fd = init_receiver("192.168.50.1", "224.0.1.2");
    int fd = init_receiver( params.localIp, params.multicastIp );

    struct timeval timeout={20,0};
    rc = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof( timeout ) );
    if( rc) {
    	perror( "setsockopt timeout" );
    	return 1;
    }

    printf("reading packets\n");
    for( int i = 0; i < 100; i++ ) {
	char buf[4096];
	int rc = recv( fd, buf, sizeof(buf), 0);
    	printf( "PACKET: %d\n", rc );
    }

  return 0;
}
