// #include <pcap.h>
// #include <net/ethernet.h>
#include <sys/types.h>  // MSG_CONFIRM
#include <sys/socket.h>  // MSG_CONFIRM
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#include "light_pcapng_ext.h"
// #include "light_special.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // memset

//#include "infinityNet.h"

#include <errno.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

#define MAXLINE 1024

int sockfd;
struct sockaddr_in     servaddr;
static char *filter_ip;
static int   filter_port;
static bool  realtime = false;
static bool  pause_flag = false;
static int   pause_count = 0;
static int running = 1;


int pos = 0;
void output_status( char * msg ) {
	printf("%s", msg );
	pos += strlen(msg);
	if( pos >= 80 ) {
		printf("\n");
		pos = 0;
		if( !realtime ) {
			usleep(20000);
		}
	}
}

void packetHandler( /*const light_pcapng packet,*/ void *data, size_t feature_count ) {
		// u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    uint32_t *body = NULL;
    size_t body_size = 0;
    // uint32_t type = LIGHT_UNKNOWN_DATA_BLOCK;
    uint8_t protocol_version;
    uint8_t ip_header_length;
    uint8_t *octets;
    int i;

    // light_get_block_info(packet, LIGHT_INFO_BODY, &body, &body_size);
    // light_get_block_info(packet, LIGHT_INFO_TYPE, &type, NULL);


    /*
  if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
      ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
      inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);
      inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);


      if (ipHeader->ip_p == IPPROTO_UDP) {
        const struct udphdr* udpHeader;
          udpHeader = (struct udphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
          sourcePort = ntohs(udpHeader->source);
          destPort = ntohs(udpHeader->dest);
          data = (u_char*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
          dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));

        printf( "*** packet protocol:%x dest:%d len:%d\n", (int)ipHeader->ip_p, destPort, dataLength );
        if( destPort == 2050 ) {
            infinityNet_parsePacket( data, dataLength );
        } else {
            printf("  Discovery/Announcement packet to port: %d\n", destPort );
        }
      }
  }
  */
}

int postValueToDDS(char *namedValue, int value)
{


}


int prep_server( bool multicast, int port, char *s_if_addr, char *s_mcast_addr )
{

    char buffer[MAXLINE];
    char *hello = "Hello from client";

	 // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if( s_if_addr == NULL ) {
    	servaddr.sin_addr.s_addr = INADDR_ANY;
    } else {
    	servaddr.sin_addr.s_addr = inet_addr(s_if_addr);  // INADDR_ANY;
    }

    if(!multicast ) {
	    return 0;
    }
    int ret;

    struct sockaddr_in bind_addr = {
	    .sin_family = AF_INET,
	    .sin_port = 0,
	    .sin_addr = {
		.s_addr = INADDR_ANY
	    }
    };

    // server bind to interface
    ret = bind( sockfd, (const struct sockaddr *)&bind_addr, sizeof( bind_addr ) );
    if( ret == -1 ) {
	    perror("bind: multicast prep error");
	    exit(EXIT_FAILURE);
    }

    // setsockopt for interface
    if( s_if_addr != NULL ) {
    	struct in_addr if_ip;
	ret = inet_pton( AF_INET, s_if_addr, &if_ip );
	if( ret <= 0 ) {
	    perror("inet_pton: could not understand interface ip4 address");
	    exit(EXIT_FAILURE);
    	}

    	ret = setsockopt( sockfd, IPPROTO_IP, IP_MULTICAST_IF, (const void *)&if_ip, sizeof(if_ip));
    	if( ret == -1 ) {
	    perror("setsockopt: interface selection error");
	    exit(EXIT_FAILURE);
    	}
    }

    // add a multicast group subscription...client only???
    /*
    struct ip_mreq group;
    group.imr_interface.s_addr = inet_addr(s_if_addr);    // 127.0.0.1
    group.imr_multiaddr.s_addr = inet_addr(s_mcast_addr); // 224.0.0.1

    ret = setsockopt( sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)&group, sizeof(group));
    if( ret == -1 ) {
        perror("setsockopt: interface selection error");
        exit(EXIT_FAILURE);
    }
    */

    return 0;
}

static void __handle_udp(uint8_t *packet_data, uint8_t *packet_end)
{
	uint16_t source_port = ntohs(((uint16_t *)packet_data)[0]);
        uint16_t destination_port = ntohs(((uint16_t *)packet_data)[1]);
        // printf("  UDP source: %u, destination: %u\n", source_port, destination_port);

	// udp frag consists of two 16-bit ints, a 16-bit len, and a checksum
	packet_data += 8;

	if( (filter_port == 0) || (filter_port == destination_port) ) {
		destination_port = 9902;	//for testing only

        	// printf("  SEND: %u\n", packet_end - packet_data );
		output_status("#");
    		servaddr.sin_port = htons( destination_port );
    		sendto(sockfd, packet_data, packet_end - packet_data,
        		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		sizeof(servaddr));
	}
}

