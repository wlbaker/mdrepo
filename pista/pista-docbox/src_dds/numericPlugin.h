

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from numeric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef numericPlugin_67916774_h
#define numericPlugin_67916774_h

#include "numeric.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#include "metricPlugin.h"

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace ice {

    #define AbsoluteRangePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define AbsoluteRangePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define AbsoluteRangePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define AbsoluteRangePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define AbsoluteRangePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern AbsoluteRange*
    AbsoluteRangePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern AbsoluteRange*
    AbsoluteRangePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern AbsoluteRange*
    AbsoluteRangePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePluginSupport_copy_data(
        AbsoluteRange *out,
        const AbsoluteRange *in);

    NDDSUSERDllExport extern void 
    AbsoluteRangePluginSupport_destroy_data_w_params(
        AbsoluteRange *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    AbsoluteRangePluginSupport_destroy_data_ex(
        AbsoluteRange *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    AbsoluteRangePluginSupport_destroy_data(
        AbsoluteRange *sample);

    NDDSUSERDllExport extern void 
    AbsoluteRangePluginSupport_print_data(
        const AbsoluteRange *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *out,
        const AbsoluteRange *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const AbsoluteRange *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    AbsoluteRangePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const AbsoluteRange *sample); 

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    AbsoluteRangePlugin_deserialize_from_cdr_buffer(
        AbsoluteRange *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    AbsoluteRangePlugin_data_to_string(
        const AbsoluteRange *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    AbsoluteRangePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    AbsoluteRangePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const AbsoluteRange * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    AbsoluteRangePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    AbsoluteRangePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    AbsoluteRangePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const AbsoluteRange *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    AbsoluteRangePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    AbsoluteRangePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define DispResolutionPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define DispResolutionPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define DispResolutionPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define DispResolutionPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define DispResolutionPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern DispResolution*
    DispResolutionPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern DispResolution*
    DispResolutionPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DispResolution*
    DispResolutionPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPluginSupport_copy_data(
        DispResolution *out,
        const DispResolution *in);

    NDDSUSERDllExport extern void 
    DispResolutionPluginSupport_destroy_data_w_params(
        DispResolution *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    DispResolutionPluginSupport_destroy_data_ex(
        DispResolution *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    DispResolutionPluginSupport_destroy_data(
        DispResolution *sample);

    NDDSUSERDllExport extern void 
    DispResolutionPluginSupport_print_data(
        const DispResolution *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *out,
        const DispResolution *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const DispResolution *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DispResolutionPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DispResolution *sample); 

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DispResolutionPlugin_deserialize_from_cdr_buffer(
        DispResolution *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    DispResolutionPlugin_data_to_string(
        const DispResolution *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    DispResolutionPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    DispResolutionPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    DispResolutionPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DispResolutionPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    DispResolutionPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const DispResolution * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    DispResolutionPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    DispResolutionPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DispResolutionPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const DispResolution *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    DispResolutionPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DispResolutionPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct NuObsValue
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct NuObsValue)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * NuObsValue must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct NuObsValue.
    */
    typedef  class NuObsValue NuObsValueKeyHolder;

    #define NuObsValuePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define NuObsValuePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define NuObsValuePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define NuObsValuePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define NuObsValuePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define NuObsValuePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define NuObsValuePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern NuObsValue*
    NuObsValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern NuObsValue*
    NuObsValuePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NuObsValue*
    NuObsValuePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePluginSupport_copy_data(
        NuObsValue *out,
        const NuObsValue *in);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_destroy_data_w_params(
        NuObsValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_destroy_data_ex(
        NuObsValue *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_destroy_data(
        NuObsValue *sample);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_print_data(
        const NuObsValue *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern NuObsValue*
    NuObsValuePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NuObsValue*
    NuObsValuePluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_destroy_key_ex(
        NuObsValueKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NuObsValuePluginSupport_destroy_key(
        NuObsValueKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *out,
        const NuObsValue *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NuObsValue *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NuObsValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NuObsValue *sample); 

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NuObsValuePlugin_deserialize_from_cdr_buffer(
        NuObsValue *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    NuObsValuePlugin_data_to_string(
        const NuObsValue *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    NuObsValuePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    NuObsValuePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    NuObsValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NuObsValuePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    NuObsValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NuObsValue * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    NuObsValuePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    NuObsValuePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NuObsValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NuObsValue *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NuObsValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValueKeyHolder *key, 
        const NuObsValue *instance);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *instance, 
        const NuObsValueKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NuObsValue *instance);

    NDDSUSERDllExport extern RTIBool 
    NuObsValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct NumericContext
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct NumericContext)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * NumericContext must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct NumericContext.
    */
    typedef  class NumericContext NumericContextKeyHolder;

    #define NumericContextPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define NumericContextPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define NumericContextPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define NumericContextPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define NumericContextPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define NumericContextPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define NumericContextPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern NumericContext*
    NumericContextPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern NumericContext*
    NumericContextPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NumericContext*
    NumericContextPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPluginSupport_copy_data(
        NumericContext *out,
        const NumericContext *in);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_destroy_data_w_params(
        NumericContext *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_destroy_data_ex(
        NumericContext *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_destroy_data(
        NumericContext *sample);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_print_data(
        const NumericContext *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern NumericContext*
    NumericContextPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NumericContext*
    NumericContextPluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_destroy_key_ex(
        NumericContextKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NumericContextPluginSupport_destroy_key(
        NumericContextKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    NumericContextPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    NumericContextPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    NumericContextPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    NumericContextPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    NumericContextPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *out,
        const NumericContext *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NumericContext *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericContextPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NumericContext *sample); 

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericContextPlugin_deserialize_from_cdr_buffer(
        NumericContext *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    NumericContextPlugin_data_to_string(
        const NumericContext *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    NumericContextPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    NumericContextPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    NumericContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NumericContextPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    NumericContextPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NumericContext * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    NumericContextPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    NumericContextPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NumericContextPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NumericContext *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericContextPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContextKeyHolder *key, 
        const NumericContext *instance);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *instance, 
        const NumericContextKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NumericContext *instance);

    NDDSUSERDllExport extern RTIBool 
    NumericContextPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    NumericContextPlugin_new(void);

    NDDSUSERDllExport extern void
    NumericContextPlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct NumericObservedValue
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct NumericObservedValue)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * NumericObservedValue must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct NumericObservedValue.
    */
    typedef  class NumericObservedValue NumericObservedValueKeyHolder;

    #define NumericObservedValuePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define NumericObservedValuePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define NumericObservedValuePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define NumericObservedValuePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define NumericObservedValuePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define NumericObservedValuePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define NumericObservedValuePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern NumericObservedValue*
    NumericObservedValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern NumericObservedValue*
    NumericObservedValuePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NumericObservedValue*
    NumericObservedValuePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePluginSupport_copy_data(
        NumericObservedValue *out,
        const NumericObservedValue *in);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_destroy_data_w_params(
        NumericObservedValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_destroy_data_ex(
        NumericObservedValue *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_destroy_data(
        NumericObservedValue *sample);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_print_data(
        const NumericObservedValue *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern NumericObservedValue*
    NumericObservedValuePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern NumericObservedValue*
    NumericObservedValuePluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_destroy_key_ex(
        NumericObservedValueKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    NumericObservedValuePluginSupport_destroy_key(
        NumericObservedValueKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    NumericObservedValuePlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    NumericObservedValuePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    NumericObservedValuePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    NumericObservedValuePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    NumericObservedValuePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *out,
        const NumericObservedValue *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NumericObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericObservedValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NumericObservedValue *sample); 

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericObservedValuePlugin_deserialize_from_cdr_buffer(
        NumericObservedValue *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    NumericObservedValuePlugin_data_to_string(
        const NumericObservedValue *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    NumericObservedValuePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    NumericObservedValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NumericObservedValue * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    NumericObservedValuePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    NumericObservedValuePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    NumericObservedValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NumericObservedValue *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    NumericObservedValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValueKeyHolder *key, 
        const NumericObservedValue *instance);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *instance, 
        const NumericObservedValueKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NumericObservedValue *instance);

    NDDSUSERDllExport extern RTIBool 
    NumericObservedValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    NumericObservedValuePlugin_new(void);

    NDDSUSERDllExport extern void
    NumericObservedValuePlugin_delete(struct PRESTypePlugin *);

} /* namespace ice  */

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* numericPlugin_67916774_h */

