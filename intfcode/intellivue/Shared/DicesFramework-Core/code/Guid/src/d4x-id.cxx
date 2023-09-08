/**
 * @file   d4x_id.h
 * @brief  DocBox ID.
 * @author WMS
 *
 * @note What is "d4x"? There are 4 letters between the 'D' and 'x' in "DocBox"
 */
//=============================================================================
//=============================================================================
//#define TEST_PROGRAM_MAIN

// Higher number = more verbose. 0 = no messages.
#define CONSOL_MSG_VERBOSITY_LEVEL_NONE (0)
#define CONSOL_MSG_VERBOSITY_LEVEL_SOME (1)
#define CONSOL_MSG_VERBOSITY_LEVEL_MOST (2)

#ifdef TEST_PROGRAM_MAIN
#define CONSOL_MSG_VERBOSITY_LEVEL CONSOL_MSG_VERBOSITY_LEVEL_MOST
#else
#define CONSOL_MSG_VERBOSITY_LEVEL CONSOL_MSG_VERBOSITY_LEVEL_NONE
#endif

#include "../d4x-id.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdint>
#include <chrono>
#include <iomanip>
#include <ratio>
#include <ctime>
#include <thread>
#include <cstdint>
#include <common.h>

#ifdef _WIN32
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#else
//#define _GNU_SOURCE     /* Get defs of NI_MAXSERV, NI_MAXHOST */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>
#include <netinet/in.h>
#include <sys/types.h>
#endif


//=============================================================================
//=============================================================================

// Fully defined Entityid_t values
#define ENTITYID_MANAGER      {KOE_MANAGER, 0x0000}
#define ENTITYID_SYSTEM_APP   {KOE_SYSTEM_APP, 0x0000}
#define ENTITYID_CLINICAL_APP {KOE_CLINICAL_APP, 0x0000}
#define ENTITYID_DEVICE       {KOE_DEVICE, 0x0000}
#define ENTITYID_COORDINATOR  {KOE_COORDINATOR, 0x0000}
#define ENTITYID_OPERATOR     {KOE_OPERATOR, 0x0000}
#define ENTITYID_PROVIDER     {KOE_PROVIDER, 0x0000}
#define ENTITYID_PATIENT      {KOE_PATIENT, 0x0000}

static int get_host_id(ice::HostId *hid);
static int get_prefix(ice::GuidPrefix *prefix);
static int get_timestamp(ice::GuidTimespec *ts);
static int get_entity_id(ice::EntityKind kind_of_entity, ice::EntityKey entity_key, ice::EntityId *eid);

//=============================================================================
int get_prefix(ice::GuidPrefix *prefix)
{
  *prefix = GUID_PREFIX_UNKNOWN;
  return 0;
}

//=============================================================================
int get_entity_id(ice::EntityKind kind_of_entity, ice::EntityKey entity_key, ice::EntityId *eid)
{
  *eid = ICE_ENTITYID_UNKNOWN;
  eid->kind_of_entity = kind_of_entity;
  eid->entity_key = entity_key;
  return 0;
}

//=============================================================================
// CONFIRM THIS
int get_timestamp(ice::GuidTimespec *ts)
{
  // Get the system time to a relatively high resolution
  std::chrono::high_resolution_clock::time_point tphires =
    std::chrono::high_resolution_clock::now();
  uint64_t nanoseconds_since_epoch =
    std::chrono::duration_cast<std::chrono::nanoseconds>
    (tphires.time_since_epoch()).count();
  int64_t seconds = nanoseconds_since_epoch / std::giga::num;
  int64_t nanoseconds = nanoseconds_since_epoch % std::giga::num;
  uint64_t value = seconds << (2 * 8);  // Shift the seconds into place.

  // grab 2 bytes of fractional seconds computed from the nanoseconds
  nanoseconds *= (1 << (2 * 8)); // save the part in 2^16
  nanoseconds /= (1000 * 1000 * 1000); // divide by 1 billion (= 1 sec, in ns)

  // mask and or to assemble finished value
  value |= (seconds & 0x0000FFFFFFFF0000UL);
  value |= (nanoseconds & 0xFFFFUL);

  uint16_t i16 = htons((value) & 0xFFFFUL);
  uint32_t i32 = htonl((value >> 16) & 0xFFFFFFFFUL);
  memcpy(&(ts->seconds[0]), &i32, 4);
  memcpy(&(ts->fraction[0]), &i16, 2);
  return 0;
}

