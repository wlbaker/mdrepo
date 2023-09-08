/**
 * @file intellivue_serial.cxx
 *
 * Constructs a serial request and checks serial responses
 * Philips IntelliVue MP70.
 *
 * Example 1:
 * If a Computer Client wants to send the data:
 * "0x3a 0x71"
 * The CRC for this data would be:
 * "0xd9 0x64"
 * after building the one�s-complement and byte-swapping, this results in:
 * "0x9b 0x26"
 * The whole frame would be:
 * "0xc0 0x3a 0x71 0x9b 0x26 0xc1"
 *
 * Example 2:
 * If a Computer Client wants to send the data:
 * "0x3a 0x91"
 * The CRC for this data would be:
 * "0x3e 0x6a"
 * after building the one�s-complement and byte-swapping, this results in:
 * "0x95 0xc1"
 * The whole frame would be:
 * "0xc0 0x3a 0x91 0x95 0x7d 0xe1 0xc1"
 * Note that byte "0xc1" in the CRC is a reserved character and must be escape.
 * This results in "0x7d 0xe1".
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================

#include <stdio.h>
#include <stdint.h>
#include "intellivue.h"
#include "intellivue_utils.h"
#include "intellivue_serial.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#define PPPINITFCS 0xffff // Initial FCS value
#define PPPGOODFCS 0xf0b8 // Good final FCS value
#define P 0x8408

static uint16_t fcstab[256];
static log4cplus::Logger g_root = log4cplus::Logger::getRoot();

intellivue_serial::intellivue_serial()
{
  create_fcs_table();
}

intellivue_serial::~intellivue_serial()
{
}

int intellivue_serial::get_numbytes()
{
	return(serialrequest.length);
}

uint8_t* intellivue_serial::get_bytes()
{
	return(serialrequest.newrequest);
}

int intellivue_serial::construct_serial_msg(uint8_t buf[], int numbytes)
{
  static const char* sfn = "intellivue_serial::construct_serial_msg()";
	std::vector<uint8_t> temp;
	std::vector<uint8_t>::iterator it;
	int x7D_counter = 0;
	uint8_t length[2] = {0};

	try
	{ // Add contents of byte array to vector
	  for(int ix = 0; ix < numbytes; ix++) temp.push_back(buf[ix]);
	}
	catch(...)
	{
	  LOG4CPLUS_ERROR(g_root, sfn << " Unable to push byte on vector");
	  return __LINE__;
	}

	/**
	 * Add header
	 * Protocol id = 0x11
	 * Message type = 0x01
	 * Length = numbytes (without the 7D bytes inserted)
	 */
	int22bytes(&length[0], numbytes);
	uint8_t header[] = {0x11, 0x01, length[0], length[1]};

	it = temp.begin();

	try
	{
	  temp.insert(it, header, header + 4);
	}
	catch(...)
	{
    LOG4CPLUS_ERROR(g_root, sfn << " Unable to insert bytes into vector");
    return __LINE__;
	}

	// Increase the number of bytes from the header
	numbytes += 4;

	// Make a buffer with header
	uint8_t bufwheader[temp.size()]; // variable length cannot be initialized

	for (std::vector<uint8_t>::size_type ix = 0; ix < temp.size(); ix++)
  {
		bufwheader[ix] = temp.at(ix);
	}

	// Create fcs table
	//create_fcs_table(); // TODO taken out an put in constructor... test to make sure still works

	// Send bytes and initial fcs value
	uint16_t fcsval = 0;
	if (pppfcs(PPPINITFCS, &fcsval, bufwheader, numbytes)) return __LINE__;

	// Take ones compliment of value
	fcsval = ~fcsval;

	// Convert result to bytes and add it to byte array.
	uint8_t fcsbytes[2] = {0};
	int22bytes(&fcsbytes[0], fcsval);
	uint8_t bufwfcs[numbytes + 2];

	// Add FCS to array
	for(int x = 0; x < numbytes; x++) bufwfcs[x] = bufwheader[x];

	// Byte swap. 1 first
	bufwfcs[numbytes] = fcsbytes[1];
	bufwfcs[numbytes + 1] = fcsbytes[0];

	numbytes += 2;

	// Clear vector
	temp.clear();

	// Add contents of byte array to vector
	for(int x = 0; x < numbytes; x++)
	{ // Check for control characters 0xC0, 0xC1, 0x7D
		if ((bufwfcs[x] == 0xC0 || bufwfcs[x] == 0xC1 || bufwfcs[x] == 0x7D)
		  && x > 3)
		{
      // Put 0x7D before character and XOR that character with 0x20.
      // Example: 0xC1 XOR 0x20 = 0xE1
			temp.push_back(0x7D);
			temp.push_back((bufwfcs[x] ^ 0x20));
      x7D_counter++;
		}
		else
		{
			temp.push_back(bufwfcs[x]);
		}
	}

	numbytes += x7D_counter;

	// Add BOF
	it = temp.begin();
	temp.insert(it, 0xC0);

	// Add EOF
	temp.push_back(0xC1);
	numbytes += 2;

	// Allocate space for new request.
	serialrequest.newrequest = new (std::nothrow) uint8_t[sizeof(uint8_t) * numbytes];
	if (!serialrequest.newrequest)
	{
	  LOG4CPLUS_ERROR(g_root, sfn << " Unable to allocate request buffer");
	  return __LINE__;
	}

	for(std::vector<uint8_t>::size_type ix = 0; ix < temp.size(); ix++)
	{
		serialrequest.newrequest[ix] = temp.at(ix);
	}

	serialrequest.length = numbytes;
	temp.clear();

	return 0;
}

