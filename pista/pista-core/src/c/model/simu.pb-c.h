/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/simu.proto */

#ifndef PROTOBUF_C_model_2fsimu_2eproto__INCLUDED
#define PROTOBUF_C_model_2fsimu_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Simu__SimuSettings Simu__SimuSettings;
typedef struct _Simu__SimuVitals Simu__SimuVitals;
typedef struct _Simu__SimuWaveform Simu__SimuWaveform;


/* --- enums --- */


/* --- messages --- */

struct  _Simu__SimuSettings
{
  ProtobufCMessage base;
  int64_t tm;
  int32_t hzz;
  int32_t rps;
  int32_t ms;
};
#define SIMU__SIMU_SETTINGS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&simu__simu_settings__descriptor) \
    , 0, 0, 0, 0 }


struct  _Simu__SimuVitals
{
  ProtobufCMessage base;
  int64_t tm;
  int32_t v0;
  int32_t v1;
  int32_t v2;
  int32_t v3;
};
#define SIMU__SIMU_VITALS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&simu__simu_vitals__descriptor) \
    , 0, 0, 0, 0, 0 }


struct  _Simu__SimuWaveform
{
  ProtobufCMessage base;
  int64_t tm;
  size_t n_w0;
  int32_t *w0;
  size_t n_w1;
  int32_t *w1;
  size_t n_w2;
  float *w2;
  size_t n_w3;
  float *w3;
};
#define SIMU__SIMU_WAVEFORM__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&simu__simu_waveform__descriptor) \
    , 0, 0,NULL, 0,NULL, 0,NULL, 0,NULL }


/* Simu__SimuSettings methods */
void   simu__simu_settings__init
                     (Simu__SimuSettings         *message);
size_t simu__simu_settings__get_packed_size
                     (const Simu__SimuSettings   *message);
size_t simu__simu_settings__pack
                     (const Simu__SimuSettings   *message,
                      uint8_t             *out);
size_t simu__simu_settings__pack_to_buffer
                     (const Simu__SimuSettings   *message,
                      ProtobufCBuffer     *buffer);
Simu__SimuSettings *
       simu__simu_settings__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   simu__simu_settings__free_unpacked
                     (Simu__SimuSettings *message,
                      ProtobufCAllocator *allocator);
/* Simu__SimuVitals methods */
void   simu__simu_vitals__init
                     (Simu__SimuVitals         *message);
size_t simu__simu_vitals__get_packed_size
                     (const Simu__SimuVitals   *message);
size_t simu__simu_vitals__pack
                     (const Simu__SimuVitals   *message,
                      uint8_t             *out);
size_t simu__simu_vitals__pack_to_buffer
                     (const Simu__SimuVitals   *message,
                      ProtobufCBuffer     *buffer);
Simu__SimuVitals *
       simu__simu_vitals__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   simu__simu_vitals__free_unpacked
                     (Simu__SimuVitals *message,
                      ProtobufCAllocator *allocator);
/* Simu__SimuWaveform methods */
void   simu__simu_waveform__init
                     (Simu__SimuWaveform         *message);
size_t simu__simu_waveform__get_packed_size
                     (const Simu__SimuWaveform   *message);
size_t simu__simu_waveform__pack
                     (const Simu__SimuWaveform   *message,
                      uint8_t             *out);
size_t simu__simu_waveform__pack_to_buffer
                     (const Simu__SimuWaveform   *message,
                      ProtobufCBuffer     *buffer);
Simu__SimuWaveform *
       simu__simu_waveform__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   simu__simu_waveform__free_unpacked
                     (Simu__SimuWaveform *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Simu__SimuSettings_Closure)
                 (const Simu__SimuSettings *message,
                  void *closure_data);
typedef void (*Simu__SimuVitals_Closure)
                 (const Simu__SimuVitals *message,
                  void *closure_data);
typedef void (*Simu__SimuWaveform_Closure)
                 (const Simu__SimuWaveform *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor simu__simu_settings__descriptor;
extern const ProtobufCMessageDescriptor simu__simu_vitals__descriptor;
extern const ProtobufCMessageDescriptor simu__simu_waveform__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_model_2fsimu_2eproto__INCLUDED */
