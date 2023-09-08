

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from metric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef metricPlugin_611712278_h
#define metricPlugin_611712278_h

#include "metric.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#include "commonPlugin.h"

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace ice {

    #define MetricSourceListPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricSourceListPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricSourceListPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricSourceListPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricSourceListPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricSourceList*
    MetricSourceListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricSourceList*
    MetricSourceListPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricSourceList*
    MetricSourceListPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPluginSupport_copy_data(
        MetricSourceList *out,
        const MetricSourceList *in);

    NDDSUSERDllExport extern void 
    MetricSourceListPluginSupport_destroy_data_w_params(
        MetricSourceList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricSourceListPluginSupport_destroy_data_ex(
        MetricSourceList *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricSourceListPluginSupport_destroy_data(
        MetricSourceList *sample);

    NDDSUSERDllExport extern void 
    MetricSourceListPluginSupport_print_data(
        const MetricSourceList *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *out,
        const MetricSourceList *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricSourceListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricSourceListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricSourceListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricSourceListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricSourceList * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricSourceListPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricSourceListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricSourceListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSourceList *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricSourceListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricSourceListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define SiteListPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define SiteListPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define SiteListPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define SiteListPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define SiteListPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern SiteList*
    SiteListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern SiteList*
    SiteListPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SiteList*
    SiteListPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    SiteListPluginSupport_copy_data(
        SiteList *out,
        const SiteList *in);

    NDDSUSERDllExport extern void 
    SiteListPluginSupport_destroy_data_w_params(
        SiteList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    SiteListPluginSupport_destroy_data_ex(
        SiteList *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    SiteListPluginSupport_destroy_data(
        SiteList *sample);

    NDDSUSERDllExport extern void 
    SiteListPluginSupport_print_data(
        const SiteList *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SiteListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *out,
        const SiteList *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    SiteListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SiteList *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SiteListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SiteListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    SiteListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    SiteListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SiteListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SiteListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SiteList * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    SiteListPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    SiteListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    SiteListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    SiteListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SiteList *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    SiteListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SiteListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define MetricStatusPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricStatusPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricStatusPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricStatusPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricStatusPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricStatus*
    MetricStatusPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricStatus*
    MetricStatusPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricStatus*
    MetricStatusPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPluginSupport_copy_data(
        MetricStatus *out,
        const MetricStatus *in);

    NDDSUSERDllExport extern void 
    MetricStatusPluginSupport_destroy_data_w_params(
        MetricStatus *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricStatusPluginSupport_destroy_data_ex(
        MetricStatus *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricStatusPluginSupport_destroy_data(
        MetricStatus *sample);

    NDDSUSERDllExport extern void 
    MetricStatusPluginSupport_print_data(
        const MetricStatus *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *out,
        const MetricStatus *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricStatusPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricStatusPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricStatus * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricStatusPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatus *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricStatusPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricStatusBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricStatusBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricStatusBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricStatusBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricStatusBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricStatusBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricStatusBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatusBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricStatusBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricStatusBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricStatusBitsPluginSupport_print_data(
        const MetricStatusBits *sample, const char *desc, int indent_level);

    #define MetricAccessPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricAccessPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricAccessPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricAccessPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricAccessPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricAccess*
    MetricAccessPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricAccess*
    MetricAccessPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricAccess*
    MetricAccessPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPluginSupport_copy_data(
        MetricAccess *out,
        const MetricAccess *in);

    NDDSUSERDllExport extern void 
    MetricAccessPluginSupport_destroy_data_w_params(
        MetricAccess *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricAccessPluginSupport_destroy_data_ex(
        MetricAccess *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricAccessPluginSupport_destroy_data(
        MetricAccess *sample);

    NDDSUSERDllExport extern void 
    MetricAccessPluginSupport_print_data(
        const MetricAccess *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *out,
        const MetricAccess *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccess *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricAccessPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricAccessPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricAccessPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricAccess * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricAccessPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccess *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricAccessPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricAccessBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccessBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricAccessBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricAccessBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricAccessBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricAccessBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricAccessBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricAccessBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccessBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricAccessBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricAccessBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricAccessBitsPluginSupport_print_data(
        const MetricAccessBits *sample, const char *desc, int indent_level);

    #define MetricRelevancePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricRelevancePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricRelevancePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricRelevancePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricRelevancePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricRelevance*
    MetricRelevancePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricRelevance*
    MetricRelevancePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricRelevance*
    MetricRelevancePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePluginSupport_copy_data(
        MetricRelevance *out,
        const MetricRelevance *in);

    NDDSUSERDllExport extern void 
    MetricRelevancePluginSupport_destroy_data_w_params(
        MetricRelevance *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricRelevancePluginSupport_destroy_data_ex(
        MetricRelevance *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricRelevancePluginSupport_destroy_data(
        MetricRelevance *sample);

    NDDSUSERDllExport extern void 
    MetricRelevancePluginSupport_print_data(
        const MetricRelevance *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *out,
        const MetricRelevance *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevance *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricRelevancePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevancePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricRelevancePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevancePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricRelevancePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricRelevance * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricRelevancePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevancePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevancePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevance *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevancePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricRelevancePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricRelevanceBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevanceBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevanceBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricRelevanceBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricRelevanceBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricRelevanceBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevanceBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevanceBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricRelevanceBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricRelevanceBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricRelevanceBitsPluginSupport_print_data(
        const MetricRelevanceBits *sample, const char *desc, int indent_level);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCategoryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCategory *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCategoryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCategoryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricCategoryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricCategoryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCategoryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricCategoryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCategory * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricCategoryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCategoryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricCategoryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCategory *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCategoryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCategoryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricCategoryPluginSupport_print_data(
        const MetricCategory *sample, const char *desc, int indent_level);

    #define MetricSpecPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricSpecPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricSpecPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricSpecPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricSpecPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricSpec*
    MetricSpecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricSpec*
    MetricSpecPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricSpec*
    MetricSpecPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPluginSupport_copy_data(
        MetricSpec *out,
        const MetricSpec *in);

    NDDSUSERDllExport extern void 
    MetricSpecPluginSupport_destroy_data_w_params(
        MetricSpec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricSpecPluginSupport_destroy_data_ex(
        MetricSpec *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricSpecPluginSupport_destroy_data(
        MetricSpec *sample);

    NDDSUSERDllExport extern void 
    MetricSpecPluginSupport_print_data(
        const MetricSpec *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *out,
        const MetricSpec *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricSpecPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricSpec *sample); 

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricSpecPlugin_deserialize_from_cdr_buffer(
        MetricSpec *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MetricSpecPlugin_data_to_string(
        const MetricSpec *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    MetricSpecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricSpecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricSpecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricSpecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricSpecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricSpec * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricSpecPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricSpecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricSpecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSpec *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricSpecPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricSpecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define VmoSourceEntryPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define VmoSourceEntryPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define VmoSourceEntryPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define VmoSourceEntryPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define VmoSourceEntryPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern VmoSourceEntry*
    VmoSourceEntryPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern VmoSourceEntry*
    VmoSourceEntryPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern VmoSourceEntry*
    VmoSourceEntryPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPluginSupport_copy_data(
        VmoSourceEntry *out,
        const VmoSourceEntry *in);

    NDDSUSERDllExport extern void 
    VmoSourceEntryPluginSupport_destroy_data_w_params(
        VmoSourceEntry *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    VmoSourceEntryPluginSupport_destroy_data_ex(
        VmoSourceEntry *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    VmoSourceEntryPluginSupport_destroy_data(
        VmoSourceEntry *sample);

    NDDSUSERDllExport extern void 
    VmoSourceEntryPluginSupport_print_data(
        const VmoSourceEntry *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *out,
        const VmoSourceEntry *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VmoSourceEntryPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const VmoSourceEntry *sample); 

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VmoSourceEntryPlugin_deserialize_from_cdr_buffer(
        VmoSourceEntry *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    VmoSourceEntryPlugin_data_to_string(
        const VmoSourceEntry *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    VmoSourceEntryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    VmoSourceEntryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const VmoSourceEntry * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    VmoSourceEntryPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceEntryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceEntryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceEntry *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceEntryPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VmoSourceEntryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define VmoSourceListPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define VmoSourceListPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define VmoSourceListPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define VmoSourceListPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define VmoSourceListPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern VmoSourceList*
    VmoSourceListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern VmoSourceList*
    VmoSourceListPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern VmoSourceList*
    VmoSourceListPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPluginSupport_copy_data(
        VmoSourceList *out,
        const VmoSourceList *in);

    NDDSUSERDllExport extern void 
    VmoSourceListPluginSupport_destroy_data_w_params(
        VmoSourceList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    VmoSourceListPluginSupport_destroy_data_ex(
        VmoSourceList *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    VmoSourceListPluginSupport_destroy_data(
        VmoSourceList *sample);

    NDDSUSERDllExport extern void 
    VmoSourceListPluginSupport_print_data(
        const VmoSourceList *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *out,
        const VmoSourceList *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VmoSourceListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    VmoSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    VmoSourceListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const VmoSourceList * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    VmoSourceListPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VmoSourceListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceList *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VmoSourceListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VmoSourceListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define MeasurementStatusPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MeasurementStatusPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MeasurementStatusPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MeasurementStatusPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MeasurementStatusPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MeasurementStatus*
    MeasurementStatusPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MeasurementStatus*
    MeasurementStatusPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MeasurementStatus*
    MeasurementStatusPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPluginSupport_copy_data(
        MeasurementStatus *out,
        const MeasurementStatus *in);

    NDDSUSERDllExport extern void 
    MeasurementStatusPluginSupport_destroy_data_w_params(
        MeasurementStatus *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MeasurementStatusPluginSupport_destroy_data_ex(
        MeasurementStatus *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MeasurementStatusPluginSupport_destroy_data(
        MeasurementStatus *sample);

    NDDSUSERDllExport extern void 
    MeasurementStatusPluginSupport_print_data(
        const MeasurementStatus *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *out,
        const MeasurementStatus *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MeasurementStatusPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MeasurementStatusPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MeasurementStatus * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MeasurementStatusPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatus *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MeasurementStatusPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MeasurementStatusBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MeasurementStatusBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MeasurementStatusBits * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatusBits *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MeasurementStatusBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MeasurementStatusBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MeasurementStatusBitsPluginSupport_print_data(
        const MeasurementStatusBits *sample, const char *desc, int indent_level);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalStatePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalState *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalStatePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalStatePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricCalStatePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricCalStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalStatePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricCalStatePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalState * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricCalStatePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricCalStatePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalState *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalStatePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalStatePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricCalStatePluginSupport_print_data(
        const MetricCalState *sample, const char *desc, int indent_level);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalType *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricCalTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricCalTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricCalTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalType * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    MetricCalTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalTypePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricCalTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalType *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern void
    MetricCalTypePluginSupport_print_data(
        const MetricCalType *sample, const char *desc, int indent_level);

    #define MetricCalEntryPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricCalEntryPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricCalEntryPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricCalEntryPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricCalEntryPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricCalEntry*
    MetricCalEntryPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricCalEntry*
    MetricCalEntryPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricCalEntry*
    MetricCalEntryPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPluginSupport_copy_data(
        MetricCalEntry *out,
        const MetricCalEntry *in);

    NDDSUSERDllExport extern void 
    MetricCalEntryPluginSupport_destroy_data_w_params(
        MetricCalEntry *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricCalEntryPluginSupport_destroy_data_ex(
        MetricCalEntry *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricCalEntryPluginSupport_destroy_data(
        MetricCalEntry *sample);

    NDDSUSERDllExport extern void 
    MetricCalEntryPluginSupport_print_data(
        const MetricCalEntry *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *out,
        const MetricCalEntry *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalEntryPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricCalEntry *sample); 

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalEntryPlugin_deserialize_from_cdr_buffer(
        MetricCalEntry *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MetricCalEntryPlugin_data_to_string(
        const MetricCalEntry *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    MetricCalEntryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricCalEntryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalEntry * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricCalEntryPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricCalEntryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalEntryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalEntry *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalEntryPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalEntryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define MetricCalibrationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricCalibrationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricCalibrationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricCalibrationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricCalibrationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricCalibration*
    MetricCalibrationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricCalibration*
    MetricCalibrationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricCalibration*
    MetricCalibrationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPluginSupport_copy_data(
        MetricCalibration *out,
        const MetricCalibration *in);

    NDDSUSERDllExport extern void 
    MetricCalibrationPluginSupport_destroy_data_w_params(
        MetricCalibration *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricCalibrationPluginSupport_destroy_data_ex(
        MetricCalibration *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricCalibrationPluginSupport_destroy_data(
        MetricCalibration *sample);

    NDDSUSERDllExport extern void 
    MetricCalibrationPluginSupport_print_data(
        const MetricCalibration *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *out,
        const MetricCalibration *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalibration *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalibrationPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricCalibrationPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalibration * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricCalibrationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricCalibrationPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricCalibrationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalibration *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricCalibrationPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricCalibrationPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    #define MetricMeasurePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricMeasurePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricMeasurePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricMeasurePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricMeasurePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricMeasure*
    MetricMeasurePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricMeasure*
    MetricMeasurePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricMeasure*
    MetricMeasurePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePluginSupport_copy_data(
        MetricMeasure *out,
        const MetricMeasure *in);

    NDDSUSERDllExport extern void 
    MetricMeasurePluginSupport_destroy_data_w_params(
        MetricMeasure *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricMeasurePluginSupport_destroy_data_ex(
        MetricMeasure *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricMeasurePluginSupport_destroy_data(
        MetricMeasure *sample);

    NDDSUSERDllExport extern void 
    MetricMeasurePluginSupport_print_data(
        const MetricMeasure *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *out,
        const MetricMeasure *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricMeasure *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricMeasurePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricMeasure *sample); 

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricMeasurePlugin_deserialize_from_cdr_buffer(
        MetricMeasure *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MetricMeasurePlugin_data_to_string(
        const MetricMeasure *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    MetricMeasurePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricMeasurePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricMeasurePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricMeasurePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricMeasurePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricMeasure * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricMeasurePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricMeasurePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricMeasurePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricMeasure *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricMeasurePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricMeasurePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct MetricContext
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct MetricContext)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * MetricContext must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct MetricContext.
    */
    typedef  class MetricContext MetricContextKeyHolder;

    #define MetricContextPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricContextPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricContextPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricContextPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define MetricContextPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define MetricContextPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricContextPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricContext*
    MetricContextPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricContext*
    MetricContextPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricContext*
    MetricContextPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPluginSupport_copy_data(
        MetricContext *out,
        const MetricContext *in);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_destroy_data_w_params(
        MetricContext *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_destroy_data_ex(
        MetricContext *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_destroy_data(
        MetricContext *sample);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_print_data(
        const MetricContext *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern MetricContext*
    MetricContextPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricContext*
    MetricContextPluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_destroy_key_ex(
        MetricContextKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricContextPluginSupport_destroy_key(
        MetricContextKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *out,
        const MetricContext *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricContext *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricContextPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricContext *sample); 

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricContextPlugin_deserialize_from_cdr_buffer(
        MetricContext *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MetricContextPlugin_data_to_string(
        const MetricContext *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    MetricContextPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricContextPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricContextPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricContextPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricContext * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricContextPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricContextPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricContextPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricContext *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricContextPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContextKeyHolder *key, 
        const MetricContext *instance);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *instance, 
        const MetricContextKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const MetricContext *instance);

    NDDSUSERDllExport extern RTIBool 
    MetricContextPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct MetricObservedValue
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct MetricObservedValue)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * MetricObservedValue must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct MetricObservedValue.
    */
    typedef  class MetricObservedValue MetricObservedValueKeyHolder;

    #define MetricObservedValuePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define MetricObservedValuePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MetricObservedValuePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define MetricObservedValuePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define MetricObservedValuePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define MetricObservedValuePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MetricObservedValuePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MetricObservedValue*
    MetricObservedValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MetricObservedValue*
    MetricObservedValuePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricObservedValue*
    MetricObservedValuePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePluginSupport_copy_data(
        MetricObservedValue *out,
        const MetricObservedValue *in);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_destroy_data_w_params(
        MetricObservedValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_destroy_data_ex(
        MetricObservedValue *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_destroy_data(
        MetricObservedValue *sample);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_print_data(
        const MetricObservedValue *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern MetricObservedValue*
    MetricObservedValuePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MetricObservedValue*
    MetricObservedValuePluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_destroy_key_ex(
        MetricObservedValueKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MetricObservedValuePluginSupport_destroy_key(
        MetricObservedValueKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *out,
        const MetricObservedValue *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricObservedValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricObservedValue *sample); 

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricObservedValuePlugin_deserialize_from_cdr_buffer(
        MetricObservedValue *sample,
        const char * buffer,
        unsigned int length);    
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MetricObservedValuePlugin_data_to_string(
        const MetricObservedValue *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    

    NDDSUSERDllExport extern RTIBool
    MetricObservedValuePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    MetricObservedValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricObservedValue * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MetricObservedValuePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MetricObservedValuePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MetricObservedValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricObservedValue *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MetricObservedValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValueKeyHolder *key, 
        const MetricObservedValue *instance);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *instance, 
        const MetricObservedValueKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const MetricObservedValue *instance);

    NDDSUSERDllExport extern RTIBool 
    MetricObservedValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

} /* namespace ice  */

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* metricPlugin_611712278_h */