#ifdef _WIN32
//=============================================================================
// WINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOWSWINDOW
//=============================================================================

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
/* Note: could also use malloc() and free() */

static int tell_the_world(PIP_ADAPTER_ADDRESSES ipaa, const std::string &sphysaddr)
{
  int rc = 0;
  int ix = 0;

#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_NONE
  printf("\tAdapter name:\t\t%s\n", ipaa->AdapterName);
  printf("\tDescription:\t\t%wS\n", ipaa->Description);
  printf("\tFriendly name:\t\t%wS\n", ipaa->FriendlyName);
  printf("\tPhysical address:\t%s\n", sphysaddr.c_str());

#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_SOME
  printf("\tPIP_ADAPTER_ADDRESSES struct length: %ld\n",
    ipaa->Length);
  printf("\tIfIndex (IPv4 interface): %u\n", ipaa->IfIndex);

  ix = 0;
  PIP_ADAPTER_UNICAST_ADDRESS puni = ipaa->FirstUnicastAddress;
  if (puni != nullptr)
  {
    for (; puni != nullptr; ix++) puni = puni->Next;
  }
  printf("\tUnicast Address count:    %d\n", ix);

  ix = 0;
  PIP_ADAPTER_ANYCAST_ADDRESS pany = ipaa->FirstAnycastAddress;
  if (pany)
  {
    for (ix = 0; pany != nullptr; ix++) pany = pany->Next;
  }
  printf("\tAnycast Address count:    %d\n", ix);

  ix = 0;
  PIP_ADAPTER_MULTICAST_ADDRESS pmulti = ipaa->FirstMulticastAddress;
  if (pmulti)
  {
    for (ix = 0; pmulti != nullptr; ix++) pmulti = pmulti->Next;
  }
  printf("\tMulticast Address count:  %d\n", ix);

  ix = 0;
  IP_ADAPTER_DNS_SERVER_ADDRESS *pdns = ipaa->FirstDnsServerAddress;
  if (pdns)
  {
    for (ix = 0; pdns != nullptr; ix++) pdns = pdns->Next;
  }
  printf("\tDNS Server Address count: %d\n", ix);

  printf("\tDNS Suffix: %wS\n", ipaa->DnsSuffix);

  printf("\tFlags:      %ld\n", ipaa->Flags);
  printf("\tMtu:        %lu\n", ipaa->Mtu);
  printf("\tIfType:     %ld\n", ipaa->IfType);
  printf("\tOperStatus: %ld\n", ipaa->OperStatus);
  printf("\tIpv6IfIndex (IPv6 interface):   %u\n", ipaa->Ipv6IfIndex);
  printf("\tZoneIndices (hex):     ");
  for (ix = 0; ix < 16; ix++)
  {
    printf("%lx ", ipaa->ZoneIndices[ix]);
  }
  printf("\n");

  printf("\tTransmit link speed:   %I64u\n", ipaa->TransmitLinkSpeed);
  printf("\tReceive link speed:    %I64u\n", ipaa->ReceiveLinkSpeed);

  ix = 0;
  IP_ADAPTER_PREFIX *ppfix = ipaa->FirstPrefix;
  if (ppfix)
  {
    for (ix = 0; ppfix != nullptr; ix++) ppfix = ppfix->Next;
  }
  printf("\tIP Adapter Prefix entries count: %d\n", ix);
#endif
  printf("\n");
#endif

  return rc;
}

