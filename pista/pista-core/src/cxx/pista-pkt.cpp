
#include <math.h>
#include <string.h>

#include "pista-cl.h"
#include "pista-internal.h"

using namespace pistax;

#define LOG_PREFIX "pista-pkt"


// hack..don't know why pista_err() isnt found in link of jpista dll
#include <stdio.h>
#define DO_ERR printf


PistaDataPacket::PistaDataPacket( pista_data_packet *pkt ) {
	this->pkt = pkt;
	// printf("ALLOCATED CXX PKT: 0x%p\n", this );
}

PistaDataPacket::~PistaDataPacket( ) {
	// printf("DEALLOCATED CXX PKT: 0x%p\n", this );
}

int64_t PistaDataPacket::getTm() {
	return pkt->tm;
}

int PistaDataPacket::getStreamID() {
	return pkt->stream_id;
}

int PistaDataPacket::getDescriptorCount() {
	return (pkt == NULL) ? 0 : pista_get_field_count(pkt);
}

const char *PistaDataPacket::getDescriptorLoc( int desc_idx ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx);
	return pista_get_field_loc( fd );
}

PistaDescriptor PistaDataPacket::getDescriptor( int desc_idx ) {
	return PistaDescriptor( pista_get_field_descriptor( pkt, desc_idx) );
}

const ProtobufCFieldDescriptor *PistaDataPacket::_getDescriptor( int desc_idx ) {
	return pista_get_field_descriptor( pkt, desc_idx);
}
/*
PROTOBUF_C_TYPE_INT32
PROTOBUF_C_TYPE_SINT32
PROTOBUF_C_TYPE_SFIXED32
PROTOBUF_C_TYPE_INT64
PROTOBUF_C_TYPE_SINT64
PROTOBUF_C_TYPE_SFIXED64
PROTOBUF_C_TYPE_UINT32
PROTOBUF_C_TYPE_FIXED32
PROTOBUF_C_TYPE_UINT64
PROTOBUF_C_TYPE_FIXED64
PROTOBUF_C_TYPE_FLOAT
PROTOBUF_C_TYPE_DOUBLE
PROTOBUF_C_TYPE_BOOL
PROTOBUF_C_TYPE_ENUM
PROTOBUF_C_TYPE_STRING
PROTOBUF_C_TYPE_BYTES
PROTOBUF_C_TYPE_MESSAGE 
*/
int PistaDataPacket::getFieldSubtyp( int field_idx ) {
    const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, field_idx);
    return pista_get_field_subtyp( fd );
}

int PistaDataPacket::getFieldQuantifier( int field_idx ) {
    const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, field_idx);
    return pista_get_field_quantifier( pkt, fd );
}

int PistaDataPacket::getInt( int desc_idx ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( (pista_get_field_subtyp(fd) ) != INT_TYP ) {
		DO_ERR("%s: Invalid call to getInt.", LOG_PREFIX);
		return -1;
	}
	int offset = pista_get_field_offset(fd);
	int *pint = (int *)(((uint8_t *)pkt->payload) + offset);
	return *pint;
}

int PistaDataPacket::getLong( int desc_idx ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( (pista_get_field_subtyp(fd) ) != LONG_TYP ) {
		DO_ERR("%s: Invalid call to getInt.", LOG_PREFIX);
		return -1;
	}
	int offset = pista_get_field_offset(fd);
	long *plong = (long *)(((uint8_t *)pkt->payload) + offset);
	return *plong;
}

float PistaDataPacket::getFloat( int desc_idx ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( (pista_get_field_subtyp(fd) ) != FLOAT_TYP ) {
		DO_ERR("%s: Invalid call to getFloat.", LOG_PREFIX);
		return NAN;
	}
	int offset = pista_get_field_offset(fd);
	float *pfloat = (float *)(((uint8_t *)pkt->payload) + offset);
	return *pfloat;
}

char *PistaDataPacket::getString( int desc_idx ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	int subtyp = pista_get_field_subtyp(fd);
	if( subtyp == STRING_TYP || subtyp == BYTE_ARR_TYP  ) {
        // ok
    	} else {
		DO_ERR("%s: Invalid call to getString.", LOG_PREFIX);
		return NULL;
	}
	int offset = pista_get_field_offset(fd);
	char **str = (char **)(((uint8_t *)pkt->payload) + offset);
	return *str;
}


const pista_data_packet *PistaDataPacket::_packet( ) {
     return pkt; 
}

char *PistaDataPacket::getByteArray( int desc_idx, size_t *sz ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( pista_get_field_subtyp( fd ) != BYTE_ARR_TYP ) {
		DO_ERR("%s: Invalid call to getByteArray.", LOG_PREFIX);
		return NULL;
	}
	int len = *sz = pista_get_field_quantifier( pkt, fd );
	int offset = pista_get_field_offset(fd);
	// size_t count = pkt->desc[desc_idx].count;

	DO_ERR("%s: Incomplete.  Allocate memory here?", LOG_PREFIX );
	char *ptr = (char *)(((uint8_t *)pkt->payload) + offset);
    // memcpy( data, *ptr, (count < len) ? count : len );

	return ptr;
}

int *PistaDataPacket::getIntArray( int desc_idx, size_t *len ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( pista_get_field_subtyp( fd ) != INT_ARR_TYP ) {
		DO_ERR("%s: Invalid call to getIntArray.", LOG_PREFIX);
		return NULL;
	}
	*len = pista_get_field_quantifier( pkt, fd );
	int offset = pista_get_field_offset(fd);
	int **ppint = (int **)(((uint8_t *)pkt->payload) + offset);
	return *ppint;
}

float *PistaDataPacket::getFloatArray( int desc_idx, size_t *len ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( pista_get_field_subtyp( fd ) != FLOAT_ARR_TYP ) {
		DO_ERR("%s: Invalid call to getFloatArray.", LOG_PREFIX);
		return NULL;
	}
	*len = pista_get_field_quantifier( pkt, fd );
	int offset = pista_get_field_offset(fd);
	float **ppfloat = (float **)( ((uint8_t *)pkt->payload) + offset);
	return *ppfloat;
}

double *PistaDataPacket::getDoubleArray( int desc_idx, size_t *len ) {
	const ProtobufCFieldDescriptor *fd = pista_get_field_descriptor( pkt, desc_idx );
	if( pista_get_field_subtyp( fd ) != DOUBLE_ARR_TYP ) {
		DO_ERR("%s: Invalid call to getDoubleArray.", LOG_PREFIX);
		return NULL;
	}
	*len = pista_get_field_quantifier( pkt, fd );
	int offset = pista_get_field_offset(fd);
	double **ppdouble = (double **)( ((uint8_t *)pkt->payload) + offset);
	return *ppdouble;
}

