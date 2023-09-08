
// #include <ctime>
#include <iostream>
#include <unistd.h>
#include <protobuf-c/protobuf-c.h>
// #include <iomanip>
// #include "boost/asio.hpp"

#include "pista-cl.h"

using namespace std;


// #include <stdlib.h>	/* for malloc, free */
// #include <string.h>	/* for strcmp, strlen, memcpy, memmove, memset */

#include "protobuf-c/protobuf-c.h"

// #define TRUE				1
// #define FALSE				0

#define PROTOBUF_C__ASSERT_NOT_REACHED() assert(0)

// #define MAX_UINT64_ENCODED_SIZE		10


#ifndef PROTOBUF_C_FIELD_FLAG_ONEOF
#define PROTOBUF_C_FIELD_FLAG_ONEOF  (1 << 2)
#endif

/**@}*/



/**
 * \defgroup packbuf message_repack() implementation
 *
 * Routines mainly used by message_pack_to_java().
 *
 * \ingroup internal
 * @{
 */

/**
 * Pack a required field to a virtual buffer.
 *
 */
static void required_field_repack(
	const ProtobufCFieldDescriptor *field,  /// protobuf c field descriptor
	const void *member                      /// data to be packed
)
{

	cout << field->name << " ";
	switch (field->type) {
	case PROTOBUF_C_TYPE_SINT32:
		cout << "SINT32: " << *(const int32_t *) member << endl;
		break;
	case PROTOBUF_C_TYPE_INT32:
		cout << "INT32: " << *(const uint32_t *) member << endl;
		break;
	case PROTOBUF_C_TYPE_UINT32:
	case PROTOBUF_C_TYPE_ENUM:
		cout << "UINT32: " << *(const uint32_t *) member << endl;
		break;
	case PROTOBUF_C_TYPE_SINT64:
		cout << "SINT64: " << *(const int64_t *) member << endl;
		break;
	case PROTOBUF_C_TYPE_INT64:
	case PROTOBUF_C_TYPE_UINT64:
		cout << "INT64: " << *(const uint64_t *) member << endl;
		break;
	case PROTOBUF_C_TYPE_SFIXED32:
	case PROTOBUF_C_TYPE_FIXED32:
	case PROTOBUF_C_TYPE_FLOAT:
		cout << "FIXED32 or FLOAT: " << *(const uint32_t *) member << endl;
		// buffer->append(buffer, rv, scratch);
		break;
	case PROTOBUF_C_TYPE_SFIXED64:
	case PROTOBUF_C_TYPE_FIXED64:
	case PROTOBUF_C_TYPE_DOUBLE:
		cout << "FIXED64 or DOUBLE: " << *(const uint64_t *) member << endl;
		// buffer->append(buffer, rv, scratch);
		break;
	case PROTOBUF_C_TYPE_BOOL:
		cout << "BOOL: " << *(const protobuf_c_boolean *) member << endl;
		// buffer->append(buffer, rv, scratch);
		break;
	case PROTOBUF_C_TYPE_STRING: {
		const char *str = *(char *const *) member;
		// size_t sublen = str ? strlen(str) : 0;

		cout << "STR: " << str << endl;
		break;
	}
/* FIXME: not ready for this
	case PROTOBUF_C_TYPE_BYTES: {
		const ProtobufCBinaryData *bd = ((const ProtobufCBinaryData *) member);
		size_t sublen = bd->len;

		scratch[0] |= PROTOBUF_C_WIRE_TYPE_LENGTH_PREFIXED;
		rv += uint32_pack(sublen, scratch + rv);
		// buffer->append(buffer, rv, scratch);
		// buffer->append(buffer, sublen, bd->data);
		rv += sublen;
		break;
	}
	case PROTOBUF_C_TYPE_MESSAGE: {
		uint8_t simple_buffer_scratch[256];
		size_t sublen;
		const ProtobufCMessage *msg = *(ProtobufCMessage * const *) member;
		ProtobufCBufferSimple simple_buffer =
			PROTOBUF_C_BUFFER_SIMPLE_INIT(simple_buffer_scratch);

		scratch[0] |= PROTOBUF_C_WIRE_TYPE_LENGTH_PREFIXED;
		if (msg == NULL)
			sublen = 0;
		else
			sublen = protobuf_c_message_pack_to_buffer(msg, &simple_buffer.base);
		rv += uint32_pack(sublen, scratch + rv);
		// buffer->append(buffer, rv, scratch);
		// buffer->append(buffer, sublen, simple_buffer.data);
		rv += sublen;
		PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&simple_buffer);
		break;
	}
*/
	default:
		PROTOBUF_C__ASSERT_NOT_REACHED();
	}

	return;
}

