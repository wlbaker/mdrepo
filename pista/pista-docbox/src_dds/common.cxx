

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from common.idl using "rtiddsgen".
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

#include "common.h"

#include <new>

namespace ice {

    /* ========================================================================= */

    DDS_TypeCode* OCTET_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode OCTET_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::OCTET", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  OCTET */

        if (is_initialized) {
            return &OCTET_g_tc;
        }

        OCTET_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;

        is_initialized = RTI_TRUE;

        return &OCTET_g_tc;
    }

    RTIBool OCTET_initialize(
        OCTET* sample) {
        return ice::OCTET_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool OCTET_initialize_ex(
        OCTET* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::OCTET_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool OCTET_initialize_w_params(
        OCTET* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initOctet(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void OCTET_finalize(
        OCTET* sample)
    {

        ice::OCTET_finalize_ex(sample,RTI_TRUE);
    }

    void OCTET_finalize_ex(
        OCTET* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::OCTET_finalize_w_params(
            sample,&deallocParams);
    }

    void OCTET_finalize_w_params(
        OCTET* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void OCTET_finalize_optional_members(
        OCTET* sample, RTIBool deletePointers)
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

    RTIBool OCTET_copy(
        OCTET* dst,
        const OCTET* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyOctet (
                dst, src)) { 
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
    * Configure and implement 'OCTET' sequence class.
    */
    #define T OCTET
    #define TSeq OCTETSeq

    #define T_initialize_w_params ice::OCTET_initialize_w_params

    #define T_finalize_w_params   ice::OCTET_finalize_w_params
    #define T_copy       ice::OCTET_copy

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

    DDS_TypeCode* INTU8_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INTU8_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INTU8", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INTU8 */

        if (is_initialized) {
            return &INTU8_g_tc;
        }

        INTU8_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::OCTET_get_typecode();

        is_initialized = RTI_TRUE;

        return &INTU8_g_tc;
    }

    RTIBool INTU8_initialize(
        INTU8* sample) {
        return ice::INTU8_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INTU8_initialize_ex(
        INTU8* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INTU8_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INTU8_initialize_w_params(
        INTU8* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OCTET_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void INTU8_finalize(
        INTU8* sample)
    {

        ice::INTU8_finalize_ex(sample,RTI_TRUE);
    }

    void INTU8_finalize_ex(
        INTU8* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INTU8_finalize_w_params(
            sample,&deallocParams);
    }

    void INTU8_finalize_w_params(
        INTU8* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OCTET_finalize_w_params(sample,deallocParams);

    }

    void INTU8_finalize_optional_members(
        INTU8* sample, RTIBool deletePointers)
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

        ice::OCTET_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool INTU8_copy(
        INTU8* dst,
        const INTU8* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OCTET_copy(
                dst,(const ice::OCTET*)src)) {
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
    * Configure and implement 'INTU8' sequence class.
    */
    #define T INTU8
    #define TSeq INTU8Seq

    #define T_initialize_w_params ice::INTU8_initialize_w_params

    #define T_finalize_w_params   ice::INTU8_finalize_w_params
    #define T_copy       ice::INTU8_copy

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

    DDS_TypeCode* INT16_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INT16_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INT16", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INT16 */

        if (is_initialized) {
            return &INT16_g_tc;
        }

        INT16_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_short;

        is_initialized = RTI_TRUE;

        return &INT16_g_tc;
    }

    RTIBool INT16_initialize(
        INT16* sample) {
        return ice::INT16_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INT16_initialize_ex(
        INT16* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INT16_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INT16_initialize_w_params(
        INT16* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initShort(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void INT16_finalize(
        INT16* sample)
    {

        ice::INT16_finalize_ex(sample,RTI_TRUE);
    }

    void INT16_finalize_ex(
        INT16* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INT16_finalize_w_params(
            sample,&deallocParams);
    }

    void INT16_finalize_w_params(
        INT16* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void INT16_finalize_optional_members(
        INT16* sample, RTIBool deletePointers)
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

    RTIBool INT16_copy(
        INT16* dst,
        const INT16* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyShort (
                dst, src)) { 
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
    * Configure and implement 'INT16' sequence class.
    */
    #define T INT16
    #define TSeq INT16Seq

    #define T_initialize_w_params ice::INT16_initialize_w_params

    #define T_finalize_w_params   ice::INT16_finalize_w_params
    #define T_copy       ice::INT16_copy

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

    DDS_TypeCode* INTU16_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INTU16_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INTU16", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INTU16 */

        if (is_initialized) {
            return &INTU16_g_tc;
        }

        INTU16_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;

        is_initialized = RTI_TRUE;

        return &INTU16_g_tc;
    }

    RTIBool INTU16_initialize(
        INTU16* sample) {
        return ice::INTU16_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INTU16_initialize_ex(
        INTU16* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INTU16_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INTU16_initialize_w_params(
        INTU16* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initUnsignedShort(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void INTU16_finalize(
        INTU16* sample)
    {

        ice::INTU16_finalize_ex(sample,RTI_TRUE);
    }

    void INTU16_finalize_ex(
        INTU16* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INTU16_finalize_w_params(
            sample,&deallocParams);
    }

    void INTU16_finalize_w_params(
        INTU16* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void INTU16_finalize_optional_members(
        INTU16* sample, RTIBool deletePointers)
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

    RTIBool INTU16_copy(
        INTU16* dst,
        const INTU16* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedShort (
                dst, src)) { 
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
    * Configure and implement 'INTU16' sequence class.
    */
    #define T INTU16
    #define TSeq INTU16Seq

    #define T_initialize_w_params ice::INTU16_initialize_w_params

    #define T_finalize_w_params   ice::INTU16_finalize_w_params
    #define T_copy       ice::INTU16_copy

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

    DDS_TypeCode* INT32_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INT32_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INT32", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INT32 */

        if (is_initialized) {
            return &INT32_g_tc;
        }

        INT32_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_long;

        is_initialized = RTI_TRUE;

        return &INT32_g_tc;
    }

    RTIBool INT32_initialize(
        INT32* sample) {
        return ice::INT32_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INT32_initialize_ex(
        INT32* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INT32_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INT32_initialize_w_params(
        INT32* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void INT32_finalize(
        INT32* sample)
    {

        ice::INT32_finalize_ex(sample,RTI_TRUE);
    }

    void INT32_finalize_ex(
        INT32* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INT32_finalize_w_params(
            sample,&deallocParams);
    }

    void INT32_finalize_w_params(
        INT32* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void INT32_finalize_optional_members(
        INT32* sample, RTIBool deletePointers)
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

    RTIBool INT32_copy(
        INT32* dst,
        const INT32* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                dst, src)) { 
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
    * Configure and implement 'INT32' sequence class.
    */
    #define T INT32
    #define TSeq INT32Seq

    #define T_initialize_w_params ice::INT32_initialize_w_params

    #define T_finalize_w_params   ice::INT32_finalize_w_params
    #define T_copy       ice::INT32_copy

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

    DDS_TypeCode* INTU32_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INTU32_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INTU32", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INTU32 */

        if (is_initialized) {
            return &INTU32_g_tc;
        }

        INTU32_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulong;

        is_initialized = RTI_TRUE;

        return &INTU32_g_tc;
    }

    RTIBool INTU32_initialize(
        INTU32* sample) {
        return ice::INTU32_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INTU32_initialize_ex(
        INTU32* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INTU32_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INTU32_initialize_w_params(
        INTU32* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initUnsignedLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void INTU32_finalize(
        INTU32* sample)
    {

        ice::INTU32_finalize_ex(sample,RTI_TRUE);
    }

    void INTU32_finalize_ex(
        INTU32* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INTU32_finalize_w_params(
            sample,&deallocParams);
    }

    void INTU32_finalize_w_params(
        INTU32* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void INTU32_finalize_optional_members(
        INTU32* sample, RTIBool deletePointers)
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

    RTIBool INTU32_copy(
        INTU32* dst,
        const INTU32* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedLong (
                dst, src)) { 
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
    * Configure and implement 'INTU32' sequence class.
    */
    #define T INTU32
    #define TSeq INTU32Seq

    #define T_initialize_w_params ice::INTU32_initialize_w_params

    #define T_finalize_w_params   ice::INTU32_finalize_w_params
    #define T_copy       ice::INTU32_copy

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

    DDS_TypeCode* INTU64_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode INTU64_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::INTU64", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  INTU64 */

        if (is_initialized) {
            return &INTU64_g_tc;
        }

        INTU64_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulonglong;

        is_initialized = RTI_TRUE;

        return &INTU64_g_tc;
    }

    RTIBool INTU64_initialize(
        INTU64* sample) {
        return ice::INTU64_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool INTU64_initialize_ex(
        INTU64* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::INTU64_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool INTU64_initialize_w_params(
        INTU64* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initUnsignedLongLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void INTU64_finalize(
        INTU64* sample)
    {

        ice::INTU64_finalize_ex(sample,RTI_TRUE);
    }

    void INTU64_finalize_ex(
        INTU64* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::INTU64_finalize_w_params(
            sample,&deallocParams);
    }

    void INTU64_finalize_w_params(
        INTU64* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void INTU64_finalize_optional_members(
        INTU64* sample, RTIBool deletePointers)
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

    RTIBool INTU64_copy(
        INTU64* dst,
        const INTU64* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedLongLong (
                dst, src)) { 
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
    * Configure and implement 'INTU64' sequence class.
    */
    #define T INTU64
    #define TSeq INTU64Seq

    #define T_initialize_w_params ice::INTU64_initialize_w_params

    #define T_finalize_w_params   ice::INTU64_finalize_w_params
    #define T_copy       ice::INTU64_copy

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

    DDS_TypeCode* BITS16_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode BITS16_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::BITS16", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  BITS16 */

        if (is_initialized) {
            return &BITS16_g_tc;
        }

        BITS16_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &BITS16_g_tc;
    }

    RTIBool BITS16_initialize(
        BITS16* sample) {
        return ice::BITS16_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool BITS16_initialize_ex(
        BITS16* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::BITS16_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool BITS16_initialize_w_params(
        BITS16* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void BITS16_finalize(
        BITS16* sample)
    {

        ice::BITS16_finalize_ex(sample,RTI_TRUE);
    }

    void BITS16_finalize_ex(
        BITS16* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::BITS16_finalize_w_params(
            sample,&deallocParams);
    }

    void BITS16_finalize_w_params(
        BITS16* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void BITS16_finalize_optional_members(
        BITS16* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool BITS16_copy(
        BITS16* dst,
        const BITS16* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'BITS16' sequence class.
    */
    #define T BITS16
    #define TSeq BITS16Seq

    #define T_initialize_w_params ice::BITS16_initialize_w_params

    #define T_finalize_w_params   ice::BITS16_finalize_w_params
    #define T_copy       ice::BITS16_copy

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

    DDS_TypeCode* BITS32_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode BITS32_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::BITS32", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  BITS32 */

        if (is_initialized) {
            return &BITS32_g_tc;
        }

        BITS32_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU32_get_typecode();

        is_initialized = RTI_TRUE;

        return &BITS32_g_tc;
    }

    RTIBool BITS32_initialize(
        BITS32* sample) {
        return ice::BITS32_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool BITS32_initialize_ex(
        BITS32* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::BITS32_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool BITS32_initialize_w_params(
        BITS32* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU32_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void BITS32_finalize(
        BITS32* sample)
    {

        ice::BITS32_finalize_ex(sample,RTI_TRUE);
    }

    void BITS32_finalize_ex(
        BITS32* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::BITS32_finalize_w_params(
            sample,&deallocParams);
    }

    void BITS32_finalize_w_params(
        BITS32* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU32_finalize_w_params(sample,deallocParams);

    }

    void BITS32_finalize_optional_members(
        BITS32* sample, RTIBool deletePointers)
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

        ice::INTU32_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool BITS32_copy(
        BITS32* dst,
        const BITS32* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU32_copy(
                dst,(const ice::INTU32*)src)) {
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
    * Configure and implement 'BITS32' sequence class.
    */
    #define T BITS32
    #define TSeq BITS32Seq

    #define T_initialize_w_params ice::BITS32_initialize_w_params

    #define T_finalize_w_params   ice::BITS32_finalize_w_params
    #define T_copy       ice::BITS32_copy

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

    DDS_TypeCode* BITS64_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode BITS64_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::BITS64", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  BITS64 */

        if (is_initialized) {
            return &BITS64_g_tc;
        }

        BITS64_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU64_get_typecode();

        is_initialized = RTI_TRUE;

        return &BITS64_g_tc;
    }

    RTIBool BITS64_initialize(
        BITS64* sample) {
        return ice::BITS64_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool BITS64_initialize_ex(
        BITS64* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::BITS64_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool BITS64_initialize_w_params(
        BITS64* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU64_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void BITS64_finalize(
        BITS64* sample)
    {

        ice::BITS64_finalize_ex(sample,RTI_TRUE);
    }

    void BITS64_finalize_ex(
        BITS64* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::BITS64_finalize_w_params(
            sample,&deallocParams);
    }

    void BITS64_finalize_w_params(
        BITS64* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU64_finalize_w_params(sample,deallocParams);

    }

    void BITS64_finalize_optional_members(
        BITS64* sample, RTIBool deletePointers)
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

        ice::INTU64_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool BITS64_copy(
        BITS64* dst,
        const BITS64* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU64_copy(
                dst,(const ice::INTU64*)src)) {
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
    * Configure and implement 'BITS64' sequence class.
    */
    #define T BITS64
    #define TSeq BITS64Seq

    #define T_initialize_w_params ice::BITS64_initialize_w_params

    #define T_finalize_w_params   ice::BITS64_finalize_w_params
    #define T_copy       ice::BITS64_copy

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

    DDS_TypeCode* TIME_T_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode TIME_T_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::TIME_T", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  TIME_T */

        if (is_initialized) {
            return &TIME_T_g_tc;
        }

        TIME_T_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_long;

        is_initialized = RTI_TRUE;

        return &TIME_T_g_tc;
    }

    RTIBool TIME_T_initialize(
        TIME_T* sample) {
        return ice::TIME_T_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool TIME_T_initialize_ex(
        TIME_T* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::TIME_T_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool TIME_T_initialize_w_params(
        TIME_T* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void TIME_T_finalize(
        TIME_T* sample)
    {

        ice::TIME_T_finalize_ex(sample,RTI_TRUE);
    }

    void TIME_T_finalize_ex(
        TIME_T* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::TIME_T_finalize_w_params(
            sample,&deallocParams);
    }

    void TIME_T_finalize_w_params(
        TIME_T* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void TIME_T_finalize_optional_members(
        TIME_T* sample, RTIBool deletePointers)
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

    RTIBool TIME_T_copy(
        TIME_T* dst,
        const TIME_T* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                dst, src)) { 
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
    * Configure and implement 'TIME_T' sequence class.
    */
    #define T TIME_T
    #define TSeq TIME_TSeq

    #define T_initialize_w_params ice::TIME_T_initialize_w_params

    #define T_finalize_w_params   ice::TIME_T_finalize_w_params
    #define T_copy       ice::TIME_T_copy

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

    DDS_TypeCode* BOOL_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode BOOL_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::BOOL", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  BOOL */

        if (is_initialized) {
            return &BOOL_g_tc;
        }

        BOOL_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_boolean;

        is_initialized = RTI_TRUE;

        return &BOOL_g_tc;
    }

    RTIBool BOOL_initialize(
        BOOL* sample) {
        return ice::BOOL_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool BOOL_initialize_ex(
        BOOL* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::BOOL_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool BOOL_initialize_w_params(
        BOOL* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initBoolean(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void BOOL_finalize(
        BOOL* sample)
    {

        ice::BOOL_finalize_ex(sample,RTI_TRUE);
    }

    void BOOL_finalize_ex(
        BOOL* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::BOOL_finalize_w_params(
            sample,&deallocParams);
    }

    void BOOL_finalize_w_params(
        BOOL* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void BOOL_finalize_optional_members(
        BOOL* sample, RTIBool deletePointers)
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

    RTIBool BOOL_copy(
        BOOL* dst,
        const BOOL* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyBoolean (
                dst, src)) { 
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
    * Configure and implement 'BOOL' sequence class.
    */
    #define T BOOL
    #define TSeq BOOLSeq

    #define T_initialize_w_params ice::BOOL_initialize_w_params

    #define T_finalize_w_params   ice::BOOL_finalize_w_params
    #define T_copy       ice::BOOL_copy

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

    DDS_TypeCode* OIDType_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode OIDType_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::OIDType", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  OIDType */

        if (is_initialized) {
            return &OIDType_g_tc;
        }

        OIDType_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &OIDType_g_tc;
    }

    RTIBool OIDType_initialize(
        OIDType* sample) {
        return ice::OIDType_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool OIDType_initialize_ex(
        OIDType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::OIDType_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool OIDType_initialize_w_params(
        OIDType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void OIDType_finalize(
        OIDType* sample)
    {

        ice::OIDType_finalize_ex(sample,RTI_TRUE);
    }

    void OIDType_finalize_ex(
        OIDType* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::OIDType_finalize_w_params(
            sample,&deallocParams);
    }

    void OIDType_finalize_w_params(
        OIDType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void OIDType_finalize_optional_members(
        OIDType* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool OIDType_copy(
        OIDType* dst,
        const OIDType* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'OIDType' sequence class.
    */
    #define T OIDType
    #define TSeq OIDTypeSeq

    #define T_initialize_w_params ice::OIDType_initialize_w_params

    #define T_finalize_w_params   ice::OIDType_finalize_w_params
    #define T_copy       ice::OIDType_copy

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

    DDS_TypeCode* PrivateOid_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode PrivateOid_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::PrivateOid", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  PrivateOid */

        if (is_initialized) {
            return &PrivateOid_g_tc;
        }

        PrivateOid_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &PrivateOid_g_tc;
    }

    RTIBool PrivateOid_initialize(
        PrivateOid* sample) {
        return ice::PrivateOid_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool PrivateOid_initialize_ex(
        PrivateOid* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::PrivateOid_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool PrivateOid_initialize_w_params(
        PrivateOid* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void PrivateOid_finalize(
        PrivateOid* sample)
    {

        ice::PrivateOid_finalize_ex(sample,RTI_TRUE);
    }

    void PrivateOid_finalize_ex(
        PrivateOid* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::PrivateOid_finalize_w_params(
            sample,&deallocParams);
    }

    void PrivateOid_finalize_w_params(
        PrivateOid* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void PrivateOid_finalize_optional_members(
        PrivateOid* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool PrivateOid_copy(
        PrivateOid* dst,
        const PrivateOid* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'PrivateOid' sequence class.
    */
    #define T PrivateOid
    #define TSeq PrivateOidSeq

    #define T_initialize_w_params ice::PrivateOid_initialize_w_params

    #define T_finalize_w_params   ice::PrivateOid_finalize_w_params
    #define T_copy       ice::PrivateOid_copy

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

    DDS_TypeCode* HANDLE_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode HANDLE_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::HANDLE", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  HANDLE */

        if (is_initialized) {
            return &HANDLE_g_tc;
        }

        HANDLE_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &HANDLE_g_tc;
    }

    RTIBool HANDLE_initialize(
        HANDLE* sample) {
        return ice::HANDLE_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool HANDLE_initialize_ex(
        HANDLE* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::HANDLE_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool HANDLE_initialize_w_params(
        HANDLE* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void HANDLE_finalize(
        HANDLE* sample)
    {

        ice::HANDLE_finalize_ex(sample,RTI_TRUE);
    }

    void HANDLE_finalize_ex(
        HANDLE* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::HANDLE_finalize_w_params(
            sample,&deallocParams);
    }

    void HANDLE_finalize_w_params(
        HANDLE* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void HANDLE_finalize_optional_members(
        HANDLE* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool HANDLE_copy(
        HANDLE* dst,
        const HANDLE* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'HANDLE' sequence class.
    */
    #define T HANDLE
    #define TSeq HANDLESeq

    #define T_initialize_w_params ice::HANDLE_initialize_w_params

    #define T_finalize_w_params   ice::HANDLE_finalize_w_params
    #define T_copy       ice::HANDLE_copy

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

    DDS_TypeCode* ICE_ID_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode ICE_ID_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAX_LEN_ICE_ID)));

        static DDS_TypeCode ICE_ID_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::ICE_ID", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  ICE_ID */

        if (is_initialized) {
            return &ICE_ID_g_tc;
        }

        ICE_ID_g_tc._data._typeCode =  (RTICdrTypeCode *)&ICE_ID_g_tc_string;

        is_initialized = RTI_TRUE;

        return &ICE_ID_g_tc;
    }

    RTIBool ICE_ID_initialize(
        ICE_ID* sample) {
        return ice::ICE_ID_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool ICE_ID_initialize_ex(
        ICE_ID* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ICE_ID_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ICE_ID_initialize_w_params(
        ICE_ID* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAX_LEN_ICE_ID)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void ICE_ID_finalize(
        ICE_ID* sample)
    {

        ice::ICE_ID_finalize_ex(sample,RTI_TRUE);
    }

    void ICE_ID_finalize_ex(
        ICE_ID* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ICE_ID_finalize_w_params(
            sample,&deallocParams);
    }

    void ICE_ID_finalize_w_params(
        ICE_ID* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void ICE_ID_finalize_optional_members(
        ICE_ID* sample, RTIBool deletePointers)
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

    RTIBool ICE_ID_copy(
        ICE_ID* dst,
        const ICE_ID* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAX_LEN_ICE_ID)) + 1, RTI_FALSE)){
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
    * Configure and implement 'ICE_ID' sequence class.
    */
    #define T ICE_ID
    #define TSeq ICE_IDSeq

    #define T_initialize_w_params ice::ICE_ID_initialize_w_params

    #define T_finalize_w_params   ice::ICE_ID_finalize_w_params
    #define T_copy       ice::ICE_ID_copy

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

    DDS_TypeCode* InstNumber_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode InstNumber_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::InstNumber", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  InstNumber */

        if (is_initialized) {
            return &InstNumber_g_tc;
        }

        InstNumber_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &InstNumber_g_tc;
    }

    RTIBool InstNumber_initialize(
        InstNumber* sample) {
        return ice::InstNumber_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool InstNumber_initialize_ex(
        InstNumber* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::InstNumber_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool InstNumber_initialize_w_params(
        InstNumber* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void InstNumber_finalize(
        InstNumber* sample)
    {

        ice::InstNumber_finalize_ex(sample,RTI_TRUE);
    }

    void InstNumber_finalize_ex(
        InstNumber* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::InstNumber_finalize_w_params(
            sample,&deallocParams);
    }

    void InstNumber_finalize_w_params(
        InstNumber* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void InstNumber_finalize_optional_members(
        InstNumber* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool InstNumber_copy(
        InstNumber* dst,
        const InstNumber* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'InstNumber' sequence class.
    */
    #define T InstNumber
    #define TSeq InstNumberSeq

    #define T_initialize_w_params ice::InstNumber_initialize_w_params

    #define T_finalize_w_params   ice::InstNumber_finalize_w_params
    #define T_copy       ice::InstNumber_copy

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

    DDS_TypeCode* FLOATType_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode FLOATType_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::FLOATType", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  FLOATType */

        if (is_initialized) {
            return &FLOATType_g_tc;
        }

        FLOATType_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;

        is_initialized = RTI_TRUE;

        return &FLOATType_g_tc;
    }

    RTIBool FLOATType_initialize(
        FLOATType* sample) {
        return ice::FLOATType_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool FLOATType_initialize_ex(
        FLOATType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::FLOATType_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool FLOATType_initialize_w_params(
        FLOATType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initFloat(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void FLOATType_finalize(
        FLOATType* sample)
    {

        ice::FLOATType_finalize_ex(sample,RTI_TRUE);
    }

    void FLOATType_finalize_ex(
        FLOATType* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::FLOATType_finalize_w_params(
            sample,&deallocParams);
    }

    void FLOATType_finalize_w_params(
        FLOATType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void FLOATType_finalize_optional_members(
        FLOATType* sample, RTIBool deletePointers)
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

    RTIBool FLOATType_copy(
        FLOATType* dst,
        const FLOATType* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyFloat (
                dst, src)) { 
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
    * Configure and implement 'FLOATType' sequence class.
    */
    #define T FLOATType
    #define TSeq FLOATTypeSeq

    #define T_initialize_w_params ice::FLOATType_initialize_w_params

    #define T_finalize_w_params   ice::FLOATType_finalize_w_params
    #define T_copy       ice::FLOATType_copy

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

    DDS_TypeCode* MdsContext_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode MdsContext_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::MdsContext", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  MdsContext */

        if (is_initialized) {
            return &MdsContext_g_tc;
        }

        MdsContext_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &MdsContext_g_tc;
    }

    RTIBool MdsContext_initialize(
        MdsContext* sample) {
        return ice::MdsContext_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool MdsContext_initialize_ex(
        MdsContext* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::MdsContext_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool MdsContext_initialize_w_params(
        MdsContext* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void MdsContext_finalize(
        MdsContext* sample)
    {

        ice::MdsContext_finalize_ex(sample,RTI_TRUE);
    }

    void MdsContext_finalize_ex(
        MdsContext* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::MdsContext_finalize_w_params(
            sample,&deallocParams);
    }

    void MdsContext_finalize_w_params(
        MdsContext* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void MdsContext_finalize_optional_members(
        MdsContext* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool MdsContext_copy(
        MdsContext* dst,
        const MdsContext* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'MdsContext' sequence class.
    */
    #define T MdsContext
    #define TSeq MdsContextSeq

    #define T_initialize_w_params ice::MdsContext_initialize_w_params

    #define T_finalize_w_params   ice::MdsContext_finalize_w_params
    #define T_copy       ice::MdsContext_copy

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
    const char *GLBHANDLETYPENAME = "ice::GLBHANDLE";

    DDS_TypeCode* GLBHANDLE_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member GLBHANDLE_g_tc_members[2]=
        {

            {
                (char *)"context_id",/* Member name */
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
                (char *)"handle",/* Member name */
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

        static DDS_TypeCode GLBHANDLE_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::GLBHANDLE", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                GLBHANDLE_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for GLBHANDLE*/

        if (is_initialized) {
            return &GLBHANDLE_g_tc;
        }

        GLBHANDLE_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::MdsContext_get_typecode();

        GLBHANDLE_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::HANDLE_get_typecode();

        is_initialized = RTI_TRUE;

        return &GLBHANDLE_g_tc;
    }

    RTIBool GLBHANDLE_initialize(
        GLBHANDLE* sample) {
        return ice::GLBHANDLE_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool GLBHANDLE_initialize_ex(
        GLBHANDLE* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::GLBHANDLE_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool GLBHANDLE_initialize_w_params(
        GLBHANDLE* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::MdsContext_initialize_w_params(&sample->context_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::HANDLE_initialize_w_params(&sample->handle,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void GLBHANDLE_finalize(
        GLBHANDLE* sample)
    {

        ice::GLBHANDLE_finalize_ex(sample,RTI_TRUE);
    }

    void GLBHANDLE_finalize_ex(
        GLBHANDLE* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::GLBHANDLE_finalize_w_params(
            sample,&deallocParams);
    }

    void GLBHANDLE_finalize_w_params(
        GLBHANDLE* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::MdsContext_finalize_w_params(&sample->context_id,deallocParams);

        ice::HANDLE_finalize_w_params(&sample->handle,deallocParams);

    }

    void GLBHANDLE_finalize_optional_members(
        GLBHANDLE* sample, RTIBool deletePointers)
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

        ice::MdsContext_finalize_optional_members(&sample->context_id, deallocParams->delete_pointers);
        ice::HANDLE_finalize_optional_members(&sample->handle, deallocParams->delete_pointers);
    }

    RTIBool GLBHANDLE_copy(
        GLBHANDLE* dst,
        const GLBHANDLE* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::MdsContext_copy(
                &dst->context_id,(const ice::MdsContext*)&src->context_id)) {
                return RTI_FALSE;
            } 
            if (!ice::HANDLE_copy(
                &dst->handle,(const ice::HANDLE*)&src->handle)) {
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
    * Configure and implement 'GLBHANDLE' sequence class.
    */
    #define T GLBHANDLE
    #define TSeq GLBHANDLESeq

    #define T_initialize_w_params ice::GLBHANDLE_initialize_w_params

    #define T_finalize_w_params   ice::GLBHANDLE_finalize_w_params
    #define T_copy       ice::GLBHANDLE_copy

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
    const char *ManagedObjectIdTYPENAME = "ice::ManagedObjectId";

    DDS_TypeCode* ManagedObjectId_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member ManagedObjectId_g_tc_members[2]=
        {

            {
                (char *)"m_obj_class",/* Member name */
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
                (char *)"m_obj_inst",/* Member name */
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

        static DDS_TypeCode ManagedObjectId_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::ManagedObjectId", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                ManagedObjectId_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for ManagedObjectId*/

        if (is_initialized) {
            return &ManagedObjectId_g_tc;
        }

        ManagedObjectId_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        ManagedObjectId_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::GLBHANDLE_get_typecode();

        is_initialized = RTI_TRUE;

        return &ManagedObjectId_g_tc;
    }

    RTIBool ManagedObjectId_initialize(
        ManagedObjectId* sample) {
        return ice::ManagedObjectId_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool ManagedObjectId_initialize_ex(
        ManagedObjectId* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ManagedObjectId_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ManagedObjectId_initialize_w_params(
        ManagedObjectId* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_initialize_w_params(&sample->m_obj_class,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::GLBHANDLE_initialize_w_params(&sample->m_obj_inst,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void ManagedObjectId_finalize(
        ManagedObjectId* sample)
    {

        ice::ManagedObjectId_finalize_ex(sample,RTI_TRUE);
    }

    void ManagedObjectId_finalize_ex(
        ManagedObjectId* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ManagedObjectId_finalize_w_params(
            sample,&deallocParams);
    }

    void ManagedObjectId_finalize_w_params(
        ManagedObjectId* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDType_finalize_w_params(&sample->m_obj_class,deallocParams);

        ice::GLBHANDLE_finalize_w_params(&sample->m_obj_inst,deallocParams);

    }

    void ManagedObjectId_finalize_optional_members(
        ManagedObjectId* sample, RTIBool deletePointers)
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

        ice::OIDType_finalize_optional_members(&sample->m_obj_class, deallocParams->delete_pointers);
        ice::GLBHANDLE_finalize_optional_members(&sample->m_obj_inst, deallocParams->delete_pointers);
    }

    RTIBool ManagedObjectId_copy(
        ManagedObjectId* dst,
        const ManagedObjectId* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDType_copy(
                &dst->m_obj_class,(const ice::OIDType*)&src->m_obj_class)) {
                return RTI_FALSE;
            } 
            if (!ice::GLBHANDLE_copy(
                &dst->m_obj_inst,(const ice::GLBHANDLE*)&src->m_obj_inst)) {
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
    * Configure and implement 'ManagedObjectId' sequence class.
    */
    #define T ManagedObjectId
    #define TSeq ManagedObjectIdSeq

    #define T_initialize_w_params ice::ManagedObjectId_initialize_w_params

    #define T_finalize_w_params   ice::ManagedObjectId_finalize_w_params
    #define T_copy       ice::ManagedObjectId_copy

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
    const char *NomPartitionTYPENAME = "ice::NomPartition";

    DDS_TypeCode* NomPartition_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member NomPartition_g_tc_members[13]=
        {

            {
                (char *)"nom_part_unspec",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_unspec, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_obj",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_obj, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_metric",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_metric, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_alert",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_alert, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_dim",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_dim, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_vattr",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_vattr, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_pgrp",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_pgrp, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_sites",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_sites, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_infrastruct",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_infrastruct, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_fef",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_fef, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_ecg_extn",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_ecg_extn, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_ext_nom",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_ext_nom, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"nom_part_priv",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                nom_part_priv, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode NomPartition_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::NomPartition", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                13, /* Number of members */
                NomPartition_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for NomPartition*/

        if (is_initialized) {
            return &NomPartition_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &NomPartition_g_tc;
    }

    RTIBool NomPartition_initialize(
        NomPartition* sample) {
        *sample = nom_part_unspec;
        return RTI_TRUE;
    }

    RTIBool NomPartition_initialize_ex(
        NomPartition* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::NomPartition_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool NomPartition_initialize_w_params(
        NomPartition* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = nom_part_unspec;
        return RTI_TRUE;
    }

    void NomPartition_finalize(
        NomPartition* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void NomPartition_finalize_ex(
        NomPartition* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::NomPartition_finalize_w_params(
            sample,&deallocParams);
    }

    void NomPartition_finalize_w_params(
        NomPartition* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void NomPartition_finalize_optional_members(
        NomPartition* sample, RTIBool deletePointers)
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

    RTIBool NomPartition_copy(
        NomPartition* dst,
        const NomPartition* src)
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
    * Configure and implement 'NomPartition' sequence class.
    */
    #define T NomPartition
    #define TSeq NomPartitionSeq

    #define T_initialize_w_params ice::NomPartition_initialize_w_params

    #define T_finalize_w_params   ice::NomPartition_finalize_w_params
    #define T_copy       ice::NomPartition_copy

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
    const char *TYPETYPENAME = "ice::TYPE";

    DDS_TypeCode* TYPE_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member TYPE_g_tc_members[2]=
        {

            {
                (char *)"partition",/* Member name */
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
                (char *)"code",/* Member name */
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

        static DDS_TypeCode TYPE_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::TYPE", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                TYPE_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for TYPE*/

        if (is_initialized) {
            return &TYPE_g_tc;
        }

        TYPE_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::NomPartition_get_typecode();

        TYPE_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        is_initialized = RTI_TRUE;

        return &TYPE_g_tc;
    }

    RTIBool TYPE_initialize(
        TYPE* sample) {
        return ice::TYPE_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool TYPE_initialize_ex(
        TYPE* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::TYPE_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool TYPE_initialize_w_params(
        TYPE* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::NomPartition_initialize_w_params(&sample->partition,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::OIDType_initialize_w_params(&sample->code,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void TYPE_finalize(
        TYPE* sample)
    {

        ice::TYPE_finalize_ex(sample,RTI_TRUE);
    }

    void TYPE_finalize_ex(
        TYPE* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::TYPE_finalize_w_params(
            sample,&deallocParams);
    }

    void TYPE_finalize_w_params(
        TYPE* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::NomPartition_finalize_w_params(&sample->partition,deallocParams);

        ice::OIDType_finalize_w_params(&sample->code,deallocParams);

    }

    void TYPE_finalize_optional_members(
        TYPE* sample, RTIBool deletePointers)
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

        ice::NomPartition_finalize_optional_members(&sample->partition, deallocParams->delete_pointers);
        ice::OIDType_finalize_optional_members(&sample->code, deallocParams->delete_pointers);
    }

    RTIBool TYPE_copy(
        TYPE* dst,
        const TYPE* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::NomPartition_copy(
                &dst->partition,(const ice::NomPartition*)&src->partition)) {
                return RTI_FALSE;
            } 
            if (!ice::OIDType_copy(
                &dst->code,(const ice::OIDType*)&src->code)) {
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
    * Configure and implement 'TYPE' sequence class.
    */
    #define T TYPE
    #define TSeq TYPESeq

    #define T_initialize_w_params ice::TYPE_initialize_w_params

    #define T_finalize_w_params   ice::TYPE_finalize_w_params
    #define T_copy       ice::TYPE_copy

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
    const char *TimespecTYPENAME = "ice::Timespec";

    DDS_TypeCode* Timespec_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Timespec_g_tc_members[2]=
        {

            {
                (char *)"seconds",/* Member name */
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
                (char *)"nanoseconds",/* Member name */
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

        static DDS_TypeCode Timespec_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Timespec", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                Timespec_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Timespec*/

        if (is_initialized) {
            return &Timespec_g_tc;
        }

        Timespec_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        Timespec_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        is_initialized = RTI_TRUE;

        return &Timespec_g_tc;
    }

    RTIBool Timespec_initialize(
        Timespec* sample) {
        return ice::Timespec_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Timespec_initialize_ex(
        Timespec* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Timespec_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Timespec_initialize_w_params(
        Timespec* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->seconds)) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->nanoseconds)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void Timespec_finalize(
        Timespec* sample)
    {

        ice::Timespec_finalize_ex(sample,RTI_TRUE);
    }

    void Timespec_finalize_ex(
        Timespec* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Timespec_finalize_w_params(
            sample,&deallocParams);
    }

    void Timespec_finalize_w_params(
        Timespec* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void Timespec_finalize_optional_members(
        Timespec* sample, RTIBool deletePointers)
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

    RTIBool Timespec_copy(
        Timespec* dst,
        const Timespec* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                &dst->seconds, &src->seconds)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyLong (
                &dst->nanoseconds, &src->nanoseconds)) { 
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
    * Configure and implement 'Timespec' sequence class.
    */
    #define T Timespec
    #define TSeq TimespecSeq

    #define T_initialize_w_params ice::Timespec_initialize_w_params

    #define T_finalize_w_params   ice::Timespec_finalize_w_params
    #define T_copy       ice::Timespec_copy

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
    const char *DurationTYPENAME = "ice::Duration";

    DDS_TypeCode* Duration_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Duration_g_tc_members[2]=
        {

            {
                (char *)"seconds",/* Member name */
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
                (char *)"nanoseconds",/* Member name */
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

        static DDS_TypeCode Duration_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Duration", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                Duration_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Duration*/

        if (is_initialized) {
            return &Duration_g_tc;
        }

        Duration_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        Duration_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

        is_initialized = RTI_TRUE;

        return &Duration_g_tc;
    }

    RTIBool Duration_initialize(
        Duration* sample) {
        return ice::Duration_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Duration_initialize_ex(
        Duration* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Duration_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Duration_initialize_w_params(
        Duration* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->seconds)) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(&sample->nanoseconds)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void Duration_finalize(
        Duration* sample)
    {

        ice::Duration_finalize_ex(sample,RTI_TRUE);
    }

    void Duration_finalize_ex(
        Duration* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Duration_finalize_w_params(
            sample,&deallocParams);
    }

    void Duration_finalize_w_params(
        Duration* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void Duration_finalize_optional_members(
        Duration* sample, RTIBool deletePointers)
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

    RTIBool Duration_copy(
        Duration* dst,
        const Duration* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                &dst->seconds, &src->seconds)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyLong (
                &dst->nanoseconds, &src->nanoseconds)) { 
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
    * Configure and implement 'Duration' sequence class.
    */
    #define T Duration
    #define TSeq DurationSeq

    #define T_initialize_w_params ice::Duration_initialize_w_params

    #define T_finalize_w_params   ice::Duration_finalize_w_params
    #define T_copy       ice::Duration_copy

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
    const char *DateTYPENAME = "ice::Date";

    DDS_TypeCode* Date_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Date_g_tc_members[4]=
        {

            {
                (char *)"century",/* Member name */
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
                (char *)"year",/* Member name */
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
                (char *)"month",/* Member name */
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
                (char *)"day",/* Member name */
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

        static DDS_TypeCode Date_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Date", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                Date_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Date*/

        if (is_initialized) {
            return &Date_g_tc;
        }

        Date_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        Date_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        Date_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        Date_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::INTU8_get_typecode();

        is_initialized = RTI_TRUE;

        return &Date_g_tc;
    }

    RTIBool Date_initialize(
        Date* sample) {
        return ice::Date_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Date_initialize_ex(
        Date* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Date_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Date_initialize_w_params(
        Date* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU8_initialize_w_params(&sample->century,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::INTU8_initialize_w_params(&sample->year,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::INTU8_initialize_w_params(&sample->month,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::INTU8_initialize_w_params(&sample->day,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Date_finalize(
        Date* sample)
    {

        ice::Date_finalize_ex(sample,RTI_TRUE);
    }

    void Date_finalize_ex(
        Date* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Date_finalize_w_params(
            sample,&deallocParams);
    }

    void Date_finalize_w_params(
        Date* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU8_finalize_w_params(&sample->century,deallocParams);

        ice::INTU8_finalize_w_params(&sample->year,deallocParams);

        ice::INTU8_finalize_w_params(&sample->month,deallocParams);

        ice::INTU8_finalize_w_params(&sample->day,deallocParams);

    }

    void Date_finalize_optional_members(
        Date* sample, RTIBool deletePointers)
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

        ice::INTU8_finalize_optional_members(&sample->century, deallocParams->delete_pointers);
        ice::INTU8_finalize_optional_members(&sample->year, deallocParams->delete_pointers);
        ice::INTU8_finalize_optional_members(&sample->month, deallocParams->delete_pointers);
        ice::INTU8_finalize_optional_members(&sample->day, deallocParams->delete_pointers);
    }

    RTIBool Date_copy(
        Date* dst,
        const Date* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU8_copy(
                &dst->century,(const ice::INTU8*)&src->century)) {
                return RTI_FALSE;
            } 
            if (!ice::INTU8_copy(
                &dst->year,(const ice::INTU8*)&src->year)) {
                return RTI_FALSE;
            } 
            if (!ice::INTU8_copy(
                &dst->month,(const ice::INTU8*)&src->month)) {
                return RTI_FALSE;
            } 
            if (!ice::INTU8_copy(
                &dst->day,(const ice::INTU8*)&src->day)) {
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
    * Configure and implement 'Date' sequence class.
    */
    #define T Date
    #define TSeq DateSeq

    #define T_initialize_w_params ice::Date_initialize_w_params

    #define T_finalize_w_params   ice::Date_finalize_w_params
    #define T_copy       ice::Date_copy

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
    const char *SimpleColorTYPENAME = "ice::SimpleColor";

    DDS_TypeCode* SimpleColor_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member SimpleColor_g_tc_members[8]=
        {

            {
                (char *)"col_black",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_black, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_red",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_red, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_green",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_green, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_yellow",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_yellow, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_blue",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_blue, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_magenta",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_magenta, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_cyan",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_cyan, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"col_white",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                col_white, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode SimpleColor_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::SimpleColor", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                8, /* Number of members */
                SimpleColor_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for SimpleColor*/

        if (is_initialized) {
            return &SimpleColor_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &SimpleColor_g_tc;
    }

    RTIBool SimpleColor_initialize(
        SimpleColor* sample) {
        *sample = col_black;
        return RTI_TRUE;
    }

    RTIBool SimpleColor_initialize_ex(
        SimpleColor* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::SimpleColor_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool SimpleColor_initialize_w_params(
        SimpleColor* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = col_black;
        return RTI_TRUE;
    }

    void SimpleColor_finalize(
        SimpleColor* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void SimpleColor_finalize_ex(
        SimpleColor* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::SimpleColor_finalize_w_params(
            sample,&deallocParams);
    }

    void SimpleColor_finalize_w_params(
        SimpleColor* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void SimpleColor_finalize_optional_members(
        SimpleColor* sample, RTIBool deletePointers)
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

    RTIBool SimpleColor_copy(
        SimpleColor* dst,
        const SimpleColor* src)
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
    * Configure and implement 'SimpleColor' sequence class.
    */
    #define T SimpleColor
    #define TSeq SimpleColorSeq

    #define T_initialize_w_params ice::SimpleColor_initialize_w_params

    #define T_finalize_w_params   ice::SimpleColor_finalize_w_params
    #define T_copy       ice::SimpleColor_copy

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
    const char *CharSetTYPENAME = "ice::CharSet";

    DDS_TypeCode* CharSet_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member CharSet_g_tc_members[23]=
        {

            {
                (char *)"charset_unspec",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_unspec, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_10646_ucs_2",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_10646_ucs_2, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_10646_ucs_4",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_10646_ucs_4, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_1",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_1, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_2",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_2, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_3",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_3, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_4",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_4, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_5",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_5, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_6",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_6, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_7",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_7, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_8",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_8, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_9",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_9, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_10",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_10, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_13",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_13, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_14",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_14, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_8859_15",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_8859_15, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_2022_kr",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_2022_kr, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_ks_c_5601",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_ks_c_5601, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_2022_jp",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_2022_jp, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_2022_jp_2",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_2022_jp_2, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_jis_x0208",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_jis_x0208, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_iso_2022_cn",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_iso_2022_cn, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"charset_gb_2312",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                charset_gb_2312, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode CharSet_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CharSet", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                23, /* Number of members */
                CharSet_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for CharSet*/

        if (is_initialized) {
            return &CharSet_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &CharSet_g_tc;
    }

    RTIBool CharSet_initialize(
        CharSet* sample) {
        *sample = charset_unspec;
        return RTI_TRUE;
    }

    RTIBool CharSet_initialize_ex(
        CharSet* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CharSet_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CharSet_initialize_w_params(
        CharSet* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = charset_unspec;
        return RTI_TRUE;
    }

    void CharSet_finalize(
        CharSet* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void CharSet_finalize_ex(
        CharSet* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CharSet_finalize_w_params(
            sample,&deallocParams);
    }

    void CharSet_finalize_w_params(
        CharSet* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CharSet_finalize_optional_members(
        CharSet* sample, RTIBool deletePointers)
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

    RTIBool CharSet_copy(
        CharSet* dst,
        const CharSet* src)
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
    * Configure and implement 'CharSet' sequence class.
    */
    #define T CharSet
    #define TSeq CharSetSeq

    #define T_initialize_w_params ice::CharSet_initialize_w_params

    #define T_finalize_w_params   ice::CharSet_finalize_w_params
    #define T_copy       ice::CharSet_copy

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

    DDS_TypeCode* StringFlags_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode StringFlags_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::StringFlags", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  StringFlags */

        if (is_initialized) {
            return &StringFlags_g_tc;
        }

        StringFlags_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &StringFlags_g_tc;
    }

    RTIBool StringFlags_initialize(
        StringFlags* sample) {
        return ice::StringFlags_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool StringFlags_initialize_ex(
        StringFlags* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::StringFlags_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool StringFlags_initialize_w_params(
        StringFlags* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    void StringFlags_finalize(
        StringFlags* sample)
    {

        ice::StringFlags_finalize_ex(sample,RTI_TRUE);
    }

    void StringFlags_finalize_ex(
        StringFlags* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::StringFlags_finalize_w_params(
            sample,&deallocParams);
    }

    void StringFlags_finalize_w_params(
        StringFlags* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void StringFlags_finalize_optional_members(
        StringFlags* sample, RTIBool deletePointers)
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

    RTIBool StringFlags_copy(
        StringFlags* dst,
        const StringFlags* src)
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
    * Configure and implement 'StringFlags' sequence class.
    */
    #define T StringFlags
    #define TSeq StringFlagsSeq

    #define T_initialize_w_params ice::StringFlags_initialize_w_params

    #define T_finalize_w_params   ice::StringFlags_finalize_w_params
    #define T_copy       ice::StringFlags_copy

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
    const char *StringFlagsBitsTYPENAME = "ice::StringFlagsBits";

    DDS_TypeCode* StringFlagsBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member StringFlagsBits_g_tc_members[1]=
        {

            {
                (char *)"str_flag_nt",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                str_flag_nt, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode StringFlagsBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::StringFlagsBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                1, /* Number of members */
                StringFlagsBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for StringFlagsBits*/

        if (is_initialized) {
            return &StringFlagsBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &StringFlagsBits_g_tc;
    }

    RTIBool StringFlagsBits_initialize(
        StringFlagsBits* sample) {
        *sample = str_flag_nt;
        return RTI_TRUE;
    }

    RTIBool StringFlagsBits_initialize_ex(
        StringFlagsBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::StringFlagsBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool StringFlagsBits_initialize_w_params(
        StringFlagsBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = str_flag_nt;
        return RTI_TRUE;
    }

    void StringFlagsBits_finalize(
        StringFlagsBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void StringFlagsBits_finalize_ex(
        StringFlagsBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::StringFlagsBits_finalize_w_params(
            sample,&deallocParams);
    }

    void StringFlagsBits_finalize_w_params(
        StringFlagsBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void StringFlagsBits_finalize_optional_members(
        StringFlagsBits* sample, RTIBool deletePointers)
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

    RTIBool StringFlagsBits_copy(
        StringFlagsBits* dst,
        const StringFlagsBits* src)
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
    * Configure and implement 'StringFlagsBits' sequence class.
    */
    #define T StringFlagsBits
    #define TSeq StringFlagsBitsSeq

    #define T_initialize_w_params ice::StringFlagsBits_initialize_w_params

    #define T_finalize_w_params   ice::StringFlagsBits_finalize_w_params
    #define T_copy       ice::StringFlagsBits_copy

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
    const char *StringSpecTYPENAME = "ice::StringSpec";

    DDS_TypeCode* StringSpec_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member StringSpec_g_tc_members[2]=
        {

            {
                (char *)"str_max_len",/* Member name */
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
                (char *)"str_flags",/* Member name */
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

        static DDS_TypeCode StringSpec_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::StringSpec", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                StringSpec_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for StringSpec*/

        if (is_initialized) {
            return &StringSpec_g_tc;
        }

        StringSpec_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::INTU16_get_typecode();

        StringSpec_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::StringFlags_get_typecode();

        is_initialized = RTI_TRUE;

        return &StringSpec_g_tc;
    }

    RTIBool StringSpec_initialize(
        StringSpec* sample) {
        return ice::StringSpec_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool StringSpec_initialize_ex(
        StringSpec* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::StringSpec_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool StringSpec_initialize_w_params(
        StringSpec* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(&sample->str_max_len,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::StringFlags_initialize_w_params(&sample->str_flags,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void StringSpec_finalize(
        StringSpec* sample)
    {

        ice::StringSpec_finalize_ex(sample,RTI_TRUE);
    }

    void StringSpec_finalize_ex(
        StringSpec* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::StringSpec_finalize_w_params(
            sample,&deallocParams);
    }

    void StringSpec_finalize_w_params(
        StringSpec* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(&sample->str_max_len,deallocParams);

        ice::StringFlags_finalize_w_params(&sample->str_flags,deallocParams);

    }

    void StringSpec_finalize_optional_members(
        StringSpec* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(&sample->str_max_len, deallocParams->delete_pointers);
        ice::StringFlags_finalize_optional_members(&sample->str_flags, deallocParams->delete_pointers);
    }

    RTIBool StringSpec_copy(
        StringSpec* dst,
        const StringSpec* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                &dst->str_max_len,(const ice::INTU16*)&src->str_max_len)) {
                return RTI_FALSE;
            } 
            if (!ice::StringFlags_copy(
                &dst->str_flags,(const ice::StringFlags*)&src->str_flags)) {
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
    * Configure and implement 'StringSpec' sequence class.
    */
    #define T StringSpec
    #define TSeq StringSpecSeq

    #define T_initialize_w_params ice::StringSpec_initialize_w_params

    #define T_finalize_w_params   ice::StringSpec_finalize_w_params
    #define T_copy       ice::StringSpec_copy

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
    const char *LocaleTYPENAME = "ice::Locale";

    DDS_TypeCode* Locale_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Locale_g_tc_members[4]=
        {

            {
                (char *)"language",/* Member name */
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
                (char *)"country",/* Member name */
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
                (char *)"charset",/* Member name */
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
                (char *)"str_spec",/* Member name */
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

        static DDS_TypeCode Locale_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Locale", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                Locale_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Locale*/

        if (is_initialized) {
            return &Locale_g_tc;
        }

        Locale_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::INTU32_get_typecode();

        Locale_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::INTU32_get_typecode();

        Locale_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::CharSet_get_typecode();

        Locale_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::StringSpec_get_typecode();

        is_initialized = RTI_TRUE;

        return &Locale_g_tc;
    }

    RTIBool Locale_initialize(
        Locale* sample) {
        return ice::Locale_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Locale_initialize_ex(
        Locale* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Locale_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Locale_initialize_w_params(
        Locale* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU32_initialize_w_params(&sample->language,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::INTU32_initialize_w_params(&sample->country,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::CharSet_initialize_w_params(&sample->charset,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::StringSpec_initialize_w_params(&sample->str_spec,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Locale_finalize(
        Locale* sample)
    {

        ice::Locale_finalize_ex(sample,RTI_TRUE);
    }

    void Locale_finalize_ex(
        Locale* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Locale_finalize_w_params(
            sample,&deallocParams);
    }

    void Locale_finalize_w_params(
        Locale* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU32_finalize_w_params(&sample->language,deallocParams);

        ice::INTU32_finalize_w_params(&sample->country,deallocParams);

        ice::CharSet_finalize_w_params(&sample->charset,deallocParams);

        ice::StringSpec_finalize_w_params(&sample->str_spec,deallocParams);

    }

    void Locale_finalize_optional_members(
        Locale* sample, RTIBool deletePointers)
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

        ice::INTU32_finalize_optional_members(&sample->language, deallocParams->delete_pointers);
        ice::INTU32_finalize_optional_members(&sample->country, deallocParams->delete_pointers);
        ice::CharSet_finalize_optional_members(&sample->charset, deallocParams->delete_pointers);
        ice::StringSpec_finalize_optional_members(&sample->str_spec, deallocParams->delete_pointers);
    }

    RTIBool Locale_copy(
        Locale* dst,
        const Locale* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU32_copy(
                &dst->language,(const ice::INTU32*)&src->language)) {
                return RTI_FALSE;
            } 
            if (!ice::INTU32_copy(
                &dst->country,(const ice::INTU32*)&src->country)) {
                return RTI_FALSE;
            } 
            if (!ice::CharSet_copy(
                &dst->charset,(const ice::CharSet*)&src->charset)) {
                return RTI_FALSE;
            } 
            if (!ice::StringSpec_copy(
                &dst->str_spec,(const ice::StringSpec*)&src->str_spec)) {
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
    * Configure and implement 'Locale' sequence class.
    */
    #define T Locale
    #define TSeq LocaleSeq

    #define T_initialize_w_params ice::Locale_initialize_w_params

    #define T_finalize_w_params   ice::Locale_finalize_w_params
    #define T_copy       ice::Locale_copy

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
    const char *ExtNomenRefTYPENAME = "ice::ExtNomenRef";

    DDS_TypeCode* ExtNomenRef_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode ExtNomenRef_g_tc_nomenclature_code_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode_Member ExtNomenRef_g_tc_members[2]=
        {

            {
                (char *)"nomenclature_id",/* Member name */
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
                (char *)"nomenclature_code",/* Member name */
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

        static DDS_TypeCode ExtNomenRef_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::ExtNomenRef", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                ExtNomenRef_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for ExtNomenRef*/

        if (is_initialized) {
            return &ExtNomenRef_g_tc;
        }

        ExtNomenRef_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        ExtNomenRef_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&ExtNomenRef_g_tc_nomenclature_code_string;

        is_initialized = RTI_TRUE;

        return &ExtNomenRef_g_tc;
    }

    RTIBool ExtNomenRef_initialize(
        ExtNomenRef* sample) {
        return ice::ExtNomenRef_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool ExtNomenRef_initialize_ex(
        ExtNomenRef* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ExtNomenRef_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ExtNomenRef_initialize_w_params(
        ExtNomenRef* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_initialize_w_params(&sample->nomenclature_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->nomenclature_code= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->nomenclature_code == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->nomenclature_code!= NULL) { 
                sample->nomenclature_code[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void ExtNomenRef_finalize(
        ExtNomenRef* sample)
    {

        ice::ExtNomenRef_finalize_ex(sample,RTI_TRUE);
    }

    void ExtNomenRef_finalize_ex(
        ExtNomenRef* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ExtNomenRef_finalize_w_params(
            sample,&deallocParams);
    }

    void ExtNomenRef_finalize_w_params(
        ExtNomenRef* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDType_finalize_w_params(&sample->nomenclature_id,deallocParams);

        if (sample->nomenclature_code != NULL) {
            DDS_String_free(sample->nomenclature_code);
            sample->nomenclature_code=NULL;

        }
    }

    void ExtNomenRef_finalize_optional_members(
        ExtNomenRef* sample, RTIBool deletePointers)
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

        ice::OIDType_finalize_optional_members(&sample->nomenclature_id, deallocParams->delete_pointers);
    }

    RTIBool ExtNomenRef_copy(
        ExtNomenRef* dst,
        const ExtNomenRef* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDType_copy(
                &dst->nomenclature_id,(const ice::OIDType*)&src->nomenclature_id)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->nomenclature_code, src->nomenclature_code, 
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
    * Configure and implement 'ExtNomenRef' sequence class.
    */
    #define T ExtNomenRef
    #define TSeq ExtNomenRefSeq

    #define T_initialize_w_params ice::ExtNomenRef_initialize_w_params

    #define T_finalize_w_params   ice::ExtNomenRef_finalize_w_params
    #define T_copy       ice::ExtNomenRef_copy

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
    const char *SystemModelTYPENAME = "ice::SystemModel";

    DDS_TypeCode* SystemModel_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode SystemModel_g_tc_manufacturer_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MEDIUM_STRING_LEN)));
        static DDS_TypeCode SystemModel_g_tc_model_number_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MEDIUM_STRING_LEN)));
        static DDS_TypeCode_Member SystemModel_g_tc_members[2]=
        {

            {
                (char *)"manufacturer",/* Member name */
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
                (char *)"model_number",/* Member name */
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

        static DDS_TypeCode SystemModel_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::SystemModel", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                SystemModel_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for SystemModel*/

        if (is_initialized) {
            return &SystemModel_g_tc;
        }

        SystemModel_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&SystemModel_g_tc_manufacturer_string;

        SystemModel_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&SystemModel_g_tc_model_number_string;

        is_initialized = RTI_TRUE;

        return &SystemModel_g_tc;
    }

    RTIBool SystemModel_initialize(
        SystemModel* sample) {
        return ice::SystemModel_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool SystemModel_initialize_ex(
        SystemModel* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::SystemModel_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool SystemModel_initialize_w_params(
        SystemModel* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            sample->manufacturer= DDS_String_alloc (((ice::MEDIUM_STRING_LEN)));
            if (sample->manufacturer == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->manufacturer!= NULL) { 
                sample->manufacturer[0] = '\0';
            }
        }

        if (allocParams->allocate_memory){
            sample->model_number= DDS_String_alloc (((ice::MEDIUM_STRING_LEN)));
            if (sample->model_number == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->model_number!= NULL) { 
                sample->model_number[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void SystemModel_finalize(
        SystemModel* sample)
    {

        ice::SystemModel_finalize_ex(sample,RTI_TRUE);
    }

    void SystemModel_finalize_ex(
        SystemModel* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::SystemModel_finalize_w_params(
            sample,&deallocParams);
    }

    void SystemModel_finalize_w_params(
        SystemModel* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if (sample->manufacturer != NULL) {
            DDS_String_free(sample->manufacturer);
            sample->manufacturer=NULL;

        }
        if (sample->model_number != NULL) {
            DDS_String_free(sample->model_number);
            sample->model_number=NULL;

        }
    }

    void SystemModel_finalize_optional_members(
        SystemModel* sample, RTIBool deletePointers)
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

    RTIBool SystemModel_copy(
        SystemModel* dst,
        const SystemModel* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &dst->manufacturer, src->manufacturer, 
                ((ice::MEDIUM_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!RTICdrType_copyStringEx (
                &dst->model_number, src->model_number, 
                ((ice::MEDIUM_STRING_LEN)) + 1, RTI_FALSE)){
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
    * Configure and implement 'SystemModel' sequence class.
    */
    #define T SystemModel
    #define TSeq SystemModelSeq

    #define T_initialize_w_params ice::SystemModel_initialize_w_params

    #define T_finalize_w_params   ice::SystemModel_finalize_w_params
    #define T_copy       ice::SystemModel_copy

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
    const char *ProdSpecTypeTYPENAME = "ice::ProdSpecType";

    DDS_TypeCode* ProdSpecType_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member ProdSpecType_g_tc_members[9]=
        {

            {
                (char *)"unspecified",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                unspecified, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"serial_number",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                serial_number, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"part_number",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                part_number, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"hw_revision",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                hw_revision, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"sw_revision",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                sw_revision, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"fw_revision",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                fw_revision, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"protocol_revision",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                protocol_revision, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"prod_spec_gmdn",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                prod_spec_gmdn, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"prod_spec_udi",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                prod_spec_udi, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode ProdSpecType_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::ProdSpecType", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                9, /* Number of members */
                ProdSpecType_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for ProdSpecType*/

        if (is_initialized) {
            return &ProdSpecType_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &ProdSpecType_g_tc;
    }

    RTIBool ProdSpecType_initialize(
        ProdSpecType* sample) {
        *sample = unspecified;
        return RTI_TRUE;
    }

    RTIBool ProdSpecType_initialize_ex(
        ProdSpecType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ProdSpecType_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ProdSpecType_initialize_w_params(
        ProdSpecType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = unspecified;
        return RTI_TRUE;
    }

    void ProdSpecType_finalize(
        ProdSpecType* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void ProdSpecType_finalize_ex(
        ProdSpecType* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ProdSpecType_finalize_w_params(
            sample,&deallocParams);
    }

    void ProdSpecType_finalize_w_params(
        ProdSpecType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void ProdSpecType_finalize_optional_members(
        ProdSpecType* sample, RTIBool deletePointers)
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

    RTIBool ProdSpecType_copy(
        ProdSpecType* dst,
        const ProdSpecType* src)
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
    * Configure and implement 'ProdSpecType' sequence class.
    */
    #define T ProdSpecType
    #define TSeq ProdSpecTypeSeq

    #define T_initialize_w_params ice::ProdSpecType_initialize_w_params

    #define T_finalize_w_params   ice::ProdSpecType_finalize_w_params
    #define T_copy       ice::ProdSpecType_copy

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
    const char *ProdSpecEntryTYPENAME = "ice::ProdSpecEntry";

    DDS_TypeCode* ProdSpecEntry_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode ProdSpecEntry_g_tc_prod_spec_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONG_STRING_LEN)));
        static DDS_TypeCode_Member ProdSpecEntry_g_tc_members[3]=
        {

            {
                (char *)"spec_type",/* Member name */
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
                (char *)"component_id",/* Member name */
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
                (char *)"prod_spec",/* Member name */
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

        static DDS_TypeCode ProdSpecEntry_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::ProdSpecEntry", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                3, /* Number of members */
                ProdSpecEntry_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for ProdSpecEntry*/

        if (is_initialized) {
            return &ProdSpecEntry_g_tc;
        }

        ProdSpecEntry_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::ProdSpecType_get_typecode();

        ProdSpecEntry_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::PrivateOid_get_typecode();

        ProdSpecEntry_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&ProdSpecEntry_g_tc_prod_spec_string;

        is_initialized = RTI_TRUE;

        return &ProdSpecEntry_g_tc;
    }

    RTIBool ProdSpecEntry_initialize(
        ProdSpecEntry* sample) {
        return ice::ProdSpecEntry_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool ProdSpecEntry_initialize_ex(
        ProdSpecEntry* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ProdSpecEntry_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ProdSpecEntry_initialize_w_params(
        ProdSpecEntry* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::ProdSpecType_initialize_w_params(&sample->spec_type,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::PrivateOid_initialize_w_params(&sample->component_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->prod_spec= DDS_String_alloc (((ice::LONG_STRING_LEN)));
            if (sample->prod_spec == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->prod_spec!= NULL) { 
                sample->prod_spec[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void ProdSpecEntry_finalize(
        ProdSpecEntry* sample)
    {

        ice::ProdSpecEntry_finalize_ex(sample,RTI_TRUE);
    }

    void ProdSpecEntry_finalize_ex(
        ProdSpecEntry* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ProdSpecEntry_finalize_w_params(
            sample,&deallocParams);
    }

    void ProdSpecEntry_finalize_w_params(
        ProdSpecEntry* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::ProdSpecType_finalize_w_params(&sample->spec_type,deallocParams);

        ice::PrivateOid_finalize_w_params(&sample->component_id,deallocParams);

        if (sample->prod_spec != NULL) {
            DDS_String_free(sample->prod_spec);
            sample->prod_spec=NULL;

        }
    }

    void ProdSpecEntry_finalize_optional_members(
        ProdSpecEntry* sample, RTIBool deletePointers)
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

        ice::ProdSpecType_finalize_optional_members(&sample->spec_type, deallocParams->delete_pointers);
        ice::PrivateOid_finalize_optional_members(&sample->component_id, deallocParams->delete_pointers);
    }

    RTIBool ProdSpecEntry_copy(
        ProdSpecEntry* dst,
        const ProdSpecEntry* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::ProdSpecType_copy(
                &dst->spec_type,(const ice::ProdSpecType*)&src->spec_type)) {
                return RTI_FALSE;
            } 
            if (!ice::PrivateOid_copy(
                &dst->component_id,(const ice::PrivateOid*)&src->component_id)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->prod_spec, src->prod_spec, 
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
    * Configure and implement 'ProdSpecEntry' sequence class.
    */
    #define T ProdSpecEntry
    #define TSeq ProdSpecEntrySeq

    #define T_initialize_w_params ice::ProdSpecEntry_initialize_w_params

    #define T_finalize_w_params   ice::ProdSpecEntry_finalize_w_params
    #define T_copy       ice::ProdSpecEntry_copy

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

    DDS_TypeCode* ProductionSpec_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode ProductionSpec_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((100),NULL);

        static DDS_TypeCode ProductionSpec_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::ProductionSpec", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  ProductionSpec */

        if (is_initialized) {
            return &ProductionSpec_g_tc;
        }

        ProductionSpec_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)ice::ProdSpecEntry_get_typecode();

        ProductionSpec_g_tc._data._typeCode =  (RTICdrTypeCode *)& ProductionSpec_g_tc_sequence;

        is_initialized = RTI_TRUE;

        return &ProductionSpec_g_tc;
    }

    RTIBool ProductionSpec_initialize(
        ProductionSpec* sample) {
        return ice::ProductionSpec_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool ProductionSpec_initialize_ex(
        ProductionSpec* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::ProductionSpec_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool ProductionSpec_initialize_w_params(
        ProductionSpec* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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
            ice::ProdSpecEntrySeq_initialize(sample );
            ice::ProdSpecEntrySeq_set_element_allocation_params(sample ,allocParams);
            ice::ProdSpecEntrySeq_set_absolute_maximum(sample , (100));
            if (!ice::ProdSpecEntrySeq_set_maximum(sample, (100))) {
                return RTI_FALSE;
            }
        } else { 
            ice::ProdSpecEntrySeq_set_length(sample, 0);
        }
        return RTI_TRUE;
    }

    void ProductionSpec_finalize(
        ProductionSpec* sample)
    {

        ice::ProductionSpec_finalize_ex(sample,RTI_TRUE);
    }

    void ProductionSpec_finalize_ex(
        ProductionSpec* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::ProductionSpec_finalize_w_params(
            sample,&deallocParams);
    }

    void ProductionSpec_finalize_w_params(
        ProductionSpec* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::ProdSpecEntrySeq_set_element_deallocation_params(
            sample,deallocParams);
        ice::ProdSpecEntrySeq_finalize(sample);

    }

    void ProductionSpec_finalize_optional_members(
        ProductionSpec* sample, RTIBool deletePointers)
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
            length = ice::ProdSpecEntrySeq_get_length(
                sample);

            for (i = 0; i < length; i++) {
                ice::ProdSpecEntry_finalize_optional_members(
                    ice::ProdSpecEntrySeq_get_reference(
                        sample, i), deallocParams->delete_pointers);
            }
        }  

    }

    RTIBool ProductionSpec_copy(
        ProductionSpec* dst,
        const ProductionSpec* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::ProdSpecEntrySeq_copy(dst ,
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
    * Configure and implement 'ProductionSpec' sequence class.
    */
    #define T ProductionSpec
    #define TSeq ProductionSpecSeq

    #define T_initialize_w_params ice::ProductionSpec_initialize_w_params

    #define T_finalize_w_params   ice::ProductionSpec_finalize_w_params
    #define T_copy       ice::ProductionSpec_copy

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

    DDS_TypeCode* CurLimAlStat_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CurLimAlStat_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CurLimAlStat", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CurLimAlStat */

        if (is_initialized) {
            return &CurLimAlStat_g_tc;
        }

        CurLimAlStat_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::BITS16_get_typecode();

        is_initialized = RTI_TRUE;

        return &CurLimAlStat_g_tc;
    }

    RTIBool CurLimAlStat_initialize(
        CurLimAlStat* sample) {
        return ice::CurLimAlStat_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CurLimAlStat_initialize_ex(
        CurLimAlStat* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CurLimAlStat_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CurLimAlStat_initialize_w_params(
        CurLimAlStat* sample, const struct DDS_TypeAllocationParams_t * allocParams)
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

    void CurLimAlStat_finalize(
        CurLimAlStat* sample)
    {

        ice::CurLimAlStat_finalize_ex(sample,RTI_TRUE);
    }

    void CurLimAlStat_finalize_ex(
        CurLimAlStat* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CurLimAlStat_finalize_w_params(
            sample,&deallocParams);
    }

    void CurLimAlStat_finalize_w_params(
        CurLimAlStat* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::BITS16_finalize_w_params(sample,deallocParams);

    }

    void CurLimAlStat_finalize_optional_members(
        CurLimAlStat* sample, RTIBool deletePointers)
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

    RTIBool CurLimAlStat_copy(
        CurLimAlStat* dst,
        const CurLimAlStat* src)
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
    * Configure and implement 'CurLimAlStat' sequence class.
    */
    #define T CurLimAlStat
    #define TSeq CurLimAlStatSeq

    #define T_initialize_w_params ice::CurLimAlStat_initialize_w_params

    #define T_finalize_w_params   ice::CurLimAlStat_finalize_w_params
    #define T_copy       ice::CurLimAlStat_copy

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
    const char *CurLimAlStatBitsTYPENAME = "ice::CurLimAlStatBits";

    DDS_TypeCode* CurLimAlStatBits_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member CurLimAlStatBits_g_tc_members[3]=
        {

            {
                (char *)"lim_alert_off",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                lim_alert_off, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"lim_low_off",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                lim_low_off, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"lim_high_off",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                lim_high_off, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode CurLimAlStatBits_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CurLimAlStatBits", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                3, /* Number of members */
                CurLimAlStatBits_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for CurLimAlStatBits*/

        if (is_initialized) {
            return &CurLimAlStatBits_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &CurLimAlStatBits_g_tc;
    }

    RTIBool CurLimAlStatBits_initialize(
        CurLimAlStatBits* sample) {
        *sample = lim_alert_off;
        return RTI_TRUE;
    }

    RTIBool CurLimAlStatBits_initialize_ex(
        CurLimAlStatBits* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CurLimAlStatBits_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CurLimAlStatBits_initialize_w_params(
        CurLimAlStatBits* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = lim_alert_off;
        return RTI_TRUE;
    }

    void CurLimAlStatBits_finalize(
        CurLimAlStatBits* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void CurLimAlStatBits_finalize_ex(
        CurLimAlStatBits* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CurLimAlStatBits_finalize_w_params(
            sample,&deallocParams);
    }

    void CurLimAlStatBits_finalize_w_params(
        CurLimAlStatBits* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CurLimAlStatBits_finalize_optional_members(
        CurLimAlStatBits* sample, RTIBool deletePointers)
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

    RTIBool CurLimAlStatBits_copy(
        CurLimAlStatBits* dst,
        const CurLimAlStatBits* src)
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
    * Configure and implement 'CurLimAlStatBits' sequence class.
    */
    #define T CurLimAlStatBits
    #define TSeq CurLimAlStatBitsSeq

    #define T_initialize_w_params ice::CurLimAlStatBits_initialize_w_params

    #define T_finalize_w_params   ice::CurLimAlStatBits_finalize_w_params
    #define T_copy       ice::CurLimAlStatBits_copy

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
    const char *CurLimAlValTYPENAME = "ice::CurLimAlVal";

    DDS_TypeCode* CurLimAlVal_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member CurLimAlVal_g_tc_members[2]=
        {

            {
                (char *)"lower",/* Member name */
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
                (char *)"upper",/* Member name */
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

        static DDS_TypeCode CurLimAlVal_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CurLimAlVal", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                CurLimAlVal_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for CurLimAlVal*/

        if (is_initialized) {
            return &CurLimAlVal_g_tc;
        }

        CurLimAlVal_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        CurLimAlVal_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::FLOATType_get_typecode();

        is_initialized = RTI_TRUE;

        return &CurLimAlVal_g_tc;
    }

    RTIBool CurLimAlVal_initialize(
        CurLimAlVal* sample) {
        return ice::CurLimAlVal_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CurLimAlVal_initialize_ex(
        CurLimAlVal* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CurLimAlVal_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CurLimAlVal_initialize_w_params(
        CurLimAlVal* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::FLOATType_initialize_w_params(&sample->lower,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::FLOATType_initialize_w_params(&sample->upper,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void CurLimAlVal_finalize(
        CurLimAlVal* sample)
    {

        ice::CurLimAlVal_finalize_ex(sample,RTI_TRUE);
    }

    void CurLimAlVal_finalize_ex(
        CurLimAlVal* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CurLimAlVal_finalize_w_params(
            sample,&deallocParams);
    }

    void CurLimAlVal_finalize_w_params(
        CurLimAlVal* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::FLOATType_finalize_w_params(&sample->lower,deallocParams);

        ice::FLOATType_finalize_w_params(&sample->upper,deallocParams);

    }

    void CurLimAlVal_finalize_optional_members(
        CurLimAlVal* sample, RTIBool deletePointers)
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

        ice::FLOATType_finalize_optional_members(&sample->lower, deallocParams->delete_pointers);
        ice::FLOATType_finalize_optional_members(&sample->upper, deallocParams->delete_pointers);
    }

    RTIBool CurLimAlVal_copy(
        CurLimAlVal* dst,
        const CurLimAlVal* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::FLOATType_copy(
                &dst->lower,(const ice::FLOATType*)&src->lower)) {
                return RTI_FALSE;
            } 
            if (!ice::FLOATType_copy(
                &dst->upper,(const ice::FLOATType*)&src->upper)) {
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
    * Configure and implement 'CurLimAlVal' sequence class.
    */
    #define T CurLimAlVal
    #define TSeq CurLimAlValSeq

    #define T_initialize_w_params ice::CurLimAlVal_initialize_w_params

    #define T_finalize_w_params   ice::CurLimAlVal_finalize_w_params
    #define T_copy       ice::CurLimAlVal_copy

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
    const char *EventReportTYPENAME = "ice::EventReport";

    DDS_TypeCode* EventReport_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member EventReport_g_tc_members[2]=
        {

            {
                (char *)"object_class",/* Member name */
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
                (char *)"object_instance",/* Member name */
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
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode EventReport_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::EventReport", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                EventReport_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for EventReport*/

        if (is_initialized) {
            return &EventReport_g_tc;
        }

        EventReport_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::OIDType_get_typecode();

        EventReport_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::HANDLE_get_typecode();

        is_initialized = RTI_TRUE;

        return &EventReport_g_tc;
    }

    RTIBool EventReport_initialize(
        EventReport* sample) {
        return ice::EventReport_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool EventReport_initialize_ex(
        EventReport* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EventReport_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EventReport_initialize_w_params(
        EventReport* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::OIDType_initialize_w_params(&sample->object_class,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::HANDLE_initialize_w_params(&sample->object_instance,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void EventReport_finalize(
        EventReport* sample)
    {

        ice::EventReport_finalize_ex(sample,RTI_TRUE);
    }

    void EventReport_finalize_ex(
        EventReport* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EventReport_finalize_w_params(
            sample,&deallocParams);
    }

    void EventReport_finalize_w_params(
        EventReport* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::OIDType_finalize_w_params(&sample->object_class,deallocParams);

        ice::HANDLE_finalize_w_params(&sample->object_instance,deallocParams);

    }

    void EventReport_finalize_optional_members(
        EventReport* sample, RTIBool deletePointers)
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

        ice::OIDType_finalize_optional_members(&sample->object_class, deallocParams->delete_pointers);
        ice::HANDLE_finalize_optional_members(&sample->object_instance, deallocParams->delete_pointers);
    }

    RTIBool EventReport_copy(
        EventReport* dst,
        const EventReport* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::OIDType_copy(
                &dst->object_class,(const ice::OIDType*)&src->object_class)) {
                return RTI_FALSE;
            } 
            if (!ice::HANDLE_copy(
                &dst->object_instance,(const ice::HANDLE*)&src->object_instance)) {
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
    * Configure and implement 'EventReport' sequence class.
    */
    #define T EventReport
    #define TSeq EventReportSeq

    #define T_initialize_w_params ice::EventReport_initialize_w_params

    #define T_finalize_w_params   ice::EventReport_finalize_w_params
    #define T_copy       ice::EventReport_copy

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
    const char *CareActivityCategoryTYPENAME = "ice::CareActivityCategory";

    DDS_TypeCode* CareActivityCategory_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member CareActivityCategory_g_tc_members[8]=
        {

            {
                (char *)"acat_unknown",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_unknown, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_diet",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_diet, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_drug",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_drug, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_encounter",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_encounter, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_observation",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_observation, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_procedure",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_procedure, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_supply",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_supply, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"acat_other",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                acat_other, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode CareActivityCategory_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CareActivityCategory", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                8, /* Number of members */
                CareActivityCategory_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for CareActivityCategory*/

        if (is_initialized) {
            return &CareActivityCategory_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &CareActivityCategory_g_tc;
    }

    RTIBool CareActivityCategory_initialize(
        CareActivityCategory* sample) {
        *sample = acat_unknown;
        return RTI_TRUE;
    }

    RTIBool CareActivityCategory_initialize_ex(
        CareActivityCategory* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CareActivityCategory_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CareActivityCategory_initialize_w_params(
        CareActivityCategory* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = acat_unknown;
        return RTI_TRUE;
    }

    void CareActivityCategory_finalize(
        CareActivityCategory* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void CareActivityCategory_finalize_ex(
        CareActivityCategory* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CareActivityCategory_finalize_w_params(
            sample,&deallocParams);
    }

    void CareActivityCategory_finalize_w_params(
        CareActivityCategory* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CareActivityCategory_finalize_optional_members(
        CareActivityCategory* sample, RTIBool deletePointers)
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

    RTIBool CareActivityCategory_copy(
        CareActivityCategory* dst,
        const CareActivityCategory* src)
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
    * Configure and implement 'CareActivityCategory' sequence class.
    */
    #define T CareActivityCategory
    #define TSeq CareActivityCategorySeq

    #define T_initialize_w_params ice::CareActivityCategory_initialize_w_params

    #define T_finalize_w_params   ice::CareActivityCategory_finalize_w_params
    #define T_copy       ice::CareActivityCategory_copy

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

    DDS_TypeCode* HostId_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode HostId_g_tc_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,6, NULL,NULL);

        static DDS_TypeCode HostId_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::HostId", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  HostId */

        if (is_initialized) {
            return &HostId_g_tc;
        }

        HostId_g_tc_array._data._typeCode =(RTICdrTypeCode *)ice::OCTET_get_typecode();

        HostId_g_tc._data._typeCode =  (RTICdrTypeCode *)& HostId_g_tc_array;

        is_initialized = RTI_TRUE;

        return &HostId_g_tc;
    }

    RTIBool HostId_initialize(
        HostId* sample) {
        return ice::HostId_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool HostId_initialize_ex(
        HostId* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::HostId_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool HostId_initialize_w_params(
        HostId* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) sample[0];

            for (i = 0; i < (int) ((6)); ++i, ++elem) {
                if (!ice::OCTET_initialize_w_params(elem,allocParams)) {
                    return RTI_FALSE;
                }
            }
        }
        return RTI_TRUE;
    }

    void HostId_finalize(
        HostId* sample)
    {

        ice::HostId_finalize_ex(sample,RTI_TRUE);
    }

    void HostId_finalize_ex(
        HostId* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::HostId_finalize_w_params(
            sample,&deallocParams);
    }

    void HostId_finalize_w_params(
        HostId* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) sample[0];

            for (i = 0; i < (int) ((6)); ++i, ++elem) {
                ice::OCTET_finalize_w_params(elem,deallocParams);
            }
        }

    }

    void HostId_finalize_optional_members(
        HostId* sample, RTIBool deletePointers)
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
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) sample[0];

            for (i = 0; i < (int) ((6)); ++i, ++elem) {
                ice::OCTET_finalize_optional_members(elem, deallocParams->delete_pointers);
            }
        }
    }

    RTIBool HostId_copy(
        HostId* dst,
        const HostId* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            {
                int i = 0;
                ice::OCTET* elemOut = (ice::OCTET*) dst[0];
                const ice::OCTET* elemIn = (const ice::OCTET*) src[0];
                for (i = 0; i < (int) ((6));++i, ++elemOut, ++elemIn) {
                    if (!ice::OCTET_copy (elemOut,(const ice::OCTET*)elemIn)) {
                        return RTI_FALSE;
                    }
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
    * Configure and implement 'HostId' sequence class.
    */
    #define T HostId
    #define TSeq HostIdSeq

    #define T_initialize_w_params ice::HostId_initialize_w_params

    #define T_finalize_w_params   ice::HostId_finalize_w_params
    #define T_copy       ice::HostId_copy

    #define T_no_get  
    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_no_get  

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

    /* ========================================================================= */
    const char *GuidTimespecTYPENAME = "ice::GuidTimespec";

    DDS_TypeCode* GuidTimespec_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode GuidTimespec_g_tc_seconds_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,4, NULL,NULL);
        static DDS_TypeCode GuidTimespec_g_tc_fraction_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,2, NULL,NULL);
        static DDS_TypeCode_Member GuidTimespec_g_tc_members[2]=
        {

            {
                (char *)"seconds",/* Member name */
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
                (char *)"fraction",/* Member name */
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

        static DDS_TypeCode GuidTimespec_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::GuidTimespec", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                GuidTimespec_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for GuidTimespec*/

        if (is_initialized) {
            return &GuidTimespec_g_tc;
        }

        GuidTimespec_g_tc_seconds_array._data._typeCode =(RTICdrTypeCode *)ice::OCTET_get_typecode();

        GuidTimespec_g_tc_fraction_array._data._typeCode =(RTICdrTypeCode *)ice::OCTET_get_typecode();

        GuidTimespec_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& GuidTimespec_g_tc_seconds_array;
        GuidTimespec_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& GuidTimespec_g_tc_fraction_array;

        is_initialized = RTI_TRUE;

        return &GuidTimespec_g_tc;
    }

    RTIBool GuidTimespec_initialize(
        GuidTimespec* sample) {
        return ice::GuidTimespec_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool GuidTimespec_initialize_ex(
        GuidTimespec* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::GuidTimespec_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool GuidTimespec_initialize_w_params(
        GuidTimespec* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->seconds[0];

            for (i = 0; i < (int) ((4)); ++i, ++elem) {
                if (!ice::OCTET_initialize_w_params(elem,allocParams)) {
                    return RTI_FALSE;
                }
            }
        }
        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->fraction[0];

            for (i = 0; i < (int) ((2)); ++i, ++elem) {
                if (!ice::OCTET_initialize_w_params(elem,allocParams)) {
                    return RTI_FALSE;
                }
            }
        }
        return RTI_TRUE;
    }

    void GuidTimespec_finalize(
        GuidTimespec* sample)
    {

        ice::GuidTimespec_finalize_ex(sample,RTI_TRUE);
    }

    void GuidTimespec_finalize_ex(
        GuidTimespec* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::GuidTimespec_finalize_w_params(
            sample,&deallocParams);
    }

    void GuidTimespec_finalize_w_params(
        GuidTimespec* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->seconds[0];

            for (i = 0; i < (int) ((4)); ++i, ++elem) {
                ice::OCTET_finalize_w_params(elem,deallocParams);
            }
        }

        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->fraction[0];

            for (i = 0; i < (int) ((2)); ++i, ++elem) {
                ice::OCTET_finalize_w_params(elem,deallocParams);
            }
        }

    }

    void GuidTimespec_finalize_optional_members(
        GuidTimespec* sample, RTIBool deletePointers)
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
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->seconds[0];

            for (i = 0; i < (int) ((4)); ++i, ++elem) {
                ice::OCTET_finalize_optional_members(elem, deallocParams->delete_pointers);
            }
        }
        {
            int i = 0;
            ice::OCTET* elem =
            (ice::OCTET*) &sample->fraction[0];

            for (i = 0; i < (int) ((2)); ++i, ++elem) {
                ice::OCTET_finalize_optional_members(elem, deallocParams->delete_pointers);
            }
        }
    }

    RTIBool GuidTimespec_copy(
        GuidTimespec* dst,
        const GuidTimespec* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            {
                int i = 0;
                ice::OCTET* elemOut = (ice::OCTET*) &dst->seconds[0];
                const ice::OCTET* elemIn = (const ice::OCTET*) &src->seconds[0];
                for (i = 0; i < (int) ((4));++i, ++elemOut, ++elemIn) {
                    if (!ice::OCTET_copy (elemOut,(const ice::OCTET*)elemIn)) {
                        return RTI_FALSE;
                    }
                }
            }
            {
                int i = 0;
                ice::OCTET* elemOut = (ice::OCTET*) &dst->fraction[0];
                const ice::OCTET* elemIn = (const ice::OCTET*) &src->fraction[0];
                for (i = 0; i < (int) ((2));++i, ++elemOut, ++elemIn) {
                    if (!ice::OCTET_copy (elemOut,(const ice::OCTET*)elemIn)) {
                        return RTI_FALSE;
                    }
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
    * Configure and implement 'GuidTimespec' sequence class.
    */
    #define T GuidTimespec
    #define TSeq GuidTimespecSeq

    #define T_initialize_w_params ice::GuidTimespec_initialize_w_params

    #define T_finalize_w_params   ice::GuidTimespec_finalize_w_params
    #define T_copy       ice::GuidTimespec_copy

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
    const char *GuidPrefixTYPENAME = "ice::GuidPrefix";

    DDS_TypeCode* GuidPrefix_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member GuidPrefix_g_tc_members[2]=
        {

            {
                (char *)"hostid",/* Member name */
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
                (char *)"timestamp",/* Member name */
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

        static DDS_TypeCode GuidPrefix_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::GuidPrefix", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                GuidPrefix_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for GuidPrefix*/

        if (is_initialized) {
            return &GuidPrefix_g_tc;
        }

        GuidPrefix_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::HostId_get_typecode();

        GuidPrefix_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::GuidTimespec_get_typecode();

        is_initialized = RTI_TRUE;

        return &GuidPrefix_g_tc;
    }

    RTIBool GuidPrefix_initialize(
        GuidPrefix* sample) {
        return ice::GuidPrefix_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool GuidPrefix_initialize_ex(
        GuidPrefix* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::GuidPrefix_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool GuidPrefix_initialize_w_params(
        GuidPrefix* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::HostId_initialize_w_params(&sample->hostid,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::GuidTimespec_initialize_w_params(&sample->timestamp,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void GuidPrefix_finalize(
        GuidPrefix* sample)
    {

        ice::GuidPrefix_finalize_ex(sample,RTI_TRUE);
    }

    void GuidPrefix_finalize_ex(
        GuidPrefix* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::GuidPrefix_finalize_w_params(
            sample,&deallocParams);
    }

    void GuidPrefix_finalize_w_params(
        GuidPrefix* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::HostId_finalize_w_params(&sample->hostid,deallocParams);

        ice::GuidTimespec_finalize_w_params(&sample->timestamp,deallocParams);

    }

    void GuidPrefix_finalize_optional_members(
        GuidPrefix* sample, RTIBool deletePointers)
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

        ice::HostId_finalize_optional_members(&sample->hostid, deallocParams->delete_pointers);
        ice::GuidTimespec_finalize_optional_members(&sample->timestamp, deallocParams->delete_pointers);
    }

    RTIBool GuidPrefix_copy(
        GuidPrefix* dst,
        const GuidPrefix* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::HostId_copy(
                &dst->hostid,(const ice::HostId*)&src->hostid)) {
                return RTI_FALSE;
            } 
            if (!ice::GuidTimespec_copy(
                &dst->timestamp,(const ice::GuidTimespec*)&src->timestamp)) {
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
    * Configure and implement 'GuidPrefix' sequence class.
    */
    #define T GuidPrefix
    #define TSeq GuidPrefixSeq

    #define T_initialize_w_params ice::GuidPrefix_initialize_w_params

    #define T_finalize_w_params   ice::GuidPrefix_finalize_w_params
    #define T_copy       ice::GuidPrefix_copy

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

    DDS_TypeCode* EntityKind_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode EntityKind_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::EntityKind", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  EntityKind */

        if (is_initialized) {
            return &EntityKind_g_tc;
        }

        EntityKind_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &EntityKind_g_tc;
    }

    RTIBool EntityKind_initialize(
        EntityKind* sample) {
        return ice::EntityKind_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool EntityKind_initialize_ex(
        EntityKind* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EntityKind_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EntityKind_initialize_w_params(
        EntityKind* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void EntityKind_finalize(
        EntityKind* sample)
    {

        ice::EntityKind_finalize_ex(sample,RTI_TRUE);
    }

    void EntityKind_finalize_ex(
        EntityKind* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EntityKind_finalize_w_params(
            sample,&deallocParams);
    }

    void EntityKind_finalize_w_params(
        EntityKind* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void EntityKind_finalize_optional_members(
        EntityKind* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool EntityKind_copy(
        EntityKind* dst,
        const EntityKind* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'EntityKind' sequence class.
    */
    #define T EntityKind
    #define TSeq EntityKindSeq

    #define T_initialize_w_params ice::EntityKind_initialize_w_params

    #define T_finalize_w_params   ice::EntityKind_finalize_w_params
    #define T_copy       ice::EntityKind_copy

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

    DDS_TypeCode* EntityKey_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode EntityKey_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::EntityKey", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  EntityKey */

        if (is_initialized) {
            return &EntityKey_g_tc;
        }

        EntityKey_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU16_get_typecode();

        is_initialized = RTI_TRUE;

        return &EntityKey_g_tc;
    }

    RTIBool EntityKey_initialize(
        EntityKey* sample) {
        return ice::EntityKey_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool EntityKey_initialize_ex(
        EntityKey* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EntityKey_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EntityKey_initialize_w_params(
        EntityKey* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU16_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void EntityKey_finalize(
        EntityKey* sample)
    {

        ice::EntityKey_finalize_ex(sample,RTI_TRUE);
    }

    void EntityKey_finalize_ex(
        EntityKey* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EntityKey_finalize_w_params(
            sample,&deallocParams);
    }

    void EntityKey_finalize_w_params(
        EntityKey* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU16_finalize_w_params(sample,deallocParams);

    }

    void EntityKey_finalize_optional_members(
        EntityKey* sample, RTIBool deletePointers)
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

        ice::INTU16_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool EntityKey_copy(
        EntityKey* dst,
        const EntityKey* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU16_copy(
                dst,(const ice::INTU16*)src)) {
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
    * Configure and implement 'EntityKey' sequence class.
    */
    #define T EntityKey
    #define TSeq EntityKeySeq

    #define T_initialize_w_params ice::EntityKey_initialize_w_params

    #define T_finalize_w_params   ice::EntityKey_finalize_w_params
    #define T_copy       ice::EntityKey_copy

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
    const char *EntityIdTYPENAME = "ice::EntityId";

    DDS_TypeCode* EntityId_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member EntityId_g_tc_members[2]=
        {

            {
                (char *)"kind_of_entity",/* Member name */
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
                (char *)"entity_key",/* Member name */
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

        static DDS_TypeCode EntityId_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::EntityId", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                EntityId_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for EntityId*/

        if (is_initialized) {
            return &EntityId_g_tc;
        }

        EntityId_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::EntityKind_get_typecode();

        EntityId_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::EntityKey_get_typecode();

        is_initialized = RTI_TRUE;

        return &EntityId_g_tc;
    }

    RTIBool EntityId_initialize(
        EntityId* sample) {
        return ice::EntityId_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool EntityId_initialize_ex(
        EntityId* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EntityId_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EntityId_initialize_w_params(
        EntityId* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::EntityKind_initialize_w_params(&sample->kind_of_entity,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::EntityKey_initialize_w_params(&sample->entity_key,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void EntityId_finalize(
        EntityId* sample)
    {

        ice::EntityId_finalize_ex(sample,RTI_TRUE);
    }

    void EntityId_finalize_ex(
        EntityId* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EntityId_finalize_w_params(
            sample,&deallocParams);
    }

    void EntityId_finalize_w_params(
        EntityId* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::EntityKind_finalize_w_params(&sample->kind_of_entity,deallocParams);

        ice::EntityKey_finalize_w_params(&sample->entity_key,deallocParams);

    }

    void EntityId_finalize_optional_members(
        EntityId* sample, RTIBool deletePointers)
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

        ice::EntityKind_finalize_optional_members(&sample->kind_of_entity, deallocParams->delete_pointers);
        ice::EntityKey_finalize_optional_members(&sample->entity_key, deallocParams->delete_pointers);
    }

    RTIBool EntityId_copy(
        EntityId* dst,
        const EntityId* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::EntityKind_copy(
                &dst->kind_of_entity,(const ice::EntityKind*)&src->kind_of_entity)) {
                return RTI_FALSE;
            } 
            if (!ice::EntityKey_copy(
                &dst->entity_key,(const ice::EntityKey*)&src->entity_key)) {
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
    * Configure and implement 'EntityId' sequence class.
    */
    #define T EntityId
    #define TSeq EntityIdSeq

    #define T_initialize_w_params ice::EntityId_initialize_w_params

    #define T_finalize_w_params   ice::EntityId_finalize_w_params
    #define T_copy       ice::EntityId_copy

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
    const char *GUIDTYPENAME = "ice::GUID";

    DDS_TypeCode* GUID_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member GUID_g_tc_members[2]=
        {

            {
                (char *)"prefix",/* Member name */
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
                (char *)"entity_id",/* Member name */
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

        static DDS_TypeCode GUID_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::GUID", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                GUID_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for GUID*/

        if (is_initialized) {
            return &GUID_g_tc;
        }

        GUID_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::GuidPrefix_get_typecode();

        GUID_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::EntityId_get_typecode();

        is_initialized = RTI_TRUE;

        return &GUID_g_tc;
    }

    RTIBool GUID_initialize(
        GUID* sample) {
        return ice::GUID_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool GUID_initialize_ex(
        GUID* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::GUID_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool GUID_initialize_w_params(
        GUID* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::GuidPrefix_initialize_w_params(&sample->prefix,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::EntityId_initialize_w_params(&sample->entity_id,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void GUID_finalize(
        GUID* sample)
    {

        ice::GUID_finalize_ex(sample,RTI_TRUE);
    }

    void GUID_finalize_ex(
        GUID* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::GUID_finalize_w_params(
            sample,&deallocParams);
    }

    void GUID_finalize_w_params(
        GUID* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::GuidPrefix_finalize_w_params(&sample->prefix,deallocParams);

        ice::EntityId_finalize_w_params(&sample->entity_id,deallocParams);

    }

    void GUID_finalize_optional_members(
        GUID* sample, RTIBool deletePointers)
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

        ice::GuidPrefix_finalize_optional_members(&sample->prefix, deallocParams->delete_pointers);
        ice::EntityId_finalize_optional_members(&sample->entity_id, deallocParams->delete_pointers);
    }

    RTIBool GUID_copy(
        GUID* dst,
        const GUID* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::GuidPrefix_copy(
                &dst->prefix,(const ice::GuidPrefix*)&src->prefix)) {
                return RTI_FALSE;
            } 
            if (!ice::EntityId_copy(
                &dst->entity_id,(const ice::EntityId*)&src->entity_id)) {
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
    * Configure and implement 'GUID' sequence class.
    */
    #define T GUID
    #define TSeq GUIDSeq

    #define T_initialize_w_params ice::GUID_initialize_w_params

    #define T_finalize_w_params   ice::GUID_finalize_w_params
    #define T_copy       ice::GUID_copy

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

    DDS_TypeCode* SequenceNumber_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode SequenceNumber_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::SequenceNumber", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  SequenceNumber */

        if (is_initialized) {
            return &SequenceNumber_g_tc;
        }

        SequenceNumber_g_tc._data._typeCode =  (RTICdrTypeCode *)ice::INTU32_get_typecode();

        is_initialized = RTI_TRUE;

        return &SequenceNumber_g_tc;
    }

    RTIBool SequenceNumber_initialize(
        SequenceNumber* sample) {
        return ice::SequenceNumber_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool SequenceNumber_initialize_ex(
        SequenceNumber* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::SequenceNumber_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool SequenceNumber_initialize_w_params(
        SequenceNumber* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::INTU32_initialize_w_params(sample,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void SequenceNumber_finalize(
        SequenceNumber* sample)
    {

        ice::SequenceNumber_finalize_ex(sample,RTI_TRUE);
    }

    void SequenceNumber_finalize_ex(
        SequenceNumber* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::SequenceNumber_finalize_w_params(
            sample,&deallocParams);
    }

    void SequenceNumber_finalize_w_params(
        SequenceNumber* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::INTU32_finalize_w_params(sample,deallocParams);

    }

    void SequenceNumber_finalize_optional_members(
        SequenceNumber* sample, RTIBool deletePointers)
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

        ice::INTU32_finalize_optional_members(sample, deallocParams->delete_pointers);
    }

    RTIBool SequenceNumber_copy(
        SequenceNumber* dst,
        const SequenceNumber* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::INTU32_copy(
                dst,(const ice::INTU32*)src)) {
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
    * Configure and implement 'SequenceNumber' sequence class.
    */
    #define T SequenceNumber
    #define TSeq SequenceNumberSeq

    #define T_initialize_w_params ice::SequenceNumber_initialize_w_params

    #define T_finalize_w_params   ice::SequenceNumber_finalize_w_params
    #define T_copy       ice::SequenceNumber_copy

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
    const char *InstanceIdentifierTYPENAME = "ice::InstanceIdentifier";

    DDS_TypeCode* InstanceIdentifier_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member InstanceIdentifier_g_tc_members[2]=
        {

            {
                (char *)"guid",/* Member name */
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
                (char *)"sequence_number",/* Member name */
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

        static DDS_TypeCode InstanceIdentifier_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::InstanceIdentifier", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                InstanceIdentifier_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for InstanceIdentifier*/

        if (is_initialized) {
            return &InstanceIdentifier_g_tc;
        }

        InstanceIdentifier_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::GUID_get_typecode();

        InstanceIdentifier_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::SequenceNumber_get_typecode();

        is_initialized = RTI_TRUE;

        return &InstanceIdentifier_g_tc;
    }

    RTIBool InstanceIdentifier_initialize(
        InstanceIdentifier* sample) {
        return ice::InstanceIdentifier_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool InstanceIdentifier_initialize_ex(
        InstanceIdentifier* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::InstanceIdentifier_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool InstanceIdentifier_initialize_w_params(
        InstanceIdentifier* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::GUID_initialize_w_params(&sample->guid,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::SequenceNumber_initialize_w_params(&sample->sequence_number,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void InstanceIdentifier_finalize(
        InstanceIdentifier* sample)
    {

        ice::InstanceIdentifier_finalize_ex(sample,RTI_TRUE);
    }

    void InstanceIdentifier_finalize_ex(
        InstanceIdentifier* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::InstanceIdentifier_finalize_w_params(
            sample,&deallocParams);
    }

    void InstanceIdentifier_finalize_w_params(
        InstanceIdentifier* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::GUID_finalize_w_params(&sample->guid,deallocParams);

        ice::SequenceNumber_finalize_w_params(&sample->sequence_number,deallocParams);

    }

    void InstanceIdentifier_finalize_optional_members(
        InstanceIdentifier* sample, RTIBool deletePointers)
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

        ice::GUID_finalize_optional_members(&sample->guid, deallocParams->delete_pointers);
        ice::SequenceNumber_finalize_optional_members(&sample->sequence_number, deallocParams->delete_pointers);
    }

    RTIBool InstanceIdentifier_copy(
        InstanceIdentifier* dst,
        const InstanceIdentifier* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::GUID_copy(
                &dst->guid,(const ice::GUID*)&src->guid)) {
                return RTI_FALSE;
            } 
            if (!ice::SequenceNumber_copy(
                &dst->sequence_number,(const ice::SequenceNumber*)&src->sequence_number)) {
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
    * Configure and implement 'InstanceIdentifier' sequence class.
    */
    #define T InstanceIdentifier
    #define TSeq InstanceIdentifierSeq

    #define T_initialize_w_params ice::InstanceIdentifier_initialize_w_params

    #define T_finalize_w_params   ice::InstanceIdentifier_finalize_w_params
    #define T_copy       ice::InstanceIdentifier_copy

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
    const char *TopTYPENAME = "ice::Top";

    DDS_TypeCode* Top_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Top_g_tc_members[4]=
        {

            {
                (char *)"ice_id",/* Member name */
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
                (char *)"handle",/* Member name */
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
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"parent_handle",/* Member name */
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
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"source_timestamp",/* Member name */
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

        static DDS_TypeCode Top_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Top", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                Top_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Top*/

        if (is_initialized) {
            return &Top_g_tc;
        }

        Top_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::ICE_ID_get_typecode();

        Top_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::HANDLE_get_typecode();

        Top_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::HANDLE_get_typecode();

        Top_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::Timespec_get_typecode();

        is_initialized = RTI_TRUE;

        return &Top_g_tc;
    }

    RTIBool Top_initialize(
        Top* sample) {
        return ice::Top_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Top_initialize_ex(
        Top* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Top_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Top_initialize_w_params(
        Top* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::ICE_ID_initialize_w_params(&sample->ice_id,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::HANDLE_initialize_w_params(&sample->handle,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::HANDLE_initialize_w_params(&sample->parent_handle,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::Timespec_initialize_w_params(&sample->source_timestamp,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Top_finalize(
        Top* sample)
    {

        ice::Top_finalize_ex(sample,RTI_TRUE);
    }

    void Top_finalize_ex(
        Top* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Top_finalize_w_params(
            sample,&deallocParams);
    }

    void Top_finalize_w_params(
        Top* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::ICE_ID_finalize_w_params(&sample->ice_id,deallocParams);

        ice::HANDLE_finalize_w_params(&sample->handle,deallocParams);

        ice::HANDLE_finalize_w_params(&sample->parent_handle,deallocParams);

        ice::Timespec_finalize_w_params(&sample->source_timestamp,deallocParams);

    }

    void Top_finalize_optional_members(
        Top* sample, RTIBool deletePointers)
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

        ice::ICE_ID_finalize_optional_members(&sample->ice_id, deallocParams->delete_pointers);
        ice::HANDLE_finalize_optional_members(&sample->handle, deallocParams->delete_pointers);
        ice::HANDLE_finalize_optional_members(&sample->parent_handle, deallocParams->delete_pointers);
        ice::Timespec_finalize_optional_members(&sample->source_timestamp, deallocParams->delete_pointers);
    }

    RTIBool Top_copy(
        Top* dst,
        const Top* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::ICE_ID_copy(
                &dst->ice_id,(const ice::ICE_ID*)&src->ice_id)) {
                return RTI_FALSE;
            } 
            if (!ice::HANDLE_copy(
                &dst->handle,(const ice::HANDLE*)&src->handle)) {
                return RTI_FALSE;
            } 
            if (!ice::HANDLE_copy(
                &dst->parent_handle,(const ice::HANDLE*)&src->parent_handle)) {
                return RTI_FALSE;
            } 
            if (!ice::Timespec_copy(
                &dst->source_timestamp,(const ice::Timespec*)&src->source_timestamp)) {
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
    * Configure and implement 'Top' sequence class.
    */
    #define T Top
    #define TSeq TopSeq

    #define T_initialize_w_params ice::Top_initialize_w_params

    #define T_finalize_w_params   ice::Top_finalize_w_params
    #define T_copy       ice::Top_copy

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
    const char *VMOTYPENAME = "ice::VMO";

    DDS_TypeCode* VMO_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member VMO_g_tc_members[1]=
        {

            {
                (char *)"type",/* Member name */
                {
                    4,/* Representation ID */          
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

        static DDS_TypeCode VMO_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::VMO", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                1, /* Number of members */
                VMO_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for VMO*/

        if (is_initialized) {
            return &VMO_g_tc;
        }

        VMO_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::TYPE_get_typecode();

        VMO_g_tc._data._typeCode = (RTICdrTypeCode *)ice::Top_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &VMO_g_tc;
    }

    RTIBool VMO_initialize(
        VMO* sample) {
        return ice::VMO_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool VMO_initialize_ex(
        VMO* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::VMO_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool VMO_initialize_w_params(
        VMO* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::Top_initialize_w_params((ice::Top*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (!ice::TYPE_initialize_w_params(&sample->type,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void VMO_finalize(
        VMO* sample)
    {

        ice::VMO_finalize_ex(sample,RTI_TRUE);
    }

    void VMO_finalize_ex(
        VMO* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::VMO_finalize_w_params(
            sample,&deallocParams);
    }

    void VMO_finalize_w_params(
        VMO* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::Top_finalize_w_params((ice::Top*)sample,deallocParams);

        ice::TYPE_finalize_w_params(&sample->type,deallocParams);

    }

    void VMO_finalize_optional_members(
        VMO* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::Top_finalize_optional_members((ice::Top*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

        ice::TYPE_finalize_optional_members(&sample->type, deallocParams->delete_pointers);
    }

    RTIBool VMO_copy(
        VMO* dst,
        const VMO* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if(!ice::Top_copy((ice::Top*)dst,(const ice::Top*)src)) {
                return RTI_FALSE;
            }

            if (!ice::TYPE_copy(
                &dst->type,(const ice::TYPE*)&src->type)) {
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
    * Configure and implement 'VMO' sequence class.
    */
    #define T VMO
    #define TSeq VMOSeq

    #define T_initialize_w_params ice::VMO_initialize_w_params

    #define T_finalize_w_params   ice::VMO_finalize_w_params
    #define T_copy       ice::VMO_copy

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

    DDS_TypeCode* CT_boolean_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_boolean_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_boolean", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_boolean */

        if (is_initialized) {
            return &CT_boolean_g_tc;
        }

        CT_boolean_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_boolean;

        is_initialized = RTI_TRUE;

        return &CT_boolean_g_tc;
    }

    RTIBool CT_boolean_initialize(
        CT_boolean* sample) {
        return ice::CT_boolean_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_boolean_initialize_ex(
        CT_boolean* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_boolean_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_boolean_initialize_w_params(
        CT_boolean* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initBoolean(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void CT_boolean_finalize(
        CT_boolean* sample)
    {

        ice::CT_boolean_finalize_ex(sample,RTI_TRUE);
    }

    void CT_boolean_finalize_ex(
        CT_boolean* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_boolean_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_boolean_finalize_w_params(
        CT_boolean* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CT_boolean_finalize_optional_members(
        CT_boolean* sample, RTIBool deletePointers)
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

    RTIBool CT_boolean_copy(
        CT_boolean* dst,
        const CT_boolean* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyBoolean (
                dst, src)) { 
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
    * Configure and implement 'CT_boolean' sequence class.
    */
    #define T CT_boolean
    #define TSeq CT_booleanSeq

    #define T_initialize_w_params ice::CT_boolean_initialize_w_params

    #define T_finalize_w_params   ice::CT_boolean_finalize_w_params
    #define T_copy       ice::CT_boolean_copy

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

    DDS_TypeCode* CT_integer_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_integer_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_integer", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_integer */

        if (is_initialized) {
            return &CT_integer_g_tc;
        }

        CT_integer_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_long;

        is_initialized = RTI_TRUE;

        return &CT_integer_g_tc;
    }

    RTIBool CT_integer_initialize(
        CT_integer* sample) {
        return ice::CT_integer_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_integer_initialize_ex(
        CT_integer* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_integer_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_integer_initialize_w_params(
        CT_integer* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void CT_integer_finalize(
        CT_integer* sample)
    {

        ice::CT_integer_finalize_ex(sample,RTI_TRUE);
    }

    void CT_integer_finalize_ex(
        CT_integer* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_integer_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_integer_finalize_w_params(
        CT_integer* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CT_integer_finalize_optional_members(
        CT_integer* sample, RTIBool deletePointers)
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

    RTIBool CT_integer_copy(
        CT_integer* dst,
        const CT_integer* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyLong (
                dst, src)) { 
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
    * Configure and implement 'CT_integer' sequence class.
    */
    #define T CT_integer
    #define TSeq CT_integerSeq

    #define T_initialize_w_params ice::CT_integer_initialize_w_params

    #define T_finalize_w_params   ice::CT_integer_finalize_w_params
    #define T_copy       ice::CT_integer_copy

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

    DDS_TypeCode* CT_unsignedInt_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_unsignedInt_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_unsignedInt", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_unsignedInt */

        if (is_initialized) {
            return &CT_unsignedInt_g_tc;
        }

        CT_unsignedInt_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulong;

        is_initialized = RTI_TRUE;

        return &CT_unsignedInt_g_tc;
    }

    RTIBool CT_unsignedInt_initialize(
        CT_unsignedInt* sample) {
        return ice::CT_unsignedInt_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_unsignedInt_initialize_ex(
        CT_unsignedInt* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_unsignedInt_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_unsignedInt_initialize_w_params(
        CT_unsignedInt* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initUnsignedLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void CT_unsignedInt_finalize(
        CT_unsignedInt* sample)
    {

        ice::CT_unsignedInt_finalize_ex(sample,RTI_TRUE);
    }

    void CT_unsignedInt_finalize_ex(
        CT_unsignedInt* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_unsignedInt_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_unsignedInt_finalize_w_params(
        CT_unsignedInt* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CT_unsignedInt_finalize_optional_members(
        CT_unsignedInt* sample, RTIBool deletePointers)
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

    RTIBool CT_unsignedInt_copy(
        CT_unsignedInt* dst,
        const CT_unsignedInt* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedLong (
                dst, src)) { 
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
    * Configure and implement 'CT_unsignedInt' sequence class.
    */
    #define T CT_unsignedInt
    #define TSeq CT_unsignedIntSeq

    #define T_initialize_w_params ice::CT_unsignedInt_initialize_w_params

    #define T_finalize_w_params   ice::CT_unsignedInt_finalize_w_params
    #define T_copy       ice::CT_unsignedInt_copy

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

    DDS_TypeCode* CT_positiveInt_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_positiveInt_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_positiveInt", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_positiveInt */

        if (is_initialized) {
            return &CT_positiveInt_g_tc;
        }

        CT_positiveInt_g_tc._data._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulong;

        is_initialized = RTI_TRUE;

        return &CT_positiveInt_g_tc;
    }

    RTIBool CT_positiveInt_initialize(
        CT_positiveInt* sample) {
        return ice::CT_positiveInt_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_positiveInt_initialize_ex(
        CT_positiveInt* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_positiveInt_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_positiveInt_initialize_w_params(
        CT_positiveInt* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initUnsignedLong(sample)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void CT_positiveInt_finalize(
        CT_positiveInt* sample)
    {

        ice::CT_positiveInt_finalize_ex(sample,RTI_TRUE);
    }

    void CT_positiveInt_finalize_ex(
        CT_positiveInt* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_positiveInt_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_positiveInt_finalize_w_params(
        CT_positiveInt* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CT_positiveInt_finalize_optional_members(
        CT_positiveInt* sample, RTIBool deletePointers)
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

    RTIBool CT_positiveInt_copy(
        CT_positiveInt* dst,
        const CT_positiveInt* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedLong (
                dst, src)) { 
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
    * Configure and implement 'CT_positiveInt' sequence class.
    */
    #define T CT_positiveInt
    #define TSeq CT_positiveIntSeq

    #define T_initialize_w_params ice::CT_positiveInt_initialize_w_params

    #define T_finalize_w_params   ice::CT_positiveInt_finalize_w_params
    #define T_copy       ice::CT_positiveInt_copy

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
    const char *CT_decimalTYPENAME = "ice::CT_decimal";

    DDS_TypeCode* CT_decimal_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member CT_decimal_g_tc_members[2]=
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
                (char *)"presentation_precision",/* Member name */
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

        static DDS_TypeCode CT_decimal_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CT_decimal", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                CT_decimal_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for CT_decimal*/

        if (is_initialized) {
            return &CT_decimal_g_tc;
        }

        CT_decimal_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

        CT_decimal_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;

        is_initialized = RTI_TRUE;

        return &CT_decimal_g_tc;
    }

    RTIBool CT_decimal_initialize(
        CT_decimal* sample) {
        return ice::CT_decimal_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_decimal_initialize_ex(
        CT_decimal* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_decimal_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_decimal_initialize_w_params(
        CT_decimal* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initFloat(&sample->value)) {
            return RTI_FALSE;
        }

        if (!RTICdrType_initOctet(&sample->presentation_precision)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;
    }

    void CT_decimal_finalize(
        CT_decimal* sample)
    {

        ice::CT_decimal_finalize_ex(sample,RTI_TRUE);
    }

    void CT_decimal_finalize_ex(
        CT_decimal* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_decimal_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_decimal_finalize_w_params(
        CT_decimal* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void CT_decimal_finalize_optional_members(
        CT_decimal* sample, RTIBool deletePointers)
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

    RTIBool CT_decimal_copy(
        CT_decimal* dst,
        const CT_decimal* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyFloat (
                &dst->value, &src->value)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyOctet (
                &dst->presentation_precision, &src->presentation_precision)) { 
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
    * Configure and implement 'CT_decimal' sequence class.
    */
    #define T CT_decimal
    #define TSeq CT_decimalSeq

    #define T_initialize_w_params ice::CT_decimal_initialize_w_params

    #define T_finalize_w_params   ice::CT_decimal_finalize_w_params
    #define T_copy       ice::CT_decimal_copy

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

    DDS_TypeCode* CT_dateTime_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_dateTime_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_DATETIME)));

        static DDS_TypeCode CT_dateTime_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_dateTime", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_dateTime */

        if (is_initialized) {
            return &CT_dateTime_g_tc;
        }

        CT_dateTime_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_dateTime_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_dateTime_g_tc;
    }

    RTIBool CT_dateTime_initialize(
        CT_dateTime* sample) {
        return ice::CT_dateTime_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_dateTime_initialize_ex(
        CT_dateTime* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_dateTime_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_dateTime_initialize_w_params(
        CT_dateTime* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_DATETIME)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_dateTime_finalize(
        CT_dateTime* sample)
    {

        ice::CT_dateTime_finalize_ex(sample,RTI_TRUE);
    }

    void CT_dateTime_finalize_ex(
        CT_dateTime* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_dateTime_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_dateTime_finalize_w_params(
        CT_dateTime* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_dateTime_finalize_optional_members(
        CT_dateTime* sample, RTIBool deletePointers)
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

    RTIBool CT_dateTime_copy(
        CT_dateTime* dst,
        const CT_dateTime* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_DATETIME)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_dateTime' sequence class.
    */
    #define T CT_dateTime
    #define TSeq CT_dateTimeSeq

    #define T_initialize_w_params ice::CT_dateTime_initialize_w_params

    #define T_finalize_w_params   ice::CT_dateTime_finalize_w_params
    #define T_copy       ice::CT_dateTime_copy

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

    DDS_TypeCode* CT_instant_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_instant_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_INSTANT)));

        static DDS_TypeCode CT_instant_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_instant", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_instant */

        if (is_initialized) {
            return &CT_instant_g_tc;
        }

        CT_instant_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_instant_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_instant_g_tc;
    }

    RTIBool CT_instant_initialize(
        CT_instant* sample) {
        return ice::CT_instant_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_instant_initialize_ex(
        CT_instant* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_instant_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_instant_initialize_w_params(
        CT_instant* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_INSTANT)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_instant_finalize(
        CT_instant* sample)
    {

        ice::CT_instant_finalize_ex(sample,RTI_TRUE);
    }

    void CT_instant_finalize_ex(
        CT_instant* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_instant_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_instant_finalize_w_params(
        CT_instant* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_instant_finalize_optional_members(
        CT_instant* sample, RTIBool deletePointers)
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

    RTIBool CT_instant_copy(
        CT_instant* dst,
        const CT_instant* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_INSTANT)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_instant' sequence class.
    */
    #define T CT_instant
    #define TSeq CT_instantSeq

    #define T_initialize_w_params ice::CT_instant_initialize_w_params

    #define T_finalize_w_params   ice::CT_instant_finalize_w_params
    #define T_copy       ice::CT_instant_copy

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

    DDS_TypeCode* CT_date_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_date_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_DATE)));

        static DDS_TypeCode CT_date_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_date", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_date */

        if (is_initialized) {
            return &CT_date_g_tc;
        }

        CT_date_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_date_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_date_g_tc;
    }

    RTIBool CT_date_initialize(
        CT_date* sample) {
        return ice::CT_date_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_date_initialize_ex(
        CT_date* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_date_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_date_initialize_w_params(
        CT_date* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_DATE)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_date_finalize(
        CT_date* sample)
    {

        ice::CT_date_finalize_ex(sample,RTI_TRUE);
    }

    void CT_date_finalize_ex(
        CT_date* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_date_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_date_finalize_w_params(
        CT_date* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_date_finalize_optional_members(
        CT_date* sample, RTIBool deletePointers)
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

    RTIBool CT_date_copy(
        CT_date* dst,
        const CT_date* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_DATE)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_date' sequence class.
    */
    #define T CT_date
    #define TSeq CT_dateSeq

    #define T_initialize_w_params ice::CT_date_initialize_w_params

    #define T_finalize_w_params   ice::CT_date_finalize_w_params
    #define T_copy       ice::CT_date_copy

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

    DDS_TypeCode* CT_time_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_time_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_TIME)));

        static DDS_TypeCode CT_time_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_time", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_time */

        if (is_initialized) {
            return &CT_time_g_tc;
        }

        CT_time_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_time_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_time_g_tc;
    }

    RTIBool CT_time_initialize(
        CT_time* sample) {
        return ice::CT_time_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_time_initialize_ex(
        CT_time* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_time_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_time_initialize_w_params(
        CT_time* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_TIME)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_time_finalize(
        CT_time* sample)
    {

        ice::CT_time_finalize_ex(sample,RTI_TRUE);
    }

    void CT_time_finalize_ex(
        CT_time* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_time_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_time_finalize_w_params(
        CT_time* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_time_finalize_optional_members(
        CT_time* sample, RTIBool deletePointers)
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

    RTIBool CT_time_copy(
        CT_time* dst,
        const CT_time* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_TIME)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_time' sequence class.
    */
    #define T CT_time
    #define TSeq CT_timeSeq

    #define T_initialize_w_params ice::CT_time_initialize_w_params

    #define T_finalize_w_params   ice::CT_time_finalize_w_params
    #define T_copy       ice::CT_time_copy

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

    DDS_TypeCode* CT_code_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_code_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_CODE)));

        static DDS_TypeCode CT_code_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_code", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_code */

        if (is_initialized) {
            return &CT_code_g_tc;
        }

        CT_code_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_code_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_code_g_tc;
    }

    RTIBool CT_code_initialize(
        CT_code* sample) {
        return ice::CT_code_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_code_initialize_ex(
        CT_code* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_code_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_code_initialize_w_params(
        CT_code* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_CODE)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_code_finalize(
        CT_code* sample)
    {

        ice::CT_code_finalize_ex(sample,RTI_TRUE);
    }

    void CT_code_finalize_ex(
        CT_code* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_code_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_code_finalize_w_params(
        CT_code* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_code_finalize_optional_members(
        CT_code* sample, RTIBool deletePointers)
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

    RTIBool CT_code_copy(
        CT_code* dst,
        const CT_code* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_CODE)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_code' sequence class.
    */
    #define T CT_code
    #define TSeq CT_codeSeq

    #define T_initialize_w_params ice::CT_code_initialize_w_params

    #define T_finalize_w_params   ice::CT_code_finalize_w_params
    #define T_copy       ice::CT_code_copy

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

    DDS_TypeCode* CT_id_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_id_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_ID)));

        static DDS_TypeCode CT_id_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_id", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_id */

        if (is_initialized) {
            return &CT_id_g_tc;
        }

        CT_id_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_id_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_id_g_tc;
    }

    RTIBool CT_id_initialize(
        CT_id* sample) {
        return ice::CT_id_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_id_initialize_ex(
        CT_id* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_id_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_id_initialize_w_params(
        CT_id* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_ID)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_id_finalize(
        CT_id* sample)
    {

        ice::CT_id_finalize_ex(sample,RTI_TRUE);
    }

    void CT_id_finalize_ex(
        CT_id* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_id_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_id_finalize_w_params(
        CT_id* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_id_finalize_optional_members(
        CT_id* sample, RTIBool deletePointers)
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

    RTIBool CT_id_copy(
        CT_id* dst,
        const CT_id* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_ID)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_id' sequence class.
    */
    #define T CT_id
    #define TSeq CT_idSeq

    #define T_initialize_w_params ice::CT_id_initialize_w_params

    #define T_finalize_w_params   ice::CT_id_finalize_w_params
    #define T_copy       ice::CT_id_copy

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

    DDS_TypeCode* CT_uri_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CT_uri_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MAXLEN_CT_URI)));

        static DDS_TypeCode CT_uri_g_tc =
        {{
                DDS_TK_ALIAS, /* Kind*/
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Ignored */
                (char *)"ice::CT_uri", /* Name */
                NULL, /* Content type code is assigned later */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                DDS_VM_NONE /* Ignored */
            }}; /* Type code for  CT_uri */

        if (is_initialized) {
            return &CT_uri_g_tc;
        }

        CT_uri_g_tc._data._typeCode =  (RTICdrTypeCode *)&CT_uri_g_tc_string;

        is_initialized = RTI_TRUE;

        return &CT_uri_g_tc;
    }

    RTIBool CT_uri_initialize(
        CT_uri* sample) {
        return ice::CT_uri_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CT_uri_initialize_ex(
        CT_uri* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CT_uri_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CT_uri_initialize_w_params(
        CT_uri* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            (*sample)= DDS_String_alloc (((ice::MAXLEN_CT_URI)));
            if ((*sample) == NULL) {
                return RTI_FALSE;
            }

        } else {
            if ((*sample)!= NULL) { 
                (*sample)[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CT_uri_finalize(
        CT_uri* sample)
    {

        ice::CT_uri_finalize_ex(sample,RTI_TRUE);
    }

    void CT_uri_finalize_ex(
        CT_uri* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CT_uri_finalize_w_params(
            sample,&deallocParams);
    }

    void CT_uri_finalize_w_params(
        CT_uri* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if ((*sample) != NULL) {
            DDS_String_free((*sample));
            (*sample)=NULL;

        }
    }

    void CT_uri_finalize_optional_members(
        CT_uri* sample, RTIBool deletePointers)
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

    RTIBool CT_uri_copy(
        CT_uri* dst,
        const CT_uri* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &(*dst), (*src), 
                ((ice::MAXLEN_CT_URI)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CT_uri' sequence class.
    */
    #define T CT_uri
    #define TSeq CT_uriSeq

    #define T_initialize_w_params ice::CT_uri_initialize_w_params

    #define T_finalize_w_params   ice::CT_uri_finalize_w_params
    #define T_copy       ice::CT_uri_copy

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
    const char *CodingTYPENAME = "ice::Coding";

    DDS_TypeCode* Coding_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode Coding_g_tc_version_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MEDIUM_STRING_LEN)));
        static DDS_TypeCode Coding_g_tc_display_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MEDIUM_STRING_LEN)));
        static DDS_TypeCode_Member Coding_g_tc_members[5]=
        {

            {
                (char *)"system",/* Member name */
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
                (char *)"version",/* Member name */
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
                (char *)"code_",/* Member name */
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
                (char *)"display",/* Member name */
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
            }, 
            {
                (char *)"user_selected",/* Member name */
                {
                    4,/* Representation ID */          
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

        static DDS_TypeCode Coding_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Coding", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                5, /* Number of members */
                Coding_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Coding*/

        if (is_initialized) {
            return &Coding_g_tc;
        }

        Coding_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::CT_uri_get_typecode();

        Coding_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Coding_g_tc_version_string;

        Coding_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::CT_code_get_typecode();

        Coding_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&Coding_g_tc_display_string;

        Coding_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)ice::CT_boolean_get_typecode();

        is_initialized = RTI_TRUE;

        return &Coding_g_tc;
    }

    RTIBool Coding_initialize(
        Coding* sample) {
        return ice::Coding_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Coding_initialize_ex(
        Coding* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Coding_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Coding_initialize_w_params(
        Coding* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::CT_uri_initialize_w_params(&sample->system,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->version= DDS_String_alloc (((ice::MEDIUM_STRING_LEN)));
            if (sample->version == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->version!= NULL) { 
                sample->version[0] = '\0';
            }
        }

        if (!ice::CT_code_initialize_w_params(&sample->code_,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->display= DDS_String_alloc (((ice::MEDIUM_STRING_LEN)));
            if (sample->display == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->display!= NULL) { 
                sample->display[0] = '\0';
            }
        }

        if (!ice::CT_boolean_initialize_w_params(&sample->user_selected,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Coding_finalize(
        Coding* sample)
    {

        ice::Coding_finalize_ex(sample,RTI_TRUE);
    }

    void Coding_finalize_ex(
        Coding* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Coding_finalize_w_params(
            sample,&deallocParams);
    }

    void Coding_finalize_w_params(
        Coding* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::CT_uri_finalize_w_params(&sample->system,deallocParams);

        if (sample->version != NULL) {
            DDS_String_free(sample->version);
            sample->version=NULL;

        }
        ice::CT_code_finalize_w_params(&sample->code_,deallocParams);

        if (sample->display != NULL) {
            DDS_String_free(sample->display);
            sample->display=NULL;

        }
        ice::CT_boolean_finalize_w_params(&sample->user_selected,deallocParams);

    }

    void Coding_finalize_optional_members(
        Coding* sample, RTIBool deletePointers)
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

        ice::CT_uri_finalize_optional_members(&sample->system, deallocParams->delete_pointers);
        ice::CT_code_finalize_optional_members(&sample->code_, deallocParams->delete_pointers);
        ice::CT_boolean_finalize_optional_members(&sample->user_selected, deallocParams->delete_pointers);
    }

    RTIBool Coding_copy(
        Coding* dst,
        const Coding* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::CT_uri_copy(
                &dst->system,(const ice::CT_uri*)&src->system)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->version, src->version, 
                ((ice::MEDIUM_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!ice::CT_code_copy(
                &dst->code_,(const ice::CT_code*)&src->code_)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->display, src->display, 
                ((ice::MEDIUM_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!ice::CT_boolean_copy(
                &dst->user_selected,(const ice::CT_boolean*)&src->user_selected)) {
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
    * Configure and implement 'Coding' sequence class.
    */
    #define T Coding
    #define TSeq CodingSeq

    #define T_initialize_w_params ice::Coding_initialize_w_params

    #define T_finalize_w_params   ice::Coding_finalize_w_params
    #define T_copy       ice::Coding_copy

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
    const char *CodeableConceptTYPENAME = "ice::CodeableConcept";

    DDS_TypeCode* CodeableConcept_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode CodeableConcept_g_tc_text_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::LONGLONG_STRING_LEN)));
        static DDS_TypeCode_Member CodeableConcept_g_tc_members[2]=
        {

            {
                (char *)"coding",/* Member name */
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
                (char *)"text",/* Member name */
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

        static DDS_TypeCode CodeableConcept_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::CodeableConcept", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                CodeableConcept_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for CodeableConcept*/

        if (is_initialized) {
            return &CodeableConcept_g_tc;
        }

        CodeableConcept_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::Coding_get_typecode();

        CodeableConcept_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&CodeableConcept_g_tc_text_string;

        is_initialized = RTI_TRUE;

        return &CodeableConcept_g_tc;
    }

    RTIBool CodeableConcept_initialize(
        CodeableConcept* sample) {
        return ice::CodeableConcept_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool CodeableConcept_initialize_ex(
        CodeableConcept* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::CodeableConcept_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool CodeableConcept_initialize_w_params(
        CodeableConcept* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::Coding_initialize_w_params(&sample->coding,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->text= DDS_String_alloc (((ice::LONGLONG_STRING_LEN)));
            if (sample->text == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->text!= NULL) { 
                sample->text[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void CodeableConcept_finalize(
        CodeableConcept* sample)
    {

        ice::CodeableConcept_finalize_ex(sample,RTI_TRUE);
    }

    void CodeableConcept_finalize_ex(
        CodeableConcept* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::CodeableConcept_finalize_w_params(
            sample,&deallocParams);
    }

    void CodeableConcept_finalize_w_params(
        CodeableConcept* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::Coding_finalize_w_params(&sample->coding,deallocParams);

        if (sample->text != NULL) {
            DDS_String_free(sample->text);
            sample->text=NULL;

        }
    }

    void CodeableConcept_finalize_optional_members(
        CodeableConcept* sample, RTIBool deletePointers)
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

        ice::Coding_finalize_optional_members(&sample->coding, deallocParams->delete_pointers);
    }

    RTIBool CodeableConcept_copy(
        CodeableConcept* dst,
        const CodeableConcept* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::Coding_copy(
                &dst->coding,(const ice::Coding*)&src->coding)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->text, src->text, 
                ((ice::LONGLONG_STRING_LEN)) + 1, RTI_FALSE)){
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
    * Configure and implement 'CodeableConcept' sequence class.
    */
    #define T CodeableConcept
    #define TSeq CodeableConceptSeq

    #define T_initialize_w_params ice::CodeableConcept_initialize_w_params

    #define T_finalize_w_params   ice::CodeableConcept_finalize_w_params
    #define T_copy       ice::CodeableConcept_copy

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
    const char *SimpleQuantityTYPENAME = "ice::SimpleQuantity";

    DDS_TypeCode* SimpleQuantity_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode SimpleQuantity_g_tc_unit_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::MEDIUM_STRING_LEN)));
        static DDS_TypeCode_Member SimpleQuantity_g_tc_members[4]=
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
                (char *)"unit",/* Member name */
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
                (char *)"system",/* Member name */
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
                (char *)"code_",/* Member name */
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

        static DDS_TypeCode SimpleQuantity_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::SimpleQuantity", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                4, /* Number of members */
                SimpleQuantity_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for SimpleQuantity*/

        if (is_initialized) {
            return &SimpleQuantity_g_tc;
        }

        SimpleQuantity_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::CT_decimal_get_typecode();

        SimpleQuantity_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&SimpleQuantity_g_tc_unit_string;

        SimpleQuantity_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)ice::CT_uri_get_typecode();

        SimpleQuantity_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)ice::CT_code_get_typecode();

        is_initialized = RTI_TRUE;

        return &SimpleQuantity_g_tc;
    }

    RTIBool SimpleQuantity_initialize(
        SimpleQuantity* sample) {
        return ice::SimpleQuantity_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool SimpleQuantity_initialize_ex(
        SimpleQuantity* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::SimpleQuantity_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool SimpleQuantity_initialize_w_params(
        SimpleQuantity* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::CT_decimal_initialize_w_params(&sample->value,
        allocParams)) {
            return RTI_FALSE;
        }
        if (allocParams->allocate_memory){
            sample->unit= DDS_String_alloc (((ice::MEDIUM_STRING_LEN)));
            if (sample->unit == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->unit!= NULL) { 
                sample->unit[0] = '\0';
            }
        }

        if (!ice::CT_uri_initialize_w_params(&sample->system,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::CT_code_initialize_w_params(&sample->code_,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void SimpleQuantity_finalize(
        SimpleQuantity* sample)
    {

        ice::SimpleQuantity_finalize_ex(sample,RTI_TRUE);
    }

    void SimpleQuantity_finalize_ex(
        SimpleQuantity* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::SimpleQuantity_finalize_w_params(
            sample,&deallocParams);
    }

    void SimpleQuantity_finalize_w_params(
        SimpleQuantity* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::CT_decimal_finalize_w_params(&sample->value,deallocParams);

        if (sample->unit != NULL) {
            DDS_String_free(sample->unit);
            sample->unit=NULL;

        }
        ice::CT_uri_finalize_w_params(&sample->system,deallocParams);

        ice::CT_code_finalize_w_params(&sample->code_,deallocParams);

    }

    void SimpleQuantity_finalize_optional_members(
        SimpleQuantity* sample, RTIBool deletePointers)
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

        ice::CT_decimal_finalize_optional_members(&sample->value, deallocParams->delete_pointers);
        ice::CT_uri_finalize_optional_members(&sample->system, deallocParams->delete_pointers);
        ice::CT_code_finalize_optional_members(&sample->code_, deallocParams->delete_pointers);
    }

    RTIBool SimpleQuantity_copy(
        SimpleQuantity* dst,
        const SimpleQuantity* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::CT_decimal_copy(
                &dst->value,(const ice::CT_decimal*)&src->value)) {
                return RTI_FALSE;
            } 
            if (!RTICdrType_copyStringEx (
                &dst->unit, src->unit, 
                ((ice::MEDIUM_STRING_LEN)) + 1, RTI_FALSE)){
                return RTI_FALSE;
            }
            if (!ice::CT_uri_copy(
                &dst->system,(const ice::CT_uri*)&src->system)) {
                return RTI_FALSE;
            } 
            if (!ice::CT_code_copy(
                &dst->code_,(const ice::CT_code*)&src->code_)) {
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
    * Configure and implement 'SimpleQuantity' sequence class.
    */
    #define T SimpleQuantity
    #define TSeq SimpleQuantitySeq

    #define T_initialize_w_params ice::SimpleQuantity_initialize_w_params

    #define T_finalize_w_params   ice::SimpleQuantity_finalize_w_params
    #define T_copy       ice::SimpleQuantity_copy

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
    const char *QuantityTYPENAME = "ice::Quantity";

    DDS_TypeCode* Quantity_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode Quantity_g_tc_comparator_string = DDS_INITIALIZE_STRING_TYPECODE(((ice::TINY_STRING_LEN)));
        static DDS_TypeCode_Member Quantity_g_tc_members[1]=
        {

            {
                (char *)"comparator",/* Member name */
                {
                    4,/* Representation ID */          
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

        static DDS_TypeCode Quantity_g_tc =
        {{
                DDS_TK_VALUE,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Quantity", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                1, /* Number of members */
                Quantity_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Quantity*/

        if (is_initialized) {
            return &Quantity_g_tc;
        }

        Quantity_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Quantity_g_tc_comparator_string;

        Quantity_g_tc._data._typeCode = (RTICdrTypeCode *)ice::SimpleQuantity_get_typecode(); /* Base class */

        is_initialized = RTI_TRUE;

        return &Quantity_g_tc;
    }

    RTIBool Quantity_initialize(
        Quantity* sample) {
        return ice::Quantity_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Quantity_initialize_ex(
        Quantity* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Quantity_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Quantity_initialize_w_params(
        Quantity* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        if (!ice::SimpleQuantity_initialize_w_params((ice::SimpleQuantity*)sample,allocParams)) {
            return RTI_FALSE;
        }

        if (allocParams->allocate_memory){
            sample->comparator= DDS_String_alloc (((ice::TINY_STRING_LEN)));
            if (sample->comparator == NULL) {
                return RTI_FALSE;
            }

        } else {
            if (sample->comparator!= NULL) { 
                sample->comparator[0] = '\0';
            }
        }

        return RTI_TRUE;
    }

    void Quantity_finalize(
        Quantity* sample)
    {

        ice::Quantity_finalize_ex(sample,RTI_TRUE);
    }

    void Quantity_finalize_ex(
        Quantity* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Quantity_finalize_w_params(
            sample,&deallocParams);
    }

    void Quantity_finalize_w_params(
        Quantity* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }
        ice::SimpleQuantity_finalize_w_params((ice::SimpleQuantity*)sample,deallocParams);

        if (sample->comparator != NULL) {
            DDS_String_free(sample->comparator);
            sample->comparator=NULL;

        }
    }

    void Quantity_finalize_optional_members(
        Quantity* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        if (deallocParams) {} /* To avoid warnings */

        ice::SimpleQuantity_finalize_optional_members((ice::SimpleQuantity*)sample,deletePointers);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool Quantity_copy(
        Quantity* dst,
        const Quantity* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if(!ice::SimpleQuantity_copy((ice::SimpleQuantity*)dst,(const ice::SimpleQuantity*)src)) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyStringEx (
                &dst->comparator, src->comparator, 
                ((ice::TINY_STRING_LEN)) + 1, RTI_FALSE)){
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
    * Configure and implement 'Quantity' sequence class.
    */
    #define T Quantity
    #define TSeq QuantitySeq

    #define T_initialize_w_params ice::Quantity_initialize_w_params

    #define T_finalize_w_params   ice::Quantity_finalize_w_params
    #define T_copy       ice::Quantity_copy

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
    const char *RangeTYPENAME = "ice::Range";

    DDS_TypeCode* Range_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Range_g_tc_members[2]=
        {

            {
                (char *)"low",/* Member name */
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
                (char *)"high",/* Member name */
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

        static DDS_TypeCode Range_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Range", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                Range_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Range*/

        if (is_initialized) {
            return &Range_g_tc;
        }

        Range_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::SimpleQuantity_get_typecode();

        Range_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::SimpleQuantity_get_typecode();

        is_initialized = RTI_TRUE;

        return &Range_g_tc;
    }

    RTIBool Range_initialize(
        Range* sample) {
        return ice::Range_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Range_initialize_ex(
        Range* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Range_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Range_initialize_w_params(
        Range* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::SimpleQuantity_initialize_w_params(&sample->low,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::SimpleQuantity_initialize_w_params(&sample->high,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Range_finalize(
        Range* sample)
    {

        ice::Range_finalize_ex(sample,RTI_TRUE);
    }

    void Range_finalize_ex(
        Range* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Range_finalize_w_params(
            sample,&deallocParams);
    }

    void Range_finalize_w_params(
        Range* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::SimpleQuantity_finalize_w_params(&sample->low,deallocParams);

        ice::SimpleQuantity_finalize_w_params(&sample->high,deallocParams);

    }

    void Range_finalize_optional_members(
        Range* sample, RTIBool deletePointers)
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

        ice::SimpleQuantity_finalize_optional_members(&sample->low, deallocParams->delete_pointers);
        ice::SimpleQuantity_finalize_optional_members(&sample->high, deallocParams->delete_pointers);
    }

    RTIBool Range_copy(
        Range* dst,
        const Range* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::SimpleQuantity_copy(
                &dst->low,(const ice::SimpleQuantity*)&src->low)) {
                return RTI_FALSE;
            } 
            if (!ice::SimpleQuantity_copy(
                &dst->high,(const ice::SimpleQuantity*)&src->high)) {
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
    * Configure and implement 'Range' sequence class.
    */
    #define T Range
    #define TSeq RangeSeq

    #define T_initialize_w_params ice::Range_initialize_w_params

    #define T_finalize_w_params   ice::Range_finalize_w_params
    #define T_copy       ice::Range_copy

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
    const char *RatioTYPENAME = "ice::Ratio";

    DDS_TypeCode* Ratio_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Ratio_g_tc_members[2]=
        {

            {
                (char *)"numerator",/* Member name */
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
                (char *)"denominator",/* Member name */
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

        static DDS_TypeCode Ratio_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Ratio", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                Ratio_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Ratio*/

        if (is_initialized) {
            return &Ratio_g_tc;
        }

        Ratio_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::Quantity_get_typecode();

        Ratio_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::Quantity_get_typecode();

        is_initialized = RTI_TRUE;

        return &Ratio_g_tc;
    }

    RTIBool Ratio_initialize(
        Ratio* sample) {
        return ice::Ratio_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Ratio_initialize_ex(
        Ratio* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Ratio_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Ratio_initialize_w_params(
        Ratio* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!ice::Quantity_initialize_w_params(&sample->numerator,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::Quantity_initialize_w_params(&sample->denominator,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void Ratio_finalize(
        Ratio* sample)
    {

        ice::Ratio_finalize_ex(sample,RTI_TRUE);
    }

    void Ratio_finalize_ex(
        Ratio* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Ratio_finalize_w_params(
            sample,&deallocParams);
    }

    void Ratio_finalize_w_params(
        Ratio* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::Quantity_finalize_w_params(&sample->numerator,deallocParams);

        ice::Quantity_finalize_w_params(&sample->denominator,deallocParams);

    }

    void Ratio_finalize_optional_members(
        Ratio* sample, RTIBool deletePointers)
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

        ice::Quantity_finalize_optional_members(&sample->numerator, deallocParams->delete_pointers);
        ice::Quantity_finalize_optional_members(&sample->denominator, deallocParams->delete_pointers);
    }

    RTIBool Ratio_copy(
        Ratio* dst,
        const Ratio* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::Quantity_copy(
                &dst->numerator,(const ice::Quantity*)&src->numerator)) {
                return RTI_FALSE;
            } 
            if (!ice::Quantity_copy(
                &dst->denominator,(const ice::Quantity*)&src->denominator)) {
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
    * Configure and implement 'Ratio' sequence class.
    */
    #define T Ratio
    #define TSeq RatioSeq

    #define T_initialize_w_params ice::Ratio_initialize_w_params

    #define T_finalize_w_params   ice::Ratio_finalize_w_params
    #define T_copy       ice::Ratio_copy

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
    const char *PeriodTYPENAME = "ice::Period";

    DDS_TypeCode* Period_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member Period_g_tc_members[2]=
        {

            {
                (char *)"start",/* Member name */
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
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"end",/* Member name */
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
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode Period_g_tc =
        {{
                DDS_TK_STRUCT,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::Period", /* Name */
                NULL, /* Ignored */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                Period_g_tc_members, /* Members */
                DDS_VM_NONE  /* Ignored */         
            }}; /* Type code for Period*/

        if (is_initialized) {
            return &Period_g_tc;
        }

        Period_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::CT_dateTime_get_typecode();

        Period_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::CT_dateTime_get_typecode();

        is_initialized = RTI_TRUE;

        return &Period_g_tc;
    }

    RTIBool Period_initialize(
        Period* sample) {
        return ice::Period_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool Period_initialize_ex(
        Period* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::Period_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool Period_initialize_w_params(
        Period* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        if (!allocParams->allocate_optional_members) {
            sample->start=NULL;
        } else {   
            if (!ice::CT_dateTime_initialize_w_params(&sample->start,
            allocParams)) {
                return RTI_FALSE;
            }
        }
        if (!allocParams->allocate_optional_members) {
            sample->end=NULL;
        } else {   
            if (!ice::CT_dateTime_initialize_w_params(&sample->end,
            allocParams)) {
                return RTI_FALSE;
            }
        }
        return RTI_TRUE;
    }

    void Period_finalize(
        Period* sample)
    {

        ice::Period_finalize_ex(sample,RTI_TRUE);
    }

    void Period_finalize_ex(
        Period* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::Period_finalize_w_params(
            sample,&deallocParams);
    }

    void Period_finalize_w_params(
        Period* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        if (deallocParams->delete_optional_members) {
            if (&sample->start != NULL) {
                ice::CT_dateTime_finalize_w_params(&sample->start,deallocParams);

            }
        }
        if (deallocParams->delete_optional_members) {
            if (&sample->end != NULL) {
                ice::CT_dateTime_finalize_w_params(&sample->end,deallocParams);

            }
        }
    }

    void Period_finalize_optional_members(
        Period* sample, RTIBool deletePointers)
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

        if (&sample->start != NULL) {
            ice::CT_dateTime_finalize_w_params(&sample->start,deallocParams);

        }
        if (&sample->end != NULL) {
            ice::CT_dateTime_finalize_w_params(&sample->end,deallocParams);

        }
    }

    RTIBool Period_copy(
        Period* dst,
        const Period* src)
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

            if (src->start!=NULL) {
                if (dst->start==NULL) {

                    if (!ice::CT_dateTime_initialize_ex(&dst->start, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }      
                if (!ice::CT_dateTime_copy(
                    &dst->start,(const ice::CT_dateTime*)&src->start)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->start != NULL) {

                    ice::CT_dateTime_finalize_w_params(&dst->start, deallocParams);
                }   
            }
            if (src->end!=NULL) {
                if (dst->end==NULL) {

                    if (!ice::CT_dateTime_initialize_ex(&dst->end, RTI_TRUE, RTI_TRUE)) {
                        return RTI_FALSE;
                    }
                }      
                if (!ice::CT_dateTime_copy(
                    &dst->end,(const ice::CT_dateTime*)&src->end)) {
                    return RTI_FALSE;
                } 
            } else {

                if (dst->end != NULL) {

                    ice::CT_dateTime_finalize_w_params(&dst->end, deallocParams);
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
    * Configure and implement 'Period' sequence class.
    */
    #define T Period
    #define TSeq PeriodSeq

    #define T_initialize_w_params ice::Period_initialize_w_params

    #define T_finalize_w_params   ice::Period_finalize_w_params
    #define T_copy       ice::Period_copy

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
    const char *EffectiveTimeTypeTYPENAME = "ice::EffectiveTimeType";

    DDS_TypeCode* EffectiveTimeType_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;

        static DDS_TypeCode_Member EffectiveTimeType_g_tc_members[2]=
        {

            {
                (char *)"et_datetime",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                et_datetime, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"et_period",/* Member name */
                {
                    0, /* Ignored */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                et_period, 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PRIVATE_MEMBER,/* Member visibility */ 

                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode EffectiveTimeType_g_tc =
        {{
                DDS_TK_ENUM,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ice::EffectiveTimeType", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                EffectiveTimeType_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for EffectiveTimeType*/

        if (is_initialized) {
            return &EffectiveTimeType_g_tc;
        }

        is_initialized = RTI_TRUE;

        return &EffectiveTimeType_g_tc;
    }

    RTIBool EffectiveTimeType_initialize(
        EffectiveTimeType* sample) {
        *sample = et_datetime;
        return RTI_TRUE;
    }

    RTIBool EffectiveTimeType_initialize_ex(
        EffectiveTimeType* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EffectiveTimeType_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EffectiveTimeType_initialize_w_params(
        EffectiveTimeType* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }
        *sample = et_datetime;
        return RTI_TRUE;
    }

    void EffectiveTimeType_finalize(
        EffectiveTimeType* sample)
    {

        if (sample==NULL) {
            return;
        }
    }

    void EffectiveTimeType_finalize_ex(
        EffectiveTimeType* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EffectiveTimeType_finalize_w_params(
            sample,&deallocParams);
    }

    void EffectiveTimeType_finalize_w_params(
        EffectiveTimeType* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void EffectiveTimeType_finalize_optional_members(
        EffectiveTimeType* sample, RTIBool deletePointers)
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

    RTIBool EffectiveTimeType_copy(
        EffectiveTimeType* dst,
        const EffectiveTimeType* src)
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
    * Configure and implement 'EffectiveTimeType' sequence class.
    */
    #define T EffectiveTimeType
    #define TSeq EffectiveTimeTypeSeq

    #define T_initialize_w_params ice::EffectiveTimeType_initialize_w_params

    #define T_finalize_w_params   ice::EffectiveTimeType_finalize_w_params
    #define T_copy       ice::EffectiveTimeType_copy

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
    const char *EffectiveTimeTYPENAME = "ice::EffectiveTime";

    DDS_TypeCode* EffectiveTime_get_typecode()
    {
        static RTIBool is_initialized = RTI_FALSE;
        static DDS_Long EffectiveTime_g_tc_datetime_labels[2] = {(DDS_Long)(ice::et_datetime), RTI_CDR_TYPE_CODE_UNION_DEFAULT_LABEL};

        static DDS_TypeCode_Member EffectiveTime_g_tc_members[2]=
        {

            {
                (char *)"period",/* Member name */
                {
                    1,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                1, /* Number of labels */
                (ice::et_period), /* First label Cpp (ice::et_period) */
                NULL, /* Labels (it is NULL when there is only one label)*/
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }, 
            {
                (char *)"datetime",/* Member name */
                {
                    2,/* Representation ID */          
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                2, /* Number of labels */
                (ice::et_datetime), /* First label Cpp (ice::et_datetime) */
                /* Labels (it is NULL when there is only one label)*/
                EffectiveTime_g_tc_datetime_labels, 
                RTI_CDR_NONKEY_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                1,
                NULL/* Ignored */
            }
        };

        static DDS_TypeCode EffectiveTime_g_tc =
        {{
                DDS_TK_UNION,/* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                1, /*Ignored*/
                (char *)"ice::EffectiveTime", /* Name */
                NULL,     /* Base class type code is assigned later */      
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                2, /* Number of members */
                EffectiveTime_g_tc_members, /* Members */
                DDS_VM_NONE   /* Type Modifier */        
            }}; /* Type code for EffectiveTime*/

        if (is_initialized) {
            return &EffectiveTime_g_tc;
        }

        EffectiveTime_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)ice::Period_get_typecode();

        EffectiveTime_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)ice::CT_dateTime_get_typecode();

        /* Discriminator type code */
        EffectiveTime_g_tc._data._typeCode = (RTICdrTypeCode *)ice::EffectiveTimeType_get_typecode();

        is_initialized = RTI_TRUE;

        return &EffectiveTime_g_tc;
    }

    DDS_LongLong EffectiveTime_getDefaultDiscriminator(){

        return 0;
    }

    RTIBool EffectiveTime_initialize(
        EffectiveTime* sample) {
        return ice::EffectiveTime_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
    }

    RTIBool EffectiveTime_initialize_ex(
        EffectiveTime* sample,RTIBool allocatePointers, RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ice::EffectiveTime_initialize_w_params(
            sample,&allocParams);

    }

    RTIBool EffectiveTime_initialize_w_params(
        EffectiveTime* sample, const struct DDS_TypeAllocationParams_t * allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        sample->_d = (ice::EffectiveTimeType)EffectiveTime_getDefaultDiscriminator();
        if (!ice::Period_initialize_w_params(&sample->_u.period,
        allocParams)) {
            return RTI_FALSE;
        }
        if (!ice::CT_dateTime_initialize_w_params(&sample->_u.datetime,
        allocParams)) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    void EffectiveTime_finalize(
        EffectiveTime* sample)
    {

        ice::EffectiveTime_finalize_ex(sample,RTI_TRUE);
    }

    void EffectiveTime_finalize_ex(
        EffectiveTime* sample,RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ice::EffectiveTime_finalize_w_params(
            sample,&deallocParams);
    }

    void EffectiveTime_finalize_w_params(
        EffectiveTime* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
    {

        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

        ice::Period_finalize_w_params(&sample->_u.period,deallocParams);

        ice::CT_dateTime_finalize_w_params(&sample->_u.datetime,deallocParams);

    }

    void EffectiveTime_finalize_optional_members(
        EffectiveTime* sample, RTIBool deletePointers)
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

        switch(sample->_d) {
            case (ice::et_period):
                {
                    ice::Period_finalize_optional_members(&sample->_u.period, deallocParams->delete_pointers);
            } break ;
            case (ice::et_datetime):
                default:
                {
                    ice::CT_dateTime_finalize_optional_members(&sample->_u.datetime, deallocParams->delete_pointers);
            } break ;
        }
    }

    RTIBool EffectiveTime_copy(
        EffectiveTime* dst,
        const EffectiveTime* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!ice::EffectiveTimeType_copy(
                &dst->_d,(const ice::EffectiveTimeType*)&src->_d)) {
                return RTI_FALSE;
            } 

            switch(src->_d) {

                case (ice::et_period):
                    {
                        if (!ice::Period_copy(
                            &dst->_u.period,(const ice::Period*)&src->_u.period)) {
                            return RTI_FALSE;
                    } 
                } break ;
                case (ice::et_datetime):
                    default:
                    {
                        if (!ice::CT_dateTime_copy(
                            &dst->_u.datetime,(const ice::CT_dateTime*)&src->_u.datetime)) {
                            return RTI_FALSE;
                    } 
                } break ;

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
    * Configure and implement 'EffectiveTime' sequence class.
    */
    #define T EffectiveTime
    #define TSeq EffectiveTimeSeq

    #define T_initialize_w_params ice::EffectiveTime_initialize_w_params

    #define T_finalize_w_params   ice::EffectiveTime_finalize_w_params
    #define T_copy       ice::EffectiveTime_copy

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

