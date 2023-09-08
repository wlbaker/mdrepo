// #include <pcap.h>
// #include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include "light_pcapng_ext.h"
// #include "light_special.h"

#include <arpa/inet.h>
#include <sys/types.h>  // MSG_CONFIRM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // memset

//#include "infinityNet.h"

#include <errno.h>
#include <unistd.h>

#define MAXLINE 1024


int pos = 0;
static void output( char *message ) {

	printf("%s",message);
	pos++;
	if( pos > 80 ) {
		printf("\n");
		pos = 0;
		usleep(10000);
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

int sockfd;
struct sockaddr_in     servaddr;
int prep_client( int port )
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
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    //		sendto(sockfd, (const char *)hello, strlen(hello),
      //  		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
        //    		sizeof(servaddr));
    //printf("Hello message sent.\n");
}

static void __handle_udp(uint8_t *packet_data, uint8_t *packet_end)
{
	uint16_t source_port = ntohs(((uint16_t *)packet_data)[0]);
        uint16_t destination_port = ntohs(((uint16_t *)packet_data)[1]);
        // printf("  UDP source: %u, destination: %u\n", source_port, destination_port);

	// udp frag consists of two 16-bit ints, a 16-bit len, and a checksum
	packet_data += 8;

	if( destination_port == 2050 ) {

        	// printf("  SEND: %u\n", packet_end - packet_data );
		output("!");
    		sendto(sockfd, packet_data, packet_end - packet_data,
        		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		sizeof(servaddr));
	}
}

static char *filter_ip;

static void __handle_ipv4(uint8_t *packet_data, uint8_t header_len, uint8_t *packet_end)
{
        uint16_t total_length = ntohs(((uint16_t *)packet_data)[1]);
        uint8_t protocol = packet_data[9];
        int i = 12;
	char src_txt[32];

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

        // printf("SRC=%s\n", src_txt );
	if( strcmp( src_txt, filter_ip) != 0 ) {
	    return;
	}
	output(".");

        if (protocol == 17) {
                __handle_udp(packet_data + header_len * 4, packet_end);
        } else {
		printf(" **ignoring protocol: %d **\n", protocol );
	}
}

int main(int argc, char *argv[]) {

  int port = 9902;

  if( argc < 3 ) {
    fprintf(stdout,"usage: %s <cap-file> <ip-addr>\n", argv[0] );
    return 0;
  }
  char * cap_file = argv[1];
  filter_ip = argv[2];

  printf("input: filtering UDP from ip:%s port:2050\n", filter_ip );
  printf("outputing UDP packets to localhost:%d\n", port);
  prep_client( port );

  // sleep(5);

  // 1- open ICE
  // 2- grab handle to TOPIC: ice--MDS to insert our device record

  // open capture file for offline processing
  light_pcapng_t *descr = light_pcapng_open_read( cap_file, LIGHT_FALSE );
  // descr = pcap_open_offline(cap_file, errbuf);
  if (descr == NULL) {
      fprintf(stdout, "pcap file open failed: %d", errno );
      return 1;
  }

  int index = 0;

  long zero = 0;
  long curr_tm = 0;
  while( 1 ) {
	  light_packet_header pkt_header;
	  const uint8_t *pkt_data = NULL;
	  uint8_t *pkt_end = NULL;
	  int res = 0;
	  int i;

	  res = light_get_next_packet( descr, &pkt_header, &pkt_data );
	  if( !res) break;

	  index++;
	  if( pkt_data != NULL) {
		curr_tm = pkt_header.timestamp.tv_sec;
		if( zero == 0 ) {
			zero = curr_tm;
		}
/*
		int millis = pkt_header.timestamp.tv_usec / 1000;
		int dt = millis;
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
                	output("*");
                	continue;
        	}

        	uint8_t ip_header_length = (*octets) & 0b1111;
        	uint8_t protocol_version = (*octets >> 4) & 0b1111;

        	if (protocol_version == 4) {
                	__handle_ipv4(octets, ip_header_length, pkt_end);
		} else if (protocol_version == 6) {
			output_status("6");
		} else {
			// printf("Protocol version = %u\n", protocol_version );
			output("6");
		}


		// int offset = 604 - 562;
    		// sendto(sockfd, pkt_data + offset, pkt_header.original_length - offset,
        		// MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		// sizeof(servaddr));
	  }
  }

  // start packet processing loop, just like live capture
  //if (pcap_loop(descr, 0, packetHandler, NULL) < 0) {
      //printf( "pcap_loop() failed: %d\n", pcap_geterr(descr) );
      //return 1;
  //}


  // 4- friendly close
  int dt = (int)(curr_tm - zero);
  printf( "processing finished: %d packets == %d secs\n" , index, dt );
  light_pcapng_close( descr );

    		sendto(sockfd, "!", 1,
        		MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            		sizeof(servaddr));
  return 0;
}