/**
 * Pack a oneof field to a buffer. Only packs the field that is selected by the case enum.
 *
 * \param field
 *      Field descriptor.
 * \param oneof_case
 *      A pointer to the case enum that selects the field in the oneof.
 * \param member
 *      The element to be packed.
 * \param[out] buffer
 *      Virtual buffer to append data to.
 * \return
 *      Number of bytes serialised to `buffer`.
 */
static void oneof_field_repack(const ProtobufCFieldDescriptor *field,
			   const uint32_t *oneof_case,
			   const void *member)
{
	if (*oneof_case == field->id) {
		if (field->type == PROTOBUF_C_TYPE_MESSAGE ||
		    field->type == PROTOBUF_C_TYPE_STRING)
		{
			const void *ptr = *(const void *const *) member;
			if (ptr == NULL || ptr == field->default_value)
				return;
		}
	} else {
		return;
	}

	required_field_repack(field, member);
}

/**
 * Pack an optional field to a buffer.
 *
 * \param field
 *      Field descriptor.
 * \param has
 *      Whether the field is set.
 * \param member
 *      The element to be packed.
 * \param[out] buffer
 *      Virtual buffer to append data to.
 * \return
 *      Number of bytes serialised to `buffer`.
 */
static void optional_field_repack(const ProtobufCFieldDescriptor *field,
			      const protobuf_c_boolean *has,
			      const void *member)
{
	if (field->type == PROTOBUF_C_TYPE_MESSAGE ||
	    field->type == PROTOBUF_C_TYPE_STRING)
	{
		const void *ptr = *(const void *const *) member;
		if (ptr == NULL || ptr == field->default_value)
			return;
	} else {
		if (!*has)
			return;
	}
	required_field_repack(field, member);
}

/**
 * Given a field type, return the in-memory size.
 *
 * \todo Implement as a table lookup.
 *
 * \param type
 *      Field type.
 * \return
 *      Size of the field.
 */
static inline size_t sizeof_elt_in_repeated_array(ProtobufCType type)
{
	switch (type) {
	case PROTOBUF_C_TYPE_SINT32:
	case PROTOBUF_C_TYPE_INT32:
	case PROTOBUF_C_TYPE_UINT32:
	case PROTOBUF_C_TYPE_SFIXED32:
	case PROTOBUF_C_TYPE_FIXED32:
	case PROTOBUF_C_TYPE_FLOAT:
	case PROTOBUF_C_TYPE_ENUM:
		return 4;
	case PROTOBUF_C_TYPE_SINT64:
	case PROTOBUF_C_TYPE_INT64:
	case PROTOBUF_C_TYPE_UINT64:
	case PROTOBUF_C_TYPE_SFIXED64:
	case PROTOBUF_C_TYPE_FIXED64:
	case PROTOBUF_C_TYPE_DOUBLE:
		return 8;
	case PROTOBUF_C_TYPE_BOOL:
		return sizeof(protobuf_c_boolean);
	case PROTOBUF_C_TYPE_STRING:
	case PROTOBUF_C_TYPE_MESSAGE:
		return sizeof(void *);
	case PROTOBUF_C_TYPE_BYTES:
		return sizeof(ProtobufCBinaryData);
	}
	PROTOBUF_C__ASSERT_NOT_REACHED();
	return 0;
}