int get_host_id(HostId_t *host_id)
{
  DWORD dwret {0};
//  ULONG family {AF_UNSPEC}; // Unspecified addr family: AF_INET and AF_INET6
  ULONG family {AF_INET};
  std::string family_name;
  PIP_ADAPTER_ADDRESSES ip_adapters {nullptr};
  const int max_tries {3};
  int ntries {0};
  int nadapters {0};
  int rc {1}; // assume fail;

#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_NONE
  if (family == AF_INET)    family_name = "AF_INET";
  if (family == AF_INET6)   family_name = "AF_INET6";
  if (family == AF_UNSPEC)  family_name = "AF_UNSPEC";
  std::cout << std::endl;
  std::cout
    << "GetAdaptersAddresses, family " << family_name
    << " (" << family << ") results:";
  std::cout << std::endl << std::endl;
#endif

  ULONG buflen {1 << 14};
  ULONG flags  {GAA_FLAG_INCLUDE_PREFIX};

  while(1)
  {
    ip_adapters = (IP_ADAPTER_ADDRESSES *) MALLOC(buflen);
    if (ip_adapters == nullptr)
    {
      printf ("Failed to allocate memory for IP_ADAPTER_ADDRESSES struct\n");
      exit(1);
    }

    dwret = GetAdaptersAddresses(family, flags, nullptr, ip_adapters, &buflen);
    if (dwret != ERROR_BUFFER_OVERFLOW) break;

    FREE(ip_adapters);
    ip_adapters = nullptr;
  }

  while(1)
  {
    if (dwret != NO_ERROR)
    {
      printf("Call to GetAdaptersAddresses failed (%d).\n", dwret);
      if (dwret == ERROR_NO_DATA)
      {
        printf("\tNo addresses found for requested parameters.\n");
      }
      else
      {
        LPVOID lpMsgBuf {nullptr};

        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER
                | FORMAT_MESSAGE_FROM_SYSTEM
                | FORMAT_MESSAGE_IGNORE_INSERTS, 
              nullptr,
              dwret,
              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Default language
              (LPTSTR)&lpMsgBuf,
              0,
              nullptr))
        {
          printf("\t%s", lpMsgBuf);
          LocalFree(lpMsgBuf);
        }
      }
      break;
    }

    // At least one adapter is availabe. Output info about it, and any others.

    PIP_ADAPTER_ADDRESSES curr_ipaa = ip_adapters;

    while (curr_ipaa)
    {
      if (curr_ipaa->PhysicalAddressLength > 0)
      {
        std::string sphysaddr;
        char sbuf[32] {0};
        uint8_t hbuf[256] {0};

        for (unsigned int ix = 0; ix < curr_ipaa->PhysicalAddressLength; ix++)
        {
          hbuf[ix] = (int)curr_ipaa->PhysicalAddress[ix];
          sprintf(sbuf, "%.2X", (unsigned int)hbuf[ix]);
          sphysaddr.append(sbuf);
          if (ix < curr_ipaa->PhysicalAddressLength - 1) sphysaddr.append("-");
        }
        std::wstring sdesc {curr_ipaa->Description};
        std::size_t found = sdesc.find(L"Ethernet");
        if (found != std::string::npos)
        {
          // The word "Ethernet" appears in the description, ASSUME this
          // is THE element of interest.
          memcpy(host_id->value, hbuf, sizeof(host_id->value));
        }
        nadapters++;
        tell_the_world(curr_ipaa, sphysaddr);
      }
      curr_ipaa = curr_ipaa->Next;
    }
    rc = 0;
    break;
  }
  if (ip_adapters) FREE(ip_adapters);
#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_NONE
  std::cout << std::endl;
  std::cout << "Total " << family_name << " adapters: " << nadapters;
  std::cout << std::endl;
#endif
  return rc;
}

#else
//=============================================================================
// NOTWINDOWSNOTWINDOWSNOTWINDOWSNOTWINDOWSNOTWINDOWSNOTWINDOWSNOTWINDOWS
//=============================================================================
static int get_ipv4_address(uint32_t *ipv4);

