#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "infinityNet.h"

#include <errno.h>

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
  const struct ether_header* ethernetHeader;
  const struct ip* ipHeader;
  const struct tcphdr* tcpHeader;
  char sourceIp[INET_ADDRSTRLEN];
  char destIp[INET_ADDRSTRLEN];
  u_int sourcePort, destPort;
  u_char *data;
  int dataLength = 0;

  ethernetHeader = (struct ether_header*)packet;
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
      if (ipHeader->ip_p == IPPROTO_TCP) {
          tcpHeader = (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
          sourcePort = ntohs(tcpHeader->source);
          destPort = ntohs(tcpHeader->dest);
          data = (u_char*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
          dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));

          // convert non-printable characters, other than carriage return, line feed,
          // or tab into periods when displayed.
          // for (int i = 0; i < dataLength; i++) {
              // if ((data[i] >= 32 && data[i] <= 126) || data[i] == 10 || data[i] == 11 || data[i] == 13) {
                  // dataStr += (char)data[i];
              // } else {
                  // dataStr += ".";
              // }
          // }

          // print the results
          // printf("%xsourceIp << ":" << sourcePort << " -> " << destIp << ":" << destPort << endl;
          // if (dataLength > 0) {
              // cout << dataStr << endl;
          // }
      }
  }
}

int postValueToDDS(char *namedValue, int value)
{


}


int main(int argc, char *argv[]) {
  pcap_t *descr;
  char errbuf[PCAP_ERRBUF_SIZE];

  if( argc < 2 ) {
    fprintf(stdout,"usage: %s <cap-file>\n", argv[0] );
    return 0;
  }
  char * cap_file = argv[1];

  // 1- open ICE
  // 2- grab handle to TOPIC: ice--MDS to insert our device record

  // open capture file for offline processing
  descr = pcap_open_offline(cap_file, errbuf);
  if (descr == NULL) {
      fprintf(stdout, "pcap_open_live() failed: %d", errno );
      return 1;
  }

  // start packet processing loop, just like live capture
  if (pcap_loop(descr, 0, packetHandler, NULL) < 0) {
      printf( "pcap_loop() failed: %d\n", pcap_geterr(descr) );
      return 1;
  }

  // 4- friendly close

  printf( "capture finished\n" );

  return 0;
}

