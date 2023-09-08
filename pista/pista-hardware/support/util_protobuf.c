#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "pista.h"
#include "pista-internal.h"
#include <google/protobuf-c/protobuf-c.h>

// typedef struct ProtobufCFieldDescriptor;
PISTA_API int pista_set_named_field_spp( ProtobufCMessage *base, const char *nm, int spp)
{
	return PISTA_OK;
}

PISTA_API int pista_set_named_field_freq( ProtobufCMessage *base, const char *nm, int freq)
{
	return PISTA_OK;
}

PISTA_API int pista_get_field_spp( const ProtobufCFieldDescriptor *fd)
{

	return PISTA_OK;
}

PISTA_API int pista_get_field_freq( const ProtobufCFieldDescriptor *fd)
{

	return PISTA_OK;
}

PISTA_API int pista_dev_register_stream( struct pista_dev_inst *di, struct pista_data_packet *pkt )
{
    pkt->next_stream = di->stream_head;
    di->stream_head = pkt;

    return PISTA_OK;
}


int util__set_named_field_freq() {
}

int util__set_named_field_spp() {
}
