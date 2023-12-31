/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/bmp180.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "bmp180.pb-c.h"
void   bmp180__measurement__init
                     (Bmp180__Measurement         *message)
{
  static const Bmp180__Measurement init_value = BMP180__MEASUREMENT__INIT;
  *message = init_value;
}
size_t bmp180__measurement__get_packed_size
                     (const Bmp180__Measurement *message)
{
  assert(message->base.descriptor == &bmp180__measurement__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t bmp180__measurement__pack
                     (const Bmp180__Measurement *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &bmp180__measurement__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t bmp180__measurement__pack_to_buffer
                     (const Bmp180__Measurement *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &bmp180__measurement__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Bmp180__Measurement *
       bmp180__measurement__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Bmp180__Measurement *)
     protobuf_c_message_unpack (&bmp180__measurement__descriptor,
                                allocator, len, data);
}
void   bmp180__measurement__free_unpacked
                     (Bmp180__Measurement *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &bmp180__measurement__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor bmp180__measurement__field_descriptors[3] =
{
  {
    "tm",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(Bmp180__Measurement, tm),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "T",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(Bmp180__Measurement, t),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "P",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(Bmp180__Measurement, p),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned bmp180__measurement__field_indices_by_name[] = {
  2,   /* field[2] = P */
  1,   /* field[1] = T */
  0,   /* field[0] = tm */
};
static const ProtobufCIntRange bmp180__measurement__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor bmp180__measurement__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "bmp180.measurement",
  "Measurement",
  "Bmp180__Measurement",
  "bmp180",
  sizeof(Bmp180__Measurement),
  3,
  bmp180__measurement__field_descriptors,
  bmp180__measurement__field_indices_by_name,
  1,  bmp180__measurement__number_ranges,
  (ProtobufCMessageInit) bmp180__measurement__init,
  NULL,NULL,NULL    /* reserved[123] */
};
