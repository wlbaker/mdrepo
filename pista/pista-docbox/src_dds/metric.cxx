

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from metric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "metric.h"

#include <new>

namespace ice {

    /* ========================================================================= */

    DDS_TypeCode* MetricSourceList_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricSourceList_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

        static DDS_TypeCode MetricSourceList_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MetricSourceList", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MetricSourceList */

        if (is_initialized) {
            return &MetricSourceList_g_tc;
        }

        MetricSourceList_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        MetricSourceList_g_tc._data._typeCode =  (RTICdrTypeCode *)& MetricSourceList_g_tc_sequence;

        is_initialized = RTI_TRUE;

        return &MetricSourceList_g_tc;
    }

    RTIBool MetricSourceList_initialize(
        MetricSourceList* sample) {
        return ice::MetricSourceList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricSourceList_initialize_ex(
        MetricSourceList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricSourceList_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricSourceList_initialize_w_params(
        MetricSourceList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        void* buffer = NULL;
        if (buffer) {} /* To avoid warnings */

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory) {
            ice::OIDTypeSeq_initialize(sample );
            ice::OIDTypeSeq_set_element_allocation_params(sample ,allocParams);
            ice::OIDTypeSeq_set_absolute_maximum(sample , (100));
            if (!ice::OIDTypeSeq_set_maximum(sample, (100))) {
                return RTI_FALSE;
            }
        } else { 
            ice::OIDTypeSeq_set_length(sample, 0);
        }
        return RTI_TRUE;
    }

    void MetricSourceList_finalize(
        MetricSourceList* sample)
    {

        ice::MetricSourceList_finalize_ex(sample,RTI_TRUE);
    }

    void MetricSourceList_finalize_ex(
        MetricSourceList* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricSourceList_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricSourceList_finalize_w_params(
        MetricSourceList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDTypeSeq_set_element_deallocation_params(
            sample,deallocParams);
        ice::OIDTypeSeq_finalize(sample);

    }

    void MetricSourceList_finalize_optional_members(
        MetricSourceList* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        {
            DDS_UnsignedLong i, length;
            length = ice::OIDTypeSeq_get_length(
                sample);

            for (i = 0; i < length; i++) {
                ice::OIDType_finalize_optional_members(
                    ice::OIDTypeSeq_get_reference(
                        sample, i), deallocParams->delete_pointers);
            }
        }  

    }

    RTIBool MetricSourceList_copy(
        MetricSourceList* dst,
        const MetricSourceList* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDTypeSeq_copy(dst ,
            src )) {
                return RTI_FALSE;
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricSourceList' sequence class.
    */
    #define T MetricSourceList
    #define TSeq MetricSourceListSeq

    #define T_initialize_w_params ice::MetricSourceList_initialize_w_params

    #define T_finalize_w_params   ice::MetricSourceList_finalize_w_params
    #define T_copy       ice::MetricSourceList_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* SiteList_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode SiteList_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

        static DDS_TypeCode SiteList_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::SiteList", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  SiteList */

        if (is_initialized) {
            return &SiteList_g_tc;
        }

        SiteList_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        SiteList_g_tc._data._typeCode =  (RTICdrTypeCode *)& SiteList_g_tc_sequence;

        is_initialized = RTI_TRUE;

        return &SiteList_g_tc;
    }

    RTIBool SiteList_initialize(
        SiteList* sample) {
        return ice::SiteList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool SiteList_initialize_ex(
        SiteList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::SiteList_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool SiteList_initialize_w_params(
        SiteList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        void* buffer = NULL;
        if (buffer) {} /* To avoid warnings */

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory) {
            ice::OIDTypeSeq_initialize(sample );
            ice::OIDTypeSeq_set_element_allocation_params(sample ,allocParams);
            ice::OIDTypeSeq_set_absolute_maximum(sample , (100));
            if (!ice::OIDTypeSeq_set_maximum(sample, (100))) {
                return RTI_FALSE;
            }
        } else { 
            ice::OIDTypeSeq_set_length(sample, 0);
        }
        return RTI_TRUE;
    }

    void SiteList_finalize(
        SiteList* sample)
    {

        ice::SiteList_finalize_ex(sample,RTI_TRUE);
    }

    void SiteList_finalize_ex(
        SiteList* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::SiteList_finalize_w_params(
            sample,&deallocParams);
    }

    void SiteList_finalize_w_params(
        SiteList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDTypeSeq_set_element_deallocation_params(
            sample,deallocParams);
        ice::OIDTypeSeq_finalize(sample);

    }

    void SiteList_finalize_optional_members(
        SiteList* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        {
            DDS_UnsignedLong i, length;
            length = ice::OIDTypeSeq_get_length(
                sample);

            for (i = 0; i < length; i++) {
                ice::OIDType_finalize_optional_members(
                    ice::OIDTypeSeq_get_reference(
                        sample, i), deallocParams->delete_pointers);
            }
        }  

    }

    RTIBool SiteList_copy(
        SiteList* dst,
        const SiteList* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDTypeSeq_copy(dst ,
            src )) {
                return RTI_FALSE;
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'SiteList' sequence class.
    */
    #define T SiteList
    #define TSeq SiteListSeq

    #define T_initialize_w_params ice::SiteList_initialize_w_params

    #define T_finalize_w_params   ice::SiteList_finalize_w_params
    #define T_copy       ice::SiteList_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* MetricStatus_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricStatus_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MetricStatus", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MetricStatus */

        if (is_initialized) {
            return &MetricStatus_g_tc;
        }

        MetricStatus_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricStatus_g_tc;
    }

    RTIBool MetricStatus_initialize(
        MetricStatus* sample) {
        return ice::MetricStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricStatus_initialize_ex(
        MetricStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricStatus_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricStatus_initialize_w_params(
        MetricStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::BITS16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricStatus_finalize(
        MetricStatus* sample)
    {

        ice::MetricStatus_finalize_ex(sample,RTI_TRUE);
    }

    void MetricStatus_finalize_ex(
        MetricStatus* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricStatus_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricStatus_finalize_w_params(
        MetricStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void MetricStatus_finalize_optional_members(
        MetricStatus* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::BITS16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool MetricStatus_copy(
        MetricStatus* dst,
        const MetricStatus* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::BITS16_copy(
                dst,(const ice::BITS16*)src)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricStatus' sequence class.
    */
    #define T MetricStatus
    #define TSeq MetricStatusSeq

    #define T_initialize_w_params ice::MetricStatus_initialize_w_params

    #define T_finalize_w_params   ice::MetricStatus_finalize_w_params
    #define T_copy       ice::MetricStatus_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricStatusBitsTYPENAME = "ice::MetricStatusBits";

    DDS_TypeCode* MetricStatusBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricStatusBits_g_tc_members[5]=
        {

            {
                (char *)"metric_off",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                metric_off, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_not_ready",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                metric_not_ready, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_standby",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                metric_standby, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_transduc_discon",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                metric_transduc_discon, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_hw_discon",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                metric_hw_discon, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricStatusBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricStatusBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                5, /* Number of members */
                MetricStatusBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricStatusBits*/

        if (is_initialized) {
            return &MetricStatusBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricStatusBits_g_tc;
    }

    RTIBool MetricStatusBits_initialize(
        MetricStatusBits* sample) {
        *sample = metric_off;
        return RTI_TRUE;
    }

    RTIBool MetricStatusBits_initialize_ex(
        MetricStatusBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricStatusBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricStatusBits_initialize_w_params(
        MetricStatusBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = metric_off;
        return RTI_TRUE;
    }

    void MetricStatusBits_finalize(
        MetricStatusBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricStatusBits_finalize_ex(
        MetricStatusBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricStatusBits_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricStatusBits_finalize_w_params(
        MetricStatusBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricStatusBits_finalize_optional_members(
        MetricStatusBits* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricStatusBits_copy(
        MetricStatusBits* dst,
        const MetricStatusBits* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricStatusBits' sequence class.
    */
    #define T MetricStatusBits
    #define TSeq MetricStatusBitsSeq

    #define T_initialize_w_params ice::MetricStatusBits_initialize_w_params

    #define T_finalize_w_params   ice::MetricStatusBits_finalize_w_params
    #define T_copy       ice::MetricStatusBits_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* MetricAccess_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricAccess_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MetricAccess", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MetricAccess */

        if (is_initialized) {
            return &MetricAccess_g_tc;
        }

        MetricAccess_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricAccess_g_tc;
    }

    RTIBool MetricAccess_initialize(
        MetricAccess* sample) {
        return ice::MetricAccess_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricAccess_initialize_ex(
        MetricAccess* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricAccess_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricAccess_initialize_w_params(
        MetricAccess* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::BITS16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricAccess_finalize(
        MetricAccess* sample)
    {

        ice::MetricAccess_finalize_ex(sample,RTI_TRUE);
    }

    void MetricAccess_finalize_ex(
        MetricAccess* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricAccess_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricAccess_finalize_w_params(
        MetricAccess* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void MetricAccess_finalize_optional_members(
        MetricAccess* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::BITS16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool MetricAccess_copy(
        MetricAccess* dst,
        const MetricAccess* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::BITS16_copy(
                dst,(const ice::BITS16*)src)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricAccess' sequence class.
    */
    #define T MetricAccess
    #define TSeq MetricAccessSeq

    #define T_initialize_w_params ice::MetricAccess_initialize_w_params

    #define T_finalize_w_params   ice::MetricAccess_finalize_w_params
    #define T_copy       ice::MetricAccess_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricAccessBitsTYPENAME = "ice::MetricAccessBits";

    DDS_TypeCode* MetricAccessBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricAccessBits_g_tc_members[12]=
        {

            {
                (char *)"avail_intermittent",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                avail_intermittent, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"upd_periodic",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                upd_periodic, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"upd_episodic",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                upd_episodic, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"msmt_noncontinuous",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                msmt_noncontinuous, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acc_evrep",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acc_evrep, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acc_get",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acc_get, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acc_scan",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acc_scan, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"gen_opt_sync",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                gen_opt_sync, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"sc_opt_normal",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                sc_opt_normal, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"sc_opt_extensive",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                sc_opt_extensive, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"sc_opt_long_pd_avail",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                sc_opt_long_pd_avail, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"sc_opt_confirm",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                sc_opt_confirm, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricAccessBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricAccessBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                12, /* Number of members */
                MetricAccessBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricAccessBits*/

        if (is_initialized) {
            return &MetricAccessBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricAccessBits_g_tc;
    }

    RTIBool MetricAccessBits_initialize(
        MetricAccessBits* sample) {
        *sample = avail_intermittent;
        return RTI_TRUE;
    }

    RTIBool MetricAccessBits_initialize_ex(
        MetricAccessBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricAccessBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricAccessBits_initialize_w_params(
        MetricAccessBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = avail_intermittent;
        return RTI_TRUE;
    }

    void MetricAccessBits_finalize(
        MetricAccessBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricAccessBits_finalize_ex(
        MetricAccessBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricAccessBits_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricAccessBits_finalize_w_params(
        MetricAccessBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricAccessBits_finalize_optional_members(
        MetricAccessBits* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricAccessBits_copy(
        MetricAccessBits* dst,
        const MetricAccessBits* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricAccessBits' sequence class.
    */
    #define T MetricAccessBits
    #define TSeq MetricAccessBitsSeq

    #define T_initialize_w_params ice::MetricAccessBits_initialize_w_params

    #define T_finalize_w_params   ice::MetricAccessBits_finalize_w_params
    #define T_copy       ice::MetricAccessBits_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* MetricRelevance_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricRelevance_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MetricRelevance", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MetricRelevance */

        if (is_initialized) {
            return &MetricRelevance_g_tc;
        }

        MetricRelevance_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricRelevance_g_tc;
    }

    RTIBool MetricRelevance_initialize(
        MetricRelevance* sample) {
        return ice::MetricRelevance_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricRelevance_initialize_ex(
        MetricRelevance* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricRelevance_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricRelevance_initialize_w_params(
        MetricRelevance* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::BITS16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricRelevance_finalize(
        MetricRelevance* sample)
    {

        ice::MetricRelevance_finalize_ex(sample,RTI_TRUE);
    }

    void MetricRelevance_finalize_ex(
        MetricRelevance* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricRelevance_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricRelevance_finalize_w_params(
        MetricRelevance* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void MetricRelevance_finalize_optional_members(
        MetricRelevance* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::BITS16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool MetricRelevance_copy(
        MetricRelevance* dst,
        const MetricRelevance* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::BITS16_copy(
                dst,(const ice::BITS16*)src)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricRelevance' sequence class.
    */
    #define T MetricRelevance
    #define TSeq MetricRelevanceSeq

    #define T_initialize_w_params ice::MetricRelevance_initialize_w_params

    #define T_finalize_w_params   ice::MetricRelevance_finalize_w_params
    #define T_copy       ice::MetricRelevance_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricRelevanceBitsTYPENAME = "ice::MetricRelevanceBits";

    DDS_TypeCode* MetricRelevanceBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricRelevanceBits_g_tc_members[8]=
        {

            {
                (char *)"rv_unspec",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_unspec, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_internal",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_internal, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_store_only",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_store_only, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_no_recording",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_no_recording, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_phys_ev_ind",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_phys_ev_ind, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_btb_metric",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_btb_metric, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_app_specific",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_app_specific, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"rv_service",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                rv_service, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricRelevanceBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricRelevanceBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                8, /* Number of members */
                MetricRelevanceBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricRelevanceBits*/

        if (is_initialized) {
            return &MetricRelevanceBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricRelevanceBits_g_tc;
    }

    RTIBool MetricRelevanceBits_initialize(
        MetricRelevanceBits* sample) {
        *sample = rv_unspec;
        return RTI_TRUE;
    }

    RTIBool MetricRelevanceBits_initialize_ex(
        MetricRelevanceBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricRelevanceBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricRelevanceBits_initialize_w_params(
        MetricRelevanceBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = rv_unspec;
        return RTI_TRUE;
    }

    void MetricRelevanceBits_finalize(
        MetricRelevanceBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricRelevanceBits_finalize_ex(
        MetricRelevanceBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricRelevanceBits_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricRelevanceBits_finalize_w_params(
        MetricRelevanceBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricRelevanceBits_finalize_optional_members(
        MetricRelevanceBits* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricRelevanceBits_copy(
        MetricRelevanceBits* dst,
        const MetricRelevanceBits* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricRelevanceBits' sequence class.
    */
    #define T MetricRelevanceBits
    #define TSeq MetricRelevanceBitsSeq

    #define T_initialize_w_params ice::MetricRelevanceBits_initialize_w_params

    #define T_finalize_w_params   ice::MetricRelevanceBits_finalize_w_params
    #define T_copy       ice::MetricRelevanceBits_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricCategoryTYPENAME = "ice::MetricCategory";

    DDS_TypeCode* MetricCategory_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricCategory_g_tc_members[7]=
        {

            {
                (char *)"mcat_unspec",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                mcat_unspec, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"auto_measurement",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                auto_measurement, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"manual_measurement",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                manual_measurement, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"auto_setting",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                auto_setting, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"manual_setting",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                manual_setting, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"auto_calculation",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                auto_calculation, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"manual_calculation",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                manual_calculation, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricCategory_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricCategory", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                7, /* Number of members */
                MetricCategory_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricCategory*/

        if (is_initialized) {
            return &MetricCategory_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricCategory_g_tc;
    }

    RTIBool MetricCategory_initialize(
        MetricCategory* sample) {
        *sample = mcat_unspec;
        return RTI_TRUE;
    }

    RTIBool MetricCategory_initialize_ex(
        MetricCategory* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricCategory_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricCategory_initialize_w_params(
        MetricCategory* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = mcat_unspec;
        return RTI_TRUE;
    }

    void MetricCategory_finalize(
        MetricCategory* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricCategory_finalize_ex(
        MetricCategory* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricCategory_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricCategory_finalize_w_params(
        MetricCategory* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricCategory_finalize_optional_members(
        MetricCategory* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricCategory_copy(
        MetricCategory* dst,
        const MetricCategory* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricCategory' sequence class.
    */
    #define T MetricCategory
    #define TSeq MetricCategorySeq

    #define T_initialize_w_params ice::MetricCategory_initialize_w_params

    #define T_finalize_w_params   ice::MetricCategory_finalize_w_params
    #define T_copy       ice::MetricCategory_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricSpecTYPENAME = "ice::MetricSpec";

    DDS_TypeCode* MetricSpec_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricSpec_g_tc_members[4]=
        {

            {
                (char *)"update_period",/* Member name */
                {
                    0,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"category",/* Member name */
                {
                    1,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"access",/* Member name */
                {
                    2,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"relevance",/* Member name */
                {
                    3,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricSpec_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricSpec", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                MetricSpec_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for MetricSpec*/

        if (is_initialized) {
            return &MetricSpec_g_tc;
        }

        MetricSpec_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::Duration_get_typecode();

        MetricSpec_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::MetricCategory_get_typecode();

        MetricSpec_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::MetricAccess_get_typecode();

        MetricSpec_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::MetricRelevance_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricSpec_g_tc;
    }

    RTIBool MetricSpec_initialize(
        MetricSpec* sample) {
        return ice::MetricSpec_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricSpec_initialize_ex(
        MetricSpec* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricSpec_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricSpec_initialize_w_params(
        MetricSpec* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::Duration_initialize_w_params(&sample->update_period,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricCategory_initialize_w_params(&sample->category,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricAccess_initialize_w_params(&sample->access,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricRelevance_initialize_w_params(&sample->relevance,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricSpec_finalize(
        MetricSpec* sample)
    {

        ice::MetricSpec_finalize_ex(sample,RTI_TRUE);
    }

    void MetricSpec_finalize_ex(
        MetricSpec* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricSpec_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricSpec_finalize_w_params(
        MetricSpec* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::Duration_finalize_w_params(&sample->update_period,deallocParams);

        ice::MetricCategory_finalize_w_params(&sample->category,deallocParams);

        ice::MetricAccess_finalize_w_params(&sample->access,deallocParams);

        ice::MetricRelevance_finalize_w_params(&sample->relevance,deallocParams);

    }

    void MetricSpec_finalize_optional_members(
        MetricSpec* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::Duration_finalize_optional_members(&sample->update_period, deallocParams->delete_pointers);
        ice::MetricCategory_finalize_optional_members(&sample->category, deallocParams->delete_pointers);
        ice::MetricAccess_finalize_optional_members(&sample->access, deallocParams->delete_pointers);
        ice::MetricRelevance_finalize_optional_members(&sample->relevance, deallocParams->delete_pointers);
    }

    RTIBool MetricSpec_copy(
        MetricSpec* dst,
        const MetricSpec* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::Duration_copy(
                &dst->update_period,(const ice::Duration*)&src->update_period)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricCategory_copy(
                &dst->category,(const ice::MetricCategory*)&src->category)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricAccess_copy(
                &dst->access,(const ice::MetricAccess*)&src->access)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricRelevance_copy(
                &dst->relevance,(const ice::MetricRelevance*)&src->relevance)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricSpec' sequence class.
    */
    #define T MetricSpec
    #define TSeq MetricSpecSeq

    #define T_initialize_w_params ice::MetricSpec_initialize_w_params

    #define T_finalize_w_params   ice::MetricSpec_finalize_w_params
    #define T_copy       ice::MetricSpec_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *VmoSourceEntryTYPENAME = "ice::VmoSourceEntry";

    DDS_TypeCode* VmoSourceEntry_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member VmoSourceEntry_g_tc_members[2]=
        {

            {
                (char *)"vmo_type",/* Member name */
                {
                    0,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"glb_handle",/* Member name */
                {
                    1,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode VmoSourceEntry_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::VmoSourceEntry", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                VmoSourceEntry_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for VmoSourceEntry*/

        if (is_initialized) {
            return &VmoSourceEntry_g_tc;
        }

        VmoSourceEntry_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        VmoSourceEntry_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::GLBHANDLE_get_typecode();

        is_initialized = RTI_TRUE;

        return &VmoSourceEntry_g_tc;
    }

    RTIBool VmoSourceEntry_initialize(
        VmoSourceEntry* sample) {
        return ice::VmoSourceEntry_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool VmoSourceEntry_initialize_ex(
        VmoSourceEntry* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::VmoSourceEntry_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool VmoSourceEntry_initialize_w_params(
        VmoSourceEntry* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_initialize_w_params(&sample->vmo_type,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::GLBHANDLE_initialize_w_params(&sample->glb_handle,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void VmoSourceEntry_finalize(
        VmoSourceEntry* sample)
    {

        ice::VmoSourceEntry_finalize_ex(sample,RTI_TRUE);
    }

    void VmoSourceEntry_finalize_ex(
        VmoSourceEntry* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::VmoSourceEntry_finalize_w_params(
            sample,&deallocParams);
    }

    void VmoSourceEntry_finalize_w_params(
        VmoSourceEntry* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDType_finalize_w_params(&sample->vmo_type,deallocParams);

        ice::GLBHANDLE_finalize_w_params(&sample->glb_handle,deallocParams);

    }

    void VmoSourceEntry_finalize_optional_members(
        VmoSourceEntry* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::OIDType_finalize_optional_members(&sample->vmo_type, deallocParams->delete_pointers);
        ice::GLBHANDLE_finalize_optional_members(&sample->glb_handle, deallocParams->delete_pointers);
    }

    RTIBool VmoSourceEntry_copy(
        VmoSourceEntry* dst,
        const VmoSourceEntry* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDType_copy(
                &dst->vmo_type,(const ice::OIDType*)&src->vmo_type)) {
                return RTI_FALSE;
            } 
            if (!ice::GLBHANDLE_copy(
                &dst->glb_handle,(const ice::GLBHANDLE*)&src->glb_handle)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'VmoSourceEntry' sequence class.
    */
    #define T VmoSourceEntry
    #define TSeq VmoSourceEntrySeq

    #define T_initialize_w_params ice::VmoSourceEntry_initialize_w_params

    #define T_finalize_w_params   ice::VmoSourceEntry_finalize_w_params
    #define T_copy       ice::VmoSourceEntry_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* VmoSourceList_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode VmoSourceList_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

        static DDS_TypeCode VmoSourceList_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::VmoSourceList", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  VmoSourceList */

        if (is_initialized) {
            return &VmoSourceList_g_tc;
        }

        VmoSourceList_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)ice::VmoSourceEntry_get_typecode();

        VmoSourceList_g_tc._data._typeCode =  (RTICdrTypeCode *)& VmoSourceList_g_tc_sequence;

        is_initialized = RTI_TRUE;

        return &VmoSourceList_g_tc;
    }

    RTIBool VmoSourceList_initialize(
        VmoSourceList* sample) {
        return ice::VmoSourceList_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool VmoSourceList_initialize_ex(
        VmoSourceList* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::VmoSourceList_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool VmoSourceList_initialize_w_params(
        VmoSourceList* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        void* buffer = NULL;
        if (buffer) {} /* To avoid warnings */

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory) {
            ice::VmoSourceEntrySeq_initialize(sample );
            ice::VmoSourceEntrySeq_set_element_allocation_params(sample ,allocParams);
            ice::VmoSourceEntrySeq_set_absolute_maximum(sample , (100));
            if (!ice::VmoSourceEntrySeq_set_maximum(sample, (100))) {
                return RTI_FALSE;
            }
        } else { 
            ice::VmoSourceEntrySeq_set_length(sample, 0);
        }
        return RTI_TRUE;
    }

    void VmoSourceList_finalize(
        VmoSourceList* sample)
    {

        ice::VmoSourceList_finalize_ex(sample,RTI_TRUE);
    }

    void VmoSourceList_finalize_ex(
        VmoSourceList* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::VmoSourceList_finalize_w_params(
            sample,&deallocParams);
    }

    void VmoSourceList_finalize_w_params(
        VmoSourceList* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::VmoSourceEntrySeq_set_element_deallocation_params(
            sample,deallocParams);
        ice::VmoSourceEntrySeq_finalize(sample);

    }

    void VmoSourceList_finalize_optional_members(
        VmoSourceList* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        {
            DDS_UnsignedLong i, length;
            length = ice::VmoSourceEntrySeq_get_length(
                sample);

            for (i = 0; i < length; i++) {
                ice::VmoSourceEntry_finalize_optional_members(
                    ice::VmoSourceEntrySeq_get_reference(
                        sample, i), deallocParams->delete_pointers);
            }
        }  

    }

    RTIBool VmoSourceList_copy(
        VmoSourceList* dst,
        const VmoSourceList* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::VmoSourceEntrySeq_copy(dst ,
            src )) {
                return RTI_FALSE;
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'VmoSourceList' sequence class.
    */
    #define T VmoSourceList
    #define TSeq VmoSourceListSeq

    #define T_initialize_w_params ice::VmoSourceList_initialize_w_params

    #define T_finalize_w_params   ice::VmoSourceList_finalize_w_params
    #define T_copy       ice::VmoSourceList_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* MeasurementStatus_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MeasurementStatus_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MeasurementStatus", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MeasurementStatus */

        if (is_initialized) {
            return &MeasurementStatus_g_tc;
        }

        MeasurementStatus_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &MeasurementStatus_g_tc;
    }

    RTIBool MeasurementStatus_initialize(
        MeasurementStatus* sample) {
        return ice::MeasurementStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MeasurementStatus_initialize_ex(
        MeasurementStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MeasurementStatus_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MeasurementStatus_initialize_w_params(
        MeasurementStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::BITS16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MeasurementStatus_finalize(
        MeasurementStatus* sample)
    {

        ice::MeasurementStatus_finalize_ex(sample,RTI_TRUE);
    }

    void MeasurementStatus_finalize_ex(
        MeasurementStatus* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MeasurementStatus_finalize_w_params(
            sample,&deallocParams);
    }

    void MeasurementStatus_finalize_w_params(
        MeasurementStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void MeasurementStatus_finalize_optional_members(
        MeasurementStatus* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::BITS16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool MeasurementStatus_copy(
        MeasurementStatus* dst,
        const MeasurementStatus* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::BITS16_copy(
                dst,(const ice::BITS16*)src)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MeasurementStatus' sequence class.
    */
    #define T MeasurementStatus
    #define TSeq MeasurementStatusSeq

    #define T_initialize_w_params ice::MeasurementStatus_initialize_w_params

    #define T_finalize_w_params   ice::MeasurementStatus_finalize_w_params
    #define T_copy       ice::MeasurementStatus_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MeasurementStatusBitsTYPENAME = "ice::MeasurementStatusBits";

    DDS_TypeCode* MeasurementStatusBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MeasurementStatusBits_g_tc_members[11]=
        {

            {
                (char *)"invalid",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                invalid, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"questionable",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                questionable, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"not_available",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                not_available, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"calibration_ongoing",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                calibration_ongoing, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"test_data",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                test_data, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"demo_data",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                demo_data, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"validated_data",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                validated_data, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"early_indication",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                early_indication, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"msmt_ongoing",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                msmt_ongoing, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"msmt_state_in_alarm",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                msmt_state_in_alarm, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"msmt_state_al_inhibited",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                msmt_state_al_inhibited, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MeasurementStatusBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MeasurementStatusBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                11, /* Number of members */
                MeasurementStatusBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MeasurementStatusBits*/

        if (is_initialized) {
            return &MeasurementStatusBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MeasurementStatusBits_g_tc;
    }

    RTIBool MeasurementStatusBits_initialize(
        MeasurementStatusBits* sample) {
        *sample = invalid;
        return RTI_TRUE;
    }

    RTIBool MeasurementStatusBits_initialize_ex(
        MeasurementStatusBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MeasurementStatusBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MeasurementStatusBits_initialize_w_params(
        MeasurementStatusBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = invalid;
        return RTI_TRUE;
    }

    void MeasurementStatusBits_finalize(
        MeasurementStatusBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MeasurementStatusBits_finalize_ex(
        MeasurementStatusBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MeasurementStatusBits_finalize_w_params(
            sample,&deallocParams);
    }

    void MeasurementStatusBits_finalize_w_params(
        MeasurementStatusBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MeasurementStatusBits_finalize_optional_members(
        MeasurementStatusBits* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MeasurementStatusBits_copy(
        MeasurementStatusBits* dst,
        const MeasurementStatusBits* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MeasurementStatusBits' sequence class.
    */
    #define T MeasurementStatusBits
    #define TSeq MeasurementStatusBitsSeq

    #define T_initialize_w_params ice::MeasurementStatusBits_initialize_w_params

    #define T_finalize_w_params   ice::MeasurementStatusBits_finalize_w_params
    #define T_copy       ice::MeasurementStatusBits_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricCalStateTYPENAME = "ice::MetricCalState";

    DDS_TypeCode* MetricCalState_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricCalState_g_tc_members[3]=
        {

            {
                (char *)"not_calibrated",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                not_calibrated, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_required",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                cal_required, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"calibrated",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                calibrated, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricCalState_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricCalState", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                3, /* Number of members */
                MetricCalState_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricCalState*/

        if (is_initialized) {
            return &MetricCalState_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricCalState_g_tc;
    }

    RTIBool MetricCalState_initialize(
        MetricCalState* sample) {
        *sample = not_calibrated;
        return RTI_TRUE;
    }

    RTIBool MetricCalState_initialize_ex(
        MetricCalState* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricCalState_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricCalState_initialize_w_params(
        MetricCalState* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = not_calibrated;
        return RTI_TRUE;
    }

    void MetricCalState_finalize(
        MetricCalState* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricCalState_finalize_ex(
        MetricCalState* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricCalState_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricCalState_finalize_w_params(
        MetricCalState* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricCalState_finalize_optional_members(
        MetricCalState* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricCalState_copy(
        MetricCalState* dst,
        const MetricCalState* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricCalState' sequence class.
    */
    #define T MetricCalState
    #define TSeq MetricCalStateSeq

    #define T_initialize_w_params ice::MetricCalState_initialize_w_params

    #define T_finalize_w_params   ice::MetricCalState_finalize_w_params
    #define T_copy       ice::MetricCalState_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricCalTypeTYPENAME = "ice::MetricCalType";

    DDS_TypeCode* MetricCalType_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricCalType_g_tc_members[4]=
        {

            {
                (char *)"cal_unspec",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                cal_unspec, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_offset",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                cal_offset, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_gain",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                cal_gain, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_two_point",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                cal_two_point, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricCalType_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricCalType", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                MetricCalType_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for MetricCalType*/

        if (is_initialized) {
            return &MetricCalType_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &MetricCalType_g_tc;
    }

    RTIBool MetricCalType_initialize(
        MetricCalType* sample) {
        *sample = cal_unspec;
        return RTI_TRUE;
    }

    RTIBool MetricCalType_initialize_ex(
        MetricCalType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricCalType_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricCalType_initialize_w_params(
        MetricCalType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = cal_unspec;
        return RTI_TRUE;
    }

    void MetricCalType_finalize(
        MetricCalType* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void MetricCalType_finalize_ex(
        MetricCalType* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricCalType_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricCalType_finalize_w_params(
        MetricCalType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void MetricCalType_finalize_optional_members(
        MetricCalType* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool MetricCalType_copy(
        MetricCalType* dst,
        const MetricCalType* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricCalType' sequence class.
    */
    #define T MetricCalType
    #define TSeq MetricCalTypeSeq

    #define T_initialize_w_params ice::MetricCalType_initialize_w_params

    #define T_finalize_w_params   ice::MetricCalType_finalize_w_params
    #define T_copy       ice::MetricCalType_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricCalEntryTYPENAME = "ice::MetricCalEntry";

    DDS_TypeCode* MetricCalEntry_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricCalEntry_g_tc_members[3]=
        {

            {
                (char *)"cal_type",/* Member name */
                {
                    0,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_state",/* Member name */
                {
                    1,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"cal_time",/* Member name */
                {
                    2,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricCalEntry_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricCalEntry", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                3, /* Number of members */
                MetricCalEntry_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for MetricCalEntry*/

        if (is_initialized) {
            return &MetricCalEntry_g_tc;
        }

        MetricCalEntry_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::MetricCalType_get_typecode();

        MetricCalEntry_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::MetricCalState_get_typecode();

        MetricCalEntry_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::Timespec_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricCalEntry_g_tc;
    }

    RTIBool MetricCalEntry_initialize(
        MetricCalEntry* sample) {
        return ice::MetricCalEntry_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricCalEntry_initialize_ex(
        MetricCalEntry* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricCalEntry_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricCalEntry_initialize_w_params(
        MetricCalEntry* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::MetricCalType_initialize_w_params(&sample->cal_type,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricCalState_initialize_w_params(&sample->cal_state,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::Timespec_initialize_w_params(&sample->cal_time,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricCalEntry_finalize(
        MetricCalEntry* sample)
    {

        ice::MetricCalEntry_finalize_ex(sample,RTI_TRUE);
    }

    void MetricCalEntry_finalize_ex(
        MetricCalEntry* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricCalEntry_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricCalEntry_finalize_w_params(
        MetricCalEntry* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::MetricCalType_finalize_w_params(&sample->cal_type,deallocParams);

        ice::MetricCalState_finalize_w_params(&sample->cal_state,deallocParams);

        ice::Timespec_finalize_w_params(&sample->cal_time,deallocParams);

    }

    void MetricCalEntry_finalize_optional_members(
        MetricCalEntry* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::MetricCalType_finalize_optional_members(&sample->cal_type, deallocParams->delete_pointers);
        ice::MetricCalState_finalize_optional_members(&sample->cal_state, deallocParams->delete_pointers);
        ice::Timespec_finalize_optional_members(&sample->cal_time, deallocParams->delete_pointers);
    }

    RTIBool MetricCalEntry_copy(
        MetricCalEntry* dst,
        const MetricCalEntry* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::MetricCalType_copy(
                &dst->cal_type,(const ice::MetricCalType*)&src->cal_type)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricCalState_copy(
                &dst->cal_state,(const ice::MetricCalState*)&src->cal_state)) {
                return RTI_FALSE;
            } 
            if (!ice::Timespec_copy(
                &dst->cal_time,(const ice::Timespec*)&src->cal_time)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricCalEntry' sequence class.
    */
    #define T MetricCalEntry
    #define TSeq MetricCalEntrySeq

    #define T_initialize_w_params ice::MetricCalEntry_initialize_w_params

    #define T_finalize_w_params   ice::MetricCalEntry_finalize_w_params
    #define T_copy       ice::MetricCalEntry_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */

    DDS_TypeCode* MetricCalibration_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricCalibration_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

        static DDS_TypeCode MetricCalibration_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MetricCalibration", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MetricCalibration */

        if (is_initialized) {
            return &MetricCalibration_g_tc;
        }

        MetricCalibration_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)ice::MetricCalEntry_get_typecode();

        MetricCalibration_g_tc._data._typeCode =  (RTICdrTypeCode *)& MetricCalibration_g_tc_sequence;

        is_initialized = RTI_TRUE;

        return &MetricCalibration_g_tc;
    }

    RTIBool MetricCalibration_initialize(
        MetricCalibration* sample) {
        return ice::MetricCalibration_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricCalibration_initialize_ex(
        MetricCalibration* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricCalibration_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricCalibration_initialize_w_params(
        MetricCalibration* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        void* buffer = NULL;
        if (buffer) {} /* To avoid warnings */

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory) {
            ice::MetricCalEntrySeq_initialize(sample );
            ice::MetricCalEntrySeq_set_element_allocation_params(sample ,allocParams);
            ice::MetricCalEntrySeq_set_absolute_maximum(sample , (100));
            if (!ice::MetricCalEntrySeq_set_maximum(sample, (100))) {
                return RTI_FALSE;
            }
        } else { 
            ice::MetricCalEntrySeq_set_length(sample, 0);
        }
        return RTI_TRUE;
    }

    void MetricCalibration_finalize(
        MetricCalibration* sample)
    {

        ice::MetricCalibration_finalize_ex(sample,RTI_TRUE);
    }

    void MetricCalibration_finalize_ex(
        MetricCalibration* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricCalibration_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricCalibration_finalize_w_params(
        MetricCalibration* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::MetricCalEntrySeq_set_element_deallocation_params(
            sample,deallocParams);
        ice::MetricCalEntrySeq_finalize(sample);

    }

    void MetricCalibration_finalize_optional_members(
        MetricCalibration* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        {
            DDS_UnsignedLong i, length;
            length = ice::MetricCalEntrySeq_get_length(
                sample);

            for (i = 0; i < length; i++) {
                ice::MetricCalEntry_finalize_optional_members(
                    ice::MetricCalEntrySeq_get_reference(
                        sample, i), deallocParams->delete_pointers);
            }
        }  

    }

    RTIBool MetricCalibration_copy(
        MetricCalibration* dst,
        const MetricCalibration* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::MetricCalEntrySeq_copy(dst ,
            src )) {
                return RTI_FALSE;
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricCalibration' sequence class.
    */
    #define T MetricCalibration
    #define TSeq MetricCalibrationSeq

    #define T_initialize_w_params ice::MetricCalibration_initialize_w_params

    #define T_finalize_w_params   ice::MetricCalibration_finalize_w_params
    #define T_copy       ice::MetricCalibration_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricMeasureTYPENAME = "ice::MetricMeasure";

    DDS_TypeCode* MetricMeasure_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricMeasure_g_tc_members[2]=
        {

            {
                (char *)"value",/* Member name */
                {
                    0,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"unit_code",/* Member name */
                {
                    1,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricMeasure_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricMeasure", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                MetricMeasure_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for MetricMeasure*/

        if (is_initialized) {
            return &MetricMeasure_g_tc;
        }

        MetricMeasure_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        MetricMeasure_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        is_initialized = RTI_TRUE;

        return &MetricMeasure_g_tc;
    }

    RTIBool MetricMeasure_initialize(
        MetricMeasure* sample) {
        return ice::MetricMeasure_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricMeasure_initialize_ex(
        MetricMeasure* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricMeasure_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricMeasure_initialize_w_params(
        MetricMeasure* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::FLOATType_initialize_w_params(&sample->value,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_initialize_w_params(&sample->unit_code,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MetricMeasure_finalize(
        MetricMeasure* sample)
    {

        ice::MetricMeasure_finalize_ex(sample,RTI_TRUE);
    }

    void MetricMeasure_finalize_ex(
        MetricMeasure* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricMeasure_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricMeasure_finalize_w_params(
        MetricMeasure* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::FLOATType_finalize_w_params(&sample->value,deallocParams);

        ice::OIDType_finalize_w_params(&sample->unit_code,deallocParams);

    }

    void MetricMeasure_finalize_optional_members(
        MetricMeasure* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::FLOATType_finalize_optional_members(&sample->value, deallocParams->delete_pointers);
        ice::OIDType_finalize_optional_members(&sample->unit_code, deallocParams->delete_pointers);
    }

    RTIBool MetricMeasure_copy(
        MetricMeasure* dst,
        const MetricMeasure* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::FLOATType_copy(
                &dst->value,(const ice::FLOATType*)&src->value)) {
                return RTI_FALSE;
            } 
            if (!ice::OIDType_copy(
                &dst->unit_code,(const ice::OIDType*)&src->unit_code)) {
                return RTI_FALSE;
            } 

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricMeasure' sequence class.
    */
    #define T MetricMeasure
    #define TSeq MetricMeasureSeq

    #define T_initialize_w_params ice::MetricMeasure_initialize_w_params

    #define T_finalize_w_params   ice::MetricMeasure_finalize_w_params
    #define T_copy       ice::MetricMeasure_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricContextTYPENAME = "ice::MetricContext";

    DDS_TypeCode* MetricContext_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MetricContext_g_tc_vmo_label_string_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode MetricContext_g_tc_unit_label_string_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode MetricContext_g_tc_metric_info_label_string_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode MetricContext_g_tc_substance_label_string_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode_Member MetricContext_g_tc_members[22]=
        {

            {
                (char *)"context_seq_number",/* Member name */
                {
                    5,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_specification",/* Member name */
                {
                    6,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"max_delay_time",/* Member name */
                {
                    7,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"vmo_label_string",/* Member name */
                {
                    8,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"vmo_source_list",/* Member name */
                {
                    9,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_source_list",/* Member name */
                {
                    10,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"unit_code",/* Member name */
                {
                    11,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"unit_label_string",/* Member name */
                {
                    12,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"msmt_site_list",/* Member name */
                {
                    13,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"body_site_list",/* Member name */
                {
                    14,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_status",/* Member name */
                {
                    15,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"measure_period",/* Member name */
                {
                    16,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"averaging_period",/* Member name */
                {
                    17,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"start_time",/* Member name */
                {
                    18,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"stop_time",/* Member name */
                {
                    19,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_calibration",/* Member name */
                {
                    20,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"color",/* Member name */
                {
                    21,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"measurement_status",/* Member name */
                {
                    22,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_id",/* Member name */
                {
                    23,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_info_label_string",/* Member name */
                {
                    24,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"substance",/* Member name */
                {
                    25,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"substance_label_string",/* Member name */
                {
                    26,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricContext_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricContext", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                22, /* Number of members */
                MetricContext_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for MetricContext*/

        if (is_initialized) {
            return &MetricContext_g_tc;
        }

        MetricContext_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        MetricContext_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::MetricSpec_get_typecode();

        MetricContext_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::Duration_get_typecode();

        MetricContext_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&MetricContext_g_tc_vmo_label_string_string;

        MetricContext_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)ice::VmoSourceList_get_typecode();

        MetricContext_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)ice::MetricSourceList_get_typecode();

        MetricContext_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        MetricContext_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&MetricContext_g_tc_unit_label_string_string;

        MetricContext_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)ice::SiteList_get_typecode();

        MetricContext_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)ice::SiteList_get_typecode();

        MetricContext_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)ice::MetricStatus_get_typecode();

        MetricContext_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)ice::MetricMeasure_get_typecode();

        MetricContext_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)ice::MetricMeasure_get_typecode();

        MetricContext_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)ice::Timespec_get_typecode();

        MetricContext_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)ice::Timespec_get_typecode();

        MetricContext_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)ice::MetricCalibration_get_typecode();

        MetricContext_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)ice::SimpleColor_get_typecode();

        MetricContext_g_tc_members[17]._representation._typeCode = (RTICdrTypeCode *)ice::MeasurementStatus_get_typecode();

        MetricContext_g_tc_members[18]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        MetricContext_g_tc_members[19]._representation._typeCode = (RTICdrTypeCode *)&MetricContext_g_tc_metric_info_label_string_string;

        MetricContext_g_tc_members[20]._representation._typeCode = (RTICdrTypeCode *)ice::ExtNomenRef_get_typecode();

        MetricContext_g_tc_members[21]._representation._typeCode = (RTICdrTypeCode *)&MetricContext_g_tc_substance_label_string_string;

        MetricContext_g_tc._data._typeCode = (RTICdrTypeCode *)ice::VMO_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &MetricContext_g_tc;
    }

    RTIBool MetricContext_initialize(
        MetricContext* sample) {
        return ice::MetricContext_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricContext_initialize_ex(
        MetricContext* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricContext_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricContext_initialize_w_params(
        MetricContext* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::VMO_initialize_w_params((ice::VMO*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->context_seq_number)) {
            return RTI_FALSE;
        }

        if (!ice::MetricSpec_initialize_w_params(&sample->metric_specification,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!allocParams->allocate_optional_members) {
            sample->max_delay_time=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->max_delay_time = new (std::nothrow)   ice::Duration  ;
                if (sample->max_delay_time==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::Duration_initialize_w_params(sample->max_delay_time,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->max_delay_time!=NULL) {
                    if (!ice::Duration_initialize_w_params(sample->max_delay_time,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (allocParams->allocate_memory){
            sample->vmo_label_string= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->vmo_label_string == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->vmo_label_string!= NULL) { 
                sample->vmo_label_string[0] = '\0';
            }
        }

        if (!ice::VmoSourceList_initialize_w_params(&sample->vmo_source_list,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricSourceList_initialize_w_params(&sample->metric_source_list,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_initialize_w_params(&sample->unit_code,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->unit_label_string= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->unit_label_string == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->unit_label_string!= NULL) { 
                sample->unit_label_string[0] = '\0';
            }
        }

        if (!ice::SiteList_initialize_w_params(&sample->msmt_site_list,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::SiteList_initialize_w_params(&sample->body_site_list,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MetricStatus_initialize_w_params(&sample->metric_status,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!allocParams->allocate_optional_members) {
            sample->measure_period=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->measure_period = new (std::nothrow)   ice::MetricMeasure  ;
                if (sample->measure_period==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::MetricMeasure_initialize_w_params(sample->measure_period,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->measure_period!=NULL) {
                    if (!ice::MetricMeasure_initialize_w_params(sample->measure_period,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->averaging_period=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->averaging_period = new (std::nothrow)   ice::MetricMeasure  ;
                if (sample->averaging_period==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::MetricMeasure_initialize_w_params(sample->averaging_period,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->averaging_period!=NULL) {
                    if (!ice::MetricMeasure_initialize_w_params(sample->averaging_period,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->start_time=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->start_time = new (std::nothrow)   ice::Timespec  ;
                if (sample->start_time==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::Timespec_initialize_w_params(sample->start_time,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->start_time!=NULL) {
                    if (!ice::Timespec_initialize_w_params(sample->start_time,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->stop_time=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->stop_time = new (std::nothrow)   ice::Timespec  ;
                if (sample->stop_time==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::Timespec_initialize_w_params(sample->stop_time,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->stop_time!=NULL) {
                    if (!ice::Timespec_initialize_w_params(sample->stop_time,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!ice::MetricCalibration_initialize_w_params(&sample->metric_calibration,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!allocParams->allocate_optional_members) {
            sample->color=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->color = new (std::nothrow)   ice::SimpleColor  ;
                if (sample->color==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::SimpleColor_initialize_w_params(sample->color,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->color!=NULL) {
                    if (!ice::SimpleColor_initialize_w_params(sample->color,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!ice::MeasurementStatus_initialize_w_params(&sample->measurement_status,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_initialize_w_params(&sample->metric_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->metric_info_label_string= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->metric_info_label_string == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->metric_info_label_string!= NULL) { 
                sample->metric_info_label_string[0] = '\0';
            }
        }

        if (!allocParams->allocate_optional_members) {
            sample->substance=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->substance = new (std::nothrow)   ice::ExtNomenRef  ;
                if (sample->substance==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::ExtNomenRef_initialize_w_params(sample->substance,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->substance!=NULL) {
                    if (!ice::ExtNomenRef_initialize_w_params(sample->substance,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (allocParams->allocate_memory){
            sample->substance_label_string= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->substance_label_string == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->substance_label_string!= NULL) { 
                sample->substance_label_string[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void MetricContext_finalize(
        MetricContext* sample)
    {

        ice::MetricContext_finalize_ex(sample,RTI_TRUE);
    }

    void MetricContext_finalize_ex(
        MetricContext* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricContext_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricContext_finalize_w_params(
        MetricContext* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::VMO_finalize_w_params((ice::VMO*)sample,deallocParams);

        ice::MetricSpec_finalize_w_params(&sample->metric_specification,deallocParams);

        if (deallocParams->delete_optional_members) {
            if (sample->max_delay_time != NULL) {
                ice::Duration_finalize_w_params(sample->max_delay_time,deallocParams);

                delete  sample->max_delay_time;
                sample->max_delay_time=NULL;
            }
        }
        if (sample->vmo_label_string != NULL) {
            DDS_String_free(sample->vmo_label_string);
            sample->vmo_label_string=NULL;

        }
        ice::VmoSourceList_finalize_w_params(&sample->vmo_source_list,deallocParams);

        ice::MetricSourceList_finalize_w_params(&sample->metric_source_list,deallocParams);

        ice::OIDType_finalize_w_params(&sample->unit_code,deallocParams);

        if (sample->unit_label_string != NULL) {
            DDS_String_free(sample->unit_label_string);
            sample->unit_label_string=NULL;

        }
        ice::SiteList_finalize_w_params(&sample->msmt_site_list,deallocParams);

        ice::SiteList_finalize_w_params(&sample->body_site_list,deallocParams);

        ice::MetricStatus_finalize_w_params(&sample->metric_status,deallocParams);

        if (deallocParams->delete_optional_members) {
            if (sample->measure_period != NULL) {
                ice::MetricMeasure_finalize_w_params(sample->measure_period,deallocParams);

                delete  sample->measure_period;
                sample->measure_period=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->averaging_period != NULL) {
                ice::MetricMeasure_finalize_w_params(sample->averaging_period,deallocParams);

                delete  sample->averaging_period;
                sample->averaging_period=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->start_time != NULL) {
                ice::Timespec_finalize_w_params(sample->start_time,deallocParams);

                delete  sample->start_time;
                sample->start_time=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->stop_time != NULL) {
                ice::Timespec_finalize_w_params(sample->stop_time,deallocParams);

                delete  sample->stop_time;
                sample->stop_time=NULL;
            }
        }
        ice::MetricCalibration_finalize_w_params(&sample->metric_calibration,deallocParams);

        if (deallocParams->delete_optional_members) {
            if (sample->color != NULL) {
                ice::SimpleColor_finalize_w_params(sample->color,deallocParams);

                delete  sample->color;
                sample->color=NULL;
            }
        }
        ice::MeasurementStatus_finalize_w_params(&sample->measurement_status,deallocParams);

        ice::OIDType_finalize_w_params(&sample->metric_id,deallocParams);

        if (sample->metric_info_label_string != NULL) {
            DDS_String_free(sample->metric_info_label_string);
            sample->metric_info_label_string=NULL;

        }
        if (deallocParams->delete_optional_members) {
            if (sample->substance != NULL) {
                ice::ExtNomenRef_finalize_w_params(sample->substance,deallocParams);

                delete  sample->substance;
                sample->substance=NULL;
            }
        }
        if (sample->substance_label_string != NULL) {
            DDS_String_free(sample->substance_label_string);
            sample->substance_label_string=NULL;

        }
    }

    void MetricContext_finalize_optional_members(
        MetricContext* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::VMO_finalize_optional_members((ice::VMO*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::MetricSpec_finalize_optional_members(&sample->metric_specification, deallocParams->delete_pointers);
        if (sample->max_delay_time != NULL) {
            ice::Duration_finalize_w_params(sample->max_delay_time,deallocParams);

            delete  sample->max_delay_time;
            sample->max_delay_time=NULL;
        }
        ice::VmoSourceList_finalize_optional_members(&sample->vmo_source_list, deallocParams->delete_pointers);
        ice::MetricSourceList_finalize_optional_members(&sample->metric_source_list, deallocParams->delete_pointers);
        ice::OIDType_finalize_optional_members(&sample->unit_code, deallocParams->delete_pointers);
        ice::SiteList_finalize_optional_members(&sample->msmt_site_list, deallocParams->delete_pointers);
        ice::SiteList_finalize_optional_members(&sample->body_site_list, deallocParams->delete_pointers);
        ice::MetricStatus_finalize_optional_members(&sample->metric_status, deallocParams->delete_pointers);
        if (sample->measure_period != NULL) {
            ice::MetricMeasure_finalize_w_params(sample->measure_period,deallocParams);

            delete  sample->measure_period;
            sample->measure_period=NULL;
        }
        if (sample->averaging_period != NULL) {
            ice::MetricMeasure_finalize_w_params(sample->averaging_period,deallocParams);

            delete  sample->averaging_period;
            sample->averaging_period=NULL;
        }
        if (sample->start_time != NULL) {
            ice::Timespec_finalize_w_params(sample->start_time,deallocParams);

            delete  sample->start_time;
            sample->start_time=NULL;
        }
        if (sample->stop_time != NULL) {
            ice::Timespec_finalize_w_params(sample->stop_time,deallocParams);

            delete  sample->stop_time;
            sample->stop_time=NULL;
        }
        ice::MetricCalibration_finalize_optional_members(&sample->metric_calibration, deallocParams->delete_pointers);
        if (sample->color != NULL) {
            ice::SimpleColor_finalize_w_params(sample->color,deallocParams);

            delete  sample->color;
            sample->color=NULL;
        }
        ice::MeasurementStatus_finalize_optional_members(&sample->measurement_status, deallocParams->delete_pointers);
        ice::OIDType_finalize_optional_members(&sample->metric_id, deallocParams->delete_pointers);
        if (sample->substance != NULL) {
            ice::ExtNomenRef_finalize_w_params(sample->substance,deallocParams);

            delete  sample->substance;
            sample->substance=NULL;
        }
    }

    RTIBool MetricContext_copy(
        MetricContext* dst,
        const MetricContext* src)
    {
        try {

            struct DDS_TypeDeallocationParams_t deallocParamsTmp =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
            struct DDS_TypeDeallocationParams_t * deallocParams =
            &deallocParamsTmp;

            if (deallocParams) {} /* To avoid warnings */

            deallocParamsTmp.delete_pointers = DDS_BOOLEAN_TRUE;
            deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if(!ice::VMO_copy((ice::VMO*)dst,(const ice::VMO*)src)) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                &dst->context_seq_number, &src->context_seq_number)) { 
                return RTI_FALSE;
            }
            if (!ice::MetricSpec_copy(
                &dst->metric_specification,(const ice::MetricSpec*)&src->metric_specification)) {
                return RTI_FALSE;
            } 
            if (src->max_delay_time!=NULL) {
                if (dst->max_delay_time==NULL) {

                    dst->max_delay_time = new (std::nothrow)   ice::Duration  ;
                    if (dst->max_delay_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Duration_initialize_ex(dst->max_delay_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::Duration_copy(
                    dst->max_delay_time,(const ice::Duration*)src->max_delay_time)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->max_delay_time != NULL) {

                    ice::Duration_finalize_w_params(dst->max_delay_time, deallocParams);
                    delete  dst->max_delay_time;
                    dst->max_delay_time=NULL;
                }   
            }
            if (!RTICdrType_copyStringEx (
                &dst->vmo_label_string, src->vmo_label_string, 
                ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!ice::VmoSourceList_copy(
                &dst->vmo_source_list,(const ice::VmoSourceList*)&src->vmo_source_list)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricSourceList_copy(
                &dst->metric_source_list,(const ice::MetricSourceList*)&src->metric_source_list)) {
                return RTI_FALSE;
            } 
            if (!ice::OIDType_copy(
                &dst->unit_code,(const ice::OIDType*)&src->unit_code)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->unit_label_string, src->unit_label_string, 
                ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!ice::SiteList_copy(
                &dst->msmt_site_list,(const ice::SiteList*)&src->msmt_site_list)) {
                return RTI_FALSE;
            } 
            if (!ice::SiteList_copy(
                &dst->body_site_list,(const ice::SiteList*)&src->body_site_list)) {
                return RTI_FALSE;
            } 
            if (!ice::MetricStatus_copy(
                &dst->metric_status,(const ice::MetricStatus*)&src->metric_status)) {
                return RTI_FALSE;
            } 
            if (src->measure_period!=NULL) {
                if (dst->measure_period==NULL) {

                    dst->measure_period = new (std::nothrow)   ice::MetricMeasure  ;
                    if (dst->measure_period==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::MetricMeasure_initialize_ex(dst->measure_period, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::MetricMeasure_copy(
                    dst->measure_period,(const ice::MetricMeasure*)src->measure_period)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->measure_period != NULL) {

                    ice::MetricMeasure_finalize_w_params(dst->measure_period, deallocParams);
                    delete  dst->measure_period;
                    dst->measure_period=NULL;
                }   
            }
            if (src->averaging_period!=NULL) {
                if (dst->averaging_period==NULL) {

                    dst->averaging_period = new (std::nothrow)   ice::MetricMeasure  ;
                    if (dst->averaging_period==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::MetricMeasure_initialize_ex(dst->averaging_period, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::MetricMeasure_copy(
                    dst->averaging_period,(const ice::MetricMeasure*)src->averaging_period)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->averaging_period != NULL) {

                    ice::MetricMeasure_finalize_w_params(dst->averaging_period, deallocParams);
                    delete  dst->averaging_period;
                    dst->averaging_period=NULL;
                }   
            }
            if (src->start_time!=NULL) {
                if (dst->start_time==NULL) {

                    dst->start_time = new (std::nothrow)   ice::Timespec  ;
                    if (dst->start_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(dst->start_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::Timespec_copy(
                    dst->start_time,(const ice::Timespec*)src->start_time)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->start_time != NULL) {

                    ice::Timespec_finalize_w_params(dst->start_time, deallocParams);
                    delete  dst->start_time;
                    dst->start_time=NULL;
                }   
            }
            if (src->stop_time!=NULL) {
                if (dst->stop_time==NULL) {

                    dst->stop_time = new (std::nothrow)   ice::Timespec  ;
                    if (dst->stop_time==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(dst->stop_time, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::Timespec_copy(
                    dst->stop_time,(const ice::Timespec*)src->stop_time)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->stop_time != NULL) {

                    ice::Timespec_finalize_w_params(dst->stop_time, deallocParams);
                    delete  dst->stop_time;
                    dst->stop_time=NULL;
                }   
            }
            if (!ice::MetricCalibration_copy(
                &dst->metric_calibration,(const ice::MetricCalibration*)&src->metric_calibration)) {
                return RTI_FALSE;
            } 
            if (src->color!=NULL) {
                if (dst->color==NULL) {

                    dst->color = new (std::nothrow)   ice::SimpleColor  ;
                    if (dst->color==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::SimpleColor_initialize_ex(dst->color, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::SimpleColor_copy(
                    dst->color,(const ice::SimpleColor*)src->color)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->color != NULL) {

                    ice::SimpleColor_finalize_w_params(dst->color, deallocParams);
                    delete  dst->color;
                    dst->color=NULL;
                }   
            }
            if (!ice::MeasurementStatus_copy(
                &dst->measurement_status,(const ice::MeasurementStatus*)&src->measurement_status)) {
                return RTI_FALSE;
            } 
            if (!ice::OIDType_copy(
                &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->metric_info_label_string, src->metric_info_label_string, 
                ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (src->substance!=NULL) {
                if (dst->substance==NULL) {

                    dst->substance = new (std::nothrow)   ice::ExtNomenRef  ;
                    if (dst->substance==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::ExtNomenRef_initialize_ex(dst->substance, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::ExtNomenRef_copy(
                    dst->substance,(const ice::ExtNomenRef*)src->substance)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->substance != NULL) {

                    ice::ExtNomenRef_finalize_w_params(dst->substance, deallocParams);
                    delete  dst->substance;
                    dst->substance=NULL;
                }   
            }
            if (!RTICdrType_copyStringEx (
                &dst->substance_label_string, src->substance_label_string, 
                ((ice::LONG_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricContext' sequence class.
    */
    #define T MetricContext
    #define TSeq MetricContextSeq

    #define T_initialize_w_params ice::MetricContext_initialize_w_params

    #define T_finalize_w_params   ice::MetricContext_finalize_w_params
    #define T_copy       ice::MetricContext_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *MetricObservedValueTYPENAME = "ice::MetricObservedValue";

    DDS_TypeCode* MetricObservedValue_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member MetricObservedValue_g_tc_members[4]=
        {

            {
                (char *)"context_seq_number",/* Member name */
                {
                    5,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"metric_id_partition",/* Member name */
                {
                    6,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"device_timestamp",/* Member name */
                {
                    7,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"device_relative_timestamp",/* Member name */
                {
                    8,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode MetricObservedValue_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::MetricObservedValue", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                MetricObservedValue_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for MetricObservedValue*/

        if (is_initialized) {
            return &MetricObservedValue_g_tc;
        }

        MetricObservedValue_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        MetricObservedValue_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::NomPartition_get_typecode();

        MetricObservedValue_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::Timespec_get_typecode();

        MetricObservedValue_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::Duration_get_typecode();

        MetricObservedValue_g_tc._data._typeCode = (RTICdrTypeCode *)ice::VMO_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &MetricObservedValue_g_tc;
    }

    RTIBool MetricObservedValue_initialize(
        MetricObservedValue* sample) {
        return ice::MetricObservedValue_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MetricObservedValue_initialize_ex(
        MetricObservedValue* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MetricObservedValue_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MetricObservedValue_initialize_w_params(
        MetricObservedValue* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::VMO_initialize_w_params((ice::VMO*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->context_seq_number)) {
            return RTI_FALSE;
        }

        if (!ice::NomPartition_initialize_w_params(&sample->metric_id_partition,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!allocParams->allocate_optional_members) {
            sample->device_timestamp=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->device_timestamp = new (std::nothrow)   ice::Timespec  ;
                if (sample->device_timestamp==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::Timespec_initialize_w_params(sample->device_timestamp,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->device_timestamp!=NULL) {
                    if (!ice::Timespec_initialize_w_params(sample->device_timestamp,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->device_relative_timestamp=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->device_relative_timestamp = new (std::nothrow)   ice::Duration  ;
                if (sample->device_relative_timestamp==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::Duration_initialize_w_params(sample->device_relative_timestamp,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->device_relative_timestamp!=NULL) {
                    if (!ice::Duration_initialize_w_params(sample->device_relative_timestamp,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        return RTI_TRUE;
    }

    void MetricObservedValue_finalize(
        MetricObservedValue* sample)
    {

        ice::MetricObservedValue_finalize_ex(sample,RTI_TRUE);
    }

    void MetricObservedValue_finalize_ex(
        MetricObservedValue* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MetricObservedValue_finalize_w_params(
            sample,&deallocParams);
    }

    void MetricObservedValue_finalize_w_params(
        MetricObservedValue* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::VMO_finalize_w_params((ice::VMO*)sample,deallocParams);

        ice::NomPartition_finalize_w_params(&sample->metric_id_partition,deallocParams);

        if (deallocParams->delete_optional_members) {
            if (sample->device_timestamp != NULL) {
                ice::Timespec_finalize_w_params(sample->device_timestamp,deallocParams);

                delete  sample->device_timestamp;
                sample->device_timestamp=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->device_relative_timestamp != NULL) {
                ice::Duration_finalize_w_params(sample->device_relative_timestamp,deallocParams);

                delete  sample->device_relative_timestamp;
                sample->device_relative_timestamp=NULL;
            }
        }
    }

    void MetricObservedValue_finalize_optional_members(
        MetricObservedValue* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::VMO_finalize_optional_members((ice::VMO*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::NomPartition_finalize_optional_members(&sample->metric_id_partition, deallocParams->delete_pointers);
        if (sample->device_timestamp != NULL) {
            ice::Timespec_finalize_w_params(sample->device_timestamp,deallocParams);

            delete  sample->device_timestamp;
            sample->device_timestamp=NULL;
        }
        if (sample->device_relative_timestamp != NULL) {
            ice::Duration_finalize_w_params(sample->device_relative_timestamp,deallocParams);

            delete  sample->device_relative_timestamp;
            sample->device_relative_timestamp=NULL;
        }
    }

    RTIBool MetricObservedValue_copy(
        MetricObservedValue* dst,
        const MetricObservedValue* src)
    {
        try {

            struct DDS_TypeDeallocationParams_t deallocParamsTmp =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
            struct DDS_TypeDeallocationParams_t * deallocParams =
            &deallocParamsTmp;

            if (deallocParams) {} /* To avoid warnings */

            deallocParamsTmp.delete_pointers = DDS_BOOLEAN_TRUE;
            deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if(!ice::VMO_copy((ice::VMO*)dst,(const ice::VMO*)src)) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                &dst->context_seq_number, &src->context_seq_number)) { 
                return RTI_FALSE;
            }
            if (!ice::NomPartition_copy(
                &dst->metric_id_partition,(const ice::NomPartition*)&src->metric_id_partition)) {
                return RTI_FALSE;
            } 
            if (src->device_timestamp!=NULL) {
                if (dst->device_timestamp==NULL) {

                    dst->device_timestamp = new (std::nothrow)   ice::Timespec  ;
                    if (dst->device_timestamp==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Timespec_initialize_ex(dst->device_timestamp, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::Timespec_copy(
                    dst->device_timestamp,(const ice::Timespec*)src->device_timestamp)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->device_timestamp != NULL) {

                    ice::Timespec_finalize_w_params(dst->device_timestamp, deallocParams);
                    delete  dst->device_timestamp;
                    dst->device_timestamp=NULL;
                }   
            }
            if (src->device_relative_timestamp!=NULL) {
                if (dst->device_relative_timestamp==NULL) {

                    dst->device_relative_timestamp = new (std::nothrow)   ice::Duration  ;
                    if (dst->device_relative_timestamp==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::Duration_initialize_ex(dst->device_relative_timestamp, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::Duration_copy(
                    dst->device_relative_timestamp,(const ice::Duration*)src->device_relative_timestamp)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->device_relative_timestamp != NULL) {

                    ice::Duration_finalize_w_params(dst->device_relative_timestamp, deallocParams);
                    delete  dst->device_relative_timestamp;
                    dst->device_relative_timestamp=NULL;
                }   
            }

            return RTI_TRUE;

        } catch (std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'MetricObservedValue' sequence class.
    */
    #define T MetricObservedValue
    #define TSeq MetricObservedValueSeq

    #define T_initialize_w_params ice::MetricObservedValue_initialize_w_params

    #define T_finalize_w_params   ice::MetricObservedValue_finalize_w_params
    #define T_copy       ice::MetricObservedValue_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T
} /* namespace ice  */