int get_host_id(ice::HostId *host_id)
{
  int rc {1};  // Assume failure
  struct ifaddrs *ifaddr {nullptr};;
  struct ifaddrs *ifa {nullptr};;
  int family {0};
  std::string family_name;
  char host[NI_MAXHOST] {0};
  char sinfo[1024] {0};
  int nafpacket {0};
  int nafinet {0};

  while (1)
  {
    if (getifaddrs(&ifaddr) == -1)
    {
      perror("getifaddrs");
      break;
    }

    /*
     * Walk through linked list. Maintain head pointer for later free list.
     */

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
    {
      if (ifa->ifa_addr == nullptr) continue;

      family = ifa->ifa_addr->sa_family;

      /*
       * Display the interface name & family.
       * For the common families, include their symbolic form.
       */

#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_NONE
      if (family == AF_INET)    family_name = "AF_INET";
      if (family == AF_INET6)   family_name = "AF_INET6";
      if (family == AF_PACKET)  family_name = "AF_PACKET";
      std::cout << std::endl;
      std::cout << ifa->ifa_name
                << "\t" << family_name << " (" << family << ")";
      std::cout << std::endl << std::endl;
#endif

      /* For an AF_INET-type interface address, display the address */

      if (family == AF_INET || family == AF_INET6)
      {
        int iret = getnameinfo(
          ifa->ifa_addr,
          (family == AF_INET) ?
            sizeof(struct sockaddr_in) :
            sizeof(struct sockaddr_in6),
          host,
          NI_MAXHOST,
          NULL,
          0,
          NI_NUMERICHOST);
        if (iret)
        {
          printf("getnameinfo() failed: %s\n", gai_strerror(iret));
          break;
        }
        nafinet++;
        printf("\t\taddress: <%s>\n", host);
      }
      else if (family == AF_PACKET)
      {
        struct sockaddr_ll *sall =
          (sockaddr_ll *)ifa->ifa_addr;

        printf("\n%-8s ", ifa->ifa_name);
        for (int ix = 0; ix < sall->sll_halen; ix++)
        {
          printf(
            "%02x%c",
            (sall->sll_addr[ix]), (ix+1 != sall->sll_halen) ? ':' : '\n');
        }
      
        if (ifa->ifa_data != NULL)
        {
          struct rtnl_link_stats *stats = (rtnl_link_stats *)(ifa->ifa_data);

          printf(
            "\t\ttx_packets = %10u, rx_packets = %10u\n"
            "\t\ttx_bytes   = %10u, rx_bytes   = %10u\n",
            stats->tx_packets, stats->rx_packets,
            stats->tx_bytes, stats->rx_bytes);

          // HACK rengland 05/10/16
          // The returned host ID is the six-byte address of an not-lo interface
          // that has packets received.
          if (stats->rx_packets > 0 && !(sall->sll_addr[0] == 0 &&
            sall->sll_addr[1] == 0 &&
            sall->sll_addr[2] == 0 &&
            sall->sll_addr[3] == 0 &&
            sall->sll_addr[4] == 0 &&
            sall->sll_addr[5] == 0))
          {
            memmove(host_id, sall->sll_addr, 6);
          }
        }
        nafpacket++;
      }
    }
    rc = 0;
    break;
  }
  if (ifaddr) freeifaddrs(ifaddr);
#if CONSOL_MSG_VERBOSITY_LEVEL > CONSOL_MSG_VERBOSITY_LEVEL_NONE
  std::cout << std::endl;
  std::cout << "Total AF_PACKET interfaces: " << nafpacket;
  std::cout << std::endl;
  std::cout << "Total AF_INET interfaces:   " << nafinet;
  std::cout << std::endl;
#endif
  return rc;
}

/*
 *  Get the IPV4 address, in network byte order, of the eth0 interface.
 *
 *  Are you sure this wants to get ONLY the eth0 interface IP address?
 */
int get_ipv4_address(uint32_t *ipv4)
{
  static const char *sfn = "get_ipv4_address";
  struct ifaddrs *ifAddrStruct {nullptr};
  struct ifaddrs *ifa {nullptr};
  void *tmpAddrPtr {nullptr};
  static const char eth0_iface_name[] = "eth0";
  int rc {1}; // assume fail

  while(ipv4)
  {
    *ipv4 = 0;

    // Get network interface info list
    if (getifaddrs(&ifAddrStruct) != 0) break;

    uint32_t ip = 0;

    for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next)
    {
      if (!ifa->ifa_addr) continue;

      if (ifa->ifa_addr->sa_family == AF_INET)
      {
        // Get IPv4 address only from interface eth0.
        if (std::string(ifa->ifa_name).find(eth0_iface_name) != std::string::npos)
        {
          ip = reinterpret_cast<struct sockaddr_in *>(ifa->ifa_addr)->sin_addr.s_addr;
          ip = htonl(ip); // Reverse byte order
          break;
        }
      }
    }
    *ipv4 = ip;
    rc = 0;
    break;
  }
  if (ifAddrStruct) freeifaddrs(ifAddrStruct);
  return rc;
}
#endif

