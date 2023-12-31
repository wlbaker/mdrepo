/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/pista.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "model/pista.pb-c.h"
void   pista__connection__init
                     (Pista__Connection         *message)
{
  static const Pista__Connection init_value = PISTA__CONNECTION__INIT;
  *message = init_value;
}
size_t pista__connection__get_packed_size
                     (const Pista__Connection *message)
{
  assert(message->base.descriptor == &pista__connection__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t pista__connection__pack
                     (const Pista__Connection *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &pista__connection__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t pista__connection__pack_to_buffer
                     (const Pista__Connection *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &pista__connection__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Pista__Connection *
       pista__connection__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Pista__Connection *)
     protobuf_c_message_unpack (&pista__connection__descriptor,
                                allocator, len, data);
}
void   pista__connection__free_unpacked
                     (Pista__Connection *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &pista__connection__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor pista__connection__field_descriptors[1] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Pista__Connection, status),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned pista__connection__field_indices_by_name[] = {
  0,   /* field[0] = status */
};
static const ProtobufCIntRange pista__connection__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor pista__connection__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "pista.connection",
  "Connection",
  "Pista__Connection",
  "pista",
  sizeof(Pista__Connection),
  1,
  pista__connection__field_descriptors,
  pista__connection__field_indices_by_name,
  1,  pista__connection__number_ranges,
  (ProtobufCMessageInit) pista__connection__init,
  NULL,NULL,NULL    /* reserved[123] */
};
