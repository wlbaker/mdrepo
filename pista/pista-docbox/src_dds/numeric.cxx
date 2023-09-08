

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from numeric.idl using "rtiddsgen".
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

#include "numeric.h"

#include <new>

namespace ice {

    /* ========================================================================= */
    const char *AbsoluteRangeTYPENAME = "ice::AbsoluteRange";

    DDS_TypeCode* AbsoluteRange_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member AbsoluteRange_g_tc_members[2]=
        {

            {
                (char *)"lower_value",/* Member name */
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
                (char *)"upper_value",/* Member name */
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

        static DDS_TypeCode AbsoluteRange_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::AbsoluteRange", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                AbsoluteRange_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for AbsoluteRange*/

        if (is_initialized) {
            return &AbsoluteRange_g_tc;
        }

        AbsoluteRange_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        AbsoluteRange_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        is_initialized = RTI_TRUE;

        return &AbsoluteRange_g_tc;
    }

    RTIBool AbsoluteRange_initialize(
        AbsoluteRange* sample) {
        return ice::AbsoluteRange_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool AbsoluteRange_initialize_ex(
        AbsoluteRange* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::AbsoluteRange_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool AbsoluteRange_initialize_w_params(
        AbsoluteRange* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::FLOATType_initialize_w_params(&sample->lower_value,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::FLOATType_initialize_w_params(&sample->upper_value,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void AbsoluteRange_finalize(
        AbsoluteRange* sample)
    {

        ice::AbsoluteRange_finalize_ex(sample,RTI_TRUE);
    }

    void AbsoluteRange_finalize_ex(
        AbsoluteRange* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::AbsoluteRange_finalize_w_params(
            sample,&deallocParams);
    }

    void AbsoluteRange_finalize_w_params(
        AbsoluteRange* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::FLOATType_finalize_w_params(&sample->lower_value,deallocParams);

        ice::FLOATType_finalize_w_params(&sample->upper_value,deallocParams);

    }

    void AbsoluteRange_finalize_optional_members(
        AbsoluteRange* sample, RTIBool deletePointers)
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

        ice::FLOATType_finalize_optional_members(&sample->lower_value, deallocParams->delete_pointers);
        ice::FLOATType_finalize_optional_members(&sample->upper_value, deallocParams->delete_pointers);
    }

    RTIBool AbsoluteRange_copy(
        AbsoluteRange* dst,
        const AbsoluteRange* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::FLOATType_copy(
                &dst->lower_value,(const ice::FLOATType*)&src->lower_value)) {
                return RTI_FALSE;
            } 
            if (!ice::FLOATType_copy(
                &dst->upper_value,(const ice::FLOATType*)&src->upper_value)) {
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
    * Configure and implement 'AbsoluteRange' sequence class.
    */
    #define T AbsoluteRange
    #define TSeq AbsoluteRangeSeq

    #define T_initialize_w_params ice::AbsoluteRange_initialize_w_params

    #define T_finalize_w_params   ice::AbsoluteRange_finalize_w_params
    #define T_copy       ice::AbsoluteRange_copy

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
    const char *DispResolutionTYPENAME = "ice::DispResolution";

    DDS_TypeCode* DispResolution_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member DispResolution_g_tc_members[2]=
        {

            {
                (char *)"pre_point",/* Member name */
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
                (char *)"post_point",/* Member name */
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

        static DDS_TypeCode DispResolution_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::DispResolution", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                DispResolution_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for DispResolution*/

        if (is_initialized) {
            return &DispResolution_g_tc;
        }

        DispResolution_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        DispResolution_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        is_initialized = RTI_TRUE;

        return &DispResolution_g_tc;
    }

    RTIBool DispResolution_initialize(
        DispResolution* sample) {
        return ice::DispResolution_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool DispResolution_initialize_ex(
        DispResolution* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::DispResolution_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool DispResolution_initialize_w_params(
        DispResolution* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU8_initialize_w_params(&sample->pre_point,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::INTU8_initialize_w_params(&sample->post_point,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void DispResolution_finalize(
        DispResolution* sample)
    {

        ice::DispResolution_finalize_ex(sample,RTI_TRUE);
    }

    void DispResolution_finalize_ex(
        DispResolution* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::DispResolution_finalize_w_params(
            sample,&deallocParams);
    }

    void DispResolution_finalize_w_params(
        DispResolution* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU8_finalize_w_params(&sample->pre_point,deallocParams);

        ice::INTU8_finalize_w_params(&sample->post_point,deallocParams);

    }

    void DispResolution_finalize_optional_members(
        DispResolution* sample, RTIBool deletePointers)
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

        ice::INTU8_finalize_optional_members(&sample->pre_point, deallocParams->delete_pointers);
        ice::INTU8_finalize_optional_members(&sample->post_point, deallocParams->delete_pointers);
    }

    RTIBool DispResolution_copy(
        DispResolution* dst,
        const DispResolution* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU8_copy(
                &dst->pre_point,(const ice::INTU8*)&src->pre_point)) {
                return RTI_FALSE;
            } 
            if (!ice::INTU8_copy(
                &dst->post_point,(const ice::INTU8*)&src->post_point)) {
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
    * Configure and implement 'DispResolution' sequence class.
    */
    #define T DispResolution
    #define TSeq DispResolutionSeq

    #define T_initialize_w_params ice::DispResolution_initialize_w_params

    #define T_finalize_w_params   ice::DispResolution_finalize_w_params
    #define T_copy       ice::DispResolution_copy

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
    const char *NuObsValueTYPENAME = "ice::NuObsValue";

    DDS_TypeCode* NuObsValue_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member NuObsValue_g_tc_members[4]=
        {

            {
                (char *)"metric_id",/* Member name */
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
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"state",/* Member name */
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
                (char *)"unit_code",/* Member name */
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
                (char *)"value",/* Member name */
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

        static DDS_TypeCode NuObsValue_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::NuObsValue", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                NuObsValue_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for NuObsValue*/

        if (is_initialized) {
            return &NuObsValue_g_tc;
        }

        NuObsValue_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        NuObsValue_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::MeasurementStatus_get_typecode();

        NuObsValue_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        NuObsValue_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        is_initialized = RTI_TRUE;

        return &NuObsValue_g_tc;
    }

    RTIBool NuObsValue_initialize(
        NuObsValue* sample) {
        return ice::NuObsValue_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool NuObsValue_initialize_ex(
        NuObsValue* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::NuObsValue_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool NuObsValue_initialize_w_params(
        NuObsValue* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_initialize_w_params(&sample->metric_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::MeasurementStatus_initialize_w_params(&sample->state,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_initialize_w_params(&sample->unit_code,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::FLOATType_initialize_w_params(&sample->value,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void NuObsValue_finalize(
        NuObsValue* sample)
    {

        ice::NuObsValue_finalize_ex(sample,RTI_TRUE);
    }

    void NuObsValue_finalize_ex(
        NuObsValue* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::NuObsValue_finalize_w_params(
            sample,&deallocParams);
    }

    void NuObsValue_finalize_w_params(
        NuObsValue* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDType_finalize_w_params(&sample->metric_id,deallocParams);

        ice::MeasurementStatus_finalize_w_params(&sample->state,deallocParams);

        ice::OIDType_finalize_w_params(&sample->unit_code,deallocParams);

        ice::FLOATType_finalize_w_params(&sample->value,deallocParams);

    }

    void NuObsValue_finalize_optional_members(
        NuObsValue* sample, RTIBool deletePointers)
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

        ice::OIDType_finalize_optional_members(&sample->metric_id, deallocParams->delete_pointers);
        ice::MeasurementStatus_finalize_optional_members(&sample->state, deallocParams->delete_pointers);
        ice::OIDType_finalize_optional_members(&sample->unit_code, deallocParams->delete_pointers);
        ice::FLOATType_finalize_optional_members(&sample->value, deallocParams->delete_pointers);
    }

    RTIBool NuObsValue_copy(
        NuObsValue* dst,
        const NuObsValue* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDType_copy(
                &dst->metric_id,(const ice::OIDType*)&src->metric_id)) {
                return RTI_FALSE;
            } 
            if (!ice::MeasurementStatus_copy(
                &dst->state,(const ice::MeasurementStatus*)&src->state)) {
                return RTI_FALSE;
            } 
            if (!ice::OIDType_copy(
                &dst->unit_code,(const ice::OIDType*)&src->unit_code)) {
                return RTI_FALSE;
            } 
            if (!ice::FLOATType_copy(
                &dst->value,(const ice::FLOATType*)&src->value)) {
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
    * Configure and implement 'NuObsValue' sequence class.
    */
    #define T NuObsValue
    #define TSeq NuObsValueSeq

    #define T_initialize_w_params ice::NuObsValue_initialize_w_params

    #define T_finalize_w_params   ice::NuObsValue_finalize_w_params
    #define T_copy       ice::NuObsValue_copy

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
    const char *NumericContextTYPENAME = "ice::NumericContext";

    DDS_TypeCode* NumericContext_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member NumericContext_g_tc_members[4]=
        {

            {
                (char *)"nu_measure_range",/* Member name */
                {
                    27,/* Representation ID */          
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
                (char *)"nu_physiological_range",/* Member name */
                {
                    28,/* Representation ID */          
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
                (char *)"display_resolution",/* Member name */
                {
                    29,/* Representation ID */          
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
                (char *)"accuracy",/* Member name */
                {
                    30,/* Representation ID */          
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

        static DDS_TypeCode NumericContext_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::NumericContext", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                NumericContext_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for NumericContext*/

        if (is_initialized) {
            return &NumericContext_g_tc;
        }

        NumericContext_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::AbsoluteRange_get_typecode();

        NumericContext_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::AbsoluteRange_get_typecode();

        NumericContext_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::DispResolution_get_typecode();

        NumericContext_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        NumericContext_g_tc._data._typeCode = (RTICdrTypeCode *)ice::MetricContext_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &NumericContext_g_tc;
    }

    RTIBool NumericContext_initialize(
        NumericContext* sample) {
        return ice::NumericContext_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool NumericContext_initialize_ex(
        NumericContext* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::NumericContext_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool NumericContext_initialize_w_params(
        NumericContext* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::MetricContext_initialize_w_params((ice::MetricContext*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (!allocParams->allocate_optional_members) {
            sample->nu_measure_range=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->nu_measure_range = new (std::nothrow)   ice::AbsoluteRange  ;
                if (sample->nu_measure_range==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::AbsoluteRange_initialize_w_params(sample->nu_measure_range,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->nu_measure_range!=NULL) {
                    if (!ice::AbsoluteRange_initialize_w_params(sample->nu_measure_range,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->nu_physiological_range=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->nu_physiological_range = new (std::nothrow)   ice::AbsoluteRange  ;
                if (sample->nu_physiological_range==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::AbsoluteRange_initialize_w_params(sample->nu_physiological_range,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->nu_physiological_range!=NULL) {
                    if (!ice::AbsoluteRange_initialize_w_params(sample->nu_physiological_range,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->display_resolution=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->display_resolution = new (std::nothrow)   ice::DispResolution  ;
                if (sample->display_resolution==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::DispResolution_initialize_w_params(sample->display_resolution,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->display_resolution!=NULL) {
                    if (!ice::DispResolution_initialize_w_params(sample->display_resolution,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->accuracy=NULL;
        } else {   
            if (allocParams->allocate_memory) {
                sample->accuracy = new (std::nothrow)   ice::FLOATType  ;
                if (sample->accuracy==NULL) {
                    return RTI_FALSE;
                }
                if (!ice::FLOATType_initialize_w_params(sample->accuracy,
                allocParams)) {
                    return RTI_FALSE;
                }
            } else {
                if (sample->accuracy!=NULL) {
                    if (!ice::FLOATType_initialize_w_params(sample->accuracy,
                    allocParams)) {
                        return RTI_FALSE;
                    }        
                }   
            }
        }
        return RTI_TRUE;
    }

    void NumericContext_finalize(
        NumericContext* sample)
    {

        ice::NumericContext_finalize_ex(sample,RTI_TRUE);
    }

    void NumericContext_finalize_ex(
        NumericContext* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::NumericContext_finalize_w_params(
            sample,&deallocParams);
    }

    void NumericContext_finalize_w_params(
        NumericContext* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::MetricContext_finalize_w_params((ice::MetricContext*)sample,deallocParams);

        if (deallocParams->delete_optional_members) {
            if (sample->nu_measure_range != NULL) {
                ice::AbsoluteRange_finalize_w_params(sample->nu_measure_range,deallocParams);

                delete  sample->nu_measure_range;
                sample->nu_measure_range=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->nu_physiological_range != NULL) {
                ice::AbsoluteRange_finalize_w_params(sample->nu_physiological_range,deallocParams);

                delete  sample->nu_physiological_range;
                sample->nu_physiological_range=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->display_resolution != NULL) {
                ice::DispResolution_finalize_w_params(sample->display_resolution,deallocParams);

                delete  sample->display_resolution;
                sample->display_resolution=NULL;
            }
        }
        if (deallocParams->delete_optional_members) {
            if (sample->accuracy != NULL) {
                ice::FLOATType_finalize_w_params(sample->accuracy,deallocParams);

                delete  sample->accuracy;
                sample->accuracy=NULL;
            }
        }
    }

    void NumericContext_finalize_optional_members(
        NumericContext* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::MetricContext_finalize_optional_members((ice::MetricContext*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        if (sample->nu_measure_range != NULL) {
            ice::AbsoluteRange_finalize_w_params(sample->nu_measure_range,deallocParams);

            delete  sample->nu_measure_range;
            sample->nu_measure_range=NULL;
        }
        if (sample->nu_physiological_range != NULL) {
            ice::AbsoluteRange_finalize_w_params(sample->nu_physiological_range,deallocParams);

            delete  sample->nu_physiological_range;
            sample->nu_physiological_range=NULL;
        }
        if (sample->display_resolution != NULL) {
            ice::DispResolution_finalize_w_params(sample->display_resolution,deallocParams);

            delete  sample->display_resolution;
            sample->display_resolution=NULL;
        }
        if (sample->accuracy != NULL) {
            ice::FLOATType_finalize_w_params(sample->accuracy,deallocParams);

            delete  sample->accuracy;
            sample->accuracy=NULL;
        }
    }

    RTIBool NumericContext_copy(
        NumericContext* dst,
        const NumericContext* src)
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

            if(!ice::MetricContext_copy((ice::MetricContext*)dst,(const ice::MetricContext*)src)) {
                return RTI_FALSE;
            }

            if (src->nu_measure_range!=NULL) {
                if (dst->nu_measure_range==NULL) {

                    dst->nu_measure_range = new (std::nothrow)   ice::AbsoluteRange  ;
                    if (dst->nu_measure_range==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::AbsoluteRange_initialize_ex(dst->nu_measure_range, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::AbsoluteRange_copy(
                    dst->nu_measure_range,(const ice::AbsoluteRange*)src->nu_measure_range)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->nu_measure_range != NULL) {

                    ice::AbsoluteRange_finalize_w_params(dst->nu_measure_range, deallocParams);
                    delete  dst->nu_measure_range;
                    dst->nu_measure_range=NULL;
                }   
            }
            if (src->nu_physiological_range!=NULL) {
                if (dst->nu_physiological_range==NULL) {

                    dst->nu_physiological_range = new (std::nothrow)   ice::AbsoluteRange  ;
                    if (dst->nu_physiological_range==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::AbsoluteRange_initialize_ex(dst->nu_physiological_range, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::AbsoluteRange_copy(
                    dst->nu_physiological_range,(const ice::AbsoluteRange*)src->nu_physiological_range)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->nu_physiological_range != NULL) {

                    ice::AbsoluteRange_finalize_w_params(dst->nu_physiological_range, deallocParams);
                    delete  dst->nu_physiological_range;
                    dst->nu_physiological_range=NULL;
                }   
            }
            if (src->display_resolution!=NULL) {
                if (dst->display_resolution==NULL) {

                    dst->display_resolution = new (std::nothrow)   ice::DispResolution  ;
                    if (dst->display_resolution==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::DispResolution_initialize_ex(dst->display_resolution, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::DispResolution_copy(
                    dst->display_resolution,(const ice::DispResolution*)src->display_resolution)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->display_resolution != NULL) {

                    ice::DispResolution_finalize_w_params(dst->display_resolution, deallocParams);
                    delete  dst->display_resolution;
                    dst->display_resolution=NULL;
                }   
            }
            if (src->accuracy!=NULL) {
                if (dst->accuracy==NULL) {

                    dst->accuracy = new (std::nothrow)   ice::FLOATType  ;
                    if (dst->accuracy==NULL) {
                        return RTI_FALSE;
                    }

                    if (!ice::FLOATType_initialize_ex(dst->accuracy, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }
                if (!ice::FLOATType_copy(
                    dst->accuracy,(const ice::FLOATType*)src->accuracy)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->accuracy != NULL) {

                    ice::FLOATType_finalize_w_params(dst->accuracy, deallocParams);
                    delete  dst->accuracy;
                    dst->accuracy=NULL;
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
    * Configure and implement 'NumericContext' sequence class.
    */
    #define T NumericContext
    #define TSeq NumericContextSeq

    #define T_initialize_w_params ice::NumericContext_initialize_w_params

    #define T_finalize_w_params   ice::NumericContext_finalize_w_params
    #define T_copy       ice::NumericContext_copy

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
    const char *NumericObservedValueTYPENAME = "ice::NumericObservedValue";

    DDS_TypeCode* NumericObservedValue_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member NumericObservedValue_g_tc_members[1]=
        {

            {
                (char *)"nu_observed_value",/* Member name */
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
            }
        };

        static DDS_TypeCode NumericObservedValue_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::NumericObservedValue", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                1, /* Number of members */
                NumericObservedValue_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for NumericObservedValue*/

        if (is_initialized) {
            return &NumericObservedValue_g_tc;
        }

        NumericObservedValue_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::NuObsValue_get_typecode();

        NumericObservedValue_g_tc._data._typeCode = (RTICdrTypeCode *)ice::MetricObservedValue_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &NumericObservedValue_g_tc;
    }

    RTIBool NumericObservedValue_initialize(
        NumericObservedValue* sample) {
        return ice::NumericObservedValue_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool NumericObservedValue_initialize_ex(
        NumericObservedValue* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::NumericObservedValue_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool NumericObservedValue_initialize_w_params(
        NumericObservedValue* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::MetricObservedValue_initialize_w_params((ice::MetricObservedValue*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (!ice::NuObsValue_initialize_w_params(&sample->nu_observed_value,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void NumericObservedValue_finalize(
        NumericObservedValue* sample)
    {

        ice::NumericObservedValue_finalize_ex(sample,RTI_TRUE);
    }

    void NumericObservedValue_finalize_ex(
        NumericObservedValue* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::NumericObservedValue_finalize_w_params(
            sample,&deallocParams);
    }

    void NumericObservedValue_finalize_w_params(
        NumericObservedValue* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::MetricObservedValue_finalize_w_params((ice::MetricObservedValue*)sample,deallocParams);

        ice::NuObsValue_finalize_w_params(&sample->nu_observed_value,deallocParams);

    }

    void NumericObservedValue_finalize_optional_members(
        NumericObservedValue* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::MetricObservedValue_finalize_optional_members((ice::MetricObservedValue*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::NuObsValue_finalize_optional_members(&sample->nu_observed_value, deallocParams->delete_pointers);
    }

    RTIBool NumericObservedValue_copy(
        NumericObservedValue* dst,
        const NumericObservedValue* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if(!ice::MetricObservedValue_copy((ice::MetricObservedValue*)dst,(const ice::MetricObservedValue*)src)) {
                return RTI_FALSE;
            }

            if (!ice::NuObsValue_copy(
                &dst->nu_observed_value,(const ice::NuObsValue*)&src->nu_observed_value)) {
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
    * Configure and implement 'NumericObservedValue' sequence class.
    */
    #define T NumericObservedValue
    #define TSeq NumericObservedValueSeq

    #define T_initialize_w_params ice::NumericObservedValue_initialize_w_params

    #define T_finalize_w_params   ice::NumericObservedValue_finalize_w_params
    #define T_copy       ice::NumericObservedValue_copy

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

