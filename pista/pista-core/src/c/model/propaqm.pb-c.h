/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: model/propaqm.proto */

#ifndef PROTOBUF_C_model_2fpropaqm_2eproto__INCLUDED
#define PROTOBUF_C_model_2fpropaqm_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Propaqm__Ident Propaqm__Ident;
typedef struct _Propaqm__Vitals Propaqm__Vitals;
typedef struct _Propaqm__Sensors Propaqm__Sensors;


/* --- enums --- */


/* --- messages --- */

struct  _Propaqm__Ident
{
  ProtobufCMessage base;
  /*
   *[9];
   */
  char *model;
  /*
   * [10];
   */
  char *serial_no;
};
#define PROPAQM__IDENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&propaqm__ident__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _Propaqm__Vitals
{
  ProtobufCMessage base;
  int64_t tm;
  int32_t sid;
  int32_t monitored_bits;
  int32_t alarm_bits;
  int32_t datastate_bits;
  /*
   * Temp_0
   */
  int32_t temp0;
  /*
   * Temp_1
   */
  int32_t temp1;
  /*
   * Temp_2
   */
  int32_t temp2;
  /*
   * Hr
   */
  int32_t hr;
  /*
   * Spo2
   */
  int32_t fico2;
  int32_t patmode;
  /*
   * 
   */
  int32_t spo2_spco;
  /*
   * 
   */
  int32_t spo2_spmet;
  /*
   * 
   */
  int32_t spo2_pvi;
  /*
   * 
   */
  int32_t spo2_pi;
  /*
   * 
   */
  int32_t spo2_spoc;
  /*
   * 
   */
  int32_t spo2_sphb;
  /*
   * 
   */
  int32_t spo2_pct;
  /*
   * Nibp.sys
   */
  int32_t nibp_sys;
  /*
   * Nibp.dia
   */
  int32_t nibp_dia;
  /*
   * Nipb.map
   */
  int32_t nibp_map;
  /*
   * etco2
   */
  int32_t etco2;
  /*
   * resp rate
   */
  int32_t resp;
  /*
   * Ibp_0.sys
   */
  int32_t ibp0_sys;
  /*
   * Ibp_0.dia
   */
  int32_t ibp0_dia;
  /*
   * Ibp_0.map
   */
  int32_t ibp0_map;
  /*
   * Ibp_1.sys
   */
  int32_t ibp1_sys;
  /*
   * Ibp_1.dia
   */
  int32_t ibp1_dia;
  /*
   * Ibp_1.map
   */
  int32_t ibp1_map;
  /*
   * Ibp_2.sys
   */
  int32_t ibp2_sys;
  /*
   * Ibp_2.dia
   */
  int32_t ibp2_dia;
  /*
   * Ibp_2.map
   */
  int32_t ibp2_map;
};
#define PROPAQM__VITALS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&propaqm__vitals__descriptor) \
    , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }


struct  _Propaqm__Sensors
{
  ProtobufCMessage base;
  int64_t tm;
  int32_t sid;
  size_t n_ecg;
  int32_t *ecg;
  size_t n_co2;
  int32_t *co2;
  size_t n_wf3;
  int32_t *wf3;
};
#define PROPAQM__SENSORS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&propaqm__sensors__descriptor) \
    , 0, 0, 0,NULL, 0,NULL, 0,NULL }


/* Propaqm__Ident methods */
void   propaqm__ident__init
                     (Propaqm__Ident         *message);
size_t propaqm__ident__get_packed_size
                     (const Propaqm__Ident   *message);
size_t propaqm__ident__pack
                     (const Propaqm__Ident   *message,
                      uint8_t             *out);
size_t propaqm__ident__pack_to_buffer
                     (const Propaqm__Ident   *message,
                      ProtobufCBuffer     *buffer);
Propaqm__Ident *
       propaqm__ident__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   propaqm__ident__free_unpacked
                     (Propaqm__Ident *message,
                      ProtobufCAllocator *allocator);
/* Propaqm__Vitals methods */
void   propaqm__vitals__init
                     (Propaqm__Vitals         *message);
size_t propaqm__vitals__get_packed_size
                     (const Propaqm__Vitals   *message);
size_t propaqm__vitals__pack
                     (const Propaqm__Vitals   *message,
                      uint8_t             *out);
size_t propaqm__vitals__pack_to_buffer
                     (const Propaqm__Vitals   *message,
                      ProtobufCBuffer     *buffer);
Propaqm__Vitals *
       propaqm__vitals__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   propaqm__vitals__free_unpacked
                     (Propaqm__Vitals *message,
                      ProtobufCAllocator *allocator);
/* Propaqm__Sensors methods */
void   propaqm__sensors__init
                     (Propaqm__Sensors         *message);
size_t propaqm__sensors__get_packed_size
                     (const Propaqm__Sensors   *message);
size_t propaqm__sensors__pack
                     (const Propaqm__Sensors   *message,
                      uint8_t             *out);
size_t propaqm__sensors__pack_to_buffer
                     (const Propaqm__Sensors   *message,
                      ProtobufCBuffer     *buffer);
Propaqm__Sensors *
       propaqm__sensors__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   propaqm__sensors__free_unpacked
                     (Propaqm__Sensors *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Propaqm__Ident_Closure)
                 (const Propaqm__Ident *message,
                  void *closure_data);
typedef void (*Propaqm__Vitals_Closure)
                 (const Propaqm__Vitals *message,
                  void *closure_data);
typedef void (*Propaqm__Sensors_Closure)
                 (const Propaqm__Sensors *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern ProtobufCMessageDescriptor propaqm__ident__descriptor;
extern ProtobufCMessageDescriptor propaqm__vitals__descriptor;
extern ProtobufCMessageDescriptor propaqm__sensors__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_model_2fpropaqm_2eproto__INCLUDED */
