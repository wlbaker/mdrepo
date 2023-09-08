
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from metric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include <string.h>

#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif

#ifndef osapi_type_h
#include "osapi/osapi_type.h"
#endif
#ifndef osapi_heap_h
#include "osapi/osapi_heap.h"
#endif

#ifndef osapi_utility_h
#include "osapi/osapi_utility.h"
#endif

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif

#ifndef cdr_type_object_h
#include "cdr/cdr_typeObject.h"
#endif

#ifndef cdr_encapsulation_h
#include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
#include "cdr/cdr_stream.h"
#endif

#ifndef cdr_log_h
#include "cdr/cdr_log.h"
#endif

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#define RTI_CDR_CURRENT_SUBMODULE RTI_CDR_SUBMODULE_MASK_STREAM

#include <new>

#include "metricPlugin.h"

namespace ice {

    /* ----------------------------------------------------------------------------
    *  Type MetricSourceList
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricSourceList*
    MetricSourceListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricSourceList *sample = NULL;

        sample = new (std::nothrow) MetricSourceList ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricSourceList_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricSourceList *
    MetricSourceListPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricSourceList *sample = NULL;

        sample = new (std::nothrow) MetricSourceList ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricSourceList_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricSourceList *
    MetricSourceListPluginSupport_create_data(void)
    {
        return ice::MetricSourceListPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricSourceListPluginSupport_destroy_data_w_params(
        MetricSourceList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricSourceList_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricSourceListPluginSupport_destroy_data_ex(
        MetricSourceList *sample,RTIBool deallocate_pointers) {

        ice::MetricSourceList_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricSourceListPluginSupport_destroy_data(
        MetricSourceList *sample) {

        ice::MetricSourceListPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricSourceListPluginSupport_copy_data(
        MetricSourceList *dst,
        const MetricSourceList *src)
    {
        return ice::MetricSourceList_copy(dst,(const MetricSourceList*) src);
    }

    void 
    MetricSourceListPluginSupport_print_data(
        const MetricSourceList *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
            RTICdrType_printArray(
                ice::OIDTypeSeq_get_contiguous_bufferI(sample), 
                ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypePrintFunction)ice::OIDTypePluginSupport_print_data,
                "", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                ice::OIDTypeSeq_get_discontiguous_bufferI(sample), 
                ice::OIDTypeSeq_get_length(sample),
                (RTICdrTypePrintFunction)ice::OIDTypePluginSupport_print_data,
                "", indent_level + 1);
        }

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricSourceListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *dst,
        const MetricSourceList *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricSourceListPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricSourceListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSourceList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    sizeof(ice::OIDType),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricSourceListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricSourceList_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            sizeof(ice::OIDType),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::OIDTypeSeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricSourceListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            {
                RTICdrUnsignedLong sequence_length;
                if (!RTICdrStream_skipNonPrimitiveSequence(
                    stream,
                    &sequence_length,
                    sizeof(ice::OIDType),
                    (RTICdrStreamSkipFunction)ice::OIDTypePlugin_skip,
                    RTI_FALSE,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricSourceListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::OIDTypePlugin_get_serialized_sample_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricSourceListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricSourceListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
            current_alignment, 0,
            ice::OIDTypePlugin_get_serialized_sample_min_size,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricSourceListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricSourceList * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += RTICdrType_get4ByteMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
            current_alignment += RTICdrType_getNonPrimitiveArraySerializedSize(
                current_alignment, ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::OIDTypePlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                endpoint_data);
        } else {
            current_alignment += RTICdrStream_getNonPrimitivePointerArraySerializedSize(
                current_alignment,  
                ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::OIDTypePlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                (const void **)ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                endpoint_data);
        }

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricSourceListPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricSourceListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSourceList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    sizeof(ice::OIDType),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricSourceListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            sizeof(ice::OIDType),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::OIDTypeSeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricSourceListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::OIDTypePlugin_get_serialized_key_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricSourceListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricSourceListPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricSourceListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            {
                RTICdrUnsignedLong sequence_length;
                if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                    if (!RTICdrStream_deserializeNonPrimitiveSequence(
                        stream,
                        ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                        &sequence_length,
                        ice::OIDTypeSeq_get_maximum(sample),
                        sizeof(ice::OIDType),
                        (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                } else {
                    if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                        stream,
                        (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                        &sequence_length,
                        ice::OIDTypeSeq_get_maximum(sample),
                        (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::OIDTypeSeq_set_length(
                    sample,sequence_length)) {
                    return RTI_FALSE;
                }        

            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type SiteList
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    SiteList*
    SiteListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        SiteList *sample = NULL;

        sample = new (std::nothrow) SiteList ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::SiteList_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    SiteList *
    SiteListPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        SiteList *sample = NULL;

        sample = new (std::nothrow) SiteList ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::SiteList_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    SiteList *
    SiteListPluginSupport_create_data(void)
    {
        return ice::SiteListPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    SiteListPluginSupport_destroy_data_w_params(
        SiteList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::SiteList_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    SiteListPluginSupport_destroy_data_ex(
        SiteList *sample,RTIBool deallocate_pointers) {

        ice::SiteList_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    SiteListPluginSupport_destroy_data(
        SiteList *sample) {

        ice::SiteListPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    SiteListPluginSupport_copy_data(
        SiteList *dst,
        const SiteList *src)
    {
        return ice::SiteList_copy(dst,(const SiteList*) src);
    }

    void 
    SiteListPluginSupport_print_data(
        const SiteList *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
            RTICdrType_printArray(
                ice::OIDTypeSeq_get_contiguous_bufferI(sample), 
                ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypePrintFunction)ice::OIDTypePluginSupport_print_data,
                "", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                ice::OIDTypeSeq_get_discontiguous_bufferI(sample), 
                ice::OIDTypeSeq_get_length(sample),
                (RTICdrTypePrintFunction)ice::OIDTypePluginSupport_print_data,
                "", indent_level + 1);
        }

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    SiteListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *dst,
        const SiteList *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::SiteListPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    SiteListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    SiteListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const SiteList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    sizeof(ice::OIDType),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    SiteListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::SiteList_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            sizeof(ice::OIDType),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::OIDTypeSeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool SiteListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            {
                RTICdrUnsignedLong sequence_length;
                if (!RTICdrStream_skipNonPrimitiveSequence(
                    stream,
                    &sequence_length,
                    sizeof(ice::OIDType),
                    (RTICdrStreamSkipFunction)ice::OIDTypePlugin_skip,
                    RTI_FALSE,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    SiteListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::OIDTypePlugin_get_serialized_sample_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    SiteListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = SiteListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    SiteListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
            current_alignment, 0,
            ice::OIDTypePlugin_get_serialized_sample_min_size,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    SiteListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const SiteList * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += RTICdrType_get4ByteMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
            current_alignment += RTICdrType_getNonPrimitiveArraySerializedSize(
                current_alignment, ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::OIDTypePlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                endpoint_data);
        } else {
            current_alignment += RTICdrStream_getNonPrimitivePointerArraySerializedSize(
                current_alignment,  
                ice::OIDTypeSeq_get_length(sample),
                sizeof(ice::OIDType),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::OIDTypePlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                (const void **)ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                endpoint_data);
        }

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    SiteListPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    SiteListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const SiteList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    sizeof(ice::OIDType),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                    ice::OIDTypeSeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::OIDTypePlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool SiteListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            sizeof(ice::OIDType),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::OIDTypeSeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::OIDTypeSeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    SiteListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::OIDTypePlugin_get_serialized_key_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    SiteListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = SiteListPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    SiteListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SiteList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            {
                RTICdrUnsignedLong sequence_length;
                if (ice::OIDTypeSeq_get_contiguous_bufferI(sample) != NULL) {
                    if (!RTICdrStream_deserializeNonPrimitiveSequence(
                        stream,
                        ice::OIDTypeSeq_get_contiguous_bufferI(sample),
                        &sequence_length,
                        ice::OIDTypeSeq_get_maximum(sample),
                        sizeof(ice::OIDType),
                        (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                } else {
                    if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                        stream,
                        (void **) ice::OIDTypeSeq_get_discontiguous_bufferI(sample),
                        &sequence_length,
                        ice::OIDTypeSeq_get_maximum(sample),
                        (RTICdrStreamDeserializeFunction)ice::OIDTypePlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::OIDTypeSeq_set_length(
                    sample,sequence_length)) {
                    return RTI_FALSE;
                }        

            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricStatus
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricStatus*
    MetricStatusPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricStatus *sample = NULL;

        sample = new (std::nothrow) MetricStatus ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricStatus_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricStatus *
    MetricStatusPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricStatus *sample = NULL;

        sample = new (std::nothrow) MetricStatus ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricStatus_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricStatus *
    MetricStatusPluginSupport_create_data(void)
    {
        return ice::MetricStatusPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricStatusPluginSupport_destroy_data_w_params(
        MetricStatus *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricStatus_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricStatusPluginSupport_destroy_data_ex(
        MetricStatus *sample,RTIBool deallocate_pointers) {

        ice::MetricStatus_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricStatusPluginSupport_destroy_data(
        MetricStatus *sample) {

        ice::MetricStatusPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricStatusPluginSupport_copy_data(
        MetricStatus *dst,
        const MetricStatus *src)
    {
        return ice::MetricStatus_copy(dst,(const MetricStatus*) src);
    }

    void 
    MetricStatusPluginSupport_print_data(
        const MetricStatus *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::BITS16PluginSupport_print_data(
            (const ice::BITS16*) sample, "", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricStatusPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *dst,
        const MetricStatus *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricStatusPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricStatusPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatus *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::BITS16Plugin_serialize(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricStatusPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricStatus_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::BITS16Plugin_deserialize_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricStatusPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::BITS16Plugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricStatusPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricStatusPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricStatusPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricStatusPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricStatus * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::BITS16Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::BITS16*) sample);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricStatusPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricStatusPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatus *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if(!ice::BITS16Plugin_serialize_key(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricStatusPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if(!ice::BITS16Plugin_deserialize_key_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricStatusPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricStatusPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricStatusPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricStatusPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if(!ice::BITS16Plugin_serialized_sample_to_key(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricStatusBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatusBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricStatusBitsPlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != metric_off && *sample != metric_not_ready && *sample != metric_standby && *sample != metric_transduc_discon && *sample != metric_hw_discon){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricStatusBits");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricStatusBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricStatusBitsPlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case metric_off:
                    *sample=metric_off;
                    break;
                    case metric_not_ready:
                    *sample=metric_not_ready;
                    break;
                    case metric_standby:
                    *sample=metric_standby;
                    break;
                    case metric_transduc_discon:
                    *sample=metric_transduc_discon;
                    break;
                    case metric_hw_discon:
                    *sample=metric_hw_discon;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricStatusBits_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricStatusBits");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricStatusBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricStatusBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricStatusBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricStatusBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricStatusBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricStatusBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricStatusBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricStatusBits * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricStatusBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricStatusBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricStatusBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricStatusBitsPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricStatusBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricStatusBitsPlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricStatusBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricStatusBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricStatusBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricStatusBitsPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricStatusBitsPluginSupport_print_data(
        const MetricStatusBits *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricStatusBits", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricAccess
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricAccess*
    MetricAccessPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricAccess *sample = NULL;

        sample = new (std::nothrow) MetricAccess ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricAccess_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricAccess *
    MetricAccessPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricAccess *sample = NULL;

        sample = new (std::nothrow) MetricAccess ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricAccess_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricAccess *
    MetricAccessPluginSupport_create_data(void)
    {
        return ice::MetricAccessPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricAccessPluginSupport_destroy_data_w_params(
        MetricAccess *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricAccess_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricAccessPluginSupport_destroy_data_ex(
        MetricAccess *sample,RTIBool deallocate_pointers) {

        ice::MetricAccess_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricAccessPluginSupport_destroy_data(
        MetricAccess *sample) {

        ice::MetricAccessPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricAccessPluginSupport_copy_data(
        MetricAccess *dst,
        const MetricAccess *src)
    {
        return ice::MetricAccess_copy(dst,(const MetricAccess*) src);
    }

    void 
    MetricAccessPluginSupport_print_data(
        const MetricAccess *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::BITS16PluginSupport_print_data(
            (const ice::BITS16*) sample, "", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricAccessPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *dst,
        const MetricAccess *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricAccessPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricAccessPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricAccessPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccess *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::BITS16Plugin_serialize(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricAccessPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricAccess_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::BITS16Plugin_deserialize_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricAccessPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::BITS16Plugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricAccessPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricAccessPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricAccessPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricAccessPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricAccessPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricAccess * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::BITS16Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::BITS16*) sample);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricAccessPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricAccessPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccess *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if(!ice::BITS16Plugin_serialize_key(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricAccessPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if(!ice::BITS16Plugin_deserialize_key_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricAccessPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricAccessPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricAccessPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricAccessPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccess *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if(!ice::BITS16Plugin_serialized_sample_to_key(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricAccessBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccessBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricAccessBitsPlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != avail_intermittent && *sample != upd_periodic && *sample != upd_episodic && *sample != msmt_noncontinuous && *sample != acc_evrep && *sample != acc_get && *sample != acc_scan && *sample != gen_opt_sync && *sample != sc_opt_normal && *sample != sc_opt_extensive && *sample != sc_opt_long_pd_avail && *sample != sc_opt_confirm){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricAccessBits");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricAccessBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricAccessBitsPlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case avail_intermittent:
                    *sample=avail_intermittent;
                    break;
                    case upd_periodic:
                    *sample=upd_periodic;
                    break;
                    case upd_episodic:
                    *sample=upd_episodic;
                    break;
                    case msmt_noncontinuous:
                    *sample=msmt_noncontinuous;
                    break;
                    case acc_evrep:
                    *sample=acc_evrep;
                    break;
                    case acc_get:
                    *sample=acc_get;
                    break;
                    case acc_scan:
                    *sample=acc_scan;
                    break;
                    case gen_opt_sync:
                    *sample=gen_opt_sync;
                    break;
                    case sc_opt_normal:
                    *sample=sc_opt_normal;
                    break;
                    case sc_opt_extensive:
                    *sample=sc_opt_extensive;
                    break;
                    case sc_opt_long_pd_avail:
                    *sample=sc_opt_long_pd_avail;
                    break;
                    case sc_opt_confirm:
                    *sample=sc_opt_confirm;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricAccessBits_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricAccessBits");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricAccessBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricAccessBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricAccessBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricAccessBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricAccessBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricAccessBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricAccessBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricAccessBits * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricAccessBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricAccessBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricAccessBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricAccessBitsPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricAccessBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricAccessBitsPlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricAccessBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricAccessBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricAccessBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricAccessBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricAccessBitsPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricAccessBitsPluginSupport_print_data(
        const MetricAccessBits *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricAccessBits", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricRelevance
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricRelevance*
    MetricRelevancePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricRelevance *sample = NULL;

        sample = new (std::nothrow) MetricRelevance ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricRelevance_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricRelevance *
    MetricRelevancePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricRelevance *sample = NULL;

        sample = new (std::nothrow) MetricRelevance ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricRelevance_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricRelevance *
    MetricRelevancePluginSupport_create_data(void)
    {
        return ice::MetricRelevancePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricRelevancePluginSupport_destroy_data_w_params(
        MetricRelevance *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricRelevance_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricRelevancePluginSupport_destroy_data_ex(
        MetricRelevance *sample,RTIBool deallocate_pointers) {

        ice::MetricRelevance_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricRelevancePluginSupport_destroy_data(
        MetricRelevance *sample) {

        ice::MetricRelevancePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricRelevancePluginSupport_copy_data(
        MetricRelevance *dst,
        const MetricRelevance *src)
    {
        return ice::MetricRelevance_copy(dst,(const MetricRelevance*) src);
    }

    void 
    MetricRelevancePluginSupport_print_data(
        const MetricRelevance *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::BITS16PluginSupport_print_data(
            (const ice::BITS16*) sample, "", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricRelevancePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *dst,
        const MetricRelevance *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricRelevancePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricRelevancePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricRelevancePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevance *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::BITS16Plugin_serialize(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricRelevancePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricRelevance_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::BITS16Plugin_deserialize_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricRelevancePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::BITS16Plugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricRelevancePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricRelevancePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricRelevancePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricRelevancePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricRelevancePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricRelevance * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::BITS16Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::BITS16*) sample);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricRelevancePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricRelevancePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevance *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if(!ice::BITS16Plugin_serialize_key(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricRelevancePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if(!ice::BITS16Plugin_deserialize_key_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricRelevancePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricRelevancePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricRelevancePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricRelevancePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevance *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if(!ice::BITS16Plugin_serialized_sample_to_key(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricRelevanceBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevanceBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricRelevanceBitsPlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != rv_unspec && *sample != rv_internal && *sample != rv_store_only && *sample != rv_no_recording && *sample != rv_phys_ev_ind && *sample != rv_btb_metric && *sample != rv_app_specific && *sample != rv_service){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricRelevanceBits");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricRelevanceBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricRelevanceBitsPlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case rv_unspec:
                    *sample=rv_unspec;
                    break;
                    case rv_internal:
                    *sample=rv_internal;
                    break;
                    case rv_store_only:
                    *sample=rv_store_only;
                    break;
                    case rv_no_recording:
                    *sample=rv_no_recording;
                    break;
                    case rv_phys_ev_ind:
                    *sample=rv_phys_ev_ind;
                    break;
                    case rv_btb_metric:
                    *sample=rv_btb_metric;
                    break;
                    case rv_app_specific:
                    *sample=rv_app_specific;
                    break;
                    case rv_service:
                    *sample=rv_service;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricRelevanceBits_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricRelevanceBits");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricRelevanceBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricRelevanceBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricRelevanceBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricRelevanceBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricRelevanceBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricRelevanceBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricRelevanceBits * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricRelevanceBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricRelevanceBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricRelevanceBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricRelevanceBitsPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricRelevanceBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricRelevanceBitsPlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricRelevanceBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricRelevanceBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricRelevanceBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricRelevanceBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricRelevanceBitsPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricRelevanceBitsPluginSupport_print_data(
        const MetricRelevanceBits *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricRelevanceBits", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricCategoryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCategory *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricCategoryPlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != mcat_unspec && *sample != auto_measurement && *sample != manual_measurement && *sample != auto_setting && *sample != manual_setting && *sample != auto_calculation && *sample != manual_calculation){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricCategory");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricCategoryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricCategoryPlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case mcat_unspec:
                    *sample=mcat_unspec;
                    break;
                    case auto_measurement:
                    *sample=auto_measurement;
                    break;
                    case manual_measurement:
                    *sample=manual_measurement;
                    break;
                    case auto_setting:
                    *sample=auto_setting;
                    break;
                    case manual_setting:
                    *sample=manual_setting;
                    break;
                    case auto_calculation:
                    *sample=auto_calculation;
                    break;
                    case manual_calculation:
                    *sample=manual_calculation;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricCategory_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricCategory");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricCategoryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricCategoryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricCategoryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCategoryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricCategoryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCategoryPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricCategoryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCategory * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricCategoryPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricCategoryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCategory *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricCategoryPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricCategoryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricCategoryPlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricCategoryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricCategoryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricCategoryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCategory *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricCategoryPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricCategoryPluginSupport_print_data(
        const MetricCategory *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricCategory", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricSpec
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricSpec*
    MetricSpecPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricSpec *sample = NULL;

        sample = new (std::nothrow) MetricSpec ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricSpec_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricSpec *
    MetricSpecPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricSpec *sample = NULL;

        sample = new (std::nothrow) MetricSpec ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricSpec_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricSpec *
    MetricSpecPluginSupport_create_data(void)
    {
        return ice::MetricSpecPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricSpecPluginSupport_destroy_data_w_params(
        MetricSpec *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricSpec_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricSpecPluginSupport_destroy_data_ex(
        MetricSpec *sample,RTIBool deallocate_pointers) {

        ice::MetricSpec_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricSpecPluginSupport_destroy_data(
        MetricSpec *sample) {

        ice::MetricSpecPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricSpecPluginSupport_copy_data(
        MetricSpec *dst,
        const MetricSpec *src)
    {
        return ice::MetricSpec_copy(dst,(const MetricSpec*) src);
    }

    void 
    MetricSpecPluginSupport_print_data(
        const MetricSpec *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::DurationPluginSupport_print_data(
            (const ice::Duration*) &sample->update_period, "update_period", indent_level + 1);

        ice::MetricCategoryPluginSupport_print_data(
            (const ice::MetricCategory*) &sample->category, "category", indent_level + 1);

        ice::MetricAccessPluginSupport_print_data(
            (const ice::MetricAccess*) &sample->access, "access", indent_level + 1);

        ice::MetricRelevancePluginSupport_print_data(
            (const ice::MetricRelevance*) &sample->relevance, "relevance", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricSpecPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *dst,
        const MetricSpec *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricSpecPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricSpecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricSpecPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSpec *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::DurationPlugin_serialize(
                endpoint_data,
                (const ice::Duration*) &sample->update_period,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricCategoryPlugin_serialize(
                endpoint_data,
                (const ice::MetricCategory*) &sample->category,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricAccessPlugin_serialize(
                endpoint_data,
                (const ice::MetricAccess*) &sample->access,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricRelevancePlugin_serialize(
                endpoint_data,
                (const ice::MetricRelevance*) &sample->relevance,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricSpecPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricSpec_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::DurationPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->update_period,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricCategoryPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->category,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricAccessPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->access,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricRelevancePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->relevance,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    MetricSpecPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricSpec *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        MetricSpecPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            MetricSpecPlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::MetricSpecPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    MetricSpecPlugin_deserialize_from_cdr_buffer(
        MetricSpec *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        MetricSpec_finalize_optional_members(sample, RTI_TRUE);
        return MetricSpecPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    MetricSpecPlugin_data_to_string(
        const MetricSpec *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!MetricSpecPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!MetricSpecPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            MetricSpec_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    MetricSpecPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "MetricSpecPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricSpecPlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "MetricSpec");

        }

        return result;

    }

    RTIBool MetricSpecPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::DurationPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricCategoryPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricAccessPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricRelevancePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricSpecPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::DurationPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricCategoryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricAccessPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricRelevancePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricSpecPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricSpecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricSpecPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::DurationPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricCategoryPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricAccessPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricRelevancePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricSpecPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricSpec * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::DurationPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::Duration*) &sample->update_period);

        current_alignment += ice::MetricCategoryPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricCategory*) &sample->category);

        current_alignment += ice::MetricAccessPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricAccess*) &sample->access);

        current_alignment += ice::MetricRelevancePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricRelevance*) &sample->relevance);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricSpecPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricSpecPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricSpec *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::MetricSpecPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricSpecPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::MetricSpecPlugin_deserialize_sample(
                    endpoint_data, sample, stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricSpecPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricSpecPlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    MetricSpecPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::MetricSpecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricSpecPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricSpecPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricSpecPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricSpec *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::MetricSpecPlugin_deserialize_sample(
                endpoint_data, sample, stream, RTI_FALSE, 
                RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type VmoSourceEntry
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    VmoSourceEntry*
    VmoSourceEntryPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        VmoSourceEntry *sample = NULL;

        sample = new (std::nothrow) VmoSourceEntry ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::VmoSourceEntry_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    VmoSourceEntry *
    VmoSourceEntryPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        VmoSourceEntry *sample = NULL;

        sample = new (std::nothrow) VmoSourceEntry ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::VmoSourceEntry_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    VmoSourceEntry *
    VmoSourceEntryPluginSupport_create_data(void)
    {
        return ice::VmoSourceEntryPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    VmoSourceEntryPluginSupport_destroy_data_w_params(
        VmoSourceEntry *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::VmoSourceEntry_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    VmoSourceEntryPluginSupport_destroy_data_ex(
        VmoSourceEntry *sample,RTIBool deallocate_pointers) {

        ice::VmoSourceEntry_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    VmoSourceEntryPluginSupport_destroy_data(
        VmoSourceEntry *sample) {

        ice::VmoSourceEntryPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    VmoSourceEntryPluginSupport_copy_data(
        VmoSourceEntry *dst,
        const VmoSourceEntry *src)
    {
        return ice::VmoSourceEntry_copy(dst,(const VmoSourceEntry*) src);
    }

    void 
    VmoSourceEntryPluginSupport_print_data(
        const VmoSourceEntry *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::OIDTypePluginSupport_print_data(
            (const ice::OIDType*) &sample->vmo_type, "vmo_type", indent_level + 1);

        ice::GLBHANDLEPluginSupport_print_data(
            (const ice::GLBHANDLE*) &sample->glb_handle, "glb_handle", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    VmoSourceEntryPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *dst,
        const VmoSourceEntry *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::VmoSourceEntryPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    VmoSourceEntryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceEntry *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::OIDTypePlugin_serialize(
                endpoint_data,
                (const ice::OIDType*) &sample->vmo_type,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::GLBHANDLEPlugin_serialize(
                endpoint_data,
                (const ice::GLBHANDLE*) &sample->glb_handle,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    VmoSourceEntryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::VmoSourceEntry_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::OIDTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->vmo_type,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::GLBHANDLEPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->glb_handle,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    VmoSourceEntryPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const VmoSourceEntry *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        VmoSourceEntryPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            VmoSourceEntryPlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::VmoSourceEntryPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    VmoSourceEntryPlugin_deserialize_from_cdr_buffer(
        VmoSourceEntry *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        VmoSourceEntry_finalize_optional_members(sample, RTI_TRUE);
        return VmoSourceEntryPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    VmoSourceEntryPlugin_data_to_string(
        const VmoSourceEntry *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!VmoSourceEntryPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!VmoSourceEntryPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            VmoSourceEntry_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    VmoSourceEntryPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "VmoSourceEntryPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::VmoSourceEntryPlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "VmoSourceEntry");

        }

        return result;

    }

    RTIBool VmoSourceEntryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::OIDTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::GLBHANDLEPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::GLBHANDLEPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = VmoSourceEntryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    VmoSourceEntryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::GLBHANDLEPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    VmoSourceEntryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const VmoSourceEntry * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::OIDTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::OIDType*) &sample->vmo_type);

        current_alignment += ice::GLBHANDLEPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::GLBHANDLE*) &sample->glb_handle);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    VmoSourceEntryPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    VmoSourceEntryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceEntry *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::VmoSourceEntryPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool VmoSourceEntryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::VmoSourceEntryPlugin_deserialize_sample(
                    endpoint_data, sample, stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool VmoSourceEntryPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::VmoSourceEntryPlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    VmoSourceEntryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VmoSourceEntryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    VmoSourceEntryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = VmoSourceEntryPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    VmoSourceEntryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::VmoSourceEntryPlugin_deserialize_sample(
                endpoint_data, sample, stream, RTI_FALSE, 
                RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type VmoSourceList
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    VmoSourceList*
    VmoSourceListPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        VmoSourceList *sample = NULL;

        sample = new (std::nothrow) VmoSourceList ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::VmoSourceList_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    VmoSourceList *
    VmoSourceListPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        VmoSourceList *sample = NULL;

        sample = new (std::nothrow) VmoSourceList ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::VmoSourceList_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    VmoSourceList *
    VmoSourceListPluginSupport_create_data(void)
    {
        return ice::VmoSourceListPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    VmoSourceListPluginSupport_destroy_data_w_params(
        VmoSourceList *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::VmoSourceList_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    VmoSourceListPluginSupport_destroy_data_ex(
        VmoSourceList *sample,RTIBool deallocate_pointers) {

        ice::VmoSourceList_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    VmoSourceListPluginSupport_destroy_data(
        VmoSourceList *sample) {

        ice::VmoSourceListPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    VmoSourceListPluginSupport_copy_data(
        VmoSourceList *dst,
        const VmoSourceList *src)
    {
        return ice::VmoSourceList_copy(dst,(const VmoSourceList*) src);
    }

    void 
    VmoSourceListPluginSupport_print_data(
        const VmoSourceList *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
            RTICdrType_printArray(
                ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample), 
                ice::VmoSourceEntrySeq_get_length(sample),
                sizeof(ice::VmoSourceEntry),
                (RTICdrTypePrintFunction)ice::VmoSourceEntryPluginSupport_print_data,
                "", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample), 
                ice::VmoSourceEntrySeq_get_length(sample),
                (RTICdrTypePrintFunction)ice::VmoSourceEntryPluginSupport_print_data,
                "", indent_level + 1);
        }

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    VmoSourceListPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *dst,
        const VmoSourceList *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::VmoSourceListPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    VmoSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    VmoSourceListPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                    ice::VmoSourceEntrySeq_get_length(sample),
                    (100),
                    sizeof(ice::VmoSourceEntry),
                    (RTICdrStreamSerializeFunction)ice::VmoSourceEntryPlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                    ice::VmoSourceEntrySeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::VmoSourceEntryPlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    VmoSourceListPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::VmoSourceList_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::VmoSourceEntrySeq_get_maximum(sample),
                            sizeof(ice::VmoSourceEntry),
                            (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::VmoSourceEntrySeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::VmoSourceEntrySeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool VmoSourceListPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            {
                RTICdrUnsignedLong sequence_length;
                if (!RTICdrStream_skipNonPrimitiveSequence(
                    stream,
                    &sequence_length,
                    sizeof(ice::VmoSourceEntry),
                    (RTICdrStreamSkipFunction)ice::VmoSourceEntryPlugin_skip,
                    RTI_FALSE,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    VmoSourceListPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::VmoSourceEntryPlugin_get_serialized_sample_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    VmoSourceListPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = VmoSourceListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    VmoSourceListPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
            current_alignment, 0,
            ice::VmoSourceEntryPlugin_get_serialized_sample_min_size,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    VmoSourceListPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const VmoSourceList * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += RTICdrType_get4ByteMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
            current_alignment += RTICdrType_getNonPrimitiveArraySerializedSize(
                current_alignment, ice::VmoSourceEntrySeq_get_length(sample),
                sizeof(ice::VmoSourceEntry),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::VmoSourceEntryPlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                endpoint_data);
        } else {
            current_alignment += RTICdrStream_getNonPrimitivePointerArraySerializedSize(
                current_alignment,  
                ice::VmoSourceEntrySeq_get_length(sample),
                sizeof(ice::VmoSourceEntry),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::VmoSourceEntryPlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                (const void **)ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                endpoint_data);
        }

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    VmoSourceListPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    VmoSourceListPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const VmoSourceList *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                    ice::VmoSourceEntrySeq_get_length(sample),
                    (100),
                    sizeof(ice::VmoSourceEntry),
                    (RTICdrStreamSerializeFunction)ice::VmoSourceEntryPlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                    ice::VmoSourceEntrySeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::VmoSourceEntryPlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool VmoSourceListPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::VmoSourceEntrySeq_get_maximum(sample),
                            sizeof(ice::VmoSourceEntry),
                            (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::VmoSourceEntrySeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::VmoSourceEntrySeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    VmoSourceListPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::VmoSourceEntryPlugin_get_serialized_key_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    VmoSourceListPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = VmoSourceListPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    VmoSourceListPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        VmoSourceList *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            {
                RTICdrUnsignedLong sequence_length;
                if (ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                    if (!RTICdrStream_deserializeNonPrimitiveSequence(
                        stream,
                        ice::VmoSourceEntrySeq_get_contiguous_bufferI(sample),
                        &sequence_length,
                        ice::VmoSourceEntrySeq_get_maximum(sample),
                        sizeof(ice::VmoSourceEntry),
                        (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                } else {
                    if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                        stream,
                        (void **) ice::VmoSourceEntrySeq_get_discontiguous_bufferI(sample),
                        &sequence_length,
                        ice::VmoSourceEntrySeq_get_maximum(sample),
                        (RTICdrStreamDeserializeFunction)ice::VmoSourceEntryPlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::VmoSourceEntrySeq_set_length(
                    sample,sequence_length)) {
                    return RTI_FALSE;
                }        

            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MeasurementStatus
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MeasurementStatus*
    MeasurementStatusPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MeasurementStatus *sample = NULL;

        sample = new (std::nothrow) MeasurementStatus ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MeasurementStatus_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MeasurementStatus *
    MeasurementStatusPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MeasurementStatus *sample = NULL;

        sample = new (std::nothrow) MeasurementStatus ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MeasurementStatus_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MeasurementStatus *
    MeasurementStatusPluginSupport_create_data(void)
    {
        return ice::MeasurementStatusPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MeasurementStatusPluginSupport_destroy_data_w_params(
        MeasurementStatus *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MeasurementStatus_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MeasurementStatusPluginSupport_destroy_data_ex(
        MeasurementStatus *sample,RTIBool deallocate_pointers) {

        ice::MeasurementStatus_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MeasurementStatusPluginSupport_destroy_data(
        MeasurementStatus *sample) {

        ice::MeasurementStatusPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MeasurementStatusPluginSupport_copy_data(
        MeasurementStatus *dst,
        const MeasurementStatus *src)
    {
        return ice::MeasurementStatus_copy(dst,(const MeasurementStatus*) src);
    }

    void 
    MeasurementStatusPluginSupport_print_data(
        const MeasurementStatus *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::BITS16PluginSupport_print_data(
            (const ice::BITS16*) sample, "", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MeasurementStatusPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *dst,
        const MeasurementStatus *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MeasurementStatusPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MeasurementStatusPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatus *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::BITS16Plugin_serialize(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MeasurementStatusPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MeasurementStatus_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::BITS16Plugin_deserialize_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MeasurementStatusPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::BITS16Plugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MeasurementStatusPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MeasurementStatusPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MeasurementStatusPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MeasurementStatus * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::BITS16Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::BITS16*) sample);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MeasurementStatusPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MeasurementStatusPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatus *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if(!ice::BITS16Plugin_serialize_key(
                endpoint_data,
                (const ice::BITS16*) sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MeasurementStatusPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if(!ice::BITS16Plugin_deserialize_key_sample(
                    endpoint_data,
                    sample,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MeasurementStatusPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::BITS16Plugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MeasurementStatusPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MeasurementStatusPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MeasurementStatusPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatus *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if(!ice::BITS16Plugin_serialized_sample_to_key(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MeasurementStatusBitsPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatusBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MeasurementStatusBitsPlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != invalid && *sample != questionable && *sample != not_available && *sample != calibration_ongoing && *sample != test_data && *sample != demo_data && *sample != validated_data && *sample != early_indication && *sample != msmt_ongoing && *sample != msmt_state_in_alarm && *sample != msmt_state_al_inhibited){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MeasurementStatusBits");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MeasurementStatusBitsPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MeasurementStatusBitsPlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case invalid:
                    *sample=invalid;
                    break;
                    case questionable:
                    *sample=questionable;
                    break;
                    case not_available:
                    *sample=not_available;
                    break;
                    case calibration_ongoing:
                    *sample=calibration_ongoing;
                    break;
                    case test_data:
                    *sample=test_data;
                    break;
                    case demo_data:
                    *sample=demo_data;
                    break;
                    case validated_data:
                    *sample=validated_data;
                    break;
                    case early_indication:
                    *sample=early_indication;
                    break;
                    case msmt_ongoing:
                    *sample=msmt_ongoing;
                    break;
                    case msmt_state_in_alarm:
                    *sample=msmt_state_in_alarm;
                    break;
                    case msmt_state_al_inhibited:
                    *sample=msmt_state_al_inhibited;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MeasurementStatusBits_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MeasurementStatusBits");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MeasurementStatusBitsPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MeasurementStatusBitsPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MeasurementStatusBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MeasurementStatusBitsPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MeasurementStatusBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MeasurementStatusBitsPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MeasurementStatusBits * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MeasurementStatusBitsPlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MeasurementStatusBitsPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MeasurementStatusBits *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MeasurementStatusBitsPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MeasurementStatusBitsPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MeasurementStatusBitsPlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MeasurementStatusBitsPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MeasurementStatusBitsPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MeasurementStatusBitsPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MeasurementStatusBits *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MeasurementStatusBitsPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MeasurementStatusBitsPluginSupport_print_data(
        const MeasurementStatusBits *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MeasurementStatusBits", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricCalStatePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalState *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricCalStatePlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != not_calibrated && *sample != cal_required && *sample != calibrated){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricCalState");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricCalStatePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricCalStatePlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case not_calibrated:
                    *sample=not_calibrated;
                    break;
                    case cal_required:
                    *sample=cal_required;
                    break;
                    case calibrated:
                    *sample=calibrated;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricCalState_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricCalState");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricCalStatePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricCalStatePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricCalStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCalStatePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricCalStatePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCalStatePlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricCalStatePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalState * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricCalStatePlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricCalStatePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalState *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricCalStatePlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricCalStatePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricCalStatePlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricCalStatePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricCalStatePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricCalStatePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalState *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricCalStatePlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricCalStatePluginSupport_print_data(
        const MetricCalState *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricCalState", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    RTIBool 
    MetricCalTypePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalType *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        const char *METHOD_NAME = "MetricCalTypePlugin_serialize";

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (*sample != cal_unspec && *sample != cal_offset && *sample != cal_gain && *sample != cal_two_point){
                RTICdrLog_exception(
                    METHOD_NAME, 
                    &RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds, 
                    *sample, 
                    "MetricCalType");
                return RTI_FALSE;       
            }

            if (!RTICdrStream_serializeEnum(stream, sample))
            {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricCalTypePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;
        DDS_Enum enum_tmp;
        const char *METHOD_NAME = "MetricCalTypePlugin_deserialize_sample";

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
                {
                    return RTI_FALSE;
                }
                switch (enum_tmp) {
                    case cal_unspec:
                    *sample=cal_unspec;
                    break;
                    case cal_offset:
                    *sample=cal_offset;
                    break;
                    case cal_gain:
                    *sample=cal_gain;
                    break;
                    case cal_two_point:
                    *sample=cal_two_point;
                    break;
                    default:
                    {
                        struct PRESTypePluginDefaultEndpointData * epd =
                        (struct PRESTypePluginDefaultEndpointData *)
                        endpoint_data;
                        const struct PRESTypePluginSampleAssignabilityProperty * ap =
                        PRESTypePluginDefaultEndpointData_getAssignabilityProperty(epd);

                        if (ap->acceptUnknownEnumValue) {
                            MetricCalType_initialize(sample);
                        } else {
                            stream->_xTypesState.unassignable = RTI_TRUE;
                            RTICdrLog_exception(
                                METHOD_NAME, 
                                &RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds, 
                                enum_tmp, 
                                "MetricCalType");
                            return RTI_FALSE;
                        }
                    }
                }

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricCalTypePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!RTICdrStream_skipEnum(stream)) {
                return RTI_FALSE;
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricCalTypePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricCalTypePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCalTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,
            NULL,
            include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    unsigned int MetricCalTypePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int initial_alignment = current_alignment;

        current_alignment += ice::MetricCalTypePlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricCalTypePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalType * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        if (sample==NULL) {
            return 0;
        }

        current_alignment += ice::MetricCalTypePlugin_get_serialized_sample_max_size(
            endpoint_data,include_encapsulation,
            encapsulation_id,
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data,
                current_alignment));

        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    RTIBool 
    MetricCalTypePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalType *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        return  ice::MetricCalTypePlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);

    }

    RTIBool MetricCalTypePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            return  ice::MetricCalTypePlugin_deserialize_sample(
                endpoint_data, sample, stream, deserialize_encapsulation, 
                deserialize_key, endpoint_plugin_qos);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricCalTypePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        current_alignment +=  ice::MetricCalTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, include_encapsulation,
            encapsulation_id, current_alignment);

        return current_alignment - initial_alignment;
    }

    RTIBool 
    MetricCalTypePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalType *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {

        return  ice::MetricCalTypePlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);

    }

    /* ----------------------------------------------------------------------------
    Support functions:
    * ---------------------------------------------------------------------------- */

