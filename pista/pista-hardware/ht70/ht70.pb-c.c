/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/ht70.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ht70.pb-c.h"
void   ht70__ident__init
                     (Ht70__Ident         *message)
{
  static const Ht70__Ident init_value = HT70__IDENT__INIT;
  *message = init_value;
}
size_t ht70__ident__get_packed_size
                     (const Ht70__Ident *message)
{
  assert(message->base.descriptor == &ht70__ident__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ht70__ident__pack
                     (const Ht70__Ident *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ht70__ident__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ht70__ident__pack_to_buffer
                     (const Ht70__Ident *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ht70__ident__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ht70__Ident *
       ht70__ident__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ht70__Ident *)
     protobuf_c_message_unpack (&ht70__ident__descriptor,
                                allocator, len, data);
}
void   ht70__ident__free_unpacked
                     (Ht70__Ident *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ht70__ident__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ht70__status__init
                     (Ht70__Status         *message)
{
  static const Ht70__Status init_value = HT70__STATUS__INIT;
  *message = init_value;
}
size_t ht70__status__get_packed_size
                     (const Ht70__Status *message)
{
  assert(message->base.descriptor == &ht70__status__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ht70__status__pack
                     (const Ht70__Status *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ht70__status__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ht70__status__pack_to_buffer
                     (const Ht70__Status *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ht70__status__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ht70__Status *
       ht70__status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ht70__Status *)
     protobuf_c_message_unpack (&ht70__status__descriptor,
                                allocator, len, data);
}
void   ht70__status__free_unpacked
                     (Ht70__Status *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ht70__status__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ht70__breath__init
                     (Ht70__Breath         *message)
{
  static const Ht70__Breath init_value = HT70__BREATH__INIT;
  *message = init_value;
}
size_t ht70__breath__get_packed_size
                     (const Ht70__Breath *message)
{
  assert(message->base.descriptor == &ht70__breath__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ht70__breath__pack
                     (const Ht70__Breath *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ht70__breath__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ht70__breath__pack_to_buffer
                     (const Ht70__Breath *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ht70__breath__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ht70__Breath *
       ht70__breath__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ht70__Breath *)
     protobuf_c_message_unpack (&ht70__breath__descriptor,
                                allocator, len, data);
}
void   ht70__breath__free_unpacked
                     (Ht70__Breath *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ht70__breath__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ht70__alarms__init
                     (Ht70__Alarms         *message)
{
  static const Ht70__Alarms init_value = HT70__ALARMS__INIT;
  *message = init_value;
}
size_t ht70__alarms__get_packed_size
                     (const Ht70__Alarms *message)
{
  assert(message->base.descriptor == &ht70__alarms__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ht70__alarms__pack
                     (const Ht70__Alarms *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ht70__alarms__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ht70__alarms__pack_to_buffer
                     (const Ht70__Alarms *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ht70__alarms__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ht70__Alarms *
       ht70__alarms__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ht70__Alarms *)
     protobuf_c_message_unpack (&ht70__alarms__descriptor,
                                allocator, len, data);
}
void   ht70__alarms__free_unpacked
                     (Ht70__Alarms *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ht70__alarms__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ht70__sensors__init
                     (Ht70__Sensors         *message)
{
  static const Ht70__Sensors init_value = HT70__SENSORS__INIT;
  *message = init_value;
}
size_t ht70__sensors__get_packed_size
                     (const Ht70__Sensors *message)
{
  assert(message->base.descriptor == &ht70__sensors__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ht70__sensors__pack
                     (const Ht70__Sensors *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ht70__sensors__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ht70__sensors__pack_to_buffer
                     (const Ht70__Sensors *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ht70__sensors__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ht70__Sensors *
       ht70__sensors__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ht70__Sensors *)
     protobuf_c_message_unpack (&ht70__sensors__descriptor,
                                allocator, len, data);
}
void   ht70__sensors__free_unpacked
                     (Ht70__Sensors *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ht70__sensors__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ht70__ident__field_descriptors[7] =
{
  {
    "model",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, model),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "serial_no",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, serial_no),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cpu_id",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, cpu_id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "adapter_id",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, adapter_id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pim_id",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, pim_id),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "spm_model",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, spm_model),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "spm_serial",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ht70__Ident, spm_serial),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ht70__ident__field_indices_by_name[] = {
  3,   /* field[3] = adapter_id */
  2,   /* field[2] = cpu_id */
  0,   /* field[0] = model */
  4,   /* field[4] = pim_id */
  1,   /* field[1] = serial_no */
  5,   /* field[5] = spm_model */
  6,   /* field[6] = spm_serial */
};
static const ProtobufCIntRange ht70__ident__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 7 }
};
const ProtobufCMessageDescriptor ht70__ident__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ht70.ident",
  "Ident",
  "Ht70__Ident",
  "ht70",
  sizeof(Ht70__Ident),
  7,
  ht70__ident__field_descriptors,
  ht70__ident__field_indices_by_name,
  1,  ht70__ident__number_ranges,
  (ProtobufCMessageInit) ht70__ident__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ht70__status__field_descriptors[27] =
{
  {
    "MODE",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, mode),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MVOLprhi",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, mvolprhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MVOLprlo",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, mvolprlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAWprhi",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, ppawprhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAWprlo",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, ppawprlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "RATEprhi",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, rateprhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "APINTVL",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, apintvl),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2prhi",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, fio2prhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2prlo",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, fio2prlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ALVOL",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, alvol),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "TVOLprcn",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, tvolprcn),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAWprcn",
    12,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, ppawprcn),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "TI",
    13,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, ti),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "RATEprcn",
    14,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, rateprcn),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "TRIG",
    15,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, trig),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PSprcn",
    16,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, psprcn),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PEEPprcn",
    17,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, peepprcn),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PFLOW",
    18,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, pflow),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FLOWTrig",
    19,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, flowtrig),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "SLOPE",
    20,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, slope),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PSeThresh",
    21,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, psethresh),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PSmaxTI",
    22,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, psmaxti),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "WAVE",
    23,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, wave),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BIASFLOW",
    24,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, biasflow),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NIV",
    25,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, niv),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NMpr",
    26,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, nmpr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PCVMODE",
    27,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Status, pcvmode),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ht70__status__field_indices_by_name[] = {
  9,   /* field[9] = ALVOL */
  6,   /* field[6] = APINTVL */
  23,   /* field[23] = BIASFLOW */
  7,   /* field[7] = FIO2prhi */
  8,   /* field[8] = FIO2prlo */
  18,   /* field[18] = FLOWTrig */
  0,   /* field[0] = MODE */
  1,   /* field[1] = MVOLprhi */
  2,   /* field[2] = MVOLprlo */
  24,   /* field[24] = NIV */
  25,   /* field[25] = NMpr */
  26,   /* field[26] = PCVMODE */
  16,   /* field[16] = PEEPprcn */
  17,   /* field[17] = PFLOW */
  11,   /* field[11] = PPAWprcn */
  3,   /* field[3] = PPAWprhi */
  4,   /* field[4] = PPAWprlo */
  20,   /* field[20] = PSeThresh */
  21,   /* field[21] = PSmaxTI */
  15,   /* field[15] = PSprcn */
  13,   /* field[13] = RATEprcn */
  5,   /* field[5] = RATEprhi */
  19,   /* field[19] = SLOPE */
  12,   /* field[12] = TI */
  14,   /* field[14] = TRIG */
  10,   /* field[10] = TVOLprcn */
  22,   /* field[22] = WAVE */
};
static const ProtobufCIntRange ht70__status__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 27 }
};
const ProtobufCMessageDescriptor ht70__status__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ht70.status",
  "Status",
  "Ht70__Status",
  "ht70",
  sizeof(Ht70__Status),
  27,
  ht70__status__field_descriptors,
  ht70__status__field_indices_by_name,
  1,  ht70__status__number_ranges,
  (ProtobufCMessageInit) ht70__status__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ht70__breath__field_descriptors[11] =
{
  {
    "TVOL",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, tvol),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MVOL",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, mvol),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "RATE",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, rate),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAW",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, ppaw),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MAP",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, map),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PEEP",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, peep),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, fio2),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PFLOW",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, pflow),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "I2E",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, i2e),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "O2CylTime",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, o2cyltime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BATTIME",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Breath, battime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ht70__breath__field_indices_by_name[] = {
  10,   /* field[10] = BATTIME */
  6,   /* field[6] = FIO2 */
  8,   /* field[8] = I2E */
  4,   /* field[4] = MAP */
  1,   /* field[1] = MVOL */
  9,   /* field[9] = O2CylTime */
  5,   /* field[5] = PEEP */
  7,   /* field[7] = PFLOW */
  3,   /* field[3] = PPAW */
  2,   /* field[2] = RATE */
  0,   /* field[0] = TVOL */
};
static const ProtobufCIntRange ht70__breath__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 11 }
};
const ProtobufCMessageDescriptor ht70__breath__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ht70.breath",
  "Breath",
  "Ht70__Breath",
  "ht70",
  sizeof(Ht70__Breath),
  11,
  ht70__breath__field_descriptors,
  ht70__breath__field_indices_by_name,
  1,  ht70__breath__number_ranges,
  (ProtobufCMessageInit) ht70__breath__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ht70__alarms__field_descriptors[25] =
{
  {
    "SYSFAULT",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, sysfault),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BATTFail",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, battfail),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PWRFail",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, pwrfail),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "OCCLUSIONsust",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, occlusionsust),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PROX",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, prox),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAWlo",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, ppawlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "OCCLUSION",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, occlusion),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "APNEA",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, apnea),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MVOLlo",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, mvollo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MVOLhi",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, mvolhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PCVNR",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, pcvnr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2lo",
    12,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, fio2lo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PEEPlo",
    13,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, peeplo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PPAWhi",
    14,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, ppawhi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BATTlo",
    15,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, battlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ExtBATTlo",
    16,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, extbattlo),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "VTEhi",
    17,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, vtehi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2hi",
    18,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, fio2hi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PEEPhi",
    19,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, peephi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BATTon",
    20,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, batton),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BATTERY",
    21,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, battery),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "RATEhi",
    22,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, ratehi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FIO2Sensor",
    23,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, fio2sensor),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "BACKUP",
    24,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, backup),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NOPWR",
    25,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ht70__Alarms, nopwr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ht70__alarms__field_indices_by_name[] = {
  7,   /* field[7] = APNEA */
  23,   /* field[23] = BACKUP */
  20,   /* field[20] = BATTERY */
  1,   /* field[1] = BATTFail */
  14,   /* field[14] = BATTlo */
  19,   /* field[19] = BATTon */
  15,   /* field[15] = ExtBATTlo */
  22,   /* field[22] = FIO2Sensor */
  17,   /* field[17] = FIO2hi */
  11,   /* field[11] = FIO2lo */
  9,   /* field[9] = MVOLhi */
  8,   /* field[8] = MVOLlo */
  24,   /* field[24] = NOPWR */
  6,   /* field[6] = OCCLUSION */
  3,   /* field[3] = OCCLUSIONsust */
  10,   /* field[10] = PCVNR */
  18,   /* field[18] = PEEPhi */
  12,   /* field[12] = PEEPlo */
  13,   /* field[13] = PPAWhi */
  5,   /* field[5] = PPAWlo */
  4,   /* field[4] = PROX */
  2,   /* field[2] = PWRFail */
  21,   /* field[21] = RATEhi */
  0,   /* field[0] = SYSFAULT */
  16,   /* field[16] = VTEhi */
};
static const ProtobufCIntRange ht70__alarms__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 25 }
};
const ProtobufCMessageDescriptor ht70__alarms__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ht70.alarms",
  "Alarms",
  "Ht70__Alarms",
  "ht70",
  sizeof(Ht70__Alarms),
  25,
  ht70__alarms__field_descriptors,
  ht70__alarms__field_indices_by_name,
  1,  ht70__alarms__number_ranges,
  (ProtobufCMessageInit) ht70__alarms__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ht70__sensors__field_descriptors[2] =
{
  {
    "PAW",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_INT32,
    offsetof(Ht70__Sensors, n_pawwave),
    offsetof(Ht70__Sensors, pawwave),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FLOW",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_INT32,
    offsetof(Ht70__Sensors, n_flowwave),
    offsetof(Ht70__Sensors, flowwave),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ht70__sensors__field_indices_by_name[] = {
  1,   /* field[1] = FLOWwave */
  0,   /* field[0] = PAWwave */
};
static const ProtobufCIntRange ht70__sensors__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ht70__sensors__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ht70.sensors",
  "Sensors",
  "Ht70__Sensors",
  "ht70",
  sizeof(Ht70__Sensors),
  2,
  ht70__sensors__field_descriptors,
  ht70__sensors__field_indices_by_name,
  1,  ht70__sensors__number_ranges,
  (ProtobufCMessageInit) ht70__sensors__init,
  NULL,NULL,NULL    /* reserved[123] */
};
