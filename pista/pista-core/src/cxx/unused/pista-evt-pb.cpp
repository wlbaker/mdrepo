// ProtobufEventHandler...undefined!

#include <iostream>
#include <protobuf-c/protobuf-c.h>
#include "pista-cl.h"

extern "C" int protob_eventfunc( const struct pista_dev_inst *h, int event_typ, void *vp) {
	const ProtobufCMessage *m = (const ProtobufCMessage *)vp;
	const ProtobufCMessageDescriptor *d = m->descriptor;

    PistaEventHandler *event_h = (PistaEventHandler *)h->event_priv;

	size_t sz = protobuf_c_message_get_packed_size( m );
	uint8_t *out = new uint8_t[sz];

	protobuf_c_message_pack(m , out);
    int rc = event_h->event( event_typ, d->name, out );

	delete out;

	return rc;
}   

ProtobufEventHandler::ProtobufEventHandler() {
    std::cout << "pb fish in the water=" << this << std::endl;
    std::cout << "pb VERSION=" << protobuf_c_version() << std::endl;
}

int ProtobufEventHandler::event( int eventTyp, const char *name, void *data ) {
    std::cout << "PLEASE INSTALL EVENT HANDLER: " << name << std::endl;
}

void ProtobufEventHandler::attach( PistaDev *dev ) {
    std::cout << "pb attaching dev=" << this << std::endl;
    dev->attach( protob_eventfunc, this );
}