//=============================================================================
//=============================================================================
const ice::EntityKind *D4X_ID::entity_kind(const ice::GUID *guid)
{
  const ice::EntityKind *kind {nullptr};
  if (guid)
  {
    kind = &guid->entity_id.kind_of_entity;
  }
  return kind;
}

bool D4X_ID::compare(ice::GUID *guid1, ice::GUID *guid2)
{
  return guid1 &&
     guid2 &&
     guid1->entity_id.kind_of_entity == guid2->entity_id.kind_of_entity &&
     guid1->entity_id.entity_key == guid2->entity_id.entity_key &&
     0 == std::memcmp(guid1->prefix.hostid, guid2->prefix.hostid, sizeof(ice::HostId)) &&
     0 == std::memcmp(guid1->prefix.timestamp.seconds, guid2->prefix.timestamp.seconds, sizeof(guid2->prefix.timestamp.seconds)) &&
     0 == std::memcmp(guid1->prefix.timestamp.fraction, guid2->prefix.timestamp.fraction, sizeof(guid2->prefix.timestamp.fraction));
}

bool D4X_ID::is_entity_kind(const ice::EntityKind entity_kind, const ice::GUID *guid)
{
  bool rc = false;
  const ice::EntityKind *kind = D4X_ID::entity_kind(guid);
  if (*kind == entity_kind) rc = true;
  return rc;
}

void D4X_ID::create(const ice::EntityKind entity_kind, ice::EntityKey entity_key, ice::GUID *guid)
{
  if (!guid)
  {
    return;
  }

  while(1)
  {
    int rc = get_host_id(&guid->prefix.hostid);
    if (rc)
    {
      memset(guid, 0xff, sizeof(*guid));
      break;
    }

    get_timestamp(&guid->prefix.timestamp);
    get_entity_id(entity_kind, entity_key, &guid->entity_id);
    break;
  }
}

#ifdef TEST_PROGRAM_MAIN
#include <stdio.h>

//=============================================================================
static void guid_to_string(
  const ice::GUID *guid,
  std::string *destination);

//=============================================================================
void guid_to_string(
    const ice::GUID *guid,
    std::string *destination)
{
  std::stringstream ss;
  for (std::size_t ix = 0; ix < sizeof(guid->prefix.hostid); ix++)
  {
    ss  << std::hex << std::setw(2) << std::setfill('0')
        << static_cast<int>(guid->prefix.hostid[ix]);
  }
  for (std::size_t ix = 0; ix < sizeof(guid->prefix.timestamp.seconds); ix++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(guid->prefix.timestamp.seconds[ix]);
  }
  for (std::size_t ix = 0; ix < sizeof(guid->prefix.timestamp.fraction); ix++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(guid->prefix.timestamp.fraction[ix]);
  }
  ss << std::hex << std::setw(4) << std::setfill('0')
     << static_cast<int>(guid->entity_id.kind_of_entity);
  ss << std::hex << std::setw(4) << std::setfill('0')
     << static_cast<int>(guid->entity_id.entity_key);

  *destination = ss.str();
}

//=============================================================================
//=============================================================================
int main(int argc, char** argv)
{
  std::string sbuf;
  ice::GUID guid = GUID_DEFAULT;
  D4X_ID::create(KOE_DEVICE, 0, &guid);

  guid_to_string(
    &guid,
    &sbuf);

  std::cout << std::endl << "D4XID:\t";
  std::cout << sbuf.substr(0, 12) << ":";
  std::cout << sbuf.substr(12, 12) << ":";
  std::cout << sbuf.substr(24, 4) << ":";
  std::cout << sbuf.substr(28, 4) << std::endl;
  return 0;
}
#endif
