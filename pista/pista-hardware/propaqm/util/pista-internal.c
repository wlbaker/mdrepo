#include <stdint.h>
#include <stdio.h>

#include <pista.h>
#include <string.h>
#include "pista-internal.h"

#include <protobuf-c/protobuf-c.h>

// for protobuf syntax 3
// const char protobuf_c_empty_string[] = "";

/*
 * PISTA private functions
 */
PISTA_API int pista_init_data_packet( struct pista_data_packet *pkt, long tm, char *driver_name, int stream_id, int payload_sz, void *payload )
{
    pkt->tm         = tm;
    strcpy( pkt->source_name, driver_name );
    pkt->stream_id  = stream_id;
    pkt->payload_sz = payload_sz;
    pkt->payload    = payload;

    return PISTA_OK;
}

struct pista_extra_meta {
    int spp;
    int freq;
};

PISTA_API void pista_util_send_connection( struct pista_dev_inst *h, int code ) {
    if( h->status != code ) {
        if( h->event_handler != NULL ) {
            struct pista_data_packet cni;
            long tm = pista_get_current_time_with_ms();
            pista_init_data_packet( &cni, tm, "propaqm", PISTA_DF_CONNECTION, 0, NULL );

            h->status = code; // PISTA_ST_CONNECTED;  // PISTA_ST_NOT_CONNECTED;
            h->event_handler( h->event_priv, &cni );
        }
    }
}


//PISTA_API int pista_get_descriptor_freq( const ProtobufCMessage *base, int idx) {
	//ProtobufCFieldDescriptor *fd = &base->descriptor->fields[idx];
    //struct pista_extra_meta *xmeta = (struct pista_extra_meta *)(fd->reserved2);
    //return (xmeta == NULL) ? 1 : xmeta->freq;
//}
struct pista_extra_meta *_pista_get_named_field_meta( ProtobufCMessage *base, const char *nm) {

	ProtobufCFieldDescriptor *fd = (ProtobufCFieldDescriptor *)protobuf_c_message_descriptor_get_field_by_name( base->descriptor, nm );
    if(  fd == NULL ) {
        fprintf(stderr,"could not find named field: %s\n", nm );
        return NULL;
    }
    struct pista_extra_meta *xmeta = (struct pista_extra_meta *)(fd->reserved2);
    if( xmeta == NULL ) {
        fprintf(stderr,"FIXME: xmeta not ready.\n");
        // xmeta = (struct pista_extra_meta *)malloc( sizeof(struct pista_extra_meta));
        // fd->reserved2 = xmeta;
    }

    return xmeta;
}


PISTA_API int pista_set_named_field_spp( ProtobufCMessage *base, const char *nm, int spp) {
    struct pista_extra_meta *xmeta = _pista_get_named_field_meta( base, nm );
    if( xmeta == NULL ) {
        return PISTA_ERR;
    }
    xmeta->spp = spp;
    return PISTA_OK;
}

PISTA_API int pista_set_named_field_freq( ProtobufCMessage *base, const char *nm, int freq) {
    struct pista_extra_meta *xmeta = _pista_get_named_field_meta( base, nm );
    if( xmeta == NULL ) {
        return PISTA_ERR;
    }
    xmeta->freq = freq;
    return PISTA_OK;
}

PISTA_API int pista_get_field_count( const struct pista_data_packet *pkt ) {
    ProtobufCMessage *base = (ProtobufCMessage *)pkt->payload;
    return (base == NULL) ? 0 : base->descriptor->n_fields;
}

PISTA_API const ProtobufCMessageDescriptor *pista_get_message_descriptor( const struct pista_data_packet *pkt ) {
    ProtobufCMessage *base = (ProtobufCMessage *)pkt->payload;
    return base->descriptor;
}

PISTA_API const ProtobufCFieldDescriptor *pista_get_field_descriptor( const struct pista_data_packet *pkt, int idx ) {
    const ProtobufCMessageDescriptor *desc = pista_get_message_descriptor( pkt );
    return &desc->fields[idx];
}

PISTA_API int pista_get_field_spp( const ProtobufCFieldDescriptor *fd) {
    if(  fd == NULL ) {
        return 0;
    }
    struct pista_extra_meta *xmeta = (struct pista_extra_meta *)(fd->reserved2);
	return (xmeta == NULL) ? 1 : xmeta->spp;
}

PISTA_API int pista_get_field_freq( const ProtobufCFieldDescriptor *fd) {
    if(  fd == NULL ) {
        return -1;
    }
    struct pista_extra_meta *xmeta = (struct pista_extra_meta *)(fd->reserved2);
	return (xmeta == NULL) ? 0 : xmeta->freq;
}

PISTA_API int pista_get_field_subtyp( const ProtobufCFieldDescriptor *fd ) {
    int subtyp = fd->type;
    int q_offset = fd->quantifier_offset;
    switch( subtyp ) {
        case PROTOBUF_C_TYPE_INT32:
        case PROTOBUF_C_TYPE_SINT32:
        case PROTOBUF_C_TYPE_SFIXED32:
        case PROTOBUF_C_TYPE_UINT32:
        case PROTOBUF_C_TYPE_FIXED32:
            subtyp = INT_TYP;
            break;
        case PROTOBUF_C_TYPE_INT64:
        case PROTOBUF_C_TYPE_SINT64:
        case PROTOBUF_C_TYPE_SFIXED64:
        case PROTOBUF_C_TYPE_UINT64:
        case PROTOBUF_C_TYPE_FIXED64:
            subtyp = LONG_TYP;
            break;
        case PROTOBUF_C_TYPE_FLOAT:
            subtyp = FLOAT_TYP;
            break;
        case PROTOBUF_C_TYPE_DOUBLE:
            subtyp = DOUBLE_TYP;
            break;
        case PROTOBUF_C_TYPE_BOOL:
            subtyp = BOOLEAN_TYP;
            break;
        case PROTOBUF_C_TYPE_STRING:
            subtyp = STRING_TYP;
            break;
        case PROTOBUF_C_TYPE_BYTES:
            subtyp = BYTE_TYP;
            break;
        default:
            fprintf(stderr,"Unsupported Protobuf-c type: %d\n", subtyp );
            subtyp = INVALID_TYP;
            break;
    }
    if( q_offset > 0 ) {
        switch( subtyp ) {
            case INT_TYP:
                subtyp = INT_ARR_TYP;
                break;
            case FLOAT_TYP:
                subtyp = FLOAT_ARR_TYP;
                break;
            case DOUBLE_TYP:
                subtyp = DOUBLE_ARR_TYP;
                break;
            case BYTE_TYP:
                // WARNING: might be some ambiguity if *q_offset = 1...really a BYTE_TYP?
                subtyp = BYTE_ARR_TYP;
                break;
            default:
                fprintf(stderr,"Unsupported array type: %d\n", subtyp );
                subtyp = INVALID_ARR_TYP;
                break;
        }
    }
    return subtyp;
}

PISTA_API int pista_get_field_offset( const ProtobufCFieldDescriptor *fd ) {
    return fd->offset;
}

PISTA_API const char *pista_get_field_loc( const ProtobufCFieldDescriptor *fd ) {
    return fd->name;
}

PISTA_API int pista_get_field_quantifier( const struct pista_data_packet *pkt, const ProtobufCFieldDescriptor *fd ) {
    if( fd->quantifier_offset == 0 ) {
        return 1;
    }
    int *quantifier = (int *)(((uint8_t *)pkt->payload) + fd->quantifier_offset);
    return *quantifier;
}