int intellivue_serial::pppfcs(
  const uint16_t fcs,
  uint16_t* return_fcs,
  uint8_t* cp,
  int len)
{
  static const char* sfn = "intellivue_serial::pppfcs()";
  if (!cp)
  {
    LOG4CPLUS_ERROR(g_root, sfn << " Parameter cp is null");
    return __LINE__;
  }

  if (sizeof(fcs) != 2)
  {
    LOG4CPLUS_ERROR(g_root, sfn << " fcs is wrong size");
    return __LINE__;
  }

  if (((uint16_t) -1) <= 0)
  {
    LOG4CPLUS_ERROR(g_root, sfn << " Not unsigned");
    return __LINE__;
  }

  uint16_t temp_fcs = fcs;

  while(len--)
  {
    temp_fcs = (temp_fcs >> 8) ^ fcstab[(temp_fcs ^ *cp++) & 0xff];
  }

  *return_fcs = temp_fcs;
  return 0;
}

/* TODO save old just in case
uint16_t intellivue_serial::pppfcs(uint16_t fcs, uint8_t *cp, int len)
{
	assert(sizeof(uint16_t) == 2);
	assert(((uint16_t) -1) > 0);
	while (len--)
		fcs = (fcs >> 8) ^ fcstab[(fcs ^ *cp++) & 0xff];
	return fcs;
}
*/

void intellivue_serial::create_fcs_table()
{
	for (unsigned int b = 0; b < 256; b++)
	{
	  unsigned int v = b;

		for (int i = 8; i--; )
			v = v & 1 ? (v >> 1) ^ P : v >> 1;

		fcstab[b] = (v & 0xFFFF);
	}
}

int intellivue_serial::unwrap_serial_msg(uint8_t* buf, ssize_t* numbytes)
{
  static const char* sfn = "intellivue_serial::unwrap_serial_msg()";
	std::vector<uint8_t> temp;
	std::vector<uint8_t>::iterator it;
	uint8_t fcstemp[2] = {0};
	int protocol_id = 0;
	int msg_type = 0;

	// Get rid of 0x7D's and XOR 0x20 to the following byte
	for(ssize_t ix = 0; ix < *numbytes; ix++)
	{
		if(buf[ix] == 0x7D)
		{
			if((ix + 1) < *numbytes)
			{
				temp.push_back(buf[ix + 1] ^ 0x20);
				ix++;
			}
		}
		else
		{
			if(ix == 0 && buf[ix] == 0xC0)
			{
				// Don't add BOF to vector
			}
			else if(ix == (*numbytes - 1) && buf[ix] == 0xC1)
			{
				// Don't add EOF to vector
			}
			else
			  temp.push_back(buf[ix]);
		}
	}

	if(temp.size() > 2)
	{
		// Save FCS value
		fcstemp[1] = temp.at(temp.size() - 1);
		fcstemp[0] = temp.at(temp.size() - 2);

		// Remove the FCS from bytes
		temp.pop_back();
		temp.pop_back();
	}

	for(int ix = 0; ix < temp.size(); ix++)
	{
		buf[ix] = temp.at(ix);
	}

	// Get the actual FCS value and take ones compliment of value
	uint16_t fcsval = 0;
	if (pppfcs(PPPINITFCS, &fcsval, buf, temp.size())) return __LINE__;
	fcsval = ~fcsval;

	// Turn fcsval into bytes
	uint8_t fcsbytes[2] = {0};
	int22bytes(&fcsbytes[0], (int)fcsval);

	// Check to make sure both FCS's match.
	if(fcsbytes[1] != fcstemp[0] || fcsbytes[0] != fcstemp[1])
	{
		// Bad message
		LOG4CPLUS_WARN(g_root, sfn << " this is fcsbytes[0] " << std::dec
		  << (int)fcsbytes[0] << std::endl
		  << "this is fcstemp[0] " << std::dec << (int)fcstemp[0] << std::endl
		  << "this is fcsbytes[1] " << std::dec << (int)fcsbytes[1] << std::endl
		  << "this is fcstemp[1] " << std::dec << (int)fcstemp[1]);
		return (1);
	}

	// Parse header for error checking and save number of bytes
	protocol_id = (int)buf[0];
	msg_type = (int)buf[1];
	*numbytes = static_cast<ssize_t>(bytes2u16(&buf[2]));

	// Check for bad protocol id and message type
	if(protocol_id != 0x11 || msg_type != 0x01)
	{
		LOG4CPLUS_WARN(g_root, sfn << " Wrong protocol_id or msg_type in "
		  "response");
		return (2);
	}

	// Remove header
	for(int x = 4; x < temp.size(); x ++)
	{
		buf[x - 4] = temp.at(x);
	}

	temp.clear();
	return 0;
}
