
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from numeric.idl using "rtiddsgen".
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

#include "numericPlugin.h"

namespace ice {

    /* ----------------------------------------------------------------------------
    *  Type AbsoluteRange
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    AbsoluteRange*
    AbsoluteRangePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        AbsoluteRange *sample = NULL;

        sample = new (std::nothrow) AbsoluteRange ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::AbsoluteRange_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    AbsoluteRange *
    AbsoluteRangePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        AbsoluteRange *sample = NULL;

        sample = new (std::nothrow) AbsoluteRange ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::AbsoluteRange_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    AbsoluteRange *
    AbsoluteRangePluginSupport_create_data(void)
    {
        return ice::AbsoluteRangePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    AbsoluteRangePluginSupport_destroy_data_w_params(
        AbsoluteRange *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::AbsoluteRange_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    AbsoluteRangePluginSupport_destroy_data_ex(
        AbsoluteRange *sample,RTIBool deallocate_pointers) {

        ice::AbsoluteRange_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    AbsoluteRangePluginSupport_destroy_data(
        AbsoluteRange *sample) {

        ice::AbsoluteRangePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    AbsoluteRangePluginSupport_copy_data(
        AbsoluteRange *dst,
        const AbsoluteRange *src)
    {
        return ice::AbsoluteRange_copy(dst,(const AbsoluteRange*) src);
    }

    void 
    AbsoluteRangePluginSupport_print_data(
        const AbsoluteRange *sample,
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
            (const ice::FLOATType*) &sample->lower_value, "lower_value", indent_level + 1);

        ice::FLOATTypePluginSupport_print_data(
            (const ice::FLOATType*) &sample->upper_value, "upper_value", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    AbsoluteRangePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *dst,
        const AbsoluteRange *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::AbsoluteRangePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    AbsoluteRangePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const AbsoluteRange *sample, 
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
                (const ice::FLOATType*) &sample->lower_value,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::FLOATTypePlugin_serialize(
                endpoint_data,
                (const ice::FLOATType*) &sample->upper_value,
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
    AbsoluteRangePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *sample,
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

                ice::AbsoluteRange_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::FLOATTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->lower_value,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::FLOATTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->upper_value,
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
    AbsoluteRangePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const AbsoluteRange *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        AbsoluteRangePlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            AbsoluteRangePlugin_get_serialized_sample_size(
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

        result = ice::AbsoluteRangePlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    AbsoluteRangePlugin_deserialize_from_cdr_buffer(
        AbsoluteRange *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        AbsoluteRange_finalize_optional_members(sample, RTI_TRUE);
        return AbsoluteRangePlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    AbsoluteRangePlugin_data_to_string(
        const AbsoluteRange *sample,
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

        if (!AbsoluteRangePlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!AbsoluteRangePlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            AbsoluteRange_get_typecode(), 
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
    AbsoluteRangePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "AbsoluteRangePlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::AbsoluteRangePlugin_deserialize_sample( 
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
                "AbsoluteRange");

        }

        return result;

    }

    RTIBool AbsoluteRangePlugin_skip(
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
            if (!ice::FLOATTypePlugin_skip(
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
    AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
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

        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    AbsoluteRangePlugin_get_serialized_sample_min_size(
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
        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_min_size(
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
    AbsoluteRangePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const AbsoluteRange * sample) 
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
            current_alignment, (const ice::FLOATType*) &sample->lower_value);

        current_alignment += ice::FLOATTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::FLOATType*) &sample->upper_value);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    AbsoluteRangePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    AbsoluteRangePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const AbsoluteRange *sample, 
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

            if (!ice::AbsoluteRangePlugin_serialize(
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

    RTIBool AbsoluteRangePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *sample, 
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

                if (!ice::AbsoluteRangePlugin_deserialize_sample(
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

    RTIBool AbsoluteRangePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::AbsoluteRangePlugin_deserialize_key_sample(
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
    AbsoluteRangePlugin_get_serialized_key_max_size_ex(
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

        current_alignment += ice::AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    AbsoluteRangePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = AbsoluteRangePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    AbsoluteRangePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        AbsoluteRange *sample,
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

            if (!ice::AbsoluteRangePlugin_deserialize_sample(
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
    *  Type DispResolution
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    DispResolution*
    DispResolutionPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        DispResolution *sample = NULL;

        sample = new (std::nothrow) DispResolution ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::DispResolution_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    DispResolution *
    DispResolutionPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        DispResolution *sample = NULL;

        sample = new (std::nothrow) DispResolution ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::DispResolution_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    DispResolution *
    DispResolutionPluginSupport_create_data(void)
    {
        return ice::DispResolutionPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    DispResolutionPluginSupport_destroy_data_w_params(
        DispResolution *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::DispResolution_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    DispResolutionPluginSupport_destroy_data_ex(
        DispResolution *sample,RTIBool deallocate_pointers) {

        ice::DispResolution_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    DispResolutionPluginSupport_destroy_data(
        DispResolution *sample) {

        ice::DispResolutionPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    DispResolutionPluginSupport_copy_data(
        DispResolution *dst,
        const DispResolution *src)
    {
        return ice::DispResolution_copy(dst,(const DispResolution*) src);
    }

    void 
    DispResolutionPluginSupport_print_data(
        const DispResolution *sample,
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

        ice::INTU8PluginSupport_print_data(
            (const ice::INTU8*) &sample->pre_point, "pre_point", indent_level + 1);

        ice::INTU8PluginSupport_print_data(
            (const ice::INTU8*) &sample->post_point, "post_point", indent_level + 1);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    DispResolutionPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *dst,
        const DispResolution *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::DispResolutionPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    DispResolutionPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    DispResolutionPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const DispResolution *sample, 
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

            if(!ice::INTU8Plugin_serialize(
                endpoint_data,
                (const ice::INTU8*) &sample->pre_point,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::INTU8Plugin_serialize(
                endpoint_data,
                (const ice::INTU8*) &sample->post_point,
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
    DispResolutionPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *sample,
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

                ice::DispResolution_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::INTU8Plugin_deserialize_sample(
                    endpoint_data,
                    &sample->pre_point,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::INTU8Plugin_deserialize_sample(
                    endpoint_data,
                    &sample->post_point,
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
    DispResolutionPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DispResolution *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        DispResolutionPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            DispResolutionPlugin_get_serialized_sample_size(
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

        result = ice::DispResolutionPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    DispResolutionPlugin_deserialize_from_cdr_buffer(
        DispResolution *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        DispResolution_finalize_optional_members(sample, RTI_TRUE);
        return DispResolutionPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    DispResolutionPlugin_data_to_string(
        const DispResolution *sample,
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

        if (!DispResolutionPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!DispResolutionPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            DispResolution_get_typecode(), 
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
    DispResolutionPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "DispResolutionPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::DispResolutionPlugin_deserialize_sample( 
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
                "DispResolution");

        }

        return result;

    }

    RTIBool DispResolutionPlugin_skip(
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

            if (!ice::INTU8Plugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
                goto fin; 
            }
            if (!ice::INTU8Plugin_skip(
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
    DispResolutionPlugin_get_serialized_sample_max_size_ex(
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

        current_alignment +=ice::INTU8Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::INTU8Plugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    DispResolutionPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = DispResolutionPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    DispResolutionPlugin_get_serialized_sample_min_size(
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

        current_alignment +=ice::INTU8Plugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::INTU8Plugin_get_serialized_sample_min_size(
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
    DispResolutionPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const DispResolution * sample) 
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

        current_alignment += ice::INTU8Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::INTU8*) &sample->pre_point);

        current_alignment += ice::INTU8Plugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::INTU8*) &sample->post_point);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    DispResolutionPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_NO_KEY;
    }

    RTIBool 
    DispResolutionPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const DispResolution *sample, 
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

            if (!ice::DispResolutionPlugin_serialize(
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

    RTIBool DispResolutionPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *sample, 
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

                if (!ice::DispResolutionPlugin_deserialize_sample(
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

    RTIBool DispResolutionPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::DispResolutionPlugin_deserialize_key_sample(
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
    DispResolutionPlugin_get_serialized_key_max_size_ex(
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

        current_alignment += ice::DispResolutionPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow,RTI_FALSE, encapsulation_id, current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    DispResolutionPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = DispResolutionPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    DispResolutionPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        DispResolution *sample,
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

            if (!ice::DispResolutionPlugin_deserialize_sample(
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
    *  Type NuObsValue
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    NuObsValue*
    NuObsValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        NuObsValue *sample = NULL;

        sample = new (std::nothrow) NuObsValue ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::NuObsValue_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    NuObsValue *
    NuObsValuePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        NuObsValue *sample = NULL;

        sample = new (std::nothrow) NuObsValue ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::NuObsValue_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    NuObsValue *
    NuObsValuePluginSupport_create_data(void)
    {
        return ice::NuObsValuePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    NuObsValuePluginSupport_destroy_data_w_params(
        NuObsValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::NuObsValue_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    NuObsValuePluginSupport_destroy_data_ex(
        NuObsValue *sample,RTIBool deallocate_pointers) {

        ice::NuObsValue_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    NuObsValuePluginSupport_destroy_data(
        NuObsValue *sample) {

        ice::NuObsValuePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    NuObsValuePluginSupport_copy_data(
        NuObsValue *dst,
        const NuObsValue *src)
    {
        return ice::NuObsValue_copy(dst,(const NuObsValue*) src);
    }

    void 
    NuObsValuePluginSupport_print_data(
        const NuObsValue *sample,
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
            (const ice::OIDType*) &sample->metric_id, "metric_id", indent_level + 1);

        ice::MeasurementStatusPluginSupport_print_data(
            (const ice::MeasurementStatus*) &sample->state, "state", indent_level + 1);

        ice::OIDTypePluginSupport_print_data(
            (const ice::OIDType*) &sample->unit_code, "unit_code", indent_level + 1);

        ice::FLOATTypePluginSupport_print_data(
            (const ice::FLOATType*) &sample->value, "value", indent_level + 1);

    }
    NuObsValue *
    NuObsValuePluginSupport_create_key_ex(RTIBool allocate_pointers){
        NuObsValue *key = NULL;

        key = new (std::nothrow) NuObsValueKeyHolder ;

        ice::NuObsValue_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    NuObsValue *
    NuObsValuePluginSupport_create_key(void)
    {
        return  ice::NuObsValuePluginSupport_create_key_ex(RTI_TRUE);
    }

    void 
    NuObsValuePluginSupport_destroy_key_ex(
        NuObsValueKeyHolder *key,RTIBool deallocate_pointers)
    {
        ice::NuObsValue_finalize_ex(key,deallocate_pointers);

        delete  key;
        key=NULL;

    }

    void 
    NuObsValuePluginSupport_destroy_key(
        NuObsValueKeyHolder *key) {

        ice::NuObsValuePluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    RTIBool 
    NuObsValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *dst,
        const NuObsValue *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::NuObsValuePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    NuObsValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    NuObsValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NuObsValue *sample, 
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
                (const ice::OIDType*) &sample->metric_id,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::MeasurementStatusPlugin_serialize(
                endpoint_data,
                (const ice::MeasurementStatus*) &sample->state,
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

            if(!ice::FLOATTypePlugin_serialize(
                endpoint_data,
                (const ice::FLOATType*) &sample->value,
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
    NuObsValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *sample,
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

                ice::NuObsValue_initialize_ex(sample, RTI_FALSE, RTI_FALSE);

                if(!ice::OIDTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->metric_id,
                    stream,
                    RTI_FALSE, RTI_TRUE,
                    endpoint_plugin_qos)) {
                    goto fin; 
                }
                if(!ice::MeasurementStatusPlugin_deserialize_sample(
                    endpoint_data,
                    &sample->state,
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
                if(!ice::FLOATTypePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->value,
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
    NuObsValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NuObsValue *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        NuObsValuePlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            NuObsValuePlugin_get_serialized_sample_size(
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

        result = ice::NuObsValuePlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    NuObsValuePlugin_deserialize_from_cdr_buffer(
        NuObsValue *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        NuObsValue_finalize_optional_members(sample, RTI_TRUE);
        return NuObsValuePlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    NuObsValuePlugin_data_to_string(
        const NuObsValue *sample,
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

        if (!NuObsValuePlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!NuObsValuePlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            NuObsValue_get_typecode(), 
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
    NuObsValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "NuObsValuePlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NuObsValuePlugin_deserialize_sample( 
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
                "NuObsValue");

        }

        return result;

    }

    RTIBool NuObsValuePlugin_skip(
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
            if (!ice::FLOATTypePlugin_skip(
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
    NuObsValuePlugin_get_serialized_sample_max_size_ex(
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

        current_alignment +=ice::MeasurementStatusPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    NuObsValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NuObsValuePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    NuObsValuePlugin_get_serialized_sample_min_size(
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
        current_alignment +=ice::MeasurementStatusPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::OIDTypePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_min_size(
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
    NuObsValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NuObsValue * sample) 
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
            current_alignment, (const ice::OIDType*) &sample->metric_id);

        current_alignment += ice::MeasurementStatusPlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::MeasurementStatus*) &sample->state);

        current_alignment += ice::OIDTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::OIDType*) &sample->unit_code);

        current_alignment += ice::FLOATTypePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::FLOATType*) &sample->value);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    NuObsValuePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool 
    NuObsValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NuObsValue *sample, 
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

    RTIBool NuObsValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *sample, 
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

    RTIBool NuObsValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NuObsValuePlugin_deserialize_key_sample(
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
    NuObsValuePlugin_get_serialized_key_max_size_ex(
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

        current_alignment +=ice::OIDTypePlugin_get_serialized_key_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    unsigned int
    NuObsValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NuObsValuePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    NuObsValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

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

            if(!ice::OIDTypePlugin_serialized_sample_to_key(
                endpoint_data,
                &sample->metric_id,
                stream,
                RTI_FALSE, RTI_TRUE,
                endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
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

            if (!ice::FLOATTypePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
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
    NuObsValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValueKeyHolder *dst, 
        const NuObsValue *src)
    {

        if (endpoint_data) {} /* To avoid warnings */   

