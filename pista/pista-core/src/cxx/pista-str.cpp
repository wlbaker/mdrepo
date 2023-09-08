
#include "pista-cl.h"
#include <protobuf-c/protobuf-c.h>

using namespace pistax;

PistaDescriptor::PistaDescriptor( const ProtobufCFieldDescriptor *fd) 
{
	this->fd = fd;
}

const char *PistaDescriptor::getLoc() { return fd->name; }
int PistaDescriptor::getSPP() { return pista_get_field_spp(fd); }
int PistaDescriptor::getFreq() { return pista_get_field_freq(fd); }

PistaStream::PistaStream( const pista_data_packet *pkt ) 
{
	this->pkt = pkt;
}

int PistaStream::getDescriptorCount( ) 
{
	return pista_get_field_count(pkt);
}

PistaDescriptor PistaStream::getDescriptorByIdx( int idx ) 
{
    ProtobufCMessage *base = (ProtobufCMessage *)pkt->payload;
	return PistaDescriptor( &base->descriptor->fields[idx] );
}

const char *PistaStream::getPackageName( ) 
{
    ProtobufCMessage *base = (ProtobufCMessage *)pkt->payload;
	return base->descriptor->package_name;
}

