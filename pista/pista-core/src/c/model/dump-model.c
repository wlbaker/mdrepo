#include <stdio.h>
#include <string.h>

#include <protobuf-c/protobuf-c.h>
#include "propaqm.pb-c.h"

void dumpModel( void *obj, ProtobufCMessage *base )
{
	printf("OBJ  PTR: %d\n", obj );
	printf("BASE PTR: %d\n", base );
	printf("unknown fields: %d\n", base->n_unknown_fields );

	fflush(stdout);

	ProtobufCMessageUnknownField *unk = base->unknown_fields;
	for( int i = 0; i < base->n_unknown_fields; i++ ) {
		printf("\n");
		printf("unknown tag: %d\n", unk[i].tag );
		printf("        len: %d\n", unk[i].len );
		printf("       data: %p\n", unk[i].data );
	}

	printf("\n");

	const ProtobufCMessageDescriptor *d = base->descriptor;
	printf("Descriptor Magic: %d\n", d->magic );
	printf("            name: %s\n", d->name );
	printf("           sname: %s\n", d->short_name );
	printf("           cname: %s\n", d->c_name );
	printf("             pkg: %s\n", d->package_name );
	printf("              sz: %d\n", d->sizeof_message );
	printf("            rsv1: %p\n", d->reserved1);
	printf("            rsv2: %p\n", d->reserved2);
	printf("            rsv3: %p\n", d->reserved3);

	printf("\n");
	printf("fields: %d\n", d->n_fields );

	ProtobufCFieldDescriptor *fd = (ProtobufCFieldDescriptor *)d->fields;
	for( int i = 0; i < d->n_fields; i++ ) {
		printf("\n");
	        printf("       name: %s\n", fd[i].name );
	fflush(stdout);
		printf("        tag: %d\n", fd[i].id );
		printf("        typ: %d\n", fd[i].type );
		printf("   typ xtra: %p\n", fd[i].descriptor );
		printf("   q offset: %d\n", fd[i].quantifier_offset );
		printf("     offset: %d\n", fd[i].offset );
		printf("       rsv2: %p\n", fd[i].reserved2 );
		printf("       rsv3: %p\n", fd[i].reserved3 );
        fd[i].reserved2 = (void *)0x12345;
	fflush(stdout);
	}

}


int main( int argc, char *argv[] ) {

	Propaqm__Vitals v = PROPAQM__VITALS__INIT;
	Propaqm__Sensors w = PROPAQM__SENSORS__INIT;

    /*
	memset( &v, 0, sizeof(v) );
	memset( &w, 0, sizeof(w) );

	printf("initting vitals\n");
	propaqm__vitals__init( &v );

	printf("initting sensors\n");
	propaqm__sensors__init( &w );
    */

	printf("dumping...\n");

	// dumpModel( &v, &v.base );
	dumpModel( &w, &w.base );
}