        if (!ice::OIDType_copy(
            &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
            return RTI_FALSE;
        } 
        return RTI_TRUE;
    }

    RTIBool 
    NuObsValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NuObsValue *dst, const
        NuObsValueKeyHolder *src)
    {

        if (endpoint_data) {} /* To avoid warnings */   
        if (!ice::OIDType_copy(
            &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
            return RTI_FALSE;
        } 
        return RTI_TRUE;
    }

    RTIBool 
    NuObsValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NuObsValue *instance)
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

        if (!ice::NuObsValuePlugin_serialize_key(
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

            size = (int)ice::NuObsValuePlugin_get_serialized_sample_size(
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
            if (!ice::NuObsValuePlugin_serialize_key(
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
    NuObsValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos) 
    {   
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        NuObsValue * sample=NULL;

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

        sample = (NuObsValue *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

        if (sample == NULL) {
            return RTI_FALSE;
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

        if (!ice::NuObsValuePlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */

    /* ----------------------------------------------------------------------------
    *  Type NumericContext
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    NumericContext*
    NumericContextPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        NumericContext *sample = NULL;

        sample = new (std::nothrow) NumericContext ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::NumericContext_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    NumericContext *
    NumericContextPluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        NumericContext *sample = NULL;

        sample = new (std::nothrow) NumericContext ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::NumericContext_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    NumericContext *
    NumericContextPluginSupport_create_data(void)
    {
        return ice::NumericContextPluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    NumericContextPluginSupport_destroy_data_w_params(
        NumericContext *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::NumericContext_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    NumericContextPluginSupport_destroy_data_ex(
        NumericContext *sample,RTIBool deallocate_pointers) {

        ice::NumericContext_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    NumericContextPluginSupport_destroy_data(
        NumericContext *sample) {

        ice::NumericContextPluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    NumericContextPluginSupport_copy_data(
        NumericContext *dst,
        const NumericContext *src)
    {
        return ice::NumericContext_copy(dst,(const NumericContext*) src);
    }

    void 
    NumericContextPluginSupport_print_data(
        const NumericContext *sample,
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

        ice::MetricContextPluginSupport_print_data((const ice::MetricContext*)sample,"",indent_level);

        ice::AbsoluteRangePluginSupport_print_data(
            (const ice::AbsoluteRange*) sample->nu_measure_range, "nu_measure_range", indent_level + 1);

        ice::AbsoluteRangePluginSupport_print_data(
            (const ice::AbsoluteRange*) sample->nu_physiological_range, "nu_physiological_range", indent_level + 1);

        ice::DispResolutionPluginSupport_print_data(
            (const ice::DispResolution*) sample->display_resolution, "display_resolution", indent_level + 1);

        ice::FLOATTypePluginSupport_print_data(
            (const ice::FLOATType*) sample->accuracy, "accuracy", indent_level + 1);

    }
    NumericContext *
    NumericContextPluginSupport_create_key_ex(RTIBool allocate_pointers){
        NumericContext *key = NULL;

        key = new (std::nothrow) NumericContextKeyHolder ;

        ice::NumericContext_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    NumericContext *
    NumericContextPluginSupport_create_key(void)
    {
        return  ice::NumericContextPluginSupport_create_key_ex(RTI_TRUE);
    }

    void 
    NumericContextPluginSupport_destroy_key_ex(
        NumericContextKeyHolder *key,RTIBool deallocate_pointers)
    {
        ice::NumericContext_finalize_ex(key,deallocate_pointers);

        delete  key;
        key=NULL;

    }

    void 
    NumericContextPluginSupport_destroy_key(
        NumericContextKeyHolder *key) {

        ice::NumericContextPluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    PRESTypePluginParticipantData 
    NumericContextPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *type_code)
    {
        if (registration_data) {} /* To avoid warnings */
        if (participant_info) {} /* To avoid warnings */
        if (top_level_registration) {} /* To avoid warnings */
        if (container_plugin_context) {} /* To avoid warnings */
        if (type_code) {} /* To avoid warnings */

        return PRESTypePluginDefaultParticipantData_new(participant_info);

    }

    void 
    NumericContextPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data)
    {

        PRESTypePluginDefaultParticipantData_delete(participant_data);
    }

    PRESTypePluginEndpointData
    NumericContextPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *containerPluginContext)
    {
        PRESTypePluginEndpointData epd = NULL;

        unsigned int serializedSampleMaxSize;

        unsigned int serializedKeyMaxSize;

        if (top_level_registration) {} /* To avoid warnings */
        if (containerPluginContext) {} /* To avoid warnings */

        epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            ice::NumericContextPluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            ice::NumericContextPluginSupport_destroy_data,
            (PRESTypePluginDefaultEndpointDataCreateKeyFunction)
            ice::NumericContextPluginSupport_create_key ,            
            (PRESTypePluginDefaultEndpointDataDestroyKeyFunction)
            ice::NumericContextPluginSupport_destroy_key);

        if (epd == NULL) {
            return NULL;
        } 
        serializedKeyMaxSize =  ice::NumericContextPlugin_get_serialized_key_max_size(
            epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);

        if(!PRESTypePluginDefaultEndpointData_createMD5StreamWithInfo(
            epd,endpoint_info,serializedKeyMaxSize))  
        {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }

        if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
            serializedSampleMaxSize = ice::NumericContextPlugin_get_serialized_sample_max_size(
                epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);

            PRESTypePluginDefaultEndpointData_setMaxSizeSerializedSample(epd, serializedSampleMaxSize);

            if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                ice::NumericContextPlugin_get_serialized_sample_max_size, epd,
                (PRESTypePluginGetSerializedSampleSizeFunction)
                ice::NumericContextPlugin_get_serialized_sample_size,
                epd) == RTI_FALSE) {
                PRESTypePluginDefaultEndpointData_delete(epd);
                return NULL;
            }
        }

        return epd;    
    }

    void 
    NumericContextPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data)
    {  

        PRESTypePluginDefaultEndpointData_delete(endpoint_data);
    }

    void    
    NumericContextPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample,
        void *handle)
    {

        NumericContext_finalize_optional_members(sample, RTI_TRUE);

        PRESTypePluginDefaultEndpointData_returnSample(
            endpoint_data, sample, handle);
    }

    RTIBool 
    NumericContextPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *dst,
        const NumericContext *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::NumericContextPluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    NumericContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    NumericContextPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NumericContext *sample, 
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

            if (!ice::MetricContextPlugin_serialize(endpoint_data,
            (const ice::MetricContext*)sample,stream,RTI_FALSE,encapsulation_id,
            RTI_TRUE,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            memberId = 27;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->nu_measure_range!=NULL) {
                if(!ice::AbsoluteRangePlugin_serialize(
                    endpoint_data,
                    (const ice::AbsoluteRange*) sample->nu_measure_range,
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

            memberId = 28;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->nu_physiological_range!=NULL) {
                if(!ice::AbsoluteRangePlugin_serialize(
                    endpoint_data,
                    (const ice::AbsoluteRange*) sample->nu_physiological_range,
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

            memberId = 29;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->display_resolution!=NULL) {
                if(!ice::DispResolutionPlugin_serialize(
                    endpoint_data,
                    (const ice::DispResolution*) sample->display_resolution,
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

            memberId = 30;
            extended = stream->_xTypesState.useExtendedId;
            memberLengthPosition = RTICdrStream_serializeParameterHeader(
                stream, &state, extended, memberId, RTI_FALSE);
            if (memberLengthPosition == NULL) {
                return RTI_FALSE;
            }
            if (sample->accuracy!=NULL) {
                if(!ice::FLOATTypePlugin_serialize(
                    endpoint_data,
                    (const ice::FLOATType*) sample->accuracy,
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
    NumericContextPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample,
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

                ice::NumericContext_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
                if (!ice::MetricContextPlugin_deserialize_sample(endpoint_data,
                (ice::MetricContext *)sample,stream,RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
                    return RTI_FALSE;
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

                    sample->nu_measure_range = new (std::nothrow) ice::AbsoluteRange ;
                    if (sample->nu_measure_range==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::AbsoluteRange_initialize_ex(sample->nu_measure_range, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::AbsoluteRangePlugin_deserialize_sample(
                        endpoint_data,
                        sample->nu_measure_range,
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

                    sample->nu_physiological_range = new (std::nothrow) ice::AbsoluteRange ;
                    if (sample->nu_physiological_range==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::AbsoluteRange_initialize_ex(sample->nu_physiological_range, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::AbsoluteRangePlugin_deserialize_sample(
                        endpoint_data,
                        sample->nu_physiological_range,
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

                    sample->display_resolution = new (std::nothrow) ice::DispResolution ;
                    if (sample->display_resolution==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::DispResolution_initialize_ex(sample->display_resolution, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::DispResolutionPlugin_deserialize_sample(
                        endpoint_data,
                        sample->display_resolution,
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

                    sample->accuracy = new (std::nothrow) ice::FLOATType ;
                    if (sample->accuracy==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::FLOATType_initialize_ex(sample->accuracy, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                    if(!ice::FLOATTypePlugin_deserialize_sample(
                        endpoint_data,
                        sample->accuracy,
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
    NumericContextPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NumericContext *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        NumericContextPlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            NumericContextPlugin_get_serialized_sample_size(
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

        result = ice::NumericContextPlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    NumericContextPlugin_deserialize_from_cdr_buffer(
        NumericContext *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        NumericContext_finalize_optional_members(sample, RTI_TRUE);
        return NumericContextPlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    NumericContextPlugin_data_to_string(
        const NumericContext *sample,
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

        if (!NumericContextPlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!NumericContextPlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            NumericContext_get_typecode(), 
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
    NumericContextPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "NumericContextPlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NumericContextPlugin_deserialize_sample( 
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
                "NumericContext");

        }

        return result;

    }

    RTIBool NumericContextPlugin_skip(
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

            if (!ice::MetricContextPlugin_skip(endpoint_data,
            stream,RTI_FALSE,RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
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

                if (!ice::AbsoluteRangePlugin_skip(
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

                if (!ice::AbsoluteRangePlugin_skip(
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

                if (!ice::DispResolutionPlugin_skip(
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

                if (!ice::FLOATTypePlugin_skip(
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
    NumericContextPlugin_get_serialized_sample_max_size_ex(
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

        current_alignment += ice::MetricContextPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,overflow,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::AbsoluteRangePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::DispResolutionPlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);
        current_alignment +=ice::FLOATTypePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,0);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    NumericContextPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NumericContextPlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    NumericContextPlugin_get_serialized_sample_min_size(
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

        current_alignment += ice::MetricContextPlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(current_alignment);

        current_alignment += RTICdrType_getPadSize(current_alignment,RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
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
    NumericContextPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NumericContext * sample) 
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

        current_alignment += ice::MetricContextPlugin_get_serialized_sample_size(endpoint_data,RTI_FALSE,encapsulation_id,current_alignment,(const ice::MetricContext*)sample);   
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->nu_measure_range!=NULL) {

            current_alignment += ice::AbsoluteRangePlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::AbsoluteRange*) sample->nu_measure_range);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->nu_physiological_range!=NULL) {

            current_alignment += ice::AbsoluteRangePlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::AbsoluteRange*) sample->nu_physiological_range);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->display_resolution!=NULL) {

            current_alignment += ice::DispResolutionPlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::DispResolution*) sample->display_resolution);

            current_alignment += RTICdrType_getPadSize(
                PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment),
                RTI_CDR_PARAMETER_HEADER_ALIGNMENT);
        }
        current_alignment += RTICdrStream_getExtendedParameterHeaderMaxSizeSerialized(
            PRESTypePluginDefaultEndpointData_getAlignment(endpoint_data, current_alignment));
        PRESTypePluginDefaultEndpointData_setBaseAlignment(endpoint_data, current_alignment);
        if (sample->accuracy!=NULL) {

            current_alignment += ice::FLOATTypePlugin_get_serialized_sample_size(
                endpoint_data,RTI_FALSE, encapsulation_id,
                current_alignment, (const ice::FLOATType*) sample->accuracy);

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
    NumericContextPlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool 
    NumericContextPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NumericContext *sample, 
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

            if (!ice::MetricContextPlugin_serialize_key(endpoint_data, 
            (const ice::MetricContext*)sample, stream, RTI_FALSE, 
            encapsulation_id,RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool NumericContextPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample, 
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

                if (!ice::MetricContextPlugin_deserialize_key_sample(endpoint_data,
                (ice::MetricContext*)sample,stream,RTI_FALSE,RTI_TRUE,endpoint_plugin_qos)) {
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

    RTIBool NumericContextPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NumericContextPlugin_deserialize_key_sample(
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
    NumericContextPlugin_get_serialized_key_max_size_ex(
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

        current_alignment += ice::MetricContextPlugin_get_serialized_key_max_size_ex(
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
    NumericContextPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NumericContextPlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    NumericContextPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *sample,
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

            if (!ice::MetricContextPlugin_serialized_sample_to_key(endpoint_data,
            (ice::MetricContext *)sample,
            stream, RTI_FALSE, RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
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

                if (!ice::AbsoluteRangePlugin_skip(
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

                if (!ice::AbsoluteRangePlugin_skip(
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

                if (!ice::DispResolutionPlugin_skip(
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

                if (!ice::FLOATTypePlugin_skip(
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
    NumericContextPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericContextKeyHolder *dst, 
        const NumericContext *src)
    {

        if (!ice::MetricContextPlugin_instance_to_key(endpoint_data,(ice::MetricContext *)dst,(const ice::MetricContext*)src)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    RTIBool 
    NumericContextPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NumericContext *dst, const
        NumericContextKeyHolder *src)
    {

        if (!ice::MetricContextPlugin_key_to_instance(endpoint_data,(ice::MetricContext*)dst,(const ice::MetricContext*)src)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    RTIBool 
    NumericContextPlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NumericContext *instance)
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

        if (!ice::NumericContextPlugin_serialize_key(
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

            size = (int)ice::NumericContextPlugin_get_serialized_sample_size(
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
            if (!ice::NumericContextPlugin_serialize_key(
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
    NumericContextPlugin_serialized_sample_to_keyhash(
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
        NumericContext * sample=NULL;

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

        sample = (NumericContext *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (!ice::MetricContextPlugin_serialized_sample_to_key(endpoint_data,
        (ice::MetricContext *)sample,
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

        if (!ice::NumericContextPlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */
    struct PRESTypePlugin *NumericContextPlugin_new(void) 
    { 
        struct PRESTypePlugin *plugin = NULL;
        const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

        RTIOsapiHeap_allocateStructure(
            &plugin, struct PRESTypePlugin);

        if (plugin == NULL) {
            return NULL;
        }

        plugin->version = PLUGIN_VERSION;

        /* set up parent's function pointers */
        plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ice::NumericContextPlugin_on_participant_attached;
        plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ice::NumericContextPlugin_on_participant_detached;
        plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ice::NumericContextPlugin_on_endpoint_attached;
        plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ice::NumericContextPlugin_on_endpoint_detached;

        plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ice::NumericContextPlugin_copy_sample;
        plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        NumericContextPlugin_create_sample;
        plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        NumericContextPlugin_destroy_sample;
        plugin->finalizeOptionalMembersFnc =
        (PRESTypePluginFinalizeOptionalMembersFunction)
        NumericContext_finalize_optional_members;

        plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        ice::NumericContextPlugin_serialize;
        plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        ice::NumericContextPlugin_deserialize;
        plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ice::NumericContextPlugin_get_serialized_sample_max_size;
        plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        ice::NumericContextPlugin_get_serialized_sample_min_size;

        plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        NumericContextPlugin_get_sample;
        plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        NumericContextPlugin_return_sample;

        plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ice::NumericContextPlugin_get_key_kind;

        plugin->getSerializedKeyMaxSizeFnc =   
        (PRESTypePluginGetSerializedKeyMaxSizeFunction)
        ice::NumericContextPlugin_get_serialized_key_max_size;
        plugin->serializeKeyFnc =
        (PRESTypePluginSerializeKeyFunction)
        ice::NumericContextPlugin_serialize_key;
        plugin->deserializeKeyFnc =
        (PRESTypePluginDeserializeKeyFunction)
        ice::NumericContextPlugin_deserialize_key;
        plugin->deserializeKeySampleFnc =
        (PRESTypePluginDeserializeKeySampleFunction)
        ice::NumericContextPlugin_deserialize_key_sample;

        plugin-> instanceToKeyHashFnc = 
        (PRESTypePluginInstanceToKeyHashFunction)
        ice::NumericContextPlugin_instance_to_keyhash;
        plugin->serializedSampleToKeyHashFnc = 
        (PRESTypePluginSerializedSampleToKeyHashFunction)
        ice::NumericContextPlugin_serialized_sample_to_keyhash;

        plugin->getKeyFnc =
        (PRESTypePluginGetKeyFunction)
        NumericContextPlugin_get_key;
        plugin->returnKeyFnc =
        (PRESTypePluginReturnKeyFunction)
        NumericContextPlugin_return_key;

        plugin->instanceToKeyFnc =
        (PRESTypePluginInstanceToKeyFunction)
        ice::NumericContextPlugin_instance_to_key;
        plugin->keyToInstanceFnc =
        (PRESTypePluginKeyToInstanceFunction)
        ice::NumericContextPlugin_key_to_instance;
        plugin->serializedKeyToKeyHashFnc = NULL; /* Not supported yet */
        plugin->typeCode =  (struct RTICdrTypeCode *)ice::NumericContext_get_typecode();

        plugin->languageKind = PRES_TYPEPLUGIN_CPP_LANG;

        /* Serialized buffer */
        plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        NumericContextPlugin_get_buffer;
        plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        NumericContextPlugin_return_buffer;
        plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        ice::NumericContextPlugin_get_serialized_sample_size;

        plugin->endpointTypeName = NumericContextTYPENAME;

        return plugin;
    }

    void
    NumericContextPlugin_delete(struct PRESTypePlugin *plugin)
    {
        RTIOsapiHeap_freeStructure(plugin);
    } 

    /* ----------------------------------------------------------------------------
    *  Type NumericObservedValue
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    NumericObservedValue*
    NumericObservedValuePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params) 
    {
        NumericObservedValue *sample = NULL;

        sample = new (std::nothrow) NumericObservedValue ;
        if (sample == NULL) {
            return NULL;
        }

        if (!ice::NumericObservedValue_initialize_w_params(sample,alloc_params)) {
            delete  sample;
            sample=NULL;
        }
        return sample; 
    } 

    NumericObservedValue *
    NumericObservedValuePluginSupport_create_data_ex(RTIBool allocate_pointers) 
    {
        NumericObservedValue *sample = NULL;

        sample = new (std::nothrow) NumericObservedValue ;

        if(sample == NULL) {
            return NULL;
        }

        if (!ice::NumericObservedValue_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            delete  sample;
            sample=NULL;
        }

        return sample; 
    }

    NumericObservedValue *
    NumericObservedValuePluginSupport_create_data(void)
    {
        return ice::NumericObservedValuePluginSupport_create_data_ex(RTI_TRUE);
    }

    void 
    NumericObservedValuePluginSupport_destroy_data_w_params(
        NumericObservedValue *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {

        ice::NumericObservedValue_finalize_w_params(sample,dealloc_params);

        delete  sample;
        sample=NULL;
    }

    void 
    NumericObservedValuePluginSupport_destroy_data_ex(
        NumericObservedValue *sample,RTIBool deallocate_pointers) {

        ice::NumericObservedValue_finalize_ex(sample,deallocate_pointers);

        delete  sample;
        sample=NULL;
    }

    void 
    NumericObservedValuePluginSupport_destroy_data(
        NumericObservedValue *sample) {

        ice::NumericObservedValuePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    RTIBool 
    NumericObservedValuePluginSupport_copy_data(
        NumericObservedValue *dst,
        const NumericObservedValue *src)
    {
        return ice::NumericObservedValue_copy(dst,(const NumericObservedValue*) src);
    }

    void 
    NumericObservedValuePluginSupport_print_data(
        const NumericObservedValue *sample,
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

        ice::MetricObservedValuePluginSupport_print_data((const ice::MetricObservedValue*)sample,"",indent_level);

        ice::NuObsValuePluginSupport_print_data(
            (const ice::NuObsValue*) &sample->nu_observed_value, "nu_observed_value", indent_level + 1);

    }
    NumericObservedValue *
    NumericObservedValuePluginSupport_create_key_ex(RTIBool allocate_pointers){
        NumericObservedValue *key = NULL;

        key = new (std::nothrow) NumericObservedValueKeyHolder ;

        ice::NumericObservedValue_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    NumericObservedValue *
    NumericObservedValuePluginSupport_create_key(void)
    {
        return  ice::NumericObservedValuePluginSupport_create_key_ex(RTI_TRUE);
    }

    void 
    NumericObservedValuePluginSupport_destroy_key_ex(
        NumericObservedValueKeyHolder *key,RTIBool deallocate_pointers)
    {
        ice::NumericObservedValue_finalize_ex(key,deallocate_pointers);

        delete  key;
        key=NULL;

    }

    void 
    NumericObservedValuePluginSupport_destroy_key(
        NumericObservedValueKeyHolder *key) {

        ice::NumericObservedValuePluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    PRESTypePluginParticipantData 
    NumericObservedValuePlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *type_code)
    {
        if (registration_data) {} /* To avoid warnings */
        if (participant_info) {} /* To avoid warnings */
        if (top_level_registration) {} /* To avoid warnings */
        if (container_plugin_context) {} /* To avoid warnings */
        if (type_code) {} /* To avoid warnings */

        return PRESTypePluginDefaultParticipantData_new(participant_info);

    }

    void 
    NumericObservedValuePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data)
    {

        PRESTypePluginDefaultParticipantData_delete(participant_data);
    }

    PRESTypePluginEndpointData
    NumericObservedValuePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *containerPluginContext)
    {
        PRESTypePluginEndpointData epd = NULL;

        unsigned int serializedSampleMaxSize;

        unsigned int serializedKeyMaxSize;

        if (top_level_registration) {} /* To avoid warnings */
        if (containerPluginContext) {} /* To avoid warnings */

        epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            ice::NumericObservedValuePluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            ice::NumericObservedValuePluginSupport_destroy_data,
            (PRESTypePluginDefaultEndpointDataCreateKeyFunction)
            ice::NumericObservedValuePluginSupport_create_key ,            
            (PRESTypePluginDefaultEndpointDataDestroyKeyFunction)
            ice::NumericObservedValuePluginSupport_destroy_key);

        if (epd == NULL) {
            return NULL;
        } 
        serializedKeyMaxSize =  ice::NumericObservedValuePlugin_get_serialized_key_max_size(
            epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);

        if(!PRESTypePluginDefaultEndpointData_createMD5StreamWithInfo(
            epd,endpoint_info,serializedKeyMaxSize))  
        {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }

        if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
            serializedSampleMaxSize = ice::NumericObservedValuePlugin_get_serialized_sample_max_size(
                epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);

            PRESTypePluginDefaultEndpointData_setMaxSizeSerializedSample(epd, serializedSampleMaxSize);

            if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                ice::NumericObservedValuePlugin_get_serialized_sample_max_size, epd,
                (PRESTypePluginGetSerializedSampleSizeFunction)
                ice::NumericObservedValuePlugin_get_serialized_sample_size,
                epd) == RTI_FALSE) {
                PRESTypePluginDefaultEndpointData_delete(epd);
                return NULL;
            }
        }

        return epd;    
    }

    void 
    NumericObservedValuePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data)
    {  

        PRESTypePluginDefaultEndpointData_delete(endpoint_data);
    }

    void    
    NumericObservedValuePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample,
        void *handle)
    {

        NumericObservedValue_finalize_optional_members(sample, RTI_TRUE);

        PRESTypePluginDefaultEndpointData_returnSample(
            endpoint_data, sample, handle);
    }

    RTIBool 
    NumericObservedValuePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *dst,
        const NumericObservedValue *src)
    {
        if (endpoint_data) {} /* To avoid warnings */
        return ice::NumericObservedValuePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool 
    NumericObservedValuePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const NumericObservedValue *sample, 
        struct RTICdrStream *stream,    
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;
        RTIBool retval = RTI_TRUE;

        if(serialize_encapsulation) {
            if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream , encapsulation_id)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if(serialize_sample) {

            if (!ice::MetricObservedValuePlugin_serialize(endpoint_data,
            (const ice::MetricObservedValue*)sample,stream,RTI_FALSE,encapsulation_id,
            RTI_TRUE,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if(!ice::NuObsValuePlugin_serialize(
                endpoint_data,
                (const ice::NuObsValue*) &sample->nu_observed_value,
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
    NumericObservedValuePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        char * position = NULL;

        RTIBool done = RTI_FALSE;

        try {

            if(deserialize_encapsulation) {

                if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
                    return RTI_FALSE;
                }

                position = RTICdrStream_resetAlignment(stream);
            }
            if(deserialize_sample) {

                ice::NumericObservedValue_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
                if (!ice::MetricObservedValuePlugin_deserialize_sample(endpoint_data,
                (ice::MetricObservedValue *)sample,stream,RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
                    return RTI_FALSE;
                }

                if(!ice::NuObsValuePlugin_deserialize_sample(
                    endpoint_data,
                    &sample->nu_observed_value,
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
    NumericObservedValuePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const NumericObservedValue *sample)
    {
        struct RTICdrStream stream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;

        if (length == NULL) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        NumericObservedValuePlugin_get_serialized_sample_max_size(
            NULL, RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 0);

        if (buffer == NULL) {
            *length = 
            NumericObservedValuePlugin_get_serialized_sample_size(
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

        result = ice::NumericObservedValuePlugin_serialize(
            (PRESTypePluginEndpointData)&epd, sample, &stream, 
            RTI_TRUE, RTICdrEncapsulation_getNativeCdrEncapsulationId(), 
            RTI_TRUE, NULL);  

        *length = RTICdrStream_getCurrentPositionOffset(&stream);
        return result;     
    }

    RTIBool
    NumericObservedValuePlugin_deserialize_from_cdr_buffer(
        NumericObservedValue *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream stream;

        RTICdrStream_init(&stream);
        RTICdrStream_set(&stream, (char *)buffer, length);

        NumericObservedValue_finalize_optional_members(sample, RTI_TRUE);
        return NumericObservedValuePlugin_deserialize_sample( 
            NULL, sample,
            &stream, RTI_TRUE, RTI_TRUE, 
            NULL);
    }

    DDS_ReturnCode_t
    NumericObservedValuePlugin_data_to_string(
        const NumericObservedValue *sample,
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

        if (!NumericObservedValuePlugin_serialize_to_cdr_buffer(
            NULL, 
            &length, 
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!NumericObservedValuePlugin_serialize_to_cdr_buffer(
            buffer, 
            &length, 
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        data = DDS_DynamicData_new(
            NumericObservedValue_get_typecode(), 
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
    NumericObservedValuePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,   
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos)
    {

        RTIBool result;
        const char *METHOD_NAME = "NumericObservedValuePlugin_deserialize";
        if (drop_sample) {} /* To avoid warnings */

        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NumericObservedValuePlugin_deserialize_sample( 
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
                "NumericObservedValue");

        }

        return result;

    }

    RTIBool NumericObservedValuePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream,   
        RTIBool skip_encapsulation,
        RTIBool skip_sample, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;

        if(skip_encapsulation) {
            if (!RTICdrStream_skipEncapsulation(stream)) {
                return RTI_FALSE;
            }

            position = RTICdrStream_resetAlignment(stream);
        }

        if (skip_sample) {

            if (!ice::MetricObservedValuePlugin_skip(endpoint_data,
            stream,RTI_FALSE,RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!ice::NuObsValuePlugin_skip(
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
    NumericObservedValuePlugin_get_serialized_sample_max_size_ex(
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

        current_alignment += ice::MetricObservedValuePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,overflow,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::NuObsValuePlugin_get_serialized_sample_max_size_ex(
            endpoint_data, overflow, RTI_FALSE,encapsulation_id,current_alignment);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return  current_alignment - initial_alignment;
    }

    unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NumericObservedValuePlugin_get_serialized_sample_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int 
    NumericObservedValuePlugin_get_serialized_sample_min_size(
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

        current_alignment += ice::MetricObservedValuePlugin_get_serialized_sample_min_size(
            endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);

        current_alignment +=ice::NuObsValuePlugin_get_serialized_sample_min_size(
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
    NumericObservedValuePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const NumericObservedValue * sample) 
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

        current_alignment += ice::MetricObservedValuePlugin_get_serialized_sample_size(endpoint_data,RTI_FALSE,encapsulation_id,current_alignment,(const ice::MetricObservedValue*)sample);   

        current_alignment += ice::NuObsValuePlugin_get_serialized_sample_size(
            endpoint_data,RTI_FALSE, encapsulation_id,
            current_alignment, (const ice::NuObsValue*) &sample->nu_observed_value);

        if (include_encapsulation) {
            current_alignment += encapsulation_size;
        }
        return current_alignment - initial_alignment;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind 
    NumericObservedValuePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool 
    NumericObservedValuePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const NumericObservedValue *sample, 
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

            if (!ice::MetricObservedValuePlugin_serialize_key(endpoint_data, 
            (const ice::MetricObservedValue*)sample, stream, RTI_FALSE, 
            encapsulation_id,RTI_TRUE, endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

        }

        if(serialize_encapsulation) {
            RTICdrStream_restoreAlignment(stream,position);
        }

        return RTI_TRUE;
    }

    RTIBool NumericObservedValuePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample, 
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

                if (!ice::MetricObservedValuePlugin_deserialize_key_sample(endpoint_data,
                (ice::MetricObservedValue*)sample,stream,RTI_FALSE,RTI_TRUE,endpoint_plugin_qos)) {
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

    RTIBool NumericObservedValuePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        if (drop_sample) {} /* To avoid warnings */
        stream->_xTypesState.unassignable = RTI_FALSE;
        result= ice::NumericObservedValuePlugin_deserialize_key_sample(
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
    NumericObservedValuePlugin_get_serialized_key_max_size_ex(
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

        current_alignment += ice::MetricObservedValuePlugin_get_serialized_key_max_size_ex(
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
    NumericObservedValuePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = NumericObservedValuePlugin_get_serialized_key_max_size_ex(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    NumericObservedValuePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos)
    {
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;

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

            if (!ice::MetricObservedValuePlugin_serialized_sample_to_key(endpoint_data,
            (ice::MetricObservedValue *)sample,
            stream, RTI_FALSE, RTI_TRUE,
            endpoint_plugin_qos)) {
                return RTI_FALSE;
            }

            if (!ice::NuObsValuePlugin_skip(
                endpoint_data,
                stream, 
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
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
    NumericObservedValuePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValueKeyHolder *dst, 
        const NumericObservedValue *src)
    {

        if (!ice::MetricObservedValuePlugin_instance_to_key(endpoint_data,(ice::MetricObservedValue *)dst,(const ice::MetricObservedValue*)src)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    RTIBool 
    NumericObservedValuePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        NumericObservedValue *dst, const
        NumericObservedValueKeyHolder *src)
    {

        if (!ice::MetricObservedValuePlugin_key_to_instance(endpoint_data,(ice::MetricObservedValue*)dst,(const ice::MetricObservedValue*)src)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    RTIBool 
    NumericObservedValuePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const NumericObservedValue *instance)
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

        if (!ice::NumericObservedValuePlugin_serialize_key(
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

            size = (int)ice::NumericObservedValuePlugin_get_serialized_sample_size(
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
            if (!ice::NumericObservedValuePlugin_serialize_key(
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
    NumericObservedValuePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos) 
    {   
        char * position = NULL;

        RTIBool done = RTI_FALSE;
        RTIBool error = RTI_FALSE;
        NumericObservedValue * sample=NULL;

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

        sample = (NumericObservedValue *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (!ice::MetricObservedValuePlugin_serialized_sample_to_key(endpoint_data,
        (ice::MetricObservedValue *)sample,
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

        if (!ice::NumericObservedValuePlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */
    struct PRESTypePlugin *NumericObservedValuePlugin_new(void) 
    { 
        struct PRESTypePlugin *plugin = NULL;
        const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

        RTIOsapiHeap_allocateStructure(
            &plugin, struct PRESTypePlugin);

        if (plugin == NULL) {
            return NULL;
        }

        plugin->version = PLUGIN_VERSION;

        /* set up parent's function pointers */
        plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ice::NumericObservedValuePlugin_on_participant_attached;
        plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ice::NumericObservedValuePlugin_on_participant_detached;
        plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ice::NumericObservedValuePlugin_on_endpoint_attached;
        plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ice::NumericObservedValuePlugin_on_endpoint_detached;

        plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ice::NumericObservedValuePlugin_copy_sample;
        plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        NumericObservedValuePlugin_create_sample;
        plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        NumericObservedValuePlugin_destroy_sample;
        plugin->finalizeOptionalMembersFnc =
        (PRESTypePluginFinalizeOptionalMembersFunction)
        NumericObservedValue_finalize_optional_members;

        plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        ice::NumericObservedValuePlugin_serialize;
        plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        ice::NumericObservedValuePlugin_deserialize;
        plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ice::NumericObservedValuePlugin_get_serialized_sample_max_size;
        plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        ice::NumericObservedValuePlugin_get_serialized_sample_min_size;

        plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        NumericObservedValuePlugin_get_sample;
        plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        NumericObservedValuePlugin_return_sample;

        plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ice::NumericObservedValuePlugin_get_key_kind;

        plugin->getSerializedKeyMaxSizeFnc =   
        (PRESTypePluginGetSerializedKeyMaxSizeFunction)
        ice::NumericObservedValuePlugin_get_serialized_key_max_size;
        plugin->serializeKeyFnc =
        (PRESTypePluginSerializeKeyFunction)
        ice::NumericObservedValuePlugin_serialize_key;
        plugin->deserializeKeyFnc =
        (PRESTypePluginDeserializeKeyFunction)
        ice::NumericObservedValuePlugin_deserialize_key;
        plugin->deserializeKeySampleFnc =
        (PRESTypePluginDeserializeKeySampleFunction)
        ice::NumericObservedValuePlugin_deserialize_key_sample;

        plugin-> instanceToKeyHashFnc = 
        (PRESTypePluginInstanceToKeyHashFunction)
        ice::NumericObservedValuePlugin_instance_to_keyhash;
        plugin->serializedSampleToKeyHashFnc = 
        (PRESTypePluginSerializedSampleToKeyHashFunction)
        ice::NumericObservedValuePlugin_serialized_sample_to_keyhash;

        plugin->getKeyFnc =
        (PRESTypePluginGetKeyFunction)
        NumericObservedValuePlugin_get_key;
        plugin->returnKeyFnc =
        (PRESTypePluginReturnKeyFunction)
        NumericObservedValuePlugin_return_key;

        plugin->instanceToKeyFnc =
        (PRESTypePluginInstanceToKeyFunction)
        ice::NumericObservedValuePlugin_instance_to_key;
        plugin->keyToInstanceFnc =
        (PRESTypePluginKeyToInstanceFunction)
        ice::NumericObservedValuePlugin_key_to_instance;
        plugin->serializedKeyToKeyHashFnc = NULL; /* Not supported yet */
        plugin->typeCode =  (struct RTICdrTypeCode *)ice::NumericObservedValue_get_typecode();

        plugin->languageKind = PRES_TYPEPLUGIN_CPP_LANG;

        /* Serialized buffer */
        plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        NumericObservedValuePlugin_get_buffer;
        plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        NumericObservedValuePlugin_return_buffer;
        plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        ice::NumericObservedValuePlugin_get_serialized_sample_size;

        plugin->endpointTypeName = NumericObservedValueTYPENAME;

        return plugin;
    }

    void
    NumericObservedValuePlugin_delete(struct PRESTypePlugin *plugin)
    {
        RTIOsapiHeap_freeStructure(plugin);
    } 
} /* namespace ice  */
#undef RTI_CDR_CURRENT_SUBMODULE 