    void MetricCalTypePluginSupport_print_data(
        const MetricCalType *sample,
        const char *description, int indent_level)
    {
        if (description != NULL) {
            RTICdrType_printIndent(indent_level);
            RTILog_debug("%s:\n", description);
        }

        if (sample == NULL) {
            RTICdrType_printIndent(indent_level+1);
            RTILog_debug("NULL\n");
            return;
        }

        RTICdrType_printEnum((RTICdrEnum *)sample, "MetricCalType", indent_level + 1);
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricCalEntry
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricCalEntry*
    MetricCalEntryPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricCalEntry *sample = NULL;

        sample = new (std::nothrow) MetricCalEntry ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricCalEntry_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricCalEntry *
    MetricCalEntryPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricCalEntry *sample = NULL;

        sample = new (std::nothrow) MetricCalEntry ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricCalEntry_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricCalEntry *
    MetricCalEntryPluginSupport_create_data(void)
    {
        return ice::MetricCalEntryPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricCalEntryPluginSupport_destroy_data_w_params(
        MetricCalEntry *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricCalEntry_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricCalEntryPluginSupport_destroy_data_ex(
        MetricCalEntry *sample,RTIBool deallocate_pointers) {

        ice::MetricCalEntry_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricCalEntryPluginSupport_destroy_data(
        MetricCalEntry *sample) {

        ice::MetricCalEntryPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricCalEntryPluginSupport_copy_data(
        MetricCalEntry *dst,
        const MetricCalEntry *src)
    {
        return ice::MetricCalEntry_copy(dst,(const MetricCalEntry*) src);
    }

    void 
    MetricCalEntryPluginSupport_print_data(
        const MetricCalEntry *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::MetricCalTypePluginSupport_print_data(
            (const ice::MetricCalType*) &sample->cal_type, "cal_type", indent_level + 1);

        ice::MetricCalStatePluginSupport_print_data(
            (const ice::MetricCalState*) &sample->cal_state, "cal_state", indent_level + 1);

        ice::TimespecPluginSupport_print_data(
            (const ice::Timespec*) &sample->cal_time, "cal_time", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricCalEntryPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *dst,
        const MetricCalEntry *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricCalEntryPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricCalEntryPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalEntry *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::MetricCalTypePlugin_serialize(
                endpoint_data,
                (const ice::MetricCalType*) &sample->cal_type,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricCalStatePlugin_serialize(
                endpoint_data,
                (const ice::MetricCalState*) &sample->cal_state,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::TimespecPlugin_serialize(
                endpoint_data,
                (const ice::Timespec*) &sample->cal_time,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricCalEntryPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricCalEntry_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::MetricCalTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->cal_type,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricCalStatePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->cal_state,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::TimespecPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->cal_time,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    MetricCalEntryPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricCalEntry *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        MetricCalEntryPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            MetricCalEntryPlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::MetricCalEntryPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    MetricCalEntryPlugin_deserialize_from_cdr_buffer(
        MetricCalEntry *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        MetricCalEntry_finalize_optional_members(sample, RTI_TRUE);
        return MetricCalEntryPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    MetricCalEntryPlugin_data_to_string(
        const MetricCalEntry *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!MetricCalEntryPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!MetricCalEntryPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            MetricCalEntry_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    MetricCalEntryPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "MetricCalEntryPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricCalEntryPlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "MetricCalEntry");

        }

        return result;

    }

    RTIBool MetricCalEntryPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::MetricCalTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricCalStatePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::TimespecPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::MetricCalTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricCalStatePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::TimespecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricCalEntryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricCalEntryPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::MetricCalTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricCalStatePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::TimespecPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricCalEntryPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalEntry * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::MetricCalTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricCalType*) &sample->cal_type);

        current_alignment += ice::MetricCalStatePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricCalState*) &sample->cal_state);

        current_alignment += ice::TimespecPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::Timespec*) &sample->cal_time);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricCalEntryPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricCalEntryPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalEntry *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::MetricCalEntryPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricCalEntryPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::MetricCalEntryPlugin_deserialize_sample(
                    endpoint_data, sample, stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricCalEntryPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricCalEntryPlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    MetricCalEntryPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::MetricCalEntryPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricCalEntryPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricCalEntryPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricCalEntryPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalEntry *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::MetricCalEntryPlugin_deserialize_sample(
                endpoint_data, sample, stream, RTI_FALSE, 
                RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricCalibration
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricCalibration*
    MetricCalibrationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricCalibration *sample = NULL;

        sample = new (std::nothrow) MetricCalibration ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricCalibration_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricCalibration *
    MetricCalibrationPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricCalibration *sample = NULL;

        sample = new (std::nothrow) MetricCalibration ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricCalibration_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricCalibration *
    MetricCalibrationPluginSupport_create_data(void)
    {
        return ice::MetricCalibrationPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricCalibrationPluginSupport_destroy_data_w_params(
        MetricCalibration *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricCalibration_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricCalibrationPluginSupport_destroy_data_ex(
        MetricCalibration *sample,RTIBool deallocate_pointers) {

        ice::MetricCalibration_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricCalibrationPluginSupport_destroy_data(
        MetricCalibration *sample) {

        ice::MetricCalibrationPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricCalibrationPluginSupport_copy_data(
        MetricCalibration *dst,
        const MetricCalibration *src)
    {
        return ice::MetricCalibration_copy(dst,(const MetricCalibration*) src);
    }

    void 
    MetricCalibrationPluginSupport_print_data(
        const MetricCalibration *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
            RTICdrType_printArray(
                ice::MetricCalEntrySeq_get_contiguous_bufferI(sample), 
                ice::MetricCalEntrySeq_get_length(sample),
                sizeof(ice::MetricCalEntry),
                (RTICdrTypePrintFunction)ice::MetricCalEntryPluginSupport_print_data,
                "", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample), 
                ice::MetricCalEntrySeq_get_length(sample),
                (RTICdrTypePrintFunction)ice::MetricCalEntryPluginSupport_print_data,
                "", indent_level + 1);
        }

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricCalibrationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *dst,
        const MetricCalibration *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricCalibrationPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricCalibrationPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalibration *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                    ice::MetricCalEntrySeq_get_length(sample),
                    (100),
                    sizeof(ice::MetricCalEntry),
                    (RTICdrStreamSerializeFunction)ice::MetricCalEntryPlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                    ice::MetricCalEntrySeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::MetricCalEntryPlugin_serialize,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricCalibrationPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricCalibration_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::MetricCalEntrySeq_get_maximum(sample),
                            sizeof(ice::MetricCalEntry),
                            (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::MetricCalEntrySeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_deserialize_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::MetricCalEntrySeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricCalibrationPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            {
                RTICdrUnsignedLong sequence_length;
                if (!RTICdrStream_skipNonPrimitiveSequence(
                    stream,
                    &sequence_length,
                    sizeof(ice::MetricCalEntry),
                    (RTICdrStreamSkipFunction)ice::MetricCalEntryPlugin_skip,
                    RTI_FALSE,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
        }

        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::MetricCalEntryPlugin_get_serialized_sample_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricCalibrationPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricCalibrationPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
            current_alignment, 0,
            ice::MetricCalEntryPlugin_get_serialized_sample_min_size,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricCalibrationPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricCalibration * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += RTICdrType_get4ByteMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
            current_alignment += RTICdrType_getNonPrimitiveArraySerializedSize(
                current_alignment, ice::MetricCalEntrySeq_get_length(sample),
                sizeof(ice::MetricCalEntry),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::MetricCalEntryPlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                endpoint_data);
        } else {
            current_alignment += RTICdrStream_getNonPrimitivePointerArraySerializedSize(
                current_alignment,  
                ice::MetricCalEntrySeq_get_length(sample),
                sizeof(ice::MetricCalEntry),
                (RTICdrTypeGetSerializedSampleSizeFunction)ice::MetricCalEntryPlugin_get_serialized_sample_size,
                RTI_FALSE,encapsulation_id,
                (const void **)ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                endpoint_data);
        }

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricCalibrationPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricCalibrationPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricCalibration *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                if (!RTICdrStream_serializeNonPrimitiveSequence(
                    stream,
                    ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                    ice::MetricCalEntrySeq_get_length(sample),
                    (100),
                    sizeof(ice::MetricCalEntry),
                    (RTICdrStreamSerializeFunction)ice::MetricCalEntryPlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            } else {
                if (!RTICdrStream_serializeNonPrimitivePointerSequence(
                    stream,
                    (const void **) ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                    ice::MetricCalEntrySeq_get_length(sample),
                    (100),
                    (RTICdrStreamSerializeFunction)ice::MetricCalEntryPlugin_serialize_key,
                    RTI_FALSE, encapsulation_id,RTI_TRUE,
                    endpoint_data,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                } 
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricCalibrationPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                {
                    RTICdrUnsignedLong sequence_length;
                    if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                        if (!RTICdrStream_deserializeNonPrimitiveSequence(
                            stream,
                            ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                            &sequence_length,
                            ice::MetricCalEntrySeq_get_maximum(sample),
                            sizeof(ice::MetricCalEntry),
                            (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    } else {
                        if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                            stream,
                            (void **) ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                            &sequence_length,
                            ice::MetricCalEntrySeq_get_maximum(sample),
                            (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_deserialize_key_sample,
                            RTI_FALSE,RTI_TRUE,
                            endpoint_data,endpoint_plugin_qos)) {
                            return RTI_FALSE;
                        }
                    }
                    if (!ice::MetricCalEntrySeq_set_length(
                        sample,sequence_length)) {
                        return RTI_FALSE;
                    }        

                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    unsigned int
    MetricCalibrationPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
            overflow,
            current_alignment, (100),
            ice::MetricCalEntryPlugin_get_serialized_key_max_size_ex,
            RTI_FALSE,encapsulation_id,endpoint_data);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricCalibrationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricCalibrationPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricCalibrationPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricCalibration *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            {
                RTICdrUnsignedLong sequence_length;
                if (ice::MetricCalEntrySeq_get_contiguous_bufferI(sample) != NULL) {
                    if (!RTICdrStream_deserializeNonPrimitiveSequence(
                        stream,
                        ice::MetricCalEntrySeq_get_contiguous_bufferI(sample),
                        &sequence_length,
                        ice::MetricCalEntrySeq_get_maximum(sample),
                        sizeof(ice::MetricCalEntry),
                        (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                } else {
                    if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                        stream,
                        (void **) ice::MetricCalEntrySeq_get_discontiguous_bufferI(sample),
                        &sequence_length,
                        ice::MetricCalEntrySeq_get_maximum(sample),
                        (RTICdrStreamDeserializeFunction)ice::MetricCalEntryPlugin_serialized_sample_to_key,
                        RTI_FALSE,RTI_TRUE,
                        endpoint_data,endpoint_plugin_qos)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::MetricCalEntrySeq_set_length(
                    sample,sequence_length)) {
                    return RTI_FALSE;
                }        

            }

        }

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricMeasure
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricMeasure*
    MetricMeasurePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricMeasure *sample = NULL;

        sample = new (std::nothrow) MetricMeasure ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricMeasure_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricMeasure *
    MetricMeasurePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricMeasure *sample = NULL;

        sample = new (std::nothrow) MetricMeasure ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricMeasure_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricMeasure *
    MetricMeasurePluginSupport_create_data(void)
    {
        return ice::MetricMeasurePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricMeasurePluginSupport_destroy_data_w_params(
        MetricMeasure *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricMeasure_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricMeasurePluginSupport_destroy_data_ex(
        MetricMeasure *sample,RTIBool deallocate_pointers) {

        ice::MetricMeasure_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricMeasurePluginSupport_destroy_data(
        MetricMeasure *sample) {

        ice::MetricMeasurePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricMeasurePluginSupport_copy_data(
        MetricMeasure *dst,
        const MetricMeasure *src)
    {
        return ice::MetricMeasure_copy(dst,(const MetricMeasure*) src);
    }

    void 
    MetricMeasurePluginSupport_print_data(
        const MetricMeasure *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::FLOATTypePluginSupport_print_data(
            (const ice::FLOATType*) &sample->value, "value", indent_level + 1);

        ice::OIDTypePluginSupport_print_data(
            (const ice::OIDType*) &sample->unit_code, "unit_code", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricMeasurePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *dst,
        const MetricMeasure *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricMeasurePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricMeasurePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricMeasurePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricMeasure *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if(!ice::FLOATTypePlugin_serialize(
                endpoint_data,
                (const ice::FLOATType*) &sample->value,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::OIDTypePlugin_serialize(
                endpoint_data,
                (const ice::OIDType*) &sample->unit_code,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricMeasurePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        try {

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */
            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricMeasure_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::FLOATTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->value,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::OIDTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->unit_code,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    MetricMeasurePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricMeasure *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        MetricMeasurePlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            MetricMeasurePlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::MetricMeasurePlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    MetricMeasurePlugin_deserialize_from_cdr_buffer(
        MetricMeasure *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        MetricMeasure_finalize_optional_members(sample, RTI_TRUE);
        return MetricMeasurePlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    MetricMeasurePlugin_data_to_string(
        const MetricMeasure *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!MetricMeasurePlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!MetricMeasurePlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            MetricMeasure_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    MetricMeasurePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "MetricMeasurePlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricMeasurePlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "MetricMeasure");

        }

        return result;

    }

    RTIBool MetricMeasurePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::FLOATTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::OIDTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricMeasurePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricMeasurePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricMeasurePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricMeasurePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */ 

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricMeasurePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricMeasure * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (sample==NULL) {
            return 0;
        }
        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::FLOATTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::FLOATType*) &sample->value);

        current_alignment += ice::OIDTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::OIDType*) &sample->unit_code);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricMeasurePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    MetricMeasurePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricMeasure *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::MetricMeasurePlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricMeasurePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if (endpoint_data) {} /* To avoid warnings */
            if (endpoint_plugin_qos) {} /* To avoid warnings */

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::MetricMeasurePlugin_deserialize_sample(
                    endpoint_data, sample, stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricMeasurePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricMeasurePlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    MetricMeasurePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (endpoint_data) {} /* To avoid warnings */
        if (overflow) {} /* To avoid warnings */

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::MetricMeasurePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricMeasurePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricMeasurePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricMeasurePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricMeasure *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::MetricMeasurePlugin_deserialize_sample(
                endpoint_data, sample, stream, RTI_FALSE, 
                RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricContext
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricContext*
    MetricContextPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricContext *sample = NULL;

        sample = new (std::nothrow) MetricContext ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricContext_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricContext *
    MetricContextPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricContext *sample = NULL;

        sample = new (std::nothrow) MetricContext ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricContext_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricContext *
    MetricContextPluginSupport_create_data(void)
    {
        return ice::MetricContextPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricContextPluginSupport_destroy_data_w_params(
        MetricContext *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricContext_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricContextPluginSupport_destroy_data_ex(
        MetricContext *sample,RTIBool deallocate_pointers) {

        ice::MetricContext_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricContextPluginSupport_destroy_data(
        MetricContext *sample) {

        ice::MetricContextPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricContextPluginSupport_copy_data(
        MetricContext *dst,
        const MetricContext *src)
    {
        return ice::MetricContext_copy(dst,(const MetricContext*) src);
    }

    void 
    MetricContextPluginSupport_print_data(
        const MetricContext *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::VMOPluginSupport_print_data((const ice::VMO*)sample,"",indent_level);

        RTICdrType_printLong(
            &sample->context_seq_number, "context_seq_number", indent_level + 1);    

        ice::MetricSpecPluginSupport_print_data(
            (const ice::MetricSpec*) &sample->metric_specification, "metric_specification", indent_level + 1);

        ice::DurationPluginSupport_print_data(
            (const ice::Duration*) sample->max_delay_time, "max_delay_time", indent_level + 1);

        if (sample->vmo_label_string==NULL) {
            RTICdrType_printString(
                NULL,"vmo_label_string", indent_level + 1);
        } else {
            RTICdrType_printString(
                sample->vmo_label_string,"vmo_label_string", indent_level + 1);    
        }

        ice::VmoSourceListPluginSupport_print_data(
            (const ice::VmoSourceList*) &sample->vmo_source_list, "vmo_source_list", indent_level + 1);

        ice::MetricSourceListPluginSupport_print_data(
            (const ice::MetricSourceList*) &sample->metric_source_list, "metric_source_list", indent_level + 1);

        ice::OIDTypePluginSupport_print_data(
            (const ice::OIDType*) &sample->unit_code, "unit_code", indent_level + 1);

        if (sample->unit_label_string==NULL) {
            RTICdrType_printString(
                NULL,"unit_label_string", indent_level + 1);
        } else {
            RTICdrType_printString(
                sample->unit_label_string,"unit_label_string", indent_level + 1);    
        }

        ice::SiteListPluginSupport_print_data(
            (const ice::SiteList*) &sample->msmt_site_list, "msmt_site_list", indent_level + 1);

        ice::SiteListPluginSupport_print_data(
            (const ice::SiteList*) &sample->body_site_list, "body_site_list", indent_level + 1);

        ice::MetricStatusPluginSupport_print_data(
            (const ice::MetricStatus*) &sample->metric_status, "metric_status", indent_level + 1);

        ice::MetricMeasurePluginSupport_print_data(
            (const ice::MetricMeasure*) sample->measure_period, "measure_period", indent_level + 1);

        ice::MetricMeasurePluginSupport_print_data(
            (const ice::MetricMeasure*) sample->averaging_period, "averaging_period", indent_level + 1);

        ice::TimespecPluginSupport_print_data(
            (const ice::Timespec*) sample->start_time, "start_time", indent_level + 1);

        ice::TimespecPluginSupport_print_data(
            (const ice::Timespec*) sample->stop_time, "stop_time", indent_level + 1);

        ice::MetricCalibrationPluginSupport_print_data(
            (const ice::MetricCalibration*) &sample->metric_calibration, "metric_calibration", indent_level + 1);

        ice::SimpleColorPluginSupport_print_data(
            (const ice::SimpleColor*) sample->color, "color", indent_level + 1);

        ice::MeasurementStatusPluginSupport_print_data(
            (const ice::MeasurementStatus*) &sample->measurement_status, "measurement_status", indent_level + 1);

        ice::OIDTypePluginSupport_print_data(
            (const ice::OIDType*) &sample->metric_id, "metric_id", indent_level + 1);

        if (sample->metric_info_label_string==NULL) {
            RTICdrType_printString(
                NULL,"metric_info_label_string", indent_level + 1);
        } else {
            RTICdrType_printString(
                sample->metric_info_label_string,"metric_info_label_string", indent_level + 1);    
        }

        ice::ExtNomenRefPluginSupport_print_data(
            (const ice::ExtNomenRef*) sample->substance, "substance", indent_level + 1);

        if (sample->substance_label_string==NULL) {
            RTICdrType_printString(
                NULL,"substance_label_string", indent_level + 1);
        } else {
            RTICdrType_printString(
                sample->substance_label_string,"substance_label_string", indent_level + 1);    
        }

    }
    MetricContext *
    MetricContextPluginSupport_create_key_ex(RTIBool allocate_pointers){
        MetricContext *key = NULL;

        key = new (std::nothrow) MetricContextKeyHolder ;

        ice::MetricContext_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    MetricContext *
    MetricContextPluginSupport_create_key(void)
    {
        return  ice::MetricContextPluginSupport_create_key_ex(RTI_TRUE);
    }

    void 
    MetricContextPluginSupport_destroy_key_ex(
        MetricContextKeyHolder *key,RTIBool deallocate_pointers)
    {
        ice::MetricContext_finalize_ex(key,deallocate_pointers);

        delete  key;
        key=NULL;

    }

    void 
    MetricContextPluginSupport_destroy_key(
        MetricContextKeyHolder *key) {

        ice::MetricContextPluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricContextPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *dst,
        const MetricContext *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricContextPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricContextPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricContext *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        DDS_UnsignedLong memberId = 0;
        char *memberLengthPosition = NULL;
        RTIBool extended;
        struct RTICdrStreamState state;

        if(serialize_encapsulation) {
            if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_BE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_BE;
            } else if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_LE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_LE;
            }

            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {
            if (RTICdrStream_isDirty(stream)) {
            } else {
                /* Top level */
                RTICdrStream_setDirtyBit(stream,RTI_TRUE);

                if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedSample(endpoint_data) > 65535) {
                    stream->_xTypesState.useExtendedId = RTI_TRUE;
                } else {
                    stream->_xTypesState.useExtendedId = RTI_FALSE;
                }
            }

            if (!ice::VMOPlugin_serialize(endpoint_data,
            (const ice::VMO*)sample,stream,RTI_FALSE,encapsulation_id,
            RTI_TRUE,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeLong(
                stream, &sample->context_seq_number)) {
                return RTI_FALSE;
            }

            if(!ice::MetricSpecPlugin_serialize(
                endpoint_data,
                (const ice::MetricSpec*) &sample->metric_specification,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            memberId = 7;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->max_delay_time!=NULL) {
                if(!ice::DurationPlugin_serialize(
                    endpoint_data,
                    (const ice::Duration*) sample->max_delay_time,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeString(
                stream, sample->vmo_label_string, ((ice::LONG_STRING_LEN)) + 1)) {
                return RTI_FALSE;
            }

            if(!ice::VmoSourceListPlugin_serialize(
                endpoint_data,
                (const ice::VmoSourceList*) &sample->vmo_source_list,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricSourceListPlugin_serialize(
                endpoint_data,
                (const ice::MetricSourceList*) &sample->metric_source_list,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::OIDTypePlugin_serialize(
                endpoint_data,
                (const ice::OIDType*) &sample->unit_code,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeString(
                stream, sample->unit_label_string, ((ice::LONG_STRING_LEN)) + 1)) {
                return RTI_FALSE;
            }

            if(!ice::SiteListPlugin_serialize(
                endpoint_data,
                (const ice::SiteList*) &sample->msmt_site_list,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::SiteListPlugin_serialize(
                endpoint_data,
                (const ice::SiteList*) &sample->body_site_list,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MetricStatusPlugin_serialize(
                endpoint_data,
                (const ice::MetricStatus*) &sample->metric_status,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            memberId = 16;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->measure_period!=NULL) {
                if(!ice::MetricMeasurePlugin_serialize(
                    endpoint_data,
                    (const ice::MetricMeasure*) sample->measure_period,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            memberId = 17;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->averaging_period!=NULL) {
                if(!ice::MetricMeasurePlugin_serialize(
                    endpoint_data,
                    (const ice::MetricMeasure*) sample->averaging_period,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            memberId = 18;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->start_time!=NULL) {
                if(!ice::TimespecPlugin_serialize(
                    endpoint_data,
                    (const ice::Timespec*) sample->start_time,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            memberId = 19;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->stop_time!=NULL) {
                if(!ice::TimespecPlugin_serialize(
                    endpoint_data,
                    (const ice::Timespec*) sample->stop_time,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            if(!ice::MetricCalibrationPlugin_serialize(
                endpoint_data,
                (const ice::MetricCalibration*) &sample->metric_calibration,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            memberId = 21;
            extended = RTI_FALSE;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->color!=NULL) {
                if(!ice::SimpleColorPlugin_serialize(
                    endpoint_data,
                    (const ice::SimpleColor*) sample->color,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            if(!ice::MeasurementStatusPlugin_serialize(
                endpoint_data,
                (const ice::MeasurementStatus*) &sample->measurement_status,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::OIDTypePlugin_serialize(
                endpoint_data,
                (const ice::OIDType*) &sample->metric_id,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeString(
                stream, sample->metric_info_label_string, ((ice::LONG_STRING_LEN)) + 1)) {
                return RTI_FALSE;
            }

            memberId = 25;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->substance!=NULL) {
                if(!ice::ExtNomenRefPlugin_serialize(
                    endpoint_data,
                    (const ice::ExtNomenRef*) sample->substance,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeString(
                stream, sample->substance_label_string, ((ice::LONG_STRING_LEN)) + 1)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricContextPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;
        RTIBool extended;

        try {

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricContext_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
                if (!ice::VMOPlugin_deserialize_sample(endpoint_data,
                (ice::VMO *)sample,stream,RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }

                if (!RTICdrStream_deserializeLong(
                    stream, &sample->context_seq_number)) {
                    goto fin; 
                }
                if(!ice::MetricSpecPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_specification,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->max_delay_time = new (std::nothrow) ice::Duration ;
                    if (sample->max_delay_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Duration_initialize_ex(sample->max_delay_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::DurationPlugin_deserialize_sample(
                        endpoint_data,
                        sample->max_delay_time,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);
                if (!RTICdrStream_deserializeStringEx(
                    stream,&sample->vmo_label_string, ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)) {
                    goto fin; 
                }
                if(!ice::VmoSourceListPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->vmo_source_list,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricSourceListPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_source_list,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::OIDTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->unit_code,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if (!RTICdrStream_deserializeStringEx(
                    stream,&sample->unit_label_string, ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)) {
                    goto fin; 
                }
                if(!ice::SiteListPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->msmt_site_list,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::SiteListPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->body_site_list,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MetricStatusPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_status,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->measure_period = new (std::nothrow) ice::MetricMeasure ;
                    if (sample->measure_period==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::MetricMeasure_initialize_ex(sample->measure_period, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::MetricMeasurePlugin_deserialize_sample(
                        endpoint_data,
                        sample->measure_period,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->averaging_period = new (std::nothrow) ice::MetricMeasure ;
                    if (sample->averaging_period==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::MetricMeasure_initialize_ex(sample->averaging_period, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::MetricMeasurePlugin_deserialize_sample(
                        endpoint_data,
                        sample->averaging_period,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->start_time = new (std::nothrow) ice::Timespec ;
                    if (sample->start_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(sample->start_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::TimespecPlugin_deserialize_sample(
                        endpoint_data,
                        sample->start_time,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->stop_time = new (std::nothrow) ice::Timespec ;
                    if (sample->stop_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(sample->stop_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::TimespecPlugin_deserialize_sample(
                        endpoint_data,
                        sample->stop_time,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);
                if(!ice::MetricCalibrationPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_calibration,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->color = new (std::nothrow) ice::SimpleColor ;
                    if (sample->color==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::SimpleColor_initialize_ex(sample->color, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::SimpleColorPlugin_deserialize_sample(
                        endpoint_data,
                        sample->color,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);
                if(!ice::MeasurementStatusPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->measurement_status,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::OIDTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_id,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if (!RTICdrStream_deserializeStringEx(
                    stream,&sample->metric_info_label_string, ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)) {
                    goto fin; 
                }

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->substance = new (std::nothrow) ice::ExtNomenRef ;
                    if (sample->substance==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::ExtNomenRef_initialize_ex(sample->substance, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::ExtNomenRefPlugin_deserialize_sample(
                        endpoint_data,
                        sample->substance,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);
                if (!RTICdrStream_deserializeStringEx(
                    stream,&sample->substance_label_string, ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)) {
                    goto fin; 
                }
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    MetricContextPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricContext *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        MetricContextPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            MetricContextPlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::MetricContextPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    MetricContextPlugin_deserialize_from_cdr_buffer(
        MetricContext *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        MetricContext_finalize_optional_members(sample, RTI_TRUE);
        return MetricContextPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    MetricContextPlugin_data_to_string(
        const MetricContext *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!MetricContextPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!MetricContextPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            MetricContext_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    MetricContextPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "MetricContextPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricContextPlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "MetricContext");

        }

        return result;

    }

    RTIBool MetricContextPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;
        RTIBool extended;

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::VMOPlugin_skip(endpoint_data,
            stream,RTI_FALSE,RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_skipLong (stream)) {
                goto fin; 
            }
            if (!ice::MetricSpecPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::DurationPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);
            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }
            if (!ice::VmoSourceListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricSourceListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::OIDTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }
            if (!ice::SiteListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::SiteListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::MetricStatusPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::MetricMeasurePlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::MetricMeasurePlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);
            if (!ice::MetricCalibrationPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::SimpleColorPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);
            if (!ice::MeasurementStatusPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::OIDTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::ExtNomenRefPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);
            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricContextPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,overflow,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getLongMaxSizeSerialized(
            current_alignment);

        current_alignment +=ice::MetricSpecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::DurationPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, ((ice::LONG_STRING_LEN))+1);

        current_alignment +=ice::VmoSourceListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricSourceListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, ((ice::LONG_STRING_LEN))+1);

        current_alignment +=ice::SiteListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::SiteListPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::MetricStatusPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::MetricMeasurePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::MetricMeasurePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::TimespecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::TimespecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment +=ice::MetricCalibrationPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::SimpleColorPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment +=ice::MeasurementStatusPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, ((ice::LONG_STRING_LEN))+1);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::ExtNomenRefPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, ((ice::LONG_STRING_LEN))+1);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricContextPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricContextPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getLongMaxSizeSerialized(
            current_alignment);
        current_alignment +=ice::MetricSpecPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, 1);
        current_alignment +=ice::VmoSourceListPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricSourceListPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, 1);
        current_alignment +=ice::SiteListPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::SiteListPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::MetricStatusPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment +=ice::MetricCalibrationPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment += RTICdrStream_getParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment +=ice::MeasurementStatusPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, 1);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment +=RTICdrType_getStringMaxSizeSerialized(
            current_alignment, 1);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricContextPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricContext * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_size(endpoint_data,RTI_FALSE,encapsulation_id,current_alignment,(const ice::VMO*)sample);   

        current_alignment += RTICdrType_getLongMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        current_alignment += ice::MetricSpecPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricSpec*) &sample->metric_specification);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->max_delay_time!=NULL) {

            current_alignment += ice::DurationPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::Duration*) sample->max_delay_time);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }

        current_alignment += RTICdrType_getStringSerializedSize(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment), sample->vmo_label_string);

        current_alignment += ice::VmoSourceListPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::VmoSourceList*) &sample->vmo_source_list);

        current_alignment += ice::MetricSourceListPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricSourceList*) &sample->metric_source_list);

        current_alignment += ice::OIDTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::OIDType*) &sample->unit_code);

        current_alignment += RTICdrType_getStringSerializedSize(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment), sample->unit_label_string);

        current_alignment += ice::SiteListPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::SiteList*) &sample->msmt_site_list);

        current_alignment += ice::SiteListPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::SiteList*) &sample->body_site_list);

        current_alignment += ice::MetricStatusPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricStatus*) &sample->metric_status);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->measure_period!=NULL) {

            current_alignment += ice::MetricMeasurePlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::MetricMeasure*) sample->measure_period);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->averaging_period!=NULL) {

            current_alignment += ice::MetricMeasurePlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::MetricMeasure*) sample->averaging_period);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->start_time!=NULL) {

            current_alignment += ice::TimespecPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::Timespec*) sample->start_time);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->stop_time!=NULL) {

            current_alignment += ice::TimespecPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::Timespec*) sample->stop_time);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }

        current_alignment += ice::MetricCalibrationPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MetricCalibration*) &sample->metric_calibration);
        current_alignment += RTICdrStream_getParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->color!=NULL) {

            current_alignment += ice::SimpleColorPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::SimpleColor*) sample->color);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }

        current_alignment += ice::MeasurementStatusPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MeasurementStatus*) &sample->measurement_status);

        current_alignment += ice::OIDTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::OIDType*) &sample->metric_id);

        current_alignment += RTICdrType_getStringSerializedSize(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment), sample->metric_info_label_string);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->substance!=NULL) {

            current_alignment += ice::ExtNomenRefPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::ExtNomenRef*) sample->substance);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }

        current_alignment += RTICdrType_getStringSerializedSize(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment), sample->substance_label_string);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricContextPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool 
    MetricContextPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricContext *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_BE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_BE;
            } else if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_LE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_LE;
            }

            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::VMOPlugin_serialize_key(endpoint_data, 
            (const ice::VMO*)sample, stream, RTI_FALSE, 
            encapsulation_id,RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::OIDTypePlugin_serialize_key(
                endpoint_data,
                (const ice::OIDType*) &sample->metric_id,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricContextPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::VMOPlugin_deserialize_key_sample(endpoint_data,
                (ice::VMO*)sample,stream,RTI_FALSE,RTI_TRUE,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }    

                if(!ice::OIDTypePlugin_deserialize_key_sample(
                    endpoint_data,
                    &sample->metric_id,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricContextPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricContextPlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    MetricContextPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_key_max_size_ex(
            endpoint_data,
            overflow,
            RTI_FALSE, encapsulation_id,
            current_alignment);

        current_alignment +=ice::OIDTypePlugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricContextPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricContextPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricContextPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool extended;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::VMOPlugin_serialized_sample_to_key(endpoint_data,
            (ice::VMO *)sample,
            stream, RTI_FALSE, RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_skipLong (stream)) {
                goto fin; 
            }

            if (!ice::MetricSpecPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::DurationPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }

            if (!ice::VmoSourceListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!ice::MetricSourceListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!ice::OIDTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }

            if (!ice::SiteListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!ice::SiteListPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!ice::MetricStatusPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::MetricMeasurePlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::MetricMeasurePlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!ice::MetricCalibrationPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::SimpleColorPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!ice::MeasurementStatusPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if(!ice::OIDTypePlugin_serialized_sample_to_key(
                endpoint_data,
                &sample->metric_id,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::ExtNomenRefPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
                goto fin; 
            }

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricContextPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricContextKeyHolder *dst, 
        const MetricContext *src)
    {

        if (!ice::VMOPlugin_instance_to_key(endpoint_data,(ice::VMO *)dst,(const ice::VMO*)src)) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_copy(
            &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
            return RTI_FALSE;
        } 
        return RTI_TRUE;
    }

    RTIBool 
    MetricContextPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        MetricContext *dst, const
        MetricContextKeyHolder *src)
    {

        if (!ice::VMOPlugin_key_to_instance(endpoint_data,(ice::VMO*)dst,(const ice::VMO*)src)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_copy(
            &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
            return RTI_FALSE;
        } 
        return RTI_TRUE;
    }

    RTIBool 
    MetricContextPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const MetricContext *instance)
    {
        struct RTICdrStream * md5Stream = NULL;
        struct RTICdrStreamState cdrState;
        char * buffer = NULL;

        RTICdrStreamState_init(&cdrState);
        md5Stream = PRESTypePluginDefaultEndpointData_getMD5Stream(endpoint_data);

        if (md5Stream == NULL) {
            return RTI_FALSE;
        }

        RTICdrStream_resetPosition(md5Stream);
        RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);

        if (!ice::MetricContextPlugin_serialize_key(
            endpoint_data,
            instance,
            md5Stream, 
            RTI_FALSE, 
            RTI_CDR_ENCAPSULATION_ID_CDR_BE, 
            RTI_TRUE,
            NULL)) 
        {
            int size;

            RTICdrStream_pushState(md5Stream, &cdrState, -1);

            size = (int)ice::MetricContextPlugin_get_serialized_sample_size(
                endpoint_data,
                RTI_FALSE,
                RTI_CDR_ENCAPSULATION_ID_CDR_BE,
                0,
                instance);

            if (size <= RTICdrStream_getBufferLength(md5Stream)) {
                RTICdrStream_popState(md5Stream, &cdrState);        
                return RTI_FALSE;
            }   

            RTIOsapiHeap_allocateBuffer(&buffer,size,0);

            if (buffer == NULL) {
                RTICdrStream_popState(md5Stream, &cdrState);
                return RTI_FALSE;
            }

            RTICdrStream_set(md5Stream, buffer, size);
            RTIOsapiMemory_zero(
                RTICdrStream_getBuffer(md5Stream),
                RTICdrStream_getBufferLength(md5Stream));
            RTICdrStream_resetPosition(md5Stream);
            RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);
            if (!ice::MetricContextPlugin_serialize_key(
                endpoint_data,
                instance,
                md5Stream, 
                RTI_FALSE, 
                RTI_CDR_ENCAPSULATION_ID_CDR_BE, 
                RTI_TRUE,
                NULL)) 
            {
                RTICdrStream_popState(md5Stream, &cdrState);
                RTIOsapiHeap_freeBuffer(buffer);
                return RTI_FALSE;
            }        
        }   

        if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedKey(endpoint_data) > 
        (unsigned int)(MIG_RTPS_KEY_HASH_MAX_LENGTH) ||
        PRESTypePluginDefaultEndpointData_forceMD5KeyHash(endpoint_data)) {
            RTICdrStream_computeMD5(md5Stream, keyhash->value);
        } else {
            RTIOsapiMemory_zero(keyhash->value,MIG_RTPS_KEY_HASH_MAX_LENGTH);
            RTIOsapiMemory_copy(
                keyhash->value, 
                RTICdrStream_getBuffer(md5Stream), 
                RTICdrStream_getCurrentPositionOffset(md5Stream));
        }

        keyhash->length = MIG_RTPS_KEY_HASH_MAX_LENGTH;

        if (buffer != NULL) {
            RTICdrStream_popState(md5Stream, &cdrState);
            RTIOsapiHeap_freeBuffer(buffer);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricContextPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos) 
    {   
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        RTIBool extended = RTI_FALSE;
        struct RTICdrStreamState state = {NULL, NULL, 0};
        MetricContext * sample=NULL;

        if (endpoint_plugin_qos) {} /* To avoid warnings */
        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }

        if (memberId) {} /* To avoid warnings */
        if (length) {} /* To avoid warnings */
        if (mustUnderstand) {} /* To avoid warnings */
        if (extended) {} /* To avoid warnings */
        if (state.buffer != NULL) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        sample = (MetricContext *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (!ice::VMOPlugin_serialized_sample_to_key(endpoint_data,
        (ice::VMO *)sample,
        stream, RTI_FALSE, RTI_TRUE,
        endpoint_plugin_qos)) {
            return RTI_FALSE;
        }

        if (!RTICdrStream_skipLong (stream)) {
            goto fin; 
        }
        if (!ice::MetricSpecPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::DurationPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);
        if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
            goto fin; 
        }
        if (!ice::VmoSourceListPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if (!ice::MetricSourceListPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if (!ice::OIDTypePlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if (!RTICdrStream_skipString (stream, ((ice::LONG_STRING_LEN))+1)) {
            goto fin; 
        }
        if (!ice::SiteListPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if (!ice::SiteListPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if (!ice::MetricStatusPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::MetricMeasurePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::MetricMeasurePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::TimespecPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::TimespecPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);
        if (!ice::MetricCalibrationPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }

        if (!RTICdrStream_deserializeParameterHeader(
            stream,
            &state,
            &memberId,
            &length,
            &extended,
            &mustUnderstand)) {
            goto fin; 
        }
        if (length > 0) {

            if (!ice::SimpleColorPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
        }
        RTICdrStream_moveToNextParameterHeader(stream, &state, length);
        if (!ice::MeasurementStatusPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
            goto fin; 
        }
        if(!ice::OIDTypePlugin_serialized_sample_to_key(
            endpoint_data,
            &sample->metric_id,
            stream,
            RTI_FALSE, RTI_TRUE,
            endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        } 

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        if (!ice::MetricContextPlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type MetricObservedValue
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    MetricObservedValue*
    MetricObservedValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        MetricObservedValue *sample = NULL;

        sample = new (std::nothrow) MetricObservedValue ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::MetricObservedValue_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    MetricObservedValue *
    MetricObservedValuePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        MetricObservedValue *sample = NULL;

        sample = new (std::nothrow) MetricObservedValue ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::MetricObservedValue_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    MetricObservedValue *
    MetricObservedValuePluginSupport_create_data(void)
    {
        return ice::MetricObservedValuePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    MetricObservedValuePluginSupport_destroy_data_w_params(
        MetricObservedValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::MetricObservedValue_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricObservedValuePluginSupport_destroy_data_ex(
        MetricObservedValue *sample,RTIBool deallocate_pointers) {

        ice::MetricObservedValue_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    MetricObservedValuePluginSupport_destroy_data(
        MetricObservedValue *sample) {

        ice::MetricObservedValuePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    MetricObservedValuePluginSupport_copy_data(
        MetricObservedValue *dst,
        const MetricObservedValue *src)
    {
        return ice::MetricObservedValue_copy(dst,(const MetricObservedValue*) src);
    }

    void 
    MetricObservedValuePluginSupport_print_data(
        const MetricObservedValue *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILog_debug("%s:\n", desc);
        } else {
            RTILog_debug("\n");
        }

        if (sample == NULL) {
            RTILog_debug("NULL\n");
            return;
        }

        ice::VMOPluginSupport_print_data((const ice::VMO*)sample,"",indent_level);

        RTICdrType_printLong(
            &sample->context_seq_number, "context_seq_number", indent_level + 1);    

        ice::NomPartitionPluginSupport_print_data(
            (const ice::NomPartition*) &sample->metric_id_partition, "metric_id_partition", indent_level + 1);

        ice::TimespecPluginSupport_print_data(
            (const ice::Timespec*) sample->device_timestamp, "device_timestamp", indent_level + 1);

        ice::DurationPluginSupport_print_data(
            (const ice::Duration*) sample->device_relative_timestamp, "device_relative_timestamp", indent_level + 1);

    }
    MetricObservedValue *
    MetricObservedValuePluginSupport_create_key_ex(RTIBool allocate_pointers){
        MetricObservedValue *key = NULL;

        key = new (std::nothrow) MetricObservedValueKeyHolder ;

        ice::MetricObservedValue_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    MetricObservedValue *
    MetricObservedValuePluginSupport_create_key(void)
    {
        return  ice::MetricObservedValuePluginSupport_create_key_ex(RTI_TRUE);
    }

    void 
    MetricObservedValuePluginSupport_destroy_key_ex(
        MetricObservedValueKeyHolder *key,RTIBool deallocate_pointers)
    {
        ice::MetricObservedValue_finalize_ex(key,deallocate_pointers);

        delete  key;
        key=NULL;

    }

    void 
    MetricObservedValuePluginSupport_destroy_key(
        MetricObservedValueKeyHolder *key) {

        ice::MetricObservedValuePluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    MetricObservedValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *dst,
        const MetricObservedValue *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::MetricObservedValuePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    MetricObservedValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const MetricObservedValue *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        DDS_UnsignedLong memberId = 0;
        char *memberLengthPosition = NULL;
        RTIBool extended;
        struct RTICdrStreamState state;

        if(serialize_encapsulation) {
            if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_BE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_BE;
            } else if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_LE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_LE;
            }

            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {
            if (RTICdrStream_isDirty(stream)) {
            } else {
                /* Top level */
                RTICdrStream_setDirtyBit(stream,RTI_TRUE);

                if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedSample(endpoint_data) > 65535) {
                    stream->_xTypesState.useExtendedId = RTI_TRUE;
                } else {
                    stream->_xTypesState.useExtendedId = RTI_FALSE;
                }
            }

            if (!ice::VMOPlugin_serialize(endpoint_data,
            (const ice::VMO*)sample,stream,RTI_FALSE,encapsulation_id,
            RTI_TRUE,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_serializeLong(
                stream, &sample->context_seq_number)) {
                return RTI_FALSE;
            }

            if(!ice::NomPartitionPlugin_serialize(
                endpoint_data,
                (const ice::NomPartition*) &sample->metric_id_partition,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            memberId = 7;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->device_timestamp!=NULL) {
                if(!ice::TimespecPlugin_serialize(
                    endpoint_data,
                    (const ice::Timespec*) sample->device_timestamp,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

            memberId = 8;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->device_relative_timestamp!=NULL) {
                if(!ice::DurationPlugin_serialize(
                    endpoint_data,
                    (const ice::Duration*) sample->device_relative_timestamp,
                    stream,
                    RTI_FALSE, encapsulation_id,
                    RTI_TRUE,
                    endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }
            }
            if (!RTICdrStream_serializeParameterLength(
                stream, &state, extended, memberLengthPosition)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return retval;
    }

    RTIBool 
    MetricObservedValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;
        RTIBool extended;

        try {

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::MetricObservedValue_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
                if (!ice::VMOPlugin_deserialize_sample(endpoint_data,
                (ice::VMO *)sample,stream,RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }

                if (!RTICdrStream_deserializeLong(
                    stream, &sample->context_seq_number)) {
                    goto fin; 
                }
                if(!ice::NomPartitionPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_id_partition,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->device_timestamp = new (std::nothrow) ice::Timespec ;
                    if (sample->device_timestamp==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(sample->device_timestamp, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::TimespecPlugin_deserialize_sample(
                        endpoint_data,
                        sample->device_timestamp,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);

                if (!RTICdrStream_deserializeParameterHeader(
                    stream,
                    &state,
                    &memberId,
                    &length,
                    &extended,
                    &mustUnderstand)) {
                    goto fin; 
                }
                if (length > 0) {

                    sample->device_relative_timestamp = new (std::nothrow) ice::Duration ;
                    if (sample->device_relative_timestamp==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Duration_initialize_ex(sample->device_relative_timestamp, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::DurationPlugin_deserialize_sample(
                        endpoint_data,
                        sample->device_relative_timestamp,
                        stream,
                        RTI_FALSE, RTI_TRUE,
                        endpoint_plugin_qos)) {
                        goto fin; 
                    }
                }
                RTICdrStream_moveToNextParameterHeader(stream, &state, length);
            }

            done = RTI_TRUE;
          fin:
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool
    MetricObservedValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MetricObservedValue *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        MetricObservedValuePlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            MetricObservedValuePlugin_get_serialized_sample_size(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                RTICdrEncapsulation_getNativeCdrEncapsulationId(),
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }    

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, *length);

        result = ice::MetricObservedValuePlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    MetricObservedValuePlugin_deserialize_from_cdr_buffer(
        MetricObservedValue *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        MetricObservedValue_finalize_optional_members(sample, RTI_TRUE);
        return MetricObservedValuePlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    MetricObservedValuePlugin_data_to_string(
        const MetricObservedValue *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (!MetricObservedValuePlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!MetricObservedValuePlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            MetricObservedValue_get_typecode(), 
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data, 
            str,
            str_size, 
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }

    RTIBool 
    MetricObservedValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "MetricObservedValuePlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricObservedValuePlugin_deserialize_sample( 
            endpoint_data, (sample != NULL)?*sample:NULL,
            stream, deserialize_encapsulation, deserialize_sample, 
            endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }
        if (!result && stream->_xTypesState.unassignable ) {

            RTICdrLog_exception(
                METHOD_NAME, 
                &RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s, 
                "MetricObservedValue");

        }

        return result;

    }

    RTIBool MetricObservedValuePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;
        RTIBool extended;

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::VMOPlugin_skip(endpoint_data,
            stream,RTI_FALSE,RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_skipLong (stream)) {
                goto fin; 
            }
            if (!ice::NomPartitionPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::DurationPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);
        }

        done = RTI_TRUE;
      fin:
        if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
        RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            return RTI_FALSE;   
        }
        if(skip_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,overflow,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getLongMaxSizeSerialized(
            current_alignment);

        current_alignment +=ice::NomPartitionPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::TimespecPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::DurationPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricObservedValuePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    MetricObservedValuePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=RTICdrType_getLongMaxSizeSerialized(
            current_alignment);
        current_alignment +=ice::NomPartitionPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    /* Returns the size of the sample in its serialized form (in bytes).
    * It can also be an estimation in excess of the real buffer needed 
    * during a call to the serialize() function.
    * The value reported does not have to include the space for the
    * encapsulation flags.
    */
    unsigned int
    MetricObservedValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const MetricObservedValue * sample) 
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;
        struct PRESTypePluginDefaultEndpointData epd;   

        if (endpoint_data == NULL) {
            endpoint_data = (PRESTypePluginEndpointData) &epd;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);        
        }

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
            PRESTypePluginDefaultEndpointData_setBaseAlignment(
                endpoint_data,
                current_alignment);
        }

        current_alignment += ice::VMOPlugin_get_serialized_sample_size(endpoint_data,RTI_FALSE,encapsulation_id,current_alignment,(const ice::VMO*)sample);   

        current_alignment += RTICdrType_getLongMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(
                endpoint_data, current_alignment));

        current_alignment += ice::NomPartitionPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::NomPartition*) &sample->metric_id_partition);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->device_timestamp!=NULL) {

            current_alignment += ice::TimespecPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::Timespec*) sample->device_timestamp);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->device_relative_timestamp!=NULL) {

            current_alignment += ice::DurationPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::Duration*) sample->device_relative_timestamp);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    MetricObservedValuePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool 
    MetricObservedValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const MetricObservedValue *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        if(serialize_encapsulation) {
            if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_BE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_BE;
            } else if (encapsulation_id == RTI_CDR_ENCAPSULATION_ID_CDR_LE) {
                encapsulation_id = RTI_CDR_ENCAPSULATION_ID_PL_CDR_LE;
            }

            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_key) {

            if (!ice::VMOPlugin_serialize_key(endpoint_data, 
            (const ice::VMO*)sample, stream, RTI_FALSE, 
            encapsulation_id,RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool MetricObservedValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        try {

            char * position = NULL;

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if (deserialize_key) {

                if (!ice::VMOPlugin_deserialize_key_sample(endpoint_data,
                (ice::VMO*)sample,stream,RTI_FALSE,RTI_TRUE,endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }    

            }

            if(deserialize_encapsulation) {
                RTICdrStream_restoreAlignment(stream,position);
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    RTIBool MetricObservedValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::MetricObservedValuePlugin_deserialize_key_sample(
            endpoint_data, (sample != NULL)?*sample:NULL, stream,
            deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        if (result) {
            if (stream->_xTypesState.unassignable) {
                result = RTI_FALSE;
            }
        }

        return result;    

    }

    unsigned int
    MetricObservedValuePlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {

        unsigned int initial_alignment = current_alignment;

        unsigned int encapsulation_size = current_alignment;

        if (include_encapsulation) {

            if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
                return 1;
            }
            RTICdrStream_getEncapsulationSize(encapsulation_size);
            encapsulation_size -= current_alignment;
            current_alignment = 0;
            initial_alignment = 0;
        }

        current_alignment += ice::VMOPlugin_get_serialized_key_max_size_ex(
            endpoint_data,
            overflow,
            RTI_FALSE, encapsulation_id,
            current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    MetricObservedValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = MetricObservedValuePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    MetricObservedValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool extended;
        RTIBool mustUnderstand = RTI_FALSE;
        struct RTICdrStreamState state;

        if (endpoint_data) {} /* To avoid warnings */
        if (endpoint_plugin_qos) {} /* To avoid warnings */

        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }
        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }
            position = RTICdrStream_resetAlignment(stream);
        }

        if (deserialize_key) {

            if (!ice::VMOPlugin_serialized_sample_to_key(endpoint_data,
            (ice::VMO *)sample,
            stream, RTI_FALSE, RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!RTICdrStream_skipLong (stream)) {
                goto fin; 
            }

            if (!ice::NomPartitionPlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::TimespecPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

            if (!RTICdrStream_deserializeParameterHeader(
                stream,
                &state,
                &memberId,
                &length,
                &extended,
                &mustUnderstand)) {
                goto fin; 
            }
            if (length > 0) {

                if (!ice::DurationPlugin_skip(
                    endpoint_data,
                    stream, 
                    RTI_FALSE, RTI_TRUE, 
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
            }
            RTICdrStream_moveToNextParameterHeader(stream, &state, length);

        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        }       

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricObservedValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValueKeyHolder *dst, 
        const MetricObservedValue *src)
    {

        if (!ice::VMOPlugin_instance_to_key(endpoint_data,(ice::VMO *)dst,(const ice::VMO*)src)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricObservedValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        MetricObservedValue *dst, const
        MetricObservedValueKeyHolder *src)
    {

        if (!ice::VMOPlugin_key_to_instance(endpoint_data,(ice::VMO*)dst,(const ice::VMO*)src)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    RTIBool 
    MetricObservedValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const MetricObservedValue *instance)
    {
        struct RTICdrStream * md5Stream = NULL;
        struct RTICdrStreamState cdrState;
        char * buffer = NULL;

        RTICdrStreamState_init(&cdrState);
        md5Stream = PRESTypePluginDefaultEndpointData_getMD5Stream(endpoint_data);

        if (md5Stream == NULL) {
            return RTI_FALSE;
        }

        RTICdrStream_resetPosition(md5Stream);
        RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);

        if (!ice::MetricObservedValuePlugin_serialize_key(
            endpoint_data,
            instance,
            md5Stream, 
            RTI_FALSE, 
            RTI_CDR_ENCAPSULATION_ID_CDR_BE, 
            RTI_TRUE,
            NULL)) 
        {
            int size;

            RTICdrStream_pushState(md5Stream, &cdrState, -1);

            size = (int)ice::MetricObservedValuePlugin_get_serialized_sample_size(
                endpoint_data,
                RTI_FALSE,
                RTI_CDR_ENCAPSULATION_ID_CDR_BE,
                0,
                instance);

            if (size <= RTICdrStream_getBufferLength(md5Stream)) {
                RTICdrStream_popState(md5Stream, &cdrState);        
                return RTI_FALSE;
            }   

            RTIOsapiHeap_allocateBuffer(&buffer,size,0);

            if (buffer == NULL) {
                RTICdrStream_popState(md5Stream, &cdrState);
                return RTI_FALSE;
            }

            RTICdrStream_set(md5Stream, buffer, size);
            RTIOsapiMemory_zero(
                RTICdrStream_getBuffer(md5Stream),
                RTICdrStream_getBufferLength(md5Stream));
            RTICdrStream_resetPosition(md5Stream);
            RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);
            if (!ice::MetricObservedValuePlugin_serialize_key(
                endpoint_data,
                instance,
                md5Stream, 
                RTI_FALSE, 
                RTI_CDR_ENCAPSULATION_ID_CDR_BE, 
                RTI_TRUE,
                NULL)) 
            {
                RTICdrStream_popState(md5Stream, &cdrState);
                RTIOsapiHeap_freeBuffer(buffer);
                return RTI_FALSE;
            }        
        }   

        if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedKey(endpoint_data) > 
        (unsigned int)(MIG_RTPS_KEY_HASH_MAX_LENGTH) ||
        PRESTypePluginDefaultEndpointData_forceMD5KeyHash(endpoint_data)) {
            RTICdrStream_computeMD5(md5Stream, keyhash->value);
        } else {
            RTIOsapiMemory_zero(keyhash->value,MIG_RTPS_KEY_HASH_MAX_LENGTH);
            RTIOsapiMemory_copy(
                keyhash->value, 
                RTICdrStream_getBuffer(md5Stream), 
                RTICdrStream_getCurrentPositionOffset(md5Stream));
        }

        keyhash->length = MIG_RTPS_KEY_HASH_MAX_LENGTH;

        if (buffer != NULL) {
            RTICdrStream_popState(md5Stream, &cdrState);
            RTIOsapiHeap_freeBuffer(buffer);
        }

        return RTI_TRUE;
    }

    RTIBool 
    MetricObservedValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos) 
    {   
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        DDS_UnsignedLong memberId = 0;
        DDS_UnsignedLong length = 0;
        RTIBool mustUnderstand = RTI_FALSE;
        RTIBool extended = RTI_FALSE;
        struct RTICdrStreamState state = {NULL, NULL, 0};
        MetricObservedValue * sample=NULL;

        if (endpoint_plugin_qos) {} /* To avoid warnings */
        if (stream == NULL) {
            error = RTI_TRUE;
            goto fin;
        }

        if (memberId) {} /* To avoid warnings */
        if (length) {} /* To avoid warnings */
        if (mustUnderstand) {} /* To avoid warnings */
        if (extended) {} /* To avoid warnings */
        if (state.buffer != NULL) {} /* To avoid warnings */

        if(deserialize_encapsulation) {
            if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        sample = (MetricObservedValue *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (!ice::VMOPlugin_serialized_sample_to_key(endpoint_data,
        (ice::VMO *)sample,
        stream, RTI_FALSE, RTI_TRUE,
        endpoint_plugin_qos)) {
            return RTI_FALSE;
        }

        done = RTI_TRUE;
      fin:
        if(!error) {
            if (done != RTI_TRUE && 
            RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
                return RTI_FALSE;   
            }
        } else {
            return RTI_FALSE;
        } 

        if(deserialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        if (!ice::MetricObservedValuePlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */
} /* namespace ice  */
#undef RTI_CDR_CURRENT_SUBMODULE 
