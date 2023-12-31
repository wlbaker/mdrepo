/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/mccul.proto */

#ifndef PROTOBUF_C_model_2fmccul_2eproto__INCLUDED
#define PROTOBUF_C_model_2fmccul_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Mccul__McculSettings Mccul__McculSettings;
typedef struct _Mccul__McculIsensor Mccul__McculIsensor;
typedef struct _Mccul__McculFsensor Mccul__McculFsensor;


/* --- enums --- */


/* --- messages --- */

struct  _Mccul__McculSettings
{
  ProtobufCMessage base;
  int32_t hzz;
  int32_t rps;
  int32_t ms;
  int32_t gain;
  int32_t low_chan;
  int32_t high_chan;
};
#define MCCUL__MCCUL_SETTINGS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&mccul__mccul_settings__descriptor) \
    , 0, 0, 0, 0, 0, 0 }


struct  _Mccul__McculIsensor
{
  ProtobufCMessage base;
  int64_t tm;
  size_t n_ch0;
  int32_t *ch0;
  size_t n_ch1;
  int32_t *ch1;
  size_t n_ch2;
  int32_t *ch2;
  size_t n_ch3;
  int32_t *ch3;
  size_t n_ch4;
  int32_t *ch4;
  size_t n_ch5;
  int32_t *ch5;
  size_t n_ch6;
  int32_t *ch6;
  size_t n_ch7;
  int32_t *ch7;
  size_t n_ch8;
  int32_t *ch8;
  size_t n_ch9;
  int32_t *ch9;
  size_t n_ch10;
  int32_t *ch10;
  size_t n_ch11;
  int32_t *ch11;
  size_t n_ch12;
  int32_t *ch12;
  size_t n_ch13;
  int32_t *ch13;
  size_t n_ch14;
  int32_t *ch14;
  size_t n_ch15;
  int32_t *ch15;
};
#define MCCUL__MCCUL_ISENSOR__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&mccul__mccul_isensor__descriptor) \
    , 0, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL }


struct  _Mccul__McculFsensor
{
  ProtobufCMessage base;
  int64_t tm;
  size_t n_ch0;
  float *ch0;
  size_t n_ch1;
  float *ch1;
  size_t n_ch2;
  float *ch2;
  size_t n_ch3;
  float *ch3;
  size_t n_ch4;
  float *ch4;
  size_t n_ch5;
  float *ch5;
  size_t n_ch6;
  float *ch6;
  size_t n_ch7;
  float *ch7;
  size_t n_ch8;
  float *ch8;
  size_t n_ch9;
  float *ch9;
  size_t n_ch10;
  float *ch10;
  size_t n_ch11;
  float *ch11;
  size_t n_ch12;
  float *ch12;
  size_t n_ch13;
  float *ch13;
  size_t n_ch14;
  float *ch14;
  size_t n_ch15;
  float *ch15;
};
#define MCCUL__MCCUL_FSENSOR__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&mccul__mccul_fsensor__descriptor) \
    , 0, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL }


/* Mccul__McculSettings methods */
void   mccul__mccul_settings__init
                     (Mccul__McculSettings         *message);
size_t mccul__mccul_settings__get_packed_size
                     (const Mccul__McculSettings   *message);
size_t mccul__mccul_settings__pack
                     (const Mccul__McculSettings   *message,
                      uint8_t             *out);
size_t mccul__mccul_settings__pack_to_buffer
                     (const Mccul__McculSettings   *message,
                      ProtobufCBuffer     *buffer);
Mccul__McculSettings *
       mccul__mccul_settings__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   mccul__mccul_settings__free_unpacked
                     (Mccul__McculSettings *message,
                      ProtobufCAllocator *allocator);
/* Mccul__McculIsensor methods */
void   mccul__mccul_isensor__init
                     (Mccul__McculIsensor         *message);
size_t mccul__mccul_isensor__get_packed_size
                     (const Mccul__McculIsensor   *message);
size_t mccul__mccul_isensor__pack
                     (const Mccul__McculIsensor   *message,
                      uint8_t             *out);
size_t mccul__mccul_isensor__pack_to_buffer
                     (const Mccul__McculIsensor   *message,
                      ProtobufCBuffer     *buffer);
Mccul__McculIsensor *
       mccul__mccul_isensor__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   mccul__mccul_isensor__free_unpacked
                     (Mccul__McculIsensor *message,
                      ProtobufCAllocator *allocator);
/* Mccul__McculFsensor methods */
void   mccul__mccul_fsensor__init
                     (Mccul__McculFsensor         *message);
size_t mccul__mccul_fsensor__get_packed_size
                     (const Mccul__McculFsensor   *message);
size_t mccul__mccul_fsensor__pack
                     (const Mccul__McculFsensor   *message,
                      uint8_t             *out);
size_t mccul__mccul_fsensor__pack_to_buffer
                     (const Mccul__McculFsensor   *message,
                      ProtobufCBuffer     *buffer);
Mccul__McculFsensor *
       mccul__mccul_fsensor__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   mccul__mccul_fsensor__free_unpacked
                     (Mccul__McculFsensor *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Mccul__McculSettings_Closure)
                 (const Mccul__McculSettings *message,
                  void *closure_data);
typedef void (*Mccul__McculIsensor_Closure)
                 (const Mccul__McculIsensor *message,
                  void *closure_data);
typedef void (*Mccul__McculFsensor_Closure)
                 (const Mccul__McculFsensor *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor mccul__mccul_settings__descriptor;
extern const ProtobufCMessageDescriptor mccul__mccul_isensor__descriptor;
extern const ProtobufCMessageDescriptor mccul__mccul_fsensor__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_model_2fmccul_2eproto__INCLUDED */
