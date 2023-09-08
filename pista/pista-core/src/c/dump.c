#include <stdio.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"

#include <google/protobuf-c/protobuf-c.h>

PISTA_PRIV void pista_dump_desc( const ProtobufCFieldDescriptor *fd, void *payload );

PISTA_PRIV void pista_dump_long( long *src, int count ) {
    while( count-- > 0 ) {
        long val = *(src++);
        printf( "%lxL ", val );
    }
}

PISTA_PRIV void pista_dump_int( int *src, int count ) {
    while( count-- > 0 ) {
        int val = *(src++);
        printf( "%d, ", val );
    }
}

PISTA_PRIV void pista_dump_float( float *src, int count ) {
    while( count-- > 0 ) {
        float val = *(src++);
        printf( "%f, ", val );
    }
}

PISTA_PRIV void pista_dump_byte_array( char **psrc, int count ) {
    char *src = *psrc;
    while( count-- > 0 ) {
        char val = *(src++);
        printf( "%c, ", val );
    }
}

PISTA_API void pista_dump_packet( const struct pista_data_packet *pkt ) {
    const ProtobufCMessageDescriptor *mdesc = pista_get_message_descriptor( pkt );

    printf("DUMPING PACKET: %s/%d\n", pkt->source_name, pkt->stream_id );
    int tot = pista_get_field_count( pkt );
    for( int i =0 ; i < tot; i++ ) {
        const ProtobufCFieldDescriptor *fdesc = pista_get_field_descriptor( pkt, i );
        pista_dump_desc( fdesc, pkt->payload );
    }
}

PISTA_API void pista_dump_java( const struct pista_data_packet *pkt ) {
    //pista_dump_jdesc( pkt->desc, pkt->field_cnt, pkt->payload );
    printf("FIXME: pista_dump_java");
}


PISTA_PRIV void pista_dump_desc( const ProtobufCFieldDescriptor *fd, void *payload ) {

    void *base = payload;

        const char *loc  = pista_get_field_loc( fd );
        const char *code = pista_get_field_loc( fd );
        const char *desc = pista_get_field_loc( fd );
        int offset = pista_get_field_offset( fd );
        int count = pista_get_field_spp( fd );
        int subtyp = pista_get_field_subtyp( fd );

		payload = base + offset;

        // printf("%lx{%d}", (unsigned long)payload, ndesc);
        printf("@%d %s:%s:%s [%d]: ", offset, loc, code, desc, count);
        switch( subtyp ) {
        case LONG_TYP:
            pista_dump_long( (long *)payload, 1 );
            break;
        case INT_TYP:
            pista_dump_int( (int *)payload, 1 );
            break;
        case FLOAT_TYP:
            pista_dump_float( (float *)payload, 1 );
            break;
        case BYTE_ARR_TYP:
            pista_dump_byte_array( (char **)payload, count );
            break;
        case STRING_TYP:
            pista_dump_byte_array( (char **)payload, count );
            break;
        case INT_ARR_TYP:
			{
				// we skipped the COUNT field right before payload
				/// int *pi = (int *)payload;
				// int f_n = *(pi++);
				int **ppi = (int **)payload;
            	pista_dump_int( *ppi, count );
			}
            break;
        case FLOAT_ARR_TYP:
			{
				// we skipped the COUNT field right before payload
				// int *pi = (int *)payload;
				// int f_n = *(pi++);
				float **ppf = (float **)payload;
            	pista_dump_float( *ppf, count );
			}
            break;
		default:
        	printf("BROKEN TYPE!");
			break;
        }
        printf("\n");

}

#ifdef FOOFOO
PISTA_PRIV void pista_dump_jdesc( struct pista_item_desc *desc, int ndesc, void *payload ) {

    printf("public class ZZZ extends PersistentItem {\n\n");
    printf("\tprotected static RpMetric[] metrics;\n\n");
    printf("\tstatic { metrics = IntfUtil.getMetrics(ZZZ.class); }\n\n");
    printf("\tpublic () { super(StreamID.?); }\n\n");

    for( int i = 0; i < ndesc; i++ ) {
        struct pista_item_desc *pd = &desc[i];
        int count = pd->count;
        int subtyp = pd->subtyp;

        char attribute[256] = "";
        char typ[256] = "";

        switch( subtyp ) {
        case LONG_TYP:
        case INT_TYP:
        case FLOAT_TYP:
        case DOUBLE_TYP:
        case BYTE_ARR_TYP:
        case STRING_TYP:
            strcpy( attribute, "@Metric( loc=\"");
            strcat( attribute, pd->loc );
            strcat( attribute, "\"" );
            break;
        case INT_ARR_TYP:
        case FLOAT_ARR_TYP:
        case DOUBLE_ARR_TYP:
            strcpy( attribute, "@Waveform( loc=\"");
            strcat( attribute, pd->loc );
            strcat( attribute, "\"" );
            sprintf( attribute + strlen(attribute), ", sampleRate=, spp=%d", count );
            // strcat( attribute, count );
            break;
		default:
        	printf("BROKEN TYPE!");
			break;
        }

        switch( subtyp ) {
        case LONG_TYP:
            sprintf(typ, "long %s;\n", pd->loc);
            break;
        case INT_TYP:
            sprintf(typ, "int %s;\n", pd->loc);
            break;
        case FLOAT_TYP:
            sprintf(typ, "float %s;\n", pd->loc);
            break;
        case DOUBLE_TYP:
            sprintf(typ, "double %s;\n", pd->loc);
            break;
        case BYTE_ARR_TYP:
            sprintf(typ, "byte %s;\n", pd->loc);
            break;
        case STRING_TYP:
            sprintf( attribute + strlen(attribute), ", len=%d", count );
            sprintf(typ, "String %s;\n", pd->loc);
            break;
        case INT_ARR_TYP:
            sprintf(typ, "int [] %s;\n", pd->loc);
            break;
        case FLOAT_ARR_TYP:
            sprintf(typ, "float [] %s;\n", pd->loc);
            break;
        case DOUBLE_ARR_TYP:
            sprintf(typ, "double [] %s;\n", pd->loc);
            break;
		default:
        	sprintf(typ, "BROKEN TYPE!");
			break;
        }
        strcat( attribute, ")" );
        printf("\t%s\n", attribute);
        printf("\t%s\n", typ);

    }
}
#endif
