

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from common.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef commonPlugin_1183388197_h
#define commonPlugin_1183388197_h

#include "common.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace ice {

    #define OCTETPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define OCTETPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define OCTETPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define OCTETPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define OCTETPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern OCTET*
    OCTETPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern OCTET*
    OCTETPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern OCTET*
    OCTETPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    OCTETPluginSupport_copy_data(
        OCTET *out,
        const OCTET *in);

    NDDSUSERDllExport extern void 
    OCTETPluginSupport_destroy_data_w_params(
        OCTET *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    OCTETPluginSupport_destroy_data_ex(
        OCTET *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    OCTETPluginSupport_destroy_data(
        OCTET *sample);

    NDDSUSERDllExport extern void 
    OCTETPluginSupport_print_data(
        const OCTET *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    OCTETPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        OCTET *out,
        const OCTET *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    OCTETPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const OCTET *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    OCTETPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        OCTET *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    OCTETPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    OCTETPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    OCTETPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    OCTETPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    OCTETPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const OCTET * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    OCTETPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    OCTETPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    OCTETPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    OCTETPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const OCTET *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    OCTETPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        OCTET * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    OCTETPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        OCTET *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INTU8Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INTU8Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INTU8Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INTU8Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INTU8Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INTU8*
    INTU8PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INTU8*
    INTU8PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INTU8*
    INTU8PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INTU8PluginSupport_copy_data(
        INTU8 *out,
        const INTU8 *in);

    NDDSUSERDllExport extern void 
    INTU8PluginSupport_destroy_data_w_params(
        INTU8 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INTU8PluginSupport_destroy_data_ex(
        INTU8 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INTU8PluginSupport_destroy_data(
        INTU8 *sample);

    NDDSUSERDllExport extern void 
    INTU8PluginSupport_print_data(
        const INTU8 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU8Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU8 *out,
        const INTU8 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU8Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INTU8 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU8Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU8 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU8Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INTU8Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INTU8Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU8Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INTU8Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INTU8 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INTU8Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INTU8Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU8Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INTU8Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INTU8 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU8Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU8 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU8Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INTU8 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INT16Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INT16Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INT16Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INT16Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INT16Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INT16*
    INT16PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INT16*
    INT16PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INT16*
    INT16PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INT16PluginSupport_copy_data(
        INT16 *out,
        const INT16 *in);

    NDDSUSERDllExport extern void 
    INT16PluginSupport_destroy_data_w_params(
        INT16 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INT16PluginSupport_destroy_data_ex(
        INT16 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INT16PluginSupport_destroy_data(
        INT16 *sample);

    NDDSUSERDllExport extern void 
    INT16PluginSupport_print_data(
        const INT16 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INT16Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT16 *out,
        const INT16 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INT16Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INT16 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INT16Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT16 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INT16Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INT16Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INT16Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INT16Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INT16Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INT16 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INT16Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INT16Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INT16Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INT16Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INT16 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INT16Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT16 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INT16Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INT16 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INTU16Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INTU16Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INTU16Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INTU16Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INTU16Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INTU16*
    INTU16PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INTU16*
    INTU16PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INTU16*
    INTU16PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INTU16PluginSupport_copy_data(
        INTU16 *out,
        const INTU16 *in);

    NDDSUSERDllExport extern void 
    INTU16PluginSupport_destroy_data_w_params(
        INTU16 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INTU16PluginSupport_destroy_data_ex(
        INTU16 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INTU16PluginSupport_destroy_data(
        INTU16 *sample);

    NDDSUSERDllExport extern void 
    INTU16PluginSupport_print_data(
        const INTU16 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU16Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU16 *out,
        const INTU16 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU16Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INTU16 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU16Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU16 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU16Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INTU16Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INTU16Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU16Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INTU16Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INTU16 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INTU16Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INTU16Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU16Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INTU16Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INTU16 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU16Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU16 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU16Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INTU16 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INT32Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INT32Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INT32Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INT32Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INT32Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INT32*
    INT32PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INT32*
    INT32PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INT32*
    INT32PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INT32PluginSupport_copy_data(
        INT32 *out,
        const INT32 *in);

    NDDSUSERDllExport extern void 
    INT32PluginSupport_destroy_data_w_params(
        INT32 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INT32PluginSupport_destroy_data_ex(
        INT32 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INT32PluginSupport_destroy_data(
        INT32 *sample);

    NDDSUSERDllExport extern void 
    INT32PluginSupport_print_data(
        const INT32 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INT32Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT32 *out,
        const INT32 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INT32Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INT32 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INT32Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT32 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INT32Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INT32Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INT32Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INT32Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INT32Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INT32 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INT32Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INT32Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INT32Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INT32Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INT32 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INT32Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INT32 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INT32Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INT32 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INTU32Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INTU32Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INTU32Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INTU32Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INTU32Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INTU32*
    INTU32PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INTU32*
    INTU32PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INTU32*
    INTU32PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INTU32PluginSupport_copy_data(
        INTU32 *out,
        const INTU32 *in);

    NDDSUSERDllExport extern void 
    INTU32PluginSupport_destroy_data_w_params(
        INTU32 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INTU32PluginSupport_destroy_data_ex(
        INTU32 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INTU32PluginSupport_destroy_data(
        INTU32 *sample);

    NDDSUSERDllExport extern void 
    INTU32PluginSupport_print_data(
        const INTU32 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU32Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU32 *out,
        const INTU32 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU32Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INTU32 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU32Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU32 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU32Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INTU32Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INTU32Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU32Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INTU32Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INTU32 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INTU32Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INTU32Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU32Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INTU32Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INTU32 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU32Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU32 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU32Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INTU32 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define INTU64Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define INTU64Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define INTU64Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define INTU64Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define INTU64Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern INTU64*
    INTU64PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern INTU64*
    INTU64PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern INTU64*
    INTU64PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    INTU64PluginSupport_copy_data(
        INTU64 *out,
        const INTU64 *in);

    NDDSUSERDllExport extern void 
    INTU64PluginSupport_destroy_data_w_params(
        INTU64 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    INTU64PluginSupport_destroy_data_ex(
        INTU64 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    INTU64PluginSupport_destroy_data(
        INTU64 *sample);

    NDDSUSERDllExport extern void 
    INTU64PluginSupport_print_data(
        const INTU64 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU64Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU64 *out,
        const INTU64 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    INTU64Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const INTU64 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU64Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU64 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU64Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    INTU64Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    INTU64Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU64Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    INTU64Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const INTU64 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    INTU64Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    INTU64Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    INTU64Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    INTU64Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const INTU64 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    INTU64Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        INTU64 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    INTU64Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        INTU64 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define BITS16Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define BITS16Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define BITS16Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define BITS16Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define BITS16Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern BITS16*
    BITS16PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern BITS16*
    BITS16PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern BITS16*
    BITS16PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    BITS16PluginSupport_copy_data(
        BITS16 *out,
        const BITS16 *in);

    NDDSUSERDllExport extern void 
    BITS16PluginSupport_destroy_data_w_params(
        BITS16 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    BITS16PluginSupport_destroy_data_ex(
        BITS16 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    BITS16PluginSupport_destroy_data(
        BITS16 *sample);

    NDDSUSERDllExport extern void 
    BITS16PluginSupport_print_data(
        const BITS16 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS16Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS16 *out,
        const BITS16 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS16Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const BITS16 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS16Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS16 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS16Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    BITS16Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    BITS16Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS16Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    BITS16Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const BITS16 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    BITS16Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    BITS16Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS16Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    BITS16Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const BITS16 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS16Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS16 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS16Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        BITS16 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define BITS32Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define BITS32Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define BITS32Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define BITS32Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define BITS32Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern BITS32*
    BITS32PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern BITS32*
    BITS32PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern BITS32*
    BITS32PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    BITS32PluginSupport_copy_data(
        BITS32 *out,
        const BITS32 *in);

    NDDSUSERDllExport extern void 
    BITS32PluginSupport_destroy_data_w_params(
        BITS32 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    BITS32PluginSupport_destroy_data_ex(
        BITS32 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    BITS32PluginSupport_destroy_data(
        BITS32 *sample);

    NDDSUSERDllExport extern void 
    BITS32PluginSupport_print_data(
        const BITS32 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS32Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS32 *out,
        const BITS32 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS32Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const BITS32 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS32Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS32 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS32Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    BITS32Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    BITS32Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS32Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    BITS32Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const BITS32 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    BITS32Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    BITS32Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS32Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    BITS32Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const BITS32 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS32Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS32 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS32Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        BITS32 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define BITS64Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define BITS64Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define BITS64Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define BITS64Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define BITS64Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern BITS64*
    BITS64PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern BITS64*
    BITS64PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern BITS64*
    BITS64PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    BITS64PluginSupport_copy_data(
        BITS64 *out,
        const BITS64 *in);

    NDDSUSERDllExport extern void 
    BITS64PluginSupport_destroy_data_w_params(
        BITS64 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    BITS64PluginSupport_destroy_data_ex(
        BITS64 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    BITS64PluginSupport_destroy_data(
        BITS64 *sample);

    NDDSUSERDllExport extern void 
    BITS64PluginSupport_print_data(
        const BITS64 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS64Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS64 *out,
        const BITS64 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BITS64Plugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const BITS64 *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS64Plugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS64 *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS64Plugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    BITS64Plugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    BITS64Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS64Plugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    BITS64Plugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const BITS64 * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    BITS64Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    BITS64Plugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BITS64Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    BITS64Plugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const BITS64 *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BITS64Plugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        BITS64 * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BITS64Plugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        BITS64 *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define TIME_TPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define TIME_TPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TIME_TPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define TIME_TPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TIME_TPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TIME_T*
    TIME_TPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TIME_T*
    TIME_TPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TIME_T*
    TIME_TPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TIME_TPluginSupport_copy_data(
        TIME_T *out,
        const TIME_T *in);

    NDDSUSERDllExport extern void 
    TIME_TPluginSupport_destroy_data_w_params(
        TIME_T *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TIME_TPluginSupport_destroy_data_ex(
        TIME_T *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TIME_TPluginSupport_destroy_data(
        TIME_T *sample);

    NDDSUSERDllExport extern void 
    TIME_TPluginSupport_print_data(
        const TIME_T *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TIME_TPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TIME_T *out,
        const TIME_T *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TIME_TPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const TIME_T *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TIME_TPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        TIME_T *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TIME_TPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    TIME_TPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    TIME_TPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TIME_TPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TIME_TPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const TIME_T * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TIME_TPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TIME_TPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TIME_TPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TIME_TPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const TIME_T *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TIME_TPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        TIME_T * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TIME_TPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        TIME_T *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define BOOLPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define BOOLPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define BOOLPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define BOOLPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define BOOLPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern BOOL*
    BOOLPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern BOOL*
    BOOLPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern BOOL*
    BOOLPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    BOOLPluginSupport_copy_data(
        BOOL *out,
        const BOOL *in);

    NDDSUSERDllExport extern void 
    BOOLPluginSupport_destroy_data_w_params(
        BOOL *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    BOOLPluginSupport_destroy_data_ex(
        BOOL *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    BOOLPluginSupport_destroy_data(
        BOOL *sample);

    NDDSUSERDllExport extern void 
    BOOLPluginSupport_print_data(
        const BOOL *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BOOLPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        BOOL *out,
        const BOOL *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    BOOLPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const BOOL *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BOOLPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        BOOL *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BOOLPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    BOOLPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    BOOLPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BOOLPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    BOOLPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const BOOL * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    BOOLPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    BOOLPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    BOOLPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    BOOLPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const BOOL *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    BOOLPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        BOOL * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    BOOLPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        BOOL *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define OIDTypePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define OIDTypePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define OIDTypePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define OIDTypePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define OIDTypePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern OIDType*
    OIDTypePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern OIDType*
    OIDTypePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern OIDType*
    OIDTypePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    OIDTypePluginSupport_copy_data(
        OIDType *out,
        const OIDType *in);

    NDDSUSERDllExport extern void 
    OIDTypePluginSupport_destroy_data_w_params(
        OIDType *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    OIDTypePluginSupport_destroy_data_ex(
        OIDType *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    OIDTypePluginSupport_destroy_data(
        OIDType *sample);

    NDDSUSERDllExport extern void 
    OIDTypePluginSupport_print_data(
        const OIDType *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    OIDTypePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        OIDType *out,
        const OIDType *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    OIDTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const OIDType *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    OIDTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        OIDType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    OIDTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    OIDTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    OIDTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    OIDTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    OIDTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const OIDType * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    OIDTypePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    OIDTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    OIDTypePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    OIDTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const OIDType *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    OIDTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        OIDType * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    OIDTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        OIDType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define PrivateOidPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define PrivateOidPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define PrivateOidPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define PrivateOidPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define PrivateOidPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PrivateOid*
    PrivateOidPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern PrivateOid*
    PrivateOidPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern PrivateOid*
    PrivateOidPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPluginSupport_copy_data(
        PrivateOid *out,
        const PrivateOid *in);

    NDDSUSERDllExport extern void 
    PrivateOidPluginSupport_destroy_data_w_params(
        PrivateOid *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    PrivateOidPluginSupport_destroy_data_ex(
        PrivateOid *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    PrivateOidPluginSupport_destroy_data(
        PrivateOid *sample);

    NDDSUSERDllExport extern void 
    PrivateOidPluginSupport_print_data(
        const PrivateOid *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        PrivateOid *out,
        const PrivateOid *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const PrivateOid *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        PrivateOid *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PrivateOidPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    PrivateOidPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    PrivateOidPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PrivateOidPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    PrivateOidPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const PrivateOid * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    PrivateOidPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    PrivateOidPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PrivateOidPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const PrivateOid *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PrivateOidPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        PrivateOid * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PrivateOidPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        PrivateOid *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define HANDLEPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define HANDLEPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define HANDLEPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define HANDLEPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define HANDLEPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern HANDLE*
    HANDLEPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern HANDLE*
    HANDLEPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern HANDLE*
    HANDLEPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    HANDLEPluginSupport_copy_data(
        HANDLE *out,
        const HANDLE *in);

    NDDSUSERDllExport extern void 
    HANDLEPluginSupport_destroy_data_w_params(
        HANDLE *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    HANDLEPluginSupport_destroy_data_ex(
        HANDLE *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    HANDLEPluginSupport_destroy_data(
        HANDLE *sample);

    NDDSUSERDllExport extern void 
    HANDLEPluginSupport_print_data(
        const HANDLE *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    HANDLEPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        HANDLE *out,
        const HANDLE *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    HANDLEPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const HANDLE *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HANDLEPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        HANDLE *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HANDLEPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    HANDLEPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    HANDLEPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HANDLEPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    HANDLEPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const HANDLE * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    HANDLEPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    HANDLEPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HANDLEPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    HANDLEPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const HANDLE *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HANDLEPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        HANDLE * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HANDLEPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        HANDLE *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define ICE_IDPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define ICE_IDPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ICE_IDPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define ICE_IDPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ICE_IDPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ICE_ID*
    ICE_IDPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ICE_ID*
    ICE_IDPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ICE_ID*
    ICE_IDPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPluginSupport_copy_data(
        ICE_ID *out,
        const ICE_ID *in);

    NDDSUSERDllExport extern void 
    ICE_IDPluginSupport_destroy_data_w_params(
        ICE_ID *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ICE_IDPluginSupport_destroy_data_ex(
        ICE_ID *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ICE_IDPluginSupport_destroy_data(
        ICE_ID *sample);

    NDDSUSERDllExport extern void 
    ICE_IDPluginSupport_print_data(
        const ICE_ID *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ICE_ID *out,
        const ICE_ID *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ICE_ID *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ICE_ID *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ICE_IDPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ICE_IDPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ICE_IDPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ICE_IDPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ICE_IDPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ICE_ID * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ICE_IDPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ICE_IDPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ICE_IDPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ICE_ID *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ICE_IDPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ICE_ID * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ICE_IDPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ICE_ID *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define InstNumberPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define InstNumberPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define InstNumberPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define InstNumberPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define InstNumberPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern InstNumber*
    InstNumberPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern InstNumber*
    InstNumberPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern InstNumber*
    InstNumberPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    InstNumberPluginSupport_copy_data(
        InstNumber *out,
        const InstNumber *in);

    NDDSUSERDllExport extern void 
    InstNumberPluginSupport_destroy_data_w_params(
        InstNumber *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    InstNumberPluginSupport_destroy_data_ex(
        InstNumber *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    InstNumberPluginSupport_destroy_data(
        InstNumber *sample);

    NDDSUSERDllExport extern void 
    InstNumberPluginSupport_print_data(
        const InstNumber *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    InstNumberPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstNumber *out,
        const InstNumber *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    InstNumberPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const InstNumber *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    InstNumberPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstNumber *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    InstNumberPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    InstNumberPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    InstNumberPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InstNumberPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    InstNumberPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const InstNumber * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    InstNumberPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    InstNumberPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InstNumberPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    InstNumberPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const InstNumber *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    InstNumberPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstNumber * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    InstNumberPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        InstNumber *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define FLOATTypePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define FLOATTypePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define FLOATTypePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define FLOATTypePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define FLOATTypePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern FLOATType*
    FLOATTypePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern FLOATType*
    FLOATTypePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern FLOATType*
    FLOATTypePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePluginSupport_copy_data(
        FLOATType *out,
        const FLOATType *in);

    NDDSUSERDllExport extern void 
    FLOATTypePluginSupport_destroy_data_w_params(
        FLOATType *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    FLOATTypePluginSupport_destroy_data_ex(
        FLOATType *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    FLOATTypePluginSupport_destroy_data(
        FLOATType *sample);

    NDDSUSERDllExport extern void 
    FLOATTypePluginSupport_print_data(
        const FLOATType *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        FLOATType *out,
        const FLOATType *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const FLOATType *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        FLOATType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    FLOATTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    FLOATTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    FLOATTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    FLOATTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    FLOATTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const FLOATType * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    FLOATTypePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    FLOATTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    FLOATTypePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const FLOATType *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    FLOATTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        FLOATType * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    FLOATTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        FLOATType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define MdsContextPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MdsContextPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MdsContextPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MdsContextPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MdsContextPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MdsContext*
    MdsContextPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MdsContext*
    MdsContextPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MdsContext*
    MdsContextPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MdsContextPluginSupport_copy_data(
        MdsContext *out,
        const MdsContext *in);

    NDDSUSERDllExport extern void 
    MdsContextPluginSupport_destroy_data_w_params(
        MdsContext *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MdsContextPluginSupport_destroy_data_ex(
        MdsContext *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MdsContextPluginSupport_destroy_data(
        MdsContext *sample);

    NDDSUSERDllExport extern void 
    MdsContextPluginSupport_print_data(
        const MdsContext *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MdsContextPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MdsContext *out,
        const MdsContext *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MdsContextPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MdsContext *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MdsContextPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MdsContext *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MdsContextPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MdsContextPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MdsContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MdsContextPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MdsContextPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MdsContext * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MdsContextPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MdsContextPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MdsContextPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MdsContextPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MdsContext *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MdsContextPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MdsContext * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MdsContextPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MdsContext *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define GLBHANDLEPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define GLBHANDLEPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define GLBHANDLEPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define GLBHANDLEPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define GLBHANDLEPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern GLBHANDLE*
    GLBHANDLEPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern GLBHANDLE*
    GLBHANDLEPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern GLBHANDLE*
    GLBHANDLEPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPluginSupport_copy_data(
        GLBHANDLE *out,
        const GLBHANDLE *in);

    NDDSUSERDllExport extern void 
    GLBHANDLEPluginSupport_destroy_data_w_params(
        GLBHANDLE *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    GLBHANDLEPluginSupport_destroy_data_ex(
        GLBHANDLE *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    GLBHANDLEPluginSupport_destroy_data(
        GLBHANDLE *sample);

    NDDSUSERDllExport extern void 
    GLBHANDLEPluginSupport_print_data(
        const GLBHANDLE *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE *out,
        const GLBHANDLE *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const GLBHANDLE *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GLBHANDLEPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const GLBHANDLE *sample); 

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GLBHANDLEPlugin_deserialize_from_cdr_buffer(
        GLBHANDLE *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    GLBHANDLEPlugin_data_to_string(
        const GLBHANDLE *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    GLBHANDLEPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    GLBHANDLEPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    GLBHANDLEPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GLBHANDLEPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    GLBHANDLEPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const GLBHANDLE * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    GLBHANDLEPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    GLBHANDLEPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GLBHANDLEPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const GLBHANDLE *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GLBHANDLEPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GLBHANDLEPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        GLBHANDLE *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define ManagedObjectIdPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define ManagedObjectIdPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ManagedObjectIdPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define ManagedObjectIdPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ManagedObjectIdPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ManagedObjectId*
    ManagedObjectIdPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ManagedObjectId*
    ManagedObjectIdPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ManagedObjectId*
    ManagedObjectIdPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPluginSupport_copy_data(
        ManagedObjectId *out,
        const ManagedObjectId *in);

    NDDSUSERDllExport extern void 
    ManagedObjectIdPluginSupport_destroy_data_w_params(
        ManagedObjectId *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ManagedObjectIdPluginSupport_destroy_data_ex(
        ManagedObjectId *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ManagedObjectIdPluginSupport_destroy_data(
        ManagedObjectId *sample);

    NDDSUSERDllExport extern void 
    ManagedObjectIdPluginSupport_print_data(
        const ManagedObjectId *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId *out,
        const ManagedObjectId *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ManagedObjectId *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ManagedObjectIdPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ManagedObjectId *sample); 

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ManagedObjectIdPlugin_deserialize_from_cdr_buffer(
        ManagedObjectId *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    ManagedObjectIdPlugin_data_to_string(
        const ManagedObjectId *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    ManagedObjectIdPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ManagedObjectIdPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ManagedObjectIdPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ManagedObjectIdPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ManagedObjectIdPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ManagedObjectId * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ManagedObjectIdPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ManagedObjectIdPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ManagedObjectIdPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ManagedObjectId *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ManagedObjectIdPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ManagedObjectIdPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ManagedObjectId *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    NomPartitionPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NomPartition *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NomPartitionPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NomPartition *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NomPartitionPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    NomPartitionPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    NomPartitionPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NomPartitionPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    NomPartitionPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NomPartition * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    NomPartitionPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NomPartitionPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    NomPartitionPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NomPartition *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NomPartitionPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NomPartition * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NomPartitionPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NomPartition *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    NomPartitionPluginSupport_print_data(
        const NomPartition *sample, const char *desc, int indent_level);

    #define TYPEPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define TYPEPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TYPEPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define TYPEPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TYPEPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TYPE*
    TYPEPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TYPE*
    TYPEPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TYPE*
    TYPEPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TYPEPluginSupport_copy_data(
        TYPE *out,
        const TYPE *in);

    NDDSUSERDllExport extern void 
    TYPEPluginSupport_destroy_data_w_params(
        TYPE *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TYPEPluginSupport_destroy_data_ex(
        TYPE *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TYPEPluginSupport_destroy_data(
        TYPE *sample);

    NDDSUSERDllExport extern void 
    TYPEPluginSupport_print_data(
        const TYPE *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TYPE *out,
        const TYPE *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const TYPE *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        TYPE *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TYPEPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const TYPE *sample); 

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        TYPE **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TYPEPlugin_deserialize_from_cdr_buffer(
        TYPE *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TYPEPlugin_data_to_string(
        const TYPE *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    TYPEPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    TYPEPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    TYPEPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TYPEPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TYPEPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const TYPE * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TYPEPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TYPEPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TYPEPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const TYPE *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        TYPE * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TYPEPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TYPE ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TYPEPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        TYPE *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define TimespecPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define TimespecPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TimespecPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define TimespecPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TimespecPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Timespec*
    TimespecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Timespec*
    TimespecPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Timespec*
    TimespecPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TimespecPluginSupport_copy_data(
        Timespec *out,
        const Timespec *in);

    NDDSUSERDllExport extern void 
    TimespecPluginSupport_destroy_data_w_params(
        Timespec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TimespecPluginSupport_destroy_data_ex(
        Timespec *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TimespecPluginSupport_destroy_data(
        Timespec *sample);

    NDDSUSERDllExport extern void 
    TimespecPluginSupport_print_data(
        const Timespec *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Timespec *out,
        const Timespec *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Timespec *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Timespec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TimespecPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Timespec *sample); 

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Timespec **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TimespecPlugin_deserialize_from_cdr_buffer(
        Timespec *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TimespecPlugin_data_to_string(
        const Timespec *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    TimespecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    TimespecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    TimespecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TimespecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TimespecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Timespec * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TimespecPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TimespecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TimespecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Timespec *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Timespec * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TimespecPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Timespec ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TimespecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Timespec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define DurationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define DurationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define DurationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define DurationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define DurationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Duration*
    DurationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Duration*
    DurationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Duration*
    DurationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    DurationPluginSupport_copy_data(
        Duration *out,
        const Duration *in);

    NDDSUSERDllExport extern void 
    DurationPluginSupport_destroy_data_w_params(
        Duration *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    DurationPluginSupport_destroy_data_ex(
        Duration *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    DurationPluginSupport_destroy_data(
        Duration *sample);

    NDDSUSERDllExport extern void 
    DurationPluginSupport_print_data(
        const Duration *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Duration *out,
        const Duration *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Duration *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Duration *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DurationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Duration *sample); 

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Duration **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DurationPlugin_deserialize_from_cdr_buffer(
        Duration *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    DurationPlugin_data_to_string(
        const Duration *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    DurationPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    DurationPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    DurationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DurationPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    DurationPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Duration * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    DurationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    DurationPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DurationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Duration *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Duration * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DurationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Duration ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DurationPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Duration *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define DatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define DatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define DatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define DatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define DatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Date*
    DatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Date*
    DatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Date*
    DatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    DatePluginSupport_copy_data(
        Date *out,
        const Date *in);

    NDDSUSERDllExport extern void 
    DatePluginSupport_destroy_data_w_params(
        Date *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    DatePluginSupport_destroy_data_ex(
        Date *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    DatePluginSupport_destroy_data(
        Date *sample);

    NDDSUSERDllExport extern void 
    DatePluginSupport_print_data(
        const Date *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Date *out,
        const Date *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Date *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Date *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Date *sample); 

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Date **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DatePlugin_deserialize_from_cdr_buffer(
        Date *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    DatePlugin_data_to_string(
        const Date *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    DatePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    DatePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    DatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DatePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    DatePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Date * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    DatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    DatePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Date *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Date * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Date ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DatePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Date *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SimpleColorPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SimpleColor *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SimpleColorPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SimpleColor *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SimpleColorPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    SimpleColorPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    SimpleColorPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SimpleColorPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SimpleColorPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SimpleColor * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    SimpleColorPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SimpleColorPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    SimpleColorPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SimpleColor *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SimpleColorPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SimpleColor * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SimpleColorPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SimpleColor *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    SimpleColorPluginSupport_print_data(
        const SimpleColor *sample, const char *desc, int indent_level);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CharSetPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CharSet *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CharSetPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CharSet *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CharSetPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CharSetPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CharSetPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CharSetPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CharSetPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CharSet * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    CharSetPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CharSetPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CharSetPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CharSet *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CharSetPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CharSet * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CharSetPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CharSet *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    CharSetPluginSupport_print_data(
        const CharSet *sample, const char *desc, int indent_level);

    #define StringFlagsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define StringFlagsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define StringFlagsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define StringFlagsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define StringFlagsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern StringFlags*
    StringFlagsPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern StringFlags*
    StringFlagsPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern StringFlags*
    StringFlagsPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPluginSupport_copy_data(
        StringFlags *out,
        const StringFlags *in);

    NDDSUSERDllExport extern void 
    StringFlagsPluginSupport_destroy_data_w_params(
        StringFlags *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    StringFlagsPluginSupport_destroy_data_ex(
        StringFlags *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    StringFlagsPluginSupport_destroy_data(
        StringFlags *sample);

    NDDSUSERDllExport extern void 
    StringFlagsPluginSupport_print_data(
        const StringFlags *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringFlags *out,
        const StringFlags *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const StringFlags *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringFlags *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringFlagsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    StringFlagsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    StringFlagsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const StringFlags * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    StringFlagsPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const StringFlags *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringFlags * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringFlagsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        StringFlags *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    StringFlagsBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const StringFlagsBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringFlagsBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringFlagsBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    StringFlagsBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    StringFlagsBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const StringFlagsBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    StringFlagsBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringFlagsBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const StringFlagsBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringFlagsBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringFlagsBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringFlagsBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        StringFlagsBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    StringFlagsBitsPluginSupport_print_data(
        const StringFlagsBits *sample, const char *desc, int indent_level);

    #define StringSpecPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define StringSpecPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define StringSpecPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define StringSpecPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define StringSpecPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern StringSpec*
    StringSpecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern StringSpec*
    StringSpecPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern StringSpec*
    StringSpecPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    StringSpecPluginSupport_copy_data(
        StringSpec *out,
        const StringSpec *in);

    NDDSUSERDllExport extern void 
    StringSpecPluginSupport_destroy_data_w_params(
        StringSpec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    StringSpecPluginSupport_destroy_data_ex(
        StringSpec *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    StringSpecPluginSupport_destroy_data(
        StringSpec *sample);

    NDDSUSERDllExport extern void 
    StringSpecPluginSupport_print_data(
        const StringSpec *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec *out,
        const StringSpec *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const StringSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringSpecPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const StringSpec *sample); 

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringSpecPlugin_deserialize_from_cdr_buffer(
        StringSpec *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    StringSpecPlugin_data_to_string(
        const StringSpec *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    StringSpecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    StringSpecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    StringSpecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringSpecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    StringSpecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const StringSpec * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    StringSpecPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    StringSpecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    StringSpecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const StringSpec *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    StringSpecPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    StringSpecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        StringSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define LocalePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define LocalePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define LocalePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define LocalePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define LocalePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Locale*
    LocalePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Locale*
    LocalePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Locale*
    LocalePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    LocalePluginSupport_copy_data(
        Locale *out,
        const Locale *in);

    NDDSUSERDllExport extern void 
    LocalePluginSupport_destroy_data_w_params(
        Locale *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    LocalePluginSupport_destroy_data_ex(
        Locale *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    LocalePluginSupport_destroy_data(
        Locale *sample);

    NDDSUSERDllExport extern void 
    LocalePluginSupport_print_data(
        const Locale *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Locale *out,
        const Locale *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Locale *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Locale *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    LocalePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Locale *sample); 

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Locale **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    LocalePlugin_deserialize_from_cdr_buffer(
        Locale *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    LocalePlugin_data_to_string(
        const Locale *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    LocalePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    LocalePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    LocalePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    LocalePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    LocalePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Locale * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    LocalePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    LocalePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    LocalePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Locale *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Locale * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    LocalePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Locale ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    LocalePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Locale *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define ExtNomenRefPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define ExtNomenRefPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ExtNomenRefPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define ExtNomenRefPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ExtNomenRefPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ExtNomenRef*
    ExtNomenRefPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ExtNomenRef*
    ExtNomenRefPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ExtNomenRef*
    ExtNomenRefPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPluginSupport_copy_data(
        ExtNomenRef *out,
        const ExtNomenRef *in);

    NDDSUSERDllExport extern void 
    ExtNomenRefPluginSupport_destroy_data_w_params(
        ExtNomenRef *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ExtNomenRefPluginSupport_destroy_data_ex(
        ExtNomenRef *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ExtNomenRefPluginSupport_destroy_data(
        ExtNomenRef *sample);

    NDDSUSERDllExport extern void 
    ExtNomenRefPluginSupport_print_data(
        const ExtNomenRef *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef *out,
        const ExtNomenRef *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ExtNomenRef *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ExtNomenRefPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ExtNomenRef *sample); 

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ExtNomenRefPlugin_deserialize_from_cdr_buffer(
        ExtNomenRef *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    ExtNomenRefPlugin_data_to_string(
        const ExtNomenRef *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    ExtNomenRefPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ExtNomenRefPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ExtNomenRefPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ExtNomenRefPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ExtNomenRefPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ExtNomenRef * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ExtNomenRefPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ExtNomenRefPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ExtNomenRefPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ExtNomenRef *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ExtNomenRefPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ExtNomenRefPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ExtNomenRef *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define SystemModelPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define SystemModelPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define SystemModelPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define SystemModelPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define SystemModelPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern SystemModel*
    SystemModelPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern SystemModel*
    SystemModelPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SystemModel*
    SystemModelPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    SystemModelPluginSupport_copy_data(
        SystemModel *out,
        const SystemModel *in);

    NDDSUSERDllExport extern void 
    SystemModelPluginSupport_destroy_data_w_params(
        SystemModel *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    SystemModelPluginSupport_destroy_data_ex(
        SystemModel *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    SystemModelPluginSupport_destroy_data(
        SystemModel *sample);

    NDDSUSERDllExport extern void 
    SystemModelPluginSupport_print_data(
        const SystemModel *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel *out,
        const SystemModel *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SystemModel *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SystemModelPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const SystemModel *sample); 

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SystemModelPlugin_deserialize_from_cdr_buffer(
        SystemModel *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    SystemModelPlugin_data_to_string(
        const SystemModel *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    SystemModelPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    SystemModelPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    SystemModelPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SystemModelPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SystemModelPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SystemModel * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    SystemModelPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    SystemModelPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SystemModelPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SystemModel *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SystemModelPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SystemModelPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SystemModel *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ProdSpecTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ProdSpecType *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProdSpecTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ProdSpecTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ProdSpecTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ProdSpecType * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    ProdSpecTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecTypePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ProdSpecType *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecType * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProdSpecTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    ProdSpecTypePluginSupport_print_data(
        const ProdSpecType *sample, const char *desc, int indent_level);

    #define ProdSpecEntryPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define ProdSpecEntryPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ProdSpecEntryPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define ProdSpecEntryPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ProdSpecEntryPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ProdSpecEntry*
    ProdSpecEntryPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ProdSpecEntry*
    ProdSpecEntryPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ProdSpecEntry*
    ProdSpecEntryPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPluginSupport_copy_data(
        ProdSpecEntry *out,
        const ProdSpecEntry *in);

    NDDSUSERDllExport extern void 
    ProdSpecEntryPluginSupport_destroy_data_w_params(
        ProdSpecEntry *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ProdSpecEntryPluginSupport_destroy_data_ex(
        ProdSpecEntry *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ProdSpecEntryPluginSupport_destroy_data(
        ProdSpecEntry *sample);

    NDDSUSERDllExport extern void 
    ProdSpecEntryPluginSupport_print_data(
        const ProdSpecEntry *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry *out,
        const ProdSpecEntry *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ProdSpecEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProdSpecEntryPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ProdSpecEntry *sample); 

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProdSpecEntryPlugin_deserialize_from_cdr_buffer(
        ProdSpecEntry *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    ProdSpecEntryPlugin_data_to_string(
        const ProdSpecEntry *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    ProdSpecEntryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecEntryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ProdSpecEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecEntryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ProdSpecEntryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ProdSpecEntry * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ProdSpecEntryPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecEntryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProdSpecEntryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ProdSpecEntry *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProdSpecEntryPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProdSpecEntryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ProdSpecEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define ProductionSpecPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define ProductionSpecPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ProductionSpecPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define ProductionSpecPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ProductionSpecPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ProductionSpec*
    ProductionSpecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ProductionSpec*
    ProductionSpecPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ProductionSpec*
    ProductionSpecPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPluginSupport_copy_data(
        ProductionSpec *out,
        const ProductionSpec *in);

    NDDSUSERDllExport extern void 
    ProductionSpecPluginSupport_destroy_data_w_params(
        ProductionSpec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ProductionSpecPluginSupport_destroy_data_ex(
        ProductionSpec *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ProductionSpecPluginSupport_destroy_data(
        ProductionSpec *sample);

    NDDSUSERDllExport extern void 
    ProductionSpecPluginSupport_print_data(
        const ProductionSpec *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProductionSpec *out,
        const ProductionSpec *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const ProductionSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProductionSpec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProductionSpecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    ProductionSpecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    ProductionSpecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProductionSpecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ProductionSpecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const ProductionSpec * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ProductionSpecPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ProductionSpecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ProductionSpecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const ProductionSpec *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ProductionSpecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        ProductionSpec * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ProductionSpecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ProductionSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CurLimAlStatPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CurLimAlStatPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CurLimAlStatPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CurLimAlStatPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CurLimAlStatPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CurLimAlStat*
    CurLimAlStatPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CurLimAlStat*
    CurLimAlStatPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CurLimAlStat*
    CurLimAlStatPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPluginSupport_copy_data(
        CurLimAlStat *out,
        const CurLimAlStat *in);

    NDDSUSERDllExport extern void 
    CurLimAlStatPluginSupport_destroy_data_w_params(
        CurLimAlStat *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CurLimAlStatPluginSupport_destroy_data_ex(
        CurLimAlStat *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CurLimAlStatPluginSupport_destroy_data(
        CurLimAlStat *sample);

    NDDSUSERDllExport extern void 
    CurLimAlStatPluginSupport_print_data(
        const CurLimAlStat *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStat *out,
        const CurLimAlStat *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlStat *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStat *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlStatPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CurLimAlStatPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CurLimAlStat * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CurLimAlStatPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlStat *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStat * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlStatPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStat *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlStatBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStatBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlStatBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CurLimAlStatBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CurLimAlStatBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlStatBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlStatBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlStatBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStatBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlStatBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlStatBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    CurLimAlStatBitsPluginSupport_print_data(
        const CurLimAlStatBits *sample, const char *desc, int indent_level);

    #define CurLimAlValPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CurLimAlValPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CurLimAlValPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CurLimAlValPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CurLimAlValPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CurLimAlVal*
    CurLimAlValPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CurLimAlVal*
    CurLimAlValPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CurLimAlVal*
    CurLimAlValPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPluginSupport_copy_data(
        CurLimAlVal *out,
        const CurLimAlVal *in);

    NDDSUSERDllExport extern void 
    CurLimAlValPluginSupport_destroy_data_w_params(
        CurLimAlVal *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CurLimAlValPluginSupport_destroy_data_ex(
        CurLimAlVal *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CurLimAlValPluginSupport_destroy_data(
        CurLimAlVal *sample);

    NDDSUSERDllExport extern void 
    CurLimAlValPluginSupport_print_data(
        const CurLimAlVal *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal *out,
        const CurLimAlVal *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlVal *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlValPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const CurLimAlVal *sample); 

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlValPlugin_deserialize_from_cdr_buffer(
        CurLimAlVal *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    CurLimAlValPlugin_data_to_string(
        const CurLimAlVal *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    CurLimAlValPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlValPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CurLimAlValPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlValPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CurLimAlValPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CurLimAlVal * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CurLimAlValPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlValPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CurLimAlValPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CurLimAlVal *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CurLimAlValPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CurLimAlValPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CurLimAlVal *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct EventReport
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct EventReport)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * EventReport must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct EventReport.
    */
    typedef  class EventReport EventReportKeyHolder;

    #define EventReportPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EventReportPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EventReportPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EventReportPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define EventReportPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define EventReportPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EventReportPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EventReport*
    EventReportPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EventReport*
    EventReportPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EventReport*
    EventReportPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EventReportPluginSupport_copy_data(
        EventReport *out,
        const EventReport *in);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_destroy_data_w_params(
        EventReport *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_destroy_data_ex(
        EventReport *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_destroy_data(
        EventReport *sample);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_print_data(
        const EventReport *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern EventReport*
    EventReportPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EventReport*
    EventReportPluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_destroy_key_ex(
        EventReportKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EventReportPluginSupport_destroy_key(
        EventReportKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    EventReportPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    EventReportPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    EventReportPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    EventReportPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    EventReportPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        EventReport *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EventReport *out,
        const EventReport *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EventReport *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EventReport *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EventReportPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const EventReport *sample); 

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        EventReport **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EventReportPlugin_deserialize_from_cdr_buffer(
        EventReport *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    EventReportPlugin_data_to_string(
        const EventReport *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    EventReportPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EventReportPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EventReportPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EventReportPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EventReportPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EventReport * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EventReportPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EventReportPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EventReportPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EventReport *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EventReport * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        EventReport ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EventReportPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EventReport *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EventReportKeyHolder *key, 
        const EventReport *instance);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        EventReport *instance, 
        const EventReportKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const EventReport *instance);

    NDDSUSERDllExport extern RTIBool 
    EventReportPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    EventReportPlugin_new(void);

    NDDSUSERDllExport extern void
    EventReportPlugin_delete(struct PRESTypePlugin *);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CareActivityCategoryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CareActivityCategory *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CareActivityCategoryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CareActivityCategory *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CareActivityCategoryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CareActivityCategoryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CareActivityCategoryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CareActivityCategoryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CareActivityCategoryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CareActivityCategory * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    CareActivityCategoryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CareActivityCategoryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CareActivityCategoryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CareActivityCategory *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CareActivityCategoryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CareActivityCategory * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CareActivityCategoryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CareActivityCategory *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    CareActivityCategoryPluginSupport_print_data(
        const CareActivityCategory *sample, const char *desc, int indent_level);

    #define HostIdPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define HostIdPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define HostIdPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define HostIdPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define HostIdPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern HostId*
    HostIdPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern HostId*
    HostIdPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern HostId*
    HostIdPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    HostIdPluginSupport_copy_data(
        HostId *out,
        const HostId *in);

    NDDSUSERDllExport extern void 
    HostIdPluginSupport_destroy_data_w_params(
        HostId *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    HostIdPluginSupport_destroy_data_ex(
        HostId *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    HostIdPluginSupport_destroy_data(
        HostId *sample);

    NDDSUSERDllExport extern void 
    HostIdPluginSupport_print_data(
        const HostId *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    HostIdPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        HostId *out,
        const HostId *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    HostIdPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const HostId *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HostIdPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        HostId *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HostIdPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    HostIdPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    HostIdPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HostIdPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    HostIdPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const HostId * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    HostIdPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    HostIdPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HostIdPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    HostIdPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const HostId *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    HostIdPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        HostId * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HostIdPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        HostId *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define GuidTimespecPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define GuidTimespecPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define GuidTimespecPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define GuidTimespecPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define GuidTimespecPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern GuidTimespec*
    GuidTimespecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern GuidTimespec*
    GuidTimespecPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern GuidTimespec*
    GuidTimespecPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPluginSupport_copy_data(
        GuidTimespec *out,
        const GuidTimespec *in);

    NDDSUSERDllExport extern void 
    GuidTimespecPluginSupport_destroy_data_w_params(
        GuidTimespec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    GuidTimespecPluginSupport_destroy_data_ex(
        GuidTimespec *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    GuidTimespecPluginSupport_destroy_data(
        GuidTimespec *sample);

    NDDSUSERDllExport extern void 
    GuidTimespecPluginSupport_print_data(
        const GuidTimespec *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec *out,
        const GuidTimespec *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const GuidTimespec *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidTimespecPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const GuidTimespec *sample); 

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidTimespecPlugin_deserialize_from_cdr_buffer(
        GuidTimespec *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    GuidTimespecPlugin_data_to_string(
        const GuidTimespec *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    GuidTimespecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    GuidTimespecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    GuidTimespecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GuidTimespecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    GuidTimespecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const GuidTimespec * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    GuidTimespecPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    GuidTimespecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GuidTimespecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const GuidTimespec *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidTimespecPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidTimespecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        GuidTimespec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define GuidPrefixPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define GuidPrefixPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define GuidPrefixPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define GuidPrefixPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define GuidPrefixPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern GuidPrefix*
    GuidPrefixPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern GuidPrefix*
    GuidPrefixPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern GuidPrefix*
    GuidPrefixPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPluginSupport_copy_data(
        GuidPrefix *out,
        const GuidPrefix *in);

    NDDSUSERDllExport extern void 
    GuidPrefixPluginSupport_destroy_data_w_params(
        GuidPrefix *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    GuidPrefixPluginSupport_destroy_data_ex(
        GuidPrefix *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    GuidPrefixPluginSupport_destroy_data(
        GuidPrefix *sample);

    NDDSUSERDllExport extern void 
    GuidPrefixPluginSupport_print_data(
        const GuidPrefix *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix *out,
        const GuidPrefix *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const GuidPrefix *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidPrefixPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const GuidPrefix *sample); 

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidPrefixPlugin_deserialize_from_cdr_buffer(
        GuidPrefix *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    GuidPrefixPlugin_data_to_string(
        const GuidPrefix *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    GuidPrefixPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    GuidPrefixPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    GuidPrefixPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GuidPrefixPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    GuidPrefixPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const GuidPrefix * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    GuidPrefixPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    GuidPrefixPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GuidPrefixPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const GuidPrefix *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GuidPrefixPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GuidPrefixPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        GuidPrefix *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define EntityKindPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EntityKindPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EntityKindPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EntityKindPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EntityKindPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EntityKind*
    EntityKindPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EntityKind*
    EntityKindPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EntityKind*
    EntityKindPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EntityKindPluginSupport_copy_data(
        EntityKind *out,
        const EntityKind *in);

    NDDSUSERDllExport extern void 
    EntityKindPluginSupport_destroy_data_w_params(
        EntityKind *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EntityKindPluginSupport_destroy_data_ex(
        EntityKind *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EntityKindPluginSupport_destroy_data(
        EntityKind *sample);

    NDDSUSERDllExport extern void 
    EntityKindPluginSupport_print_data(
        const EntityKind *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityKindPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKind *out,
        const EntityKind *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityKindPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EntityKind *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityKindPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKind *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityKindPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EntityKindPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EntityKindPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityKindPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EntityKindPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EntityKind * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EntityKindPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EntityKindPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityKindPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EntityKindPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EntityKind *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityKindPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKind * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityKindPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EntityKind *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define EntityKeyPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EntityKeyPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EntityKeyPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EntityKeyPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EntityKeyPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EntityKey*
    EntityKeyPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EntityKey*
    EntityKeyPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EntityKey*
    EntityKeyPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPluginSupport_copy_data(
        EntityKey *out,
        const EntityKey *in);

    NDDSUSERDllExport extern void 
    EntityKeyPluginSupport_destroy_data_w_params(
        EntityKey *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EntityKeyPluginSupport_destroy_data_ex(
        EntityKey *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EntityKeyPluginSupport_destroy_data(
        EntityKey *sample);

    NDDSUSERDllExport extern void 
    EntityKeyPluginSupport_print_data(
        const EntityKey *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKey *out,
        const EntityKey *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EntityKey *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKey *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityKeyPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EntityKeyPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EntityKeyPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityKeyPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EntityKeyPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EntityKey * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EntityKeyPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EntityKeyPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityKeyPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EntityKey *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityKeyPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityKey * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityKeyPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EntityKey *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define EntityIdPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EntityIdPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EntityIdPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EntityIdPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EntityIdPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EntityId*
    EntityIdPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EntityId*
    EntityIdPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EntityId*
    EntityIdPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EntityIdPluginSupport_copy_data(
        EntityId *out,
        const EntityId *in);

    NDDSUSERDllExport extern void 
    EntityIdPluginSupport_destroy_data_w_params(
        EntityId *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EntityIdPluginSupport_destroy_data_ex(
        EntityId *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EntityIdPluginSupport_destroy_data(
        EntityId *sample);

    NDDSUSERDllExport extern void 
    EntityIdPluginSupport_print_data(
        const EntityId *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityId *out,
        const EntityId *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EntityId *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityId *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityIdPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const EntityId *sample); 

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        EntityId **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityIdPlugin_deserialize_from_cdr_buffer(
        EntityId *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    EntityIdPlugin_data_to_string(
        const EntityId *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    EntityIdPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EntityIdPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EntityIdPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityIdPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EntityIdPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EntityId * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EntityIdPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EntityIdPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EntityIdPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EntityId *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EntityId * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EntityIdPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        EntityId ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EntityIdPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EntityId *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define GUIDPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define GUIDPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define GUIDPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define GUIDPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define GUIDPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern GUID*
    GUIDPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern GUID*
    GUIDPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern GUID*
    GUIDPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    GUIDPluginSupport_copy_data(
        GUID *out,
        const GUID *in);

    NDDSUSERDllExport extern void 
    GUIDPluginSupport_destroy_data_w_params(
        GUID *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    GUIDPluginSupport_destroy_data_ex(
        GUID *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    GUIDPluginSupport_destroy_data(
        GUID *sample);

    NDDSUSERDllExport extern void 
    GUIDPluginSupport_print_data(
        const GUID *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        GUID *out,
        const GUID *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const GUID *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        GUID *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GUIDPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const GUID *sample); 

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        GUID **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GUIDPlugin_deserialize_from_cdr_buffer(
        GUID *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    GUIDPlugin_data_to_string(
        const GUID *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    GUIDPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    GUIDPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    GUIDPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GUIDPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    GUIDPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const GUID * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    GUIDPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    GUIDPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    GUIDPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const GUID *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        GUID * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    GUIDPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        GUID ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    GUIDPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        GUID *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define SequenceNumberPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define SequenceNumberPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define SequenceNumberPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define SequenceNumberPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define SequenceNumberPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern SequenceNumber*
    SequenceNumberPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern SequenceNumber*
    SequenceNumberPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SequenceNumber*
    SequenceNumberPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPluginSupport_copy_data(
        SequenceNumber *out,
        const SequenceNumber *in);

    NDDSUSERDllExport extern void 
    SequenceNumberPluginSupport_destroy_data_w_params(
        SequenceNumber *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    SequenceNumberPluginSupport_destroy_data_ex(
        SequenceNumber *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    SequenceNumberPluginSupport_destroy_data(
        SequenceNumber *sample);

    NDDSUSERDllExport extern void 
    SequenceNumberPluginSupport_print_data(
        const SequenceNumber *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SequenceNumber *out,
        const SequenceNumber *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SequenceNumber *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SequenceNumber *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SequenceNumberPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    SequenceNumberPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    SequenceNumberPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SequenceNumberPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SequenceNumberPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SequenceNumber * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    SequenceNumberPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    SequenceNumberPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SequenceNumberPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SequenceNumber *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SequenceNumberPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SequenceNumber * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SequenceNumberPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SequenceNumber *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define InstanceIdentifierPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define InstanceIdentifierPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define InstanceIdentifierPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define InstanceIdentifierPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define InstanceIdentifierPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern InstanceIdentifier*
    InstanceIdentifierPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern InstanceIdentifier*
    InstanceIdentifierPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern InstanceIdentifier*
    InstanceIdentifierPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPluginSupport_copy_data(
        InstanceIdentifier *out,
        const InstanceIdentifier *in);

    NDDSUSERDllExport extern void 
    InstanceIdentifierPluginSupport_destroy_data_w_params(
        InstanceIdentifier *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    InstanceIdentifierPluginSupport_destroy_data_ex(
        InstanceIdentifier *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    InstanceIdentifierPluginSupport_destroy_data(
        InstanceIdentifier *sample);

    NDDSUSERDllExport extern void 
    InstanceIdentifierPluginSupport_print_data(
        const InstanceIdentifier *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier *out,
        const InstanceIdentifier *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const InstanceIdentifier *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    InstanceIdentifierPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const InstanceIdentifier *sample); 

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    InstanceIdentifierPlugin_deserialize_from_cdr_buffer(
        InstanceIdentifier *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    InstanceIdentifierPlugin_data_to_string(
        const InstanceIdentifier *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    InstanceIdentifierPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    InstanceIdentifierPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    InstanceIdentifierPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InstanceIdentifierPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    InstanceIdentifierPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const InstanceIdentifier * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    InstanceIdentifierPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    InstanceIdentifierPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InstanceIdentifierPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const InstanceIdentifier *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    InstanceIdentifierPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    InstanceIdentifierPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        InstanceIdentifier *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct Top
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct Top)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * Top must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct Top.
    */
    typedef  class Top TopKeyHolder;

    #define TopPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define TopPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TopPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define TopPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define TopPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define TopPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TopPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Top*
    TopPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Top*
    TopPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Top*
    TopPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TopPluginSupport_copy_data(
        Top *out,
        const Top *in);

    NDDSUSERDllExport extern void 
    TopPluginSupport_destroy_data_w_params(
        Top *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TopPluginSupport_destroy_data_ex(
        Top *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TopPluginSupport_destroy_data(
        Top *sample);

    NDDSUSERDllExport extern void 
    TopPluginSupport_print_data(
        const Top *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern Top*
    TopPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Top*
    TopPluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    TopPluginSupport_destroy_key_ex(
        TopKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TopPluginSupport_destroy_key(
        TopKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Top *out,
        const Top *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Top *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Top *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TopPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Top *sample); 

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Top **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TopPlugin_deserialize_from_cdr_buffer(
        Top *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TopPlugin_data_to_string(
        const Top *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    TopPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    TopPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    TopPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TopPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TopPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Top * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TopPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TopPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TopPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Top *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Top * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Top ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TopPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Top *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        TopKeyHolder *key, 
        const Top *instance);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        Top *instance, 
        const TopKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const Top *instance);

    NDDSUSERDllExport extern RTIBool 
    TopPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct VMO
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct VMO)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * VMO must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct VMO.
    */
    typedef  class VMO VMOKeyHolder;

    #define VMOPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define VMOPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define VMOPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define VMOPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define VMOPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define VMOPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define VMOPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern VMO*
    VMOPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern VMO*
    VMOPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern VMO*
    VMOPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    VMOPluginSupport_copy_data(
        VMO *out,
        const VMO *in);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_destroy_data_w_params(
        VMO *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_destroy_data_ex(
        VMO *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_destroy_data(
        VMO *sample);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_print_data(
        const VMO *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern VMO*
    VMOPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern VMO*
    VMOPluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_destroy_key_ex(
        VMOKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    VMOPluginSupport_destroy_key(
        VMOKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        VMO *out,
        const VMO *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const VMO *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        VMO *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VMOPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const VMO *sample); 

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        VMO **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VMOPlugin_deserialize_from_cdr_buffer(
        VMO *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    VMOPlugin_data_to_string(
        const VMO *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    VMOPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    VMOPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    VMOPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VMOPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    VMOPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const VMO * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    VMOPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    VMOPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VMOPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const VMO *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        VMO * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        VMO ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VMOPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VMO *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VMOKeyHolder *key, 
        const VMO *instance);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        VMO *instance, 
        const VMOKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const VMO *instance);

    NDDSUSERDllExport extern RTIBool 
    VMOPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    #define CT_booleanPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_booleanPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_booleanPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_booleanPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_booleanPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_boolean*
    CT_booleanPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_boolean*
    CT_booleanPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_boolean*
    CT_booleanPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPluginSupport_copy_data(
        CT_boolean *out,
        const CT_boolean *in);

    NDDSUSERDllExport extern void 
    CT_booleanPluginSupport_destroy_data_w_params(
        CT_boolean *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_booleanPluginSupport_destroy_data_ex(
        CT_boolean *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_booleanPluginSupport_destroy_data(
        CT_boolean *sample);

    NDDSUSERDllExport extern void 
    CT_booleanPluginSupport_print_data(
        const CT_boolean *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_boolean *out,
        const CT_boolean *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_boolean *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_boolean *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_booleanPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_booleanPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_booleanPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_booleanPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_booleanPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_boolean * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_booleanPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_booleanPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_booleanPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_boolean *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_booleanPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_boolean * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_booleanPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_boolean *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_integerPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_integerPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_integerPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_integerPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_integerPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_integer*
    CT_integerPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_integer*
    CT_integerPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_integer*
    CT_integerPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_integerPluginSupport_copy_data(
        CT_integer *out,
        const CT_integer *in);

    NDDSUSERDllExport extern void 
    CT_integerPluginSupport_destroy_data_w_params(
        CT_integer *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_integerPluginSupport_destroy_data_ex(
        CT_integer *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_integerPluginSupport_destroy_data(
        CT_integer *sample);

    NDDSUSERDllExport extern void 
    CT_integerPluginSupport_print_data(
        const CT_integer *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_integerPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_integer *out,
        const CT_integer *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_integerPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_integer *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_integerPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_integer *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_integerPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_integerPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_integerPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_integerPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_integerPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_integer * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_integerPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_integerPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_integerPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_integerPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_integer *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_integerPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_integer * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_integerPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_integer *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_unsignedIntPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_unsignedIntPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_unsignedIntPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_unsignedIntPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_unsignedIntPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_unsignedInt*
    CT_unsignedIntPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_unsignedInt*
    CT_unsignedIntPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_unsignedInt*
    CT_unsignedIntPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPluginSupport_copy_data(
        CT_unsignedInt *out,
        const CT_unsignedInt *in);

    NDDSUSERDllExport extern void 
    CT_unsignedIntPluginSupport_destroy_data_w_params(
        CT_unsignedInt *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_unsignedIntPluginSupport_destroy_data_ex(
        CT_unsignedInt *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_unsignedIntPluginSupport_destroy_data(
        CT_unsignedInt *sample);

    NDDSUSERDllExport extern void 
    CT_unsignedIntPluginSupport_print_data(
        const CT_unsignedInt *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_unsignedInt *out,
        const CT_unsignedInt *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_unsignedInt *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_unsignedInt *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_unsignedIntPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_unsignedIntPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_unsignedIntPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_unsignedIntPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_unsignedIntPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_unsignedInt * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_unsignedIntPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_unsignedIntPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_unsignedIntPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_unsignedInt *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_unsignedIntPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_unsignedInt * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_unsignedIntPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_unsignedInt *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_positiveIntPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_positiveIntPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_positiveIntPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_positiveIntPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_positiveIntPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_positiveInt*
    CT_positiveIntPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_positiveInt*
    CT_positiveIntPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_positiveInt*
    CT_positiveIntPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPluginSupport_copy_data(
        CT_positiveInt *out,
        const CT_positiveInt *in);

    NDDSUSERDllExport extern void 
    CT_positiveIntPluginSupport_destroy_data_w_params(
        CT_positiveInt *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_positiveIntPluginSupport_destroy_data_ex(
        CT_positiveInt *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_positiveIntPluginSupport_destroy_data(
        CT_positiveInt *sample);

    NDDSUSERDllExport extern void 
    CT_positiveIntPluginSupport_print_data(
        const CT_positiveInt *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_positiveInt *out,
        const CT_positiveInt *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_positiveInt *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_positiveInt *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_positiveIntPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_positiveIntPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_positiveIntPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_positiveIntPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_positiveIntPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_positiveInt * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_positiveIntPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_positiveIntPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_positiveIntPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_positiveInt *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_positiveIntPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_positiveInt * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_positiveIntPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_positiveInt *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_decimalPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_decimalPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_decimalPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_decimalPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_decimalPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_decimal*
    CT_decimalPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_decimal*
    CT_decimalPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_decimal*
    CT_decimalPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPluginSupport_copy_data(
        CT_decimal *out,
        const CT_decimal *in);

    NDDSUSERDllExport extern void 
    CT_decimalPluginSupport_destroy_data_w_params(
        CT_decimal *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_decimalPluginSupport_destroy_data_ex(
        CT_decimal *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_decimalPluginSupport_destroy_data(
        CT_decimal *sample);

    NDDSUSERDllExport extern void 
    CT_decimalPluginSupport_print_data(
        const CT_decimal *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    CT_decimalPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    CT_decimalPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    CT_decimalPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    CT_decimalPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    CT_decimalPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal *out,
        const CT_decimal *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_decimal *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_decimalPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const CT_decimal *sample); 

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_decimalPlugin_deserialize_from_cdr_buffer(
        CT_decimal *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    CT_decimalPlugin_data_to_string(
        const CT_decimal *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    CT_decimalPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_decimalPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_decimalPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_decimalPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_decimalPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_decimal * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_decimalPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_decimalPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_decimalPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_decimal *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_decimalPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_decimalPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_decimal *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    CT_decimalPlugin_new(void);

    NDDSUSERDllExport extern void
    CT_decimalPlugin_delete(struct PRESTypePlugin *);

    #define CT_dateTimePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_dateTimePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_dateTimePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_dateTimePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_dateTimePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_dateTime*
    CT_dateTimePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_dateTime*
    CT_dateTimePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_dateTime*
    CT_dateTimePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePluginSupport_copy_data(
        CT_dateTime *out,
        const CT_dateTime *in);

    NDDSUSERDllExport extern void 
    CT_dateTimePluginSupport_destroy_data_w_params(
        CT_dateTime *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_dateTimePluginSupport_destroy_data_ex(
        CT_dateTime *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_dateTimePluginSupport_destroy_data(
        CT_dateTime *sample);

    NDDSUSERDllExport extern void 
    CT_dateTimePluginSupport_print_data(
        const CT_dateTime *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_dateTime *out,
        const CT_dateTime *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_dateTime *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_dateTime *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_dateTimePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_dateTimePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_dateTimePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_dateTimePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_dateTimePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_dateTime * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_dateTimePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_dateTimePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_dateTimePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_dateTime *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_dateTimePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_dateTime * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_dateTimePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_dateTime *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_instantPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_instantPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_instantPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_instantPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_instantPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_instant*
    CT_instantPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_instant*
    CT_instantPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_instant*
    CT_instantPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_instantPluginSupport_copy_data(
        CT_instant *out,
        const CT_instant *in);

    NDDSUSERDllExport extern void 
    CT_instantPluginSupport_destroy_data_w_params(
        CT_instant *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_instantPluginSupport_destroy_data_ex(
        CT_instant *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_instantPluginSupport_destroy_data(
        CT_instant *sample);

    NDDSUSERDllExport extern void 
    CT_instantPluginSupport_print_data(
        const CT_instant *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_instantPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_instant *out,
        const CT_instant *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_instantPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_instant *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_instantPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_instant *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_instantPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_instantPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_instantPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_instantPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_instantPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_instant * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_instantPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_instantPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_instantPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_instantPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_instant *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_instantPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_instant * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_instantPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_instant *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_datePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_datePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_datePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_datePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_datePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_date*
    CT_datePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_date*
    CT_datePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_date*
    CT_datePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_datePluginSupport_copy_data(
        CT_date *out,
        const CT_date *in);

    NDDSUSERDllExport extern void 
    CT_datePluginSupport_destroy_data_w_params(
        CT_date *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_datePluginSupport_destroy_data_ex(
        CT_date *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_datePluginSupport_destroy_data(
        CT_date *sample);

    NDDSUSERDllExport extern void 
    CT_datePluginSupport_print_data(
        const CT_date *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_datePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_date *out,
        const CT_date *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_datePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_date *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_datePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_date *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_datePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_datePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_datePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_datePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_datePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_date * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_datePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_datePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_datePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_datePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_date *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_datePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_date * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_datePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_date *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_timePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_timePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_timePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_timePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_timePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_time*
    CT_timePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_time*
    CT_timePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_time*
    CT_timePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_timePluginSupport_copy_data(
        CT_time *out,
        const CT_time *in);

    NDDSUSERDllExport extern void 
    CT_timePluginSupport_destroy_data_w_params(
        CT_time *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_timePluginSupport_destroy_data_ex(
        CT_time *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_timePluginSupport_destroy_data(
        CT_time *sample);

    NDDSUSERDllExport extern void 
    CT_timePluginSupport_print_data(
        const CT_time *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_timePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_time *out,
        const CT_time *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_timePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_time *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_timePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_time *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_timePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_timePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_timePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_timePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_timePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_time * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_timePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_timePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_timePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_timePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_time *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_timePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_time * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_timePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_time *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_codePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_codePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_codePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_codePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_codePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_code*
    CT_codePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_code*
    CT_codePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_code*
    CT_codePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_codePluginSupport_copy_data(
        CT_code *out,
        const CT_code *in);

    NDDSUSERDllExport extern void 
    CT_codePluginSupport_destroy_data_w_params(
        CT_code *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_codePluginSupport_destroy_data_ex(
        CT_code *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_codePluginSupport_destroy_data(
        CT_code *sample);

    NDDSUSERDllExport extern void 
    CT_codePluginSupport_print_data(
        const CT_code *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_codePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_code *out,
        const CT_code *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_codePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_code *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_codePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_code *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_codePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_codePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_codePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_codePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_codePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_code * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_codePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_codePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_codePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_codePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_code *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_codePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_code * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_codePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_code *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_idPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_idPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_idPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_idPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_idPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_id*
    CT_idPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_id*
    CT_idPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_id*
    CT_idPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_idPluginSupport_copy_data(
        CT_id *out,
        const CT_id *in);

    NDDSUSERDllExport extern void 
    CT_idPluginSupport_destroy_data_w_params(
        CT_id *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_idPluginSupport_destroy_data_ex(
        CT_id *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_idPluginSupport_destroy_data(
        CT_id *sample);

    NDDSUSERDllExport extern void 
    CT_idPluginSupport_print_data(
        const CT_id *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_idPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_id *out,
        const CT_id *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_idPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_id *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_idPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_id *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_idPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_idPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_idPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_idPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_idPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_id * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_idPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_idPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_idPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_idPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_id *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_idPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_id * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_idPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_id *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CT_uriPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CT_uriPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CT_uriPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CT_uriPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CT_uriPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CT_uri*
    CT_uriPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CT_uri*
    CT_uriPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CT_uri*
    CT_uriPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CT_uriPluginSupport_copy_data(
        CT_uri *out,
        const CT_uri *in);

    NDDSUSERDllExport extern void 
    CT_uriPluginSupport_destroy_data_w_params(
        CT_uri *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CT_uriPluginSupport_destroy_data_ex(
        CT_uri *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CT_uriPluginSupport_destroy_data(
        CT_uri *sample);

    NDDSUSERDllExport extern void 
    CT_uriPluginSupport_print_data(
        const CT_uri *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_uriPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_uri *out,
        const CT_uri *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CT_uriPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CT_uri *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_uriPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_uri *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_uriPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CT_uriPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CT_uriPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_uriPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CT_uriPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CT_uri * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CT_uriPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CT_uriPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CT_uriPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CT_uriPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CT_uri *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CT_uriPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CT_uri * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CT_uriPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CT_uri *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CodingPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CodingPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CodingPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CodingPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CodingPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Coding*
    CodingPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Coding*
    CodingPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Coding*
    CodingPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CodingPluginSupport_copy_data(
        Coding *out,
        const Coding *in);

    NDDSUSERDllExport extern void 
    CodingPluginSupport_destroy_data_w_params(
        Coding *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CodingPluginSupport_destroy_data_ex(
        Coding *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CodingPluginSupport_destroy_data(
        Coding *sample);

    NDDSUSERDllExport extern void 
    CodingPluginSupport_print_data(
        const Coding *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Coding *out,
        const Coding *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Coding *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Coding *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodingPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Coding *sample); 

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Coding **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodingPlugin_deserialize_from_cdr_buffer(
        Coding *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    CodingPlugin_data_to_string(
        const Coding *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    CodingPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CodingPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CodingPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CodingPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CodingPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Coding * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CodingPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CodingPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CodingPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Coding *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Coding * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodingPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Coding ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodingPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Coding *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define CodeableConceptPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define CodeableConceptPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define CodeableConceptPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define CodeableConceptPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define CodeableConceptPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern CodeableConcept*
    CodeableConceptPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern CodeableConcept*
    CodeableConceptPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern CodeableConcept*
    CodeableConceptPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPluginSupport_copy_data(
        CodeableConcept *out,
        const CodeableConcept *in);

    NDDSUSERDllExport extern void 
    CodeableConceptPluginSupport_destroy_data_w_params(
        CodeableConcept *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    CodeableConceptPluginSupport_destroy_data_ex(
        CodeableConcept *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    CodeableConceptPluginSupport_destroy_data(
        CodeableConcept *sample);

    NDDSUSERDllExport extern void 
    CodeableConceptPluginSupport_print_data(
        const CodeableConcept *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept *out,
        const CodeableConcept *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const CodeableConcept *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodeableConceptPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const CodeableConcept *sample); 

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodeableConceptPlugin_deserialize_from_cdr_buffer(
        CodeableConcept *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    CodeableConceptPlugin_data_to_string(
        const CodeableConcept *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    CodeableConceptPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    CodeableConceptPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    CodeableConceptPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CodeableConceptPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    CodeableConceptPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const CodeableConcept * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    CodeableConceptPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    CodeableConceptPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    CodeableConceptPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const CodeableConcept *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    CodeableConceptPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    CodeableConceptPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        CodeableConcept *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define SimpleQuantityPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define SimpleQuantityPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define SimpleQuantityPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define SimpleQuantityPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define SimpleQuantityPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern SimpleQuantity*
    SimpleQuantityPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern SimpleQuantity*
    SimpleQuantityPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SimpleQuantity*
    SimpleQuantityPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPluginSupport_copy_data(
        SimpleQuantity *out,
        const SimpleQuantity *in);

    NDDSUSERDllExport extern void 
    SimpleQuantityPluginSupport_destroy_data_w_params(
        SimpleQuantity *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    SimpleQuantityPluginSupport_destroy_data_ex(
        SimpleQuantity *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    SimpleQuantityPluginSupport_destroy_data(
        SimpleQuantity *sample);

    NDDSUSERDllExport extern void 
    SimpleQuantityPluginSupport_print_data(
        const SimpleQuantity *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity *out,
        const SimpleQuantity *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SimpleQuantity *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SimpleQuantityPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const SimpleQuantity *sample); 

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SimpleQuantityPlugin_deserialize_from_cdr_buffer(
        SimpleQuantity *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    SimpleQuantityPlugin_data_to_string(
        const SimpleQuantity *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    SimpleQuantityPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    SimpleQuantityPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    SimpleQuantityPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SimpleQuantityPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SimpleQuantityPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SimpleQuantity * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    SimpleQuantityPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    SimpleQuantityPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SimpleQuantityPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SimpleQuantity *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SimpleQuantityPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SimpleQuantityPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SimpleQuantity *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define QuantityPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define QuantityPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define QuantityPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define QuantityPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define QuantityPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Quantity*
    QuantityPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Quantity*
    QuantityPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Quantity*
    QuantityPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    QuantityPluginSupport_copy_data(
        Quantity *out,
        const Quantity *in);

    NDDSUSERDllExport extern void 
    QuantityPluginSupport_destroy_data_w_params(
        Quantity *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    QuantityPluginSupport_destroy_data_ex(
        Quantity *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    QuantityPluginSupport_destroy_data(
        Quantity *sample);

    NDDSUSERDllExport extern void 
    QuantityPluginSupport_print_data(
        const Quantity *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Quantity *out,
        const Quantity *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Quantity *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Quantity *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    QuantityPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Quantity *sample); 

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Quantity **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    QuantityPlugin_deserialize_from_cdr_buffer(
        Quantity *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    QuantityPlugin_data_to_string(
        const Quantity *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    QuantityPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    QuantityPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    QuantityPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    QuantityPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    QuantityPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Quantity * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    QuantityPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    QuantityPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    QuantityPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Quantity *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Quantity * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    QuantityPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Quantity ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    QuantityPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Quantity *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define RangePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define RangePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define RangePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define RangePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define RangePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Range*
    RangePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Range*
    RangePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Range*
    RangePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    RangePluginSupport_copy_data(
        Range *out,
        const Range *in);

    NDDSUSERDllExport extern void 
    RangePluginSupport_destroy_data_w_params(
        Range *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    RangePluginSupport_destroy_data_ex(
        Range *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    RangePluginSupport_destroy_data(
        Range *sample);

    NDDSUSERDllExport extern void 
    RangePluginSupport_print_data(
        const Range *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Range *out,
        const Range *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Range *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Range *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RangePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Range *sample); 

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Range **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RangePlugin_deserialize_from_cdr_buffer(
        Range *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    RangePlugin_data_to_string(
        const Range *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    RangePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    RangePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    RangePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    RangePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    RangePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Range * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    RangePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    RangePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    RangePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Range *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Range * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RangePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Range ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RangePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Range *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define RatioPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define RatioPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define RatioPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define RatioPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define RatioPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Ratio*
    RatioPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Ratio*
    RatioPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Ratio*
    RatioPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    RatioPluginSupport_copy_data(
        Ratio *out,
        const Ratio *in);

    NDDSUSERDllExport extern void 
    RatioPluginSupport_destroy_data_w_params(
        Ratio *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    RatioPluginSupport_destroy_data_ex(
        Ratio *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    RatioPluginSupport_destroy_data(
        Ratio *sample);

    NDDSUSERDllExport extern void 
    RatioPluginSupport_print_data(
        const Ratio *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Ratio *out,
        const Ratio *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Ratio *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Ratio *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RatioPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Ratio *sample); 

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Ratio **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RatioPlugin_deserialize_from_cdr_buffer(
        Ratio *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    RatioPlugin_data_to_string(
        const Ratio *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    RatioPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    RatioPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    RatioPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    RatioPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    RatioPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Ratio * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    RatioPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    RatioPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    RatioPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Ratio *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Ratio * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    RatioPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Ratio ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    RatioPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Ratio *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define PeriodPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define PeriodPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define PeriodPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define PeriodPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define PeriodPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Period*
    PeriodPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Period*
    PeriodPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Period*
    PeriodPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    PeriodPluginSupport_copy_data(
        Period *out,
        const Period *in);

    NDDSUSERDllExport extern void 
    PeriodPluginSupport_destroy_data_w_params(
        Period *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    PeriodPluginSupport_destroy_data_ex(
        Period *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    PeriodPluginSupport_destroy_data(
        Period *sample);

    NDDSUSERDllExport extern void 
    PeriodPluginSupport_print_data(
        const Period *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Period *out,
        const Period *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Period *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Period *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PeriodPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Period *sample); 

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Period **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PeriodPlugin_deserialize_from_cdr_buffer(
        Period *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    PeriodPlugin_data_to_string(
        const Period *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    PeriodPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    PeriodPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    PeriodPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PeriodPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    PeriodPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Period * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    PeriodPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    PeriodPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    PeriodPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Period *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Period * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    PeriodPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Period ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    PeriodPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Period *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimeTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EffectiveTimeType *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimeTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTimeType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EffectiveTimeTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimeTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimeTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimeTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EffectiveTimeTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EffectiveTimeType * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimeTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimeTypePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimeTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EffectiveTimeType *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimeTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTimeType * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EffectiveTimeTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTimeType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    EffectiveTimeTypePluginSupport_print_data(
        const EffectiveTimeType *sample, const char *desc, int indent_level);

    #define EffectiveTimePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EffectiveTimePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EffectiveTimePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EffectiveTimePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EffectiveTimePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EffectiveTime*
    EffectiveTimePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EffectiveTime*
    EffectiveTimePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EffectiveTime*
    EffectiveTimePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePluginSupport_copy_data(
        EffectiveTime *out,
        const EffectiveTime *in);

    NDDSUSERDllExport extern void 
    EffectiveTimePluginSupport_destroy_data_w_params(
        EffectiveTime *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EffectiveTimePluginSupport_destroy_data_ex(
        EffectiveTime *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EffectiveTimePluginSupport_destroy_data(
        EffectiveTime *sample);

    NDDSUSERDllExport extern void 
    EffectiveTimePluginSupport_print_data(
        const EffectiveTime *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime *out,
        const EffectiveTime *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const EffectiveTime *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EffectiveTimePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const EffectiveTime *sample); 

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EffectiveTimePlugin_deserialize_from_cdr_buffer(
        EffectiveTime *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    EffectiveTimePlugin_data_to_string(
        const EffectiveTime *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    EffectiveTimePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EffectiveTimePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const EffectiveTime * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EffectiveTimePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EffectiveTimePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const EffectiveTime *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EffectiveTimePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EffectiveTimePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EffectiveTime *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

} /* namespace ice  */

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* commonPlugin_1183388197_h */