static void repeated_field_repack(const ProtobufCFieldDescriptor *field,
			      unsigned count, const void *member)
{

	if (count > 0) {

		// size_t siz = sizeof_elt_in_repeated_array(field->type);
		char *array = *(char * const *) member;
		// for (unsigned i = 0; i < 5; i++) {
		//		required_field_repack(field, array);
		//		array += siz;
		// }
		// array = *(char * const *) member;

		switch (field->type) {
		case PROTOBUF_C_TYPE_SINT32: {
				cout << field->name << " SINT32 ARR: " << *(const int32_t *) array;
				const int32_t *parr = (const int32_t *)array;
				for( unsigned i = 0; i < 5 && i < count ; i++ ) {
	 				cout << "  " << parr[i];
				}
	 			cout << endl;
			}
			break;
		case PROTOBUF_C_TYPE_INT32: {
				cout <<  field->name << " INT32  ARR: " << *(const uint32_t *)array;
				const uint32_t *parr = (const uint32_t *)array;
				for( unsigned i = 0; i < 5 && i < count ; i++ ) {
	 				cout << "  " << parr[i];
				}
	 			cout << endl;
			}
			break;
		default:
			cout << "FIELD TYP NOT HANDLE: " << field->type << endl;
		}
	}
	return;
}




void message_repack_to_java(const ProtobufCMessage *message)
{
	unsigned i;

	const ProtobufCMessageDescriptor *d = message->descriptor;

	cout << "name=" << d->name << endl;
	cout << "short_name=" << d->short_name << endl;
	cout << "c_name=" << d->c_name << endl;
	cout << "package_name=" << d->package_name << endl;

	// ASSERT_IS_MESSAGE(message);
	//
	for (i = 0; i < d->n_fields; i++) {

		const ProtobufCFieldDescriptor *field = d->fields + i;
		const void *member = ((const char *) message) + field->offset;
		const void *qmember = ((const char *) message) + field->quantifier_offset;
		if (field->label == PROTOBUF_C_LABEL_REQUIRED) {
			required_field_repack(field, member);
		} else if (field->label == PROTOBUF_C_LABEL_OPTIONAL) {
			if (0 != (field->flags & PROTOBUF_C_FIELD_FLAG_ONEOF)) {
				oneof_field_repack( field, (const uint32_t *)qmember, member);
			} else {
				optional_field_repack( field, (const protobuf_c_boolean *)qmember, member);
			}
		} else {
			repeated_field_repack( field, *(const size_t *) qmember, member);
		}
	}

	return;
}

class DumpingEventHandler : public PistaEventHandler {
	virtual int event (int eventTyp, const char *name, void *message ) {
		cout << "got data block [" << name << "/" << eventTyp << "]: " << message << endl;
		const ProtobufCMessage *m = (const ProtobufCMessage*)message;

		message_repack_to_java( m );
		return 0;
	}
};

int main(int argc, char* argv[])
{
	const char *driver_name="Labjack U3";
	bool is_serial = false;

	cout << "creating pista context" << endl;
	PistaCl &cl = PistaCl::getInstance( );
	cout << "creating driver: " << driver_name << endl;
	PistaDriver *driver = cl.driver(driver_name);

	cout << "creating device" << endl;
	PistaDev *dev = driver->allocate();

	PistaEventHandler *h = new DumpingEventHandler();

	h->attach(dev);
	dev->connect();

	if( is_serial ) {
		cout << "SYNC_READING" << endl;
		cout << "============" << endl;

    	PistaCommHandler *lsp = new LspCOMM("/dev/ttyUSB0");
    	dev->attach( lsp );
    	lsp->open();
    	lsp->config( 115200,8,1,'N');
    	lsp->test( dev );
    	lsp->close( );
	} else {

		cout << "starting wait" << endl;
		for(int i = 0; i < 2; i++ ) {
			sleep(1);
			dev->tick();
			cout << "***pack" << endl;
			dev->tick();
			cout << "** pack" << endl;
			dev->tick();
			cout << "** pack" << endl;
		}
		cout << "finished wait" << endl;

	}
	dev->disconnect();
	driver->release( dev );
}