static void __handle_ipv4(uint8_t *packet_data, uint8_t header_len, uint8_t *packet_end)
{
        uint16_t total_length = ntohs(((uint16_t *)packet_data)[1]);
        uint8_t protocol = packet_data[9];
        int i = 12;
	char src_txt[32];
	char dest_txt[32];

        // printf(" total length = %u, protocol = %u\n", total_length, protocol);

        // printf(" src: ");
        // for (; i < 16; ++i) {
                // printf("%u.", packet_data[i]);
        // }

        sprintf(src_txt, "%u.%u.%u.%u", 
				packet_data[12],
				packet_data[13],
				packet_data[14],
				packet_data[15]
				);

        sprintf(dest_txt, "%u.%u.%u.%u", 
				packet_data[16],
				packet_data[17],
				packet_data[18],
				packet_data[19]
				);
        // printf(" --> dest: ");
        // for (; i < 20; ++i) {
                // printf("%u.", packet_data[i]);
        // }
        // printf("\n");

	if( (filter_ip != NULL) && strcmp( src_txt, filter_ip) != 0 ) {
	    output_status(".");
	    return;
	}
        if (protocol == 17) {
				sprintf(dest_txt, "127.0.0.1");	//overriding for testing
                printf("SRC=%s --> DEST=%s\n", src_txt, dest_txt );
	        output_status("!");

    		// servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    		servaddr.sin_addr.s_addr = inet_addr(dest_txt);
                __handle_udp(packet_data + header_len * 4, packet_end);
        } else {
		char buf[16];
		sprintf(buf,"[P%d]", protocol );
		output_status( buf );
	}
}

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num) 
{ 
    /* Reset handler to catch SIGINT next time. 
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler); 
    printf("\n breaking execution for Ctrl+C\n"); 
    fflush(stdout); 
    running = 0;
} 

int main(int argc, char *argv[]) {

  int port = 9902;
  //port = 2050;  //Default multicast port for Draeger monitors
  char *s_mcast_addr = NULL;
  char *s_if_addr = NULL;

  if( argc < 2 ) {
    fprintf(stdout,"usage: %s [--filter_ip <ip-addr>] [--ifaddr <ip-addr>] [--filter_port <port>] [--realtime] [--multicast <ip-addr>] <cap-file> <...>\n", argv[0] );
    return 0;
  }

  filter_ip = NULL;
  filter_port = 0;

  // printf("input: filtering UDP from ip:%s port:2050\n", filter_ip );
  // printf("outputing UDP packets to localhost:%d\n", port);

  // sleep(5);

  // 1- open ICE
  // 2- grab handle to TOPIC: ice--MDS to insert our device record

  signal( SIGINT, sigintHandler );

  // open capture file for offline processing
  for( int ii = 1; ii < argc; ii++ ) {
	if( strcmp( argv[ii], "--filter_ip" ) == 0 ) {
		//Filters to only send data from the specified ip address
  		filter_ip = argv[++ii];
		continue;
	}

	if( strcmp( argv[ii], "--filter_port" ) == 0 ) {
  		filter_port = atoi( argv[++ii] );
		continue;
	}

	if( strcmp( argv[ii], "--realtime" ) == 0 ) {
		realtime = true;
		continue;
	}

	if( strcmp( argv[ii], "--multicast" ) == 0 ) {
  		s_mcast_addr = atoi( argv[++ii] );
		continue;
	}

	if( strcmp( argv[ii], "--ifaddr" ) == 0 ) {
		s_if_addr = argv[++ii];
		continue;
	}

	if( strcmp( argv[ii], "--pause" ) == 0 ) {
		pause_flag = true;
		continue;
	}

        prep_server( s_mcast_addr != NULL, port, s_if_addr, s_mcast_addr );

	if( argv[ii][0] == '-' ) {
		fprintf(stdout, "UNKNOWN ARGUMENT: %s\n", argv[ii]);
		break;
	}
	// fallthrough: treat as data file

  	char * cap_file = argv[ii];
  	printf("processing file to localhost: %s\n", cap_file );
	if( filter_ip != NULL ) {
  		printf("                   filter ip: %s\n", filter_ip );
	}
	if( filter_port != 0 ) {
  		printf("                 filter port: %d\n", filter_port );
	}
  	light_pcapng_t *descr = light_pcapng_open_read( cap_file, LIGHT_FALSE );
  	// descr = pcap_open_offline(cap_file, errbuf);
  	if (descr == NULL) {
      		fprintf(stdout, "pcap file open failed: %d", errno );
      		return 1;
  	}

	{
		char buf[256];
		sprintf( buf, "! file %s", cap_file );
    		int rc = sendto(sockfd, buf, strlen(buf),
        		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		sizeof(servaddr));
      		fprintf(stdout, "sendto: %d.%d [%s]", rc, errno, buf );
	}

  	int index = 0;
        running = 1;

  	while( running ) {
	  light_packet_header pkt_header;
	  const uint8_t *pkt_data = NULL;
	  uint8_t *pkt_end = NULL;
	  int res = 0;
	  int i;

	  if( pause_flag ) {
		pause_count--;
		while( pause_count <= 0) {
			printf("\n");
			char *count = readline( "command [quit|reset|run|number]: ");
			if( strcmp( count, "reset") == 0 ) {
				printf("RESETTING INPUT FILE\n");
				ii--;
				free(count);
				goto outer;
			} else if( strcmp( count, "quit") == 0 ) {
				ii = argc+1;
				printf("Early Exit\n");
				free(count);
				goto outer;
			} else if( strcmp( count, "run") == 0 ) {
				pause_count = 1;
				pause_flag = false;
			} else {
				pause_count = atoi( count );
			}
			free(count);
		}
	  }

	  res = light_get_next_packet( descr, &pkt_header, &pkt_data );
	  if( !res) break;

	  index++;
	  if( index > 30000000 ) {
		  fprintf(stdout, "PREMATURE BREAK -- too many records!\n");
		  fprintf(stdout, "PREMATURE BREAK -- too many records!\n");
		  break;
          }

	  long long zero;
	  if( pkt_data != NULL) {
		zero = 1000 * (int)pkt_header.timestamp.tv_sec;
		int millis = pkt_header.timestamp.tv_usec / 1000;
		int dt = millis;
		/*
		printf( "packet %d res=%d orig_len=%d, cap_len=%d, data_link=%d, timestamp=%d.%06d, dt=%3.3d",
			index, res, 
			pkt_header.original_length,
			pkt_header.captured_length,
			pkt_header.data_link,
			(int)pkt_header.timestamp.tv_sec,
			(int)pkt_header.timestamp.tv_usec,
		     	dt );
		printf("\n");
		*/

		pkt_end = pkt_data + pkt_header.original_length;

		// struct _light_enhanced_packet_block *epb = (struct _light_enhanced_packet_body *)pkt_data;
		uint8_t *octets = (uint8_t *)pkt_data;

	        // printf("  HWaddr0: "); // Print destination address.
                for (i = 0; i < 6; ++i) {
                  uint8_t byte = *octets++;
                  // printf("%x:", byte);
                }

        	// printf("  HWaddr1: "); // Print host address.
        	for (i = 0; i < 6; ++i) {
                	uint8_t byte = *octets++;
                	// printf("%x:", byte);
        	}
        	// printf("\n");

		uint16_t ethernet_type = ntohs(*(uint16_t*)(octets));
        	octets += 2; // Skip rest of Ethernet header.

        	switch (ethernet_type) {
        	case 0x0800: // Internet Protocol v4
        	case 0x86DD: // Internet Protocol v6
                	break;
        	case 0x8100: // 802.1Q Virtual LAN
                	octets += 4;
                	break;
        	case 0x9100: // 802.1Q DoubleTag
                	octets += 6;
                	break;
        	case 0x0027: // Spanning Tree (STP)
			continue;
        	case 0x0806: // ARP
			continue;
        	default:
                	// printf("  !! Unhandled Ethernet type(len) 0x%X\n", ethernet_type);
			{
				char buf[16];
				sprintf(buf, "?[%X]", ethernet_type);
                		output_status( buf );
			}
                	continue;
        	}

        	uint8_t ip_header_length = (*octets) & 0b1111;
        	uint8_t protocol_version = (*octets >> 4) & 0b1111;

        	if (protocol_version == 4) {
                	__handle_ipv4(octets, ip_header_length, pkt_end);
		} else if (protocol_version == 6) {
			output_status("6");
		} else {
			printf("Protocol version = %u\n", protocol_version );
		}


		// int offset = 604 - 562;
    		// sendto(sockfd, pkt_data + offset, pkt_header.original_length - offset,
        		// MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		// sizeof(servaddr));
	  }
  	}
outer:
  	light_pcapng_close( descr );
  	sleep(1);
  }


  // 4- friendly close
  printf( "processing finished\n" );

    		sendto(sockfd, "!", 1,
        		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		sizeof(servaddr));
  sleep(2);

  return 0;
}

