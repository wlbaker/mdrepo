

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from common.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef common_1183388197_h
#define common_1183388197_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

namespace ice {
    static const DDS_Long DDS_DOMAIN_ID_MANAGER= 2;
    static const DDS_Char * DICES_28MAY_QOS_LIBRARY_NAME= "dices_dim_library";
    static const DDS_Char * DICES_28MAY_QOS_PROFILE_NAME= "dices_dim_durable_profile";
    static const DDS_Long TINY_STRING_LEN= 8;
    static const DDS_Long SHORTSHORT_STRING_LEN= 16;
    static const DDS_Long SHORT_STRING_LEN= 32;
    static const DDS_Long MEDIUM_STRING_LEN= 64;
    static const DDS_Long LONG_STRING_LEN= 128;
    static const DDS_Long LONGLONG_STRING_LEN= 250;
    static const DDS_UnsignedLong DIM_HANDLE_MANAGER= 1;
    static const DDS_UnsignedLong DIM_HANDLE_MDS= 10;
    static const DDS_Long NOT_A_NUMBER= 0x7fffff;
    typedef    DDS_Octet   OCTET ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* OCTET_get_typecode(void); /* Type code */

    DDS_SEQUENCE(OCTETSeq, OCTET);

    NDDSUSERDllExport
    RTIBool OCTET_initialize(
        OCTET* self);

    NDDSUSERDllExport
    RTIBool OCTET_initialize_ex(
        OCTET* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool OCTET_initialize_w_params(
        OCTET* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void OCTET_finalize(
        OCTET* self);

    NDDSUSERDllExport
    void OCTET_finalize_ex(
        OCTET* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void OCTET_finalize_w_params(
        OCTET* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void OCTET_finalize_optional_members(
        OCTET* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool OCTET_copy(
        OCTET* dst,
        const OCTET* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::OCTET   INTU8 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INTU8_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INTU8Seq, INTU8);

    NDDSUSERDllExport
    RTIBool INTU8_initialize(
        INTU8* self);

    NDDSUSERDllExport
    RTIBool INTU8_initialize_ex(
        INTU8* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INTU8_initialize_w_params(
        INTU8* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INTU8_finalize(
        INTU8* self);

    NDDSUSERDllExport
    void INTU8_finalize_ex(
        INTU8* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INTU8_finalize_w_params(
        INTU8* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INTU8_finalize_optional_members(
        INTU8* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INTU8_copy(
        INTU8* dst,
        const INTU8* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Short   INT16 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INT16_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INT16Seq, INT16);

    NDDSUSERDllExport
    RTIBool INT16_initialize(
        INT16* self);

    NDDSUSERDllExport
    RTIBool INT16_initialize_ex(
        INT16* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INT16_initialize_w_params(
        INT16* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INT16_finalize(
        INT16* self);

    NDDSUSERDllExport
    void INT16_finalize_ex(
        INT16* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INT16_finalize_w_params(
        INT16* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INT16_finalize_optional_members(
        INT16* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INT16_copy(
        INT16* dst,
        const INT16* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_UnsignedShort   INTU16 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INTU16_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INTU16Seq, INTU16);

    NDDSUSERDllExport
    RTIBool INTU16_initialize(
        INTU16* self);

    NDDSUSERDllExport
    RTIBool INTU16_initialize_ex(
        INTU16* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INTU16_initialize_w_params(
        INTU16* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INTU16_finalize(
        INTU16* self);

    NDDSUSERDllExport
    void INTU16_finalize_ex(
        INTU16* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INTU16_finalize_w_params(
        INTU16* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INTU16_finalize_optional_members(
        INTU16* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INTU16_copy(
        INTU16* dst,
        const INTU16* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Long   INT32 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INT32_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INT32Seq, INT32);

    NDDSUSERDllExport
    RTIBool INT32_initialize(
        INT32* self);

    NDDSUSERDllExport
    RTIBool INT32_initialize_ex(
        INT32* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INT32_initialize_w_params(
        INT32* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INT32_finalize(
        INT32* self);

    NDDSUSERDllExport
    void INT32_finalize_ex(
        INT32* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INT32_finalize_w_params(
        INT32* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INT32_finalize_optional_members(
        INT32* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INT32_copy(
        INT32* dst,
        const INT32* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_UnsignedLong   INTU32 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INTU32_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INTU32Seq, INTU32);

    NDDSUSERDllExport
    RTIBool INTU32_initialize(
        INTU32* self);

    NDDSUSERDllExport
    RTIBool INTU32_initialize_ex(
        INTU32* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INTU32_initialize_w_params(
        INTU32* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INTU32_finalize(
        INTU32* self);

    NDDSUSERDllExport
    void INTU32_finalize_ex(
        INTU32* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INTU32_finalize_w_params(
        INTU32* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INTU32_finalize_optional_members(
        INTU32* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INTU32_copy(
        INTU32* dst,
        const INTU32* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_UnsignedLongLong   INTU64 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* INTU64_get_typecode(void); /* Type code */

    DDS_SEQUENCE(INTU64Seq, INTU64);

    NDDSUSERDllExport
    RTIBool INTU64_initialize(
        INTU64* self);

    NDDSUSERDllExport
    RTIBool INTU64_initialize_ex(
        INTU64* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool INTU64_initialize_w_params(
        INTU64* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void INTU64_finalize(
        INTU64* self);

    NDDSUSERDllExport
    void INTU64_finalize_ex(
        INTU64* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void INTU64_finalize_w_params(
        INTU64* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void INTU64_finalize_optional_members(
        INTU64* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool INTU64_copy(
        INTU64* dst,
        const INTU64* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   BITS16 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* BITS16_get_typecode(void); /* Type code */

    DDS_SEQUENCE(BITS16Seq, BITS16);

    NDDSUSERDllExport
    RTIBool BITS16_initialize(
        BITS16* self);

    NDDSUSERDllExport
    RTIBool BITS16_initialize_ex(
        BITS16* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool BITS16_initialize_w_params(
        BITS16* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void BITS16_finalize(
        BITS16* self);

    NDDSUSERDllExport
    void BITS16_finalize_ex(
        BITS16* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void BITS16_finalize_w_params(
        BITS16* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void BITS16_finalize_optional_members(
        BITS16* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool BITS16_copy(
        BITS16* dst,
        const BITS16* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU32   BITS32 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* BITS32_get_typecode(void); /* Type code */

    DDS_SEQUENCE(BITS32Seq, BITS32);

    NDDSUSERDllExport
    RTIBool BITS32_initialize(
        BITS32* self);

    NDDSUSERDllExport
    RTIBool BITS32_initialize_ex(
        BITS32* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool BITS32_initialize_w_params(
        BITS32* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void BITS32_finalize(
        BITS32* self);

    NDDSUSERDllExport
    void BITS32_finalize_ex(
        BITS32* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void BITS32_finalize_w_params(
        BITS32* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void BITS32_finalize_optional_members(
        BITS32* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool BITS32_copy(
        BITS32* dst,
        const BITS32* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU64   BITS64 ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* BITS64_get_typecode(void); /* Type code */

    DDS_SEQUENCE(BITS64Seq, BITS64);

    NDDSUSERDllExport
    RTIBool BITS64_initialize(
        BITS64* self);

    NDDSUSERDllExport
    RTIBool BITS64_initialize_ex(
        BITS64* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool BITS64_initialize_w_params(
        BITS64* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void BITS64_finalize(
        BITS64* self);

    NDDSUSERDllExport
    void BITS64_finalize_ex(
        BITS64* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void BITS64_finalize_w_params(
        BITS64* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void BITS64_finalize_optional_members(
        BITS64* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool BITS64_copy(
        BITS64* dst,
        const BITS64* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Long   TIME_T ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* TIME_T_get_typecode(void); /* Type code */

    DDS_SEQUENCE(TIME_TSeq, TIME_T);

    NDDSUSERDllExport
    RTIBool TIME_T_initialize(
        TIME_T* self);

    NDDSUSERDllExport
    RTIBool TIME_T_initialize_ex(
        TIME_T* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool TIME_T_initialize_w_params(
        TIME_T* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void TIME_T_finalize(
        TIME_T* self);

    NDDSUSERDllExport
    void TIME_T_finalize_ex(
        TIME_T* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void TIME_T_finalize_w_params(
        TIME_T* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void TIME_T_finalize_optional_members(
        TIME_T* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool TIME_T_copy(
        TIME_T* dst,
        const TIME_T* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Boolean   BOOL ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* BOOL_get_typecode(void); /* Type code */

    DDS_SEQUENCE(BOOLSeq, BOOL);

    NDDSUSERDllExport
    RTIBool BOOL_initialize(
        BOOL* self);

    NDDSUSERDllExport
    RTIBool BOOL_initialize_ex(
        BOOL* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool BOOL_initialize_w_params(
        BOOL* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void BOOL_finalize(
        BOOL* self);

    NDDSUSERDllExport
    void BOOL_finalize_ex(
        BOOL* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void BOOL_finalize_w_params(
        BOOL* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void BOOL_finalize_optional_members(
        BOOL* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool BOOL_copy(
        BOOL* dst,
        const BOOL* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   OIDType ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* OIDType_get_typecode(void); /* Type code */

    DDS_SEQUENCE(OIDTypeSeq, OIDType);

    NDDSUSERDllExport
    RTIBool OIDType_initialize(
        OIDType* self);

    NDDSUSERDllExport
    RTIBool OIDType_initialize_ex(
        OIDType* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool OIDType_initialize_w_params(
        OIDType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void OIDType_finalize(
        OIDType* self);

    NDDSUSERDllExport
    void OIDType_finalize_ex(
        OIDType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void OIDType_finalize_w_params(
        OIDType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void OIDType_finalize_optional_members(
        OIDType* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool OIDType_copy(
        OIDType* dst,
        const OIDType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   PrivateOid ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* PrivateOid_get_typecode(void); /* Type code */

    DDS_SEQUENCE(PrivateOidSeq, PrivateOid);

    NDDSUSERDllExport
    RTIBool PrivateOid_initialize(
        PrivateOid* self);

    NDDSUSERDllExport
    RTIBool PrivateOid_initialize_ex(
        PrivateOid* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool PrivateOid_initialize_w_params(
        PrivateOid* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void PrivateOid_finalize(
        PrivateOid* self);

    NDDSUSERDllExport
    void PrivateOid_finalize_ex(
        PrivateOid* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void PrivateOid_finalize_w_params(
        PrivateOid* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void PrivateOid_finalize_optional_members(
        PrivateOid* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool PrivateOid_copy(
        PrivateOid* dst,
        const PrivateOid* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   HANDLE ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* HANDLE_get_typecode(void); /* Type code */

    DDS_SEQUENCE(HANDLESeq, HANDLE);

    NDDSUSERDllExport
    RTIBool HANDLE_initialize(
        HANDLE* self);

    NDDSUSERDllExport
    RTIBool HANDLE_initialize_ex(
        HANDLE* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool HANDLE_initialize_w_params(
        HANDLE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void HANDLE_finalize(
        HANDLE* self);

    NDDSUSERDllExport
    void HANDLE_finalize_ex(
        HANDLE* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void HANDLE_finalize_w_params(
        HANDLE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void HANDLE_finalize_optional_members(
        HANDLE* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool HANDLE_copy(
        HANDLE* dst,
        const HANDLE* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    static const DDS_Long MAX_LEN_ICE_ID= 16;
    typedef    DDS_Char *   ICE_ID ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ICE_ID_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ICE_IDSeq, ICE_ID);

    NDDSUSERDllExport
    RTIBool ICE_ID_initialize(
        ICE_ID* self);

    NDDSUSERDllExport
    RTIBool ICE_ID_initialize_ex(
        ICE_ID* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ICE_ID_initialize_w_params(
        ICE_ID* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ICE_ID_finalize(
        ICE_ID* self);

    NDDSUSERDllExport
    void ICE_ID_finalize_ex(
        ICE_ID* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ICE_ID_finalize_w_params(
        ICE_ID* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ICE_ID_finalize_optional_members(
        ICE_ID* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ICE_ID_copy(
        ICE_ID* dst,
        const ICE_ID* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   InstNumber ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* InstNumber_get_typecode(void); /* Type code */

    DDS_SEQUENCE(InstNumberSeq, InstNumber);

    NDDSUSERDllExport
    RTIBool InstNumber_initialize(
        InstNumber* self);

    NDDSUSERDllExport
    RTIBool InstNumber_initialize_ex(
        InstNumber* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool InstNumber_initialize_w_params(
        InstNumber* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void InstNumber_finalize(
        InstNumber* self);

    NDDSUSERDllExport
    void InstNumber_finalize_ex(
        InstNumber* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void InstNumber_finalize_w_params(
        InstNumber* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void InstNumber_finalize_optional_members(
        InstNumber* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool InstNumber_copy(
        InstNumber* dst,
        const InstNumber* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Float   FLOATType ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* FLOATType_get_typecode(void); /* Type code */

    DDS_SEQUENCE(FLOATTypeSeq, FLOATType);

    NDDSUSERDllExport
    RTIBool FLOATType_initialize(
        FLOATType* self);

    NDDSUSERDllExport
    RTIBool FLOATType_initialize_ex(
        FLOATType* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool FLOATType_initialize_w_params(
        FLOATType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void FLOATType_finalize(
        FLOATType* self);

    NDDSUSERDllExport
    void FLOATType_finalize_ex(
        FLOATType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void FLOATType_finalize_w_params(
        FLOATType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void FLOATType_finalize_optional_members(
        FLOATType* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool FLOATType_copy(
        FLOATType* dst,
        const FLOATType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   MdsContext ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MdsContext_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MdsContextSeq, MdsContext);

    NDDSUSERDllExport
    RTIBool MdsContext_initialize(
        MdsContext* self);

    NDDSUSERDllExport
    RTIBool MdsContext_initialize_ex(
        MdsContext* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MdsContext_initialize_w_params(
        MdsContext* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MdsContext_finalize(
        MdsContext* self);

    NDDSUSERDllExport
    void MdsContext_finalize_ex(
        MdsContext* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MdsContext_finalize_w_params(
        MdsContext* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MdsContext_finalize_optional_members(
        MdsContext* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MdsContext_copy(
        MdsContext* dst,
        const MdsContext* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *GLBHANDLETYPENAME;

    struct GLBHANDLESeq;

    class GLBHANDLE 
    {
      public:
        typedef struct GLBHANDLESeq Seq;

        ice::MdsContext   context_id ;
        ice::HANDLE   handle ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* GLBHANDLE_get_typecode(void); /* Type code */

    DDS_SEQUENCE(GLBHANDLESeq, GLBHANDLE);

    NDDSUSERDllExport
    RTIBool GLBHANDLE_initialize(
        GLBHANDLE* self);

    NDDSUSERDllExport
    RTIBool GLBHANDLE_initialize_ex(
        GLBHANDLE* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool GLBHANDLE_initialize_w_params(
        GLBHANDLE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void GLBHANDLE_finalize(
        GLBHANDLE* self);

    NDDSUSERDllExport
    void GLBHANDLE_finalize_ex(
        GLBHANDLE* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void GLBHANDLE_finalize_w_params(
        GLBHANDLE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void GLBHANDLE_finalize_optional_members(
        GLBHANDLE* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool GLBHANDLE_copy(
        GLBHANDLE* dst,
        const GLBHANDLE* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *ManagedObjectIdTYPENAME;

    struct ManagedObjectIdSeq;

    class ManagedObjectId 
    {
      public:
        typedef struct ManagedObjectIdSeq Seq;

        ice::OIDType   m_obj_class ;
        ice::GLBHANDLE   m_obj_inst ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ManagedObjectId_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ManagedObjectIdSeq, ManagedObjectId);

    NDDSUSERDllExport
    RTIBool ManagedObjectId_initialize(
        ManagedObjectId* self);

    NDDSUSERDllExport
    RTIBool ManagedObjectId_initialize_ex(
        ManagedObjectId* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ManagedObjectId_initialize_w_params(
        ManagedObjectId* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ManagedObjectId_finalize(
        ManagedObjectId* self);

    NDDSUSERDllExport
    void ManagedObjectId_finalize_ex(
        ManagedObjectId* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ManagedObjectId_finalize_w_params(
        ManagedObjectId* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ManagedObjectId_finalize_optional_members(
        ManagedObjectId* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ManagedObjectId_copy(
        ManagedObjectId* dst,
        const ManagedObjectId* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum NomPartition
    {
        nom_part_unspec  = 0,      
        nom_part_obj  = 1,      
        nom_part_metric  = 2,      
        nom_part_alert  = 3,      
        nom_part_dim  = 4,      
        nom_part_vattr  = 5,      
        nom_part_pgrp  = 6,      
        nom_part_sites  = 7,      
        nom_part_infrastruct  = 8,      
        nom_part_fef  = 9,      
        nom_part_ecg_extn  = 10,      
        nom_part_ext_nom  = 256,      
        nom_part_priv  = 1024     
    } NomPartition;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* NomPartition_get_typecode(void); /* Type code */

    DDS_SEQUENCE(NomPartitionSeq, NomPartition);

    NDDSUSERDllExport
    RTIBool NomPartition_initialize(
        NomPartition* self);

    NDDSUSERDllExport
    RTIBool NomPartition_initialize_ex(
        NomPartition* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool NomPartition_initialize_w_params(
        NomPartition* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void NomPartition_finalize(
        NomPartition* self);

    NDDSUSERDllExport
    void NomPartition_finalize_ex(
        NomPartition* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void NomPartition_finalize_w_params(
        NomPartition* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void NomPartition_finalize_optional_members(
        NomPartition* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool NomPartition_copy(
        NomPartition* dst,
        const NomPartition* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *TYPETYPENAME;

    struct TYPESeq;

    class TYPE 
    {
      public:
        typedef struct TYPESeq Seq;

        ice::NomPartition   partition ;
        ice::OIDType   code ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* TYPE_get_typecode(void); /* Type code */

    DDS_SEQUENCE(TYPESeq, TYPE);

    NDDSUSERDllExport
    RTIBool TYPE_initialize(
        TYPE* self);

    NDDSUSERDllExport
    RTIBool TYPE_initialize_ex(
        TYPE* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool TYPE_initialize_w_params(
        TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void TYPE_finalize(
        TYPE* self);

    NDDSUSERDllExport
    void TYPE_finalize_ex(
        TYPE* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void TYPE_finalize_w_params(
        TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void TYPE_finalize_optional_members(
        TYPE* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool TYPE_copy(
        TYPE* dst,
        const TYPE* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *TimespecTYPENAME;

    struct TimespecSeq;

    class Timespec 
    {
      public:
        typedef struct TimespecSeq Seq;

        DDS_Long   seconds ;
        DDS_Long   nanoseconds ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Timespec_get_typecode(void); /* Type code */

    DDS_SEQUENCE(TimespecSeq, Timespec);

    NDDSUSERDllExport
    RTIBool Timespec_initialize(
        Timespec* self);

    NDDSUSERDllExport
    RTIBool Timespec_initialize_ex(
        Timespec* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Timespec_initialize_w_params(
        Timespec* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Timespec_finalize(
        Timespec* self);

    NDDSUSERDllExport
    void Timespec_finalize_ex(
        Timespec* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Timespec_finalize_w_params(
        Timespec* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Timespec_finalize_optional_members(
        Timespec* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Timespec_copy(
        Timespec* dst,
        const Timespec* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *DurationTYPENAME;

    struct DurationSeq;

    class Duration 
    {
      public:
        typedef struct DurationSeq Seq;

        DDS_Long   seconds ;
        DDS_Long   nanoseconds ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Duration_get_typecode(void); /* Type code */

    DDS_SEQUENCE(DurationSeq, Duration);

    NDDSUSERDllExport
    RTIBool Duration_initialize(
        Duration* self);

    NDDSUSERDllExport
    RTIBool Duration_initialize_ex(
        Duration* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Duration_initialize_w_params(
        Duration* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Duration_finalize(
        Duration* self);

    NDDSUSERDllExport
    void Duration_finalize_ex(
        Duration* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Duration_finalize_w_params(
        Duration* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Duration_finalize_optional_members(
        Duration* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Duration_copy(
        Duration* dst,
        const Duration* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *DateTYPENAME;

    struct DateSeq;

    class Date 
    {
      public:
        typedef struct DateSeq Seq;

        ice::INTU8   century ;
        ice::INTU8   year ;
        ice::INTU8   month ;
        ice::INTU8   day ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Date_get_typecode(void); /* Type code */

    DDS_SEQUENCE(DateSeq, Date);

    NDDSUSERDllExport
    RTIBool Date_initialize(
        Date* self);

    NDDSUSERDllExport
    RTIBool Date_initialize_ex(
        Date* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Date_initialize_w_params(
        Date* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Date_finalize(
        Date* self);

    NDDSUSERDllExport
    void Date_finalize_ex(
        Date* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Date_finalize_w_params(
        Date* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Date_finalize_optional_members(
        Date* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Date_copy(
        Date* dst,
        const Date* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum SimpleColor
    {
        col_black  = 0,      
        col_red  = 1,      
        col_green  = 2,      
        col_yellow  = 3,      
        col_blue  = 4,      
        col_magenta  = 5,      
        col_cyan  = 6,      
        col_white  = 7     
    } SimpleColor;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* SimpleColor_get_typecode(void); /* Type code */

    DDS_SEQUENCE(SimpleColorSeq, SimpleColor);

    NDDSUSERDllExport
    RTIBool SimpleColor_initialize(
        SimpleColor* self);

    NDDSUSERDllExport
    RTIBool SimpleColor_initialize_ex(
        SimpleColor* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool SimpleColor_initialize_w_params(
        SimpleColor* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void SimpleColor_finalize(
        SimpleColor* self);

    NDDSUSERDllExport
    void SimpleColor_finalize_ex(
        SimpleColor* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void SimpleColor_finalize_w_params(
        SimpleColor* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void SimpleColor_finalize_optional_members(
        SimpleColor* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool SimpleColor_copy(
        SimpleColor* dst,
        const SimpleColor* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum CharSet
    {
        charset_unspec  = 0,      
        charset_iso_10646_ucs_2  = 1000,      
        charset_iso_10646_ucs_4  = 1001,      
        charset_iso_8859_1  = 4,      
        charset_iso_8859_2  = 5,      
        charset_iso_8859_3  = 6,      
        charset_iso_8859_4  = 7,      
        charset_iso_8859_5  = 8,      
        charset_iso_8859_6  = 9,      
        charset_iso_8859_7  = 10,      
        charset_iso_8859_8  = 11,      
        charset_iso_8859_9  = 12,      
        charset_iso_8859_10  = 13,      
        charset_iso_8859_13  = 109,      
        charset_iso_8859_14  = 110,      
        charset_iso_8859_15  = 111,      
        charset_iso_2022_kr  = 37,      
        charset_ks_c_5601  = 36,      
        charset_iso_2022_jp  = 39,      
        charset_iso_2022_jp_2  = 40,      
        charset_jis_x0208  = 63,      
        charset_iso_2022_cn  = 104,      
        charset_gb_2312  = 2025     
    } CharSet;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CharSet_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CharSetSeq, CharSet);

    NDDSUSERDllExport
    RTIBool CharSet_initialize(
        CharSet* self);

    NDDSUSERDllExport
    RTIBool CharSet_initialize_ex(
        CharSet* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CharSet_initialize_w_params(
        CharSet* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CharSet_finalize(
        CharSet* self);

    NDDSUSERDllExport
    void CharSet_finalize_ex(
        CharSet* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CharSet_finalize_w_params(
        CharSet* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CharSet_finalize_optional_members(
        CharSet* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CharSet_copy(
        CharSet* dst,
        const CharSet* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   StringFlags ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* StringFlags_get_typecode(void); /* Type code */

    DDS_SEQUENCE(StringFlagsSeq, StringFlags);

    NDDSUSERDllExport
    RTIBool StringFlags_initialize(
        StringFlags* self);

    NDDSUSERDllExport
    RTIBool StringFlags_initialize_ex(
        StringFlags* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool StringFlags_initialize_w_params(
        StringFlags* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void StringFlags_finalize(
        StringFlags* self);

    NDDSUSERDllExport
    void StringFlags_finalize_ex(
        StringFlags* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void StringFlags_finalize_w_params(
        StringFlags* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void StringFlags_finalize_optional_members(
        StringFlags* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool StringFlags_copy(
        StringFlags* dst,
        const StringFlags* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum StringFlagsBits
    {
        str_flag_nt  = 1     
    } StringFlagsBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* StringFlagsBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(StringFlagsBitsSeq, StringFlagsBits);

    NDDSUSERDllExport
    RTIBool StringFlagsBits_initialize(
        StringFlagsBits* self);

    NDDSUSERDllExport
    RTIBool StringFlagsBits_initialize_ex(
        StringFlagsBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool StringFlagsBits_initialize_w_params(
        StringFlagsBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void StringFlagsBits_finalize(
        StringFlagsBits* self);

    NDDSUSERDllExport
    void StringFlagsBits_finalize_ex(
        StringFlagsBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void StringFlagsBits_finalize_w_params(
        StringFlagsBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void StringFlagsBits_finalize_optional_members(
        StringFlagsBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool StringFlagsBits_copy(
        StringFlagsBits* dst,
        const StringFlagsBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *StringSpecTYPENAME;

    struct StringSpecSeq;

    class StringSpec 
    {
      public:
        typedef struct StringSpecSeq Seq;

        ice::INTU16   str_max_len ;
        ice::StringFlags   str_flags ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* StringSpec_get_typecode(void); /* Type code */

    DDS_SEQUENCE(StringSpecSeq, StringSpec);

    NDDSUSERDllExport
    RTIBool StringSpec_initialize(
        StringSpec* self);

    NDDSUSERDllExport
    RTIBool StringSpec_initialize_ex(
        StringSpec* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool StringSpec_initialize_w_params(
        StringSpec* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void StringSpec_finalize(
        StringSpec* self);

    NDDSUSERDllExport
    void StringSpec_finalize_ex(
        StringSpec* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void StringSpec_finalize_w_params(
        StringSpec* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void StringSpec_finalize_optional_members(
        StringSpec* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool StringSpec_copy(
        StringSpec* dst,
        const StringSpec* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *LocaleTYPENAME;

    struct LocaleSeq;

    class Locale 
    {
      public:
        typedef struct LocaleSeq Seq;

        ice::INTU32   language ;
        ice::INTU32   country ;
        ice::CharSet   charset ;
        ice::StringSpec   str_spec ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Locale_get_typecode(void); /* Type code */

    DDS_SEQUENCE(LocaleSeq, Locale);

    NDDSUSERDllExport
    RTIBool Locale_initialize(
        Locale* self);

    NDDSUSERDllExport
    RTIBool Locale_initialize_ex(
        Locale* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Locale_initialize_w_params(
        Locale* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Locale_finalize(
        Locale* self);

    NDDSUSERDllExport
    void Locale_finalize_ex(
        Locale* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Locale_finalize_w_params(
        Locale* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Locale_finalize_optional_members(
        Locale* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Locale_copy(
        Locale* dst,
        const Locale* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::INTU32 LocaleLanguageEnglish= 0x656E0000;

    static const ice::INTU32 LocaleCountryUSA= 0x55530000;
    static const DDS_Long LocaleCharSetUTF8= 4;

    static const ice::INTU16 LocaleStrMaxLen= 256;

    extern const char *ExtNomenRefTYPENAME;

    struct ExtNomenRefSeq;

    class ExtNomenRef 
    {
      public:
        typedef struct ExtNomenRefSeq Seq;

        ice::OIDType   nomenclature_id ;
        DDS_Char *   nomenclature_code ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ExtNomenRef_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ExtNomenRefSeq, ExtNomenRef);

    NDDSUSERDllExport
    RTIBool ExtNomenRef_initialize(
        ExtNomenRef* self);

    NDDSUSERDllExport
    RTIBool ExtNomenRef_initialize_ex(
        ExtNomenRef* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ExtNomenRef_initialize_w_params(
        ExtNomenRef* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ExtNomenRef_finalize(
        ExtNomenRef* self);

    NDDSUSERDllExport
    void ExtNomenRef_finalize_ex(
        ExtNomenRef* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ExtNomenRef_finalize_w_params(
        ExtNomenRef* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ExtNomenRef_finalize_optional_members(
        ExtNomenRef* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ExtNomenRef_copy(
        ExtNomenRef* dst,
        const ExtNomenRef* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *SystemModelTYPENAME;

    struct SystemModelSeq;

    class SystemModel 
    {
      public:
        typedef struct SystemModelSeq Seq;

        DDS_Char *   manufacturer ;
        DDS_Char *   model_number ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* SystemModel_get_typecode(void); /* Type code */

    DDS_SEQUENCE(SystemModelSeq, SystemModel);

    NDDSUSERDllExport
    RTIBool SystemModel_initialize(
        SystemModel* self);

    NDDSUSERDllExport
    RTIBool SystemModel_initialize_ex(
        SystemModel* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool SystemModel_initialize_w_params(
        SystemModel* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void SystemModel_finalize(
        SystemModel* self);

    NDDSUSERDllExport
    void SystemModel_finalize_ex(
        SystemModel* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void SystemModel_finalize_w_params(
        SystemModel* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void SystemModel_finalize_optional_members(
        SystemModel* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool SystemModel_copy(
        SystemModel* dst,
        const SystemModel* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum ProdSpecType
    {
        unspecified  = 0,      
        serial_number  = 1,      
        part_number  = 2,      
        hw_revision  = 3,      
        sw_revision  = 4,      
        fw_revision  = 5,      
        protocol_revision  = 6,      
        prod_spec_gmdn  = 7,      
        prod_spec_udi  = 8     
    } ProdSpecType;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ProdSpecType_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ProdSpecTypeSeq, ProdSpecType);

    NDDSUSERDllExport
    RTIBool ProdSpecType_initialize(
        ProdSpecType* self);

    NDDSUSERDllExport
    RTIBool ProdSpecType_initialize_ex(
        ProdSpecType* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ProdSpecType_initialize_w_params(
        ProdSpecType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ProdSpecType_finalize(
        ProdSpecType* self);

    NDDSUSERDllExport
    void ProdSpecType_finalize_ex(
        ProdSpecType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ProdSpecType_finalize_w_params(
        ProdSpecType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ProdSpecType_finalize_optional_members(
        ProdSpecType* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ProdSpecType_copy(
        ProdSpecType* dst,
        const ProdSpecType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *ProdSpecEntryTYPENAME;

    struct ProdSpecEntrySeq;

    class ProdSpecEntry 
    {
      public:
        typedef struct ProdSpecEntrySeq Seq;

        ice::ProdSpecType   spec_type ;
        ice::PrivateOid   component_id ;
        DDS_Char *   prod_spec ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ProdSpecEntry_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ProdSpecEntrySeq, ProdSpecEntry);

    NDDSUSERDllExport
    RTIBool ProdSpecEntry_initialize(
        ProdSpecEntry* self);

    NDDSUSERDllExport
    RTIBool ProdSpecEntry_initialize_ex(
        ProdSpecEntry* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ProdSpecEntry_initialize_w_params(
        ProdSpecEntry* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ProdSpecEntry_finalize(
        ProdSpecEntry* self);

    NDDSUSERDllExport
    void ProdSpecEntry_finalize_ex(
        ProdSpecEntry* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ProdSpecEntry_finalize_w_params(
        ProdSpecEntry* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ProdSpecEntry_finalize_optional_members(
        ProdSpecEntry* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ProdSpecEntry_copy(
        ProdSpecEntry* dst,
        const ProdSpecEntry* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef     ice::ProdSpecEntrySeq  ProductionSpec ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* ProductionSpec_get_typecode(void); /* Type code */

    DDS_SEQUENCE(ProductionSpecSeq, ProductionSpec);

    NDDSUSERDllExport
    RTIBool ProductionSpec_initialize(
        ProductionSpec* self);

    NDDSUSERDllExport
    RTIBool ProductionSpec_initialize_ex(
        ProductionSpec* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ProductionSpec_initialize_w_params(
        ProductionSpec* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void ProductionSpec_finalize(
        ProductionSpec* self);

    NDDSUSERDllExport
    void ProductionSpec_finalize_ex(
        ProductionSpec* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ProductionSpec_finalize_w_params(
        ProductionSpec* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ProductionSpec_finalize_optional_members(
        ProductionSpec* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ProductionSpec_copy(
        ProductionSpec* dst,
        const ProductionSpec* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   CurLimAlStat ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CurLimAlStat_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CurLimAlStatSeq, CurLimAlStat);

    NDDSUSERDllExport
    RTIBool CurLimAlStat_initialize(
        CurLimAlStat* self);

    NDDSUSERDllExport
    RTIBool CurLimAlStat_initialize_ex(
        CurLimAlStat* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CurLimAlStat_initialize_w_params(
        CurLimAlStat* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CurLimAlStat_finalize(
        CurLimAlStat* self);

    NDDSUSERDllExport
    void CurLimAlStat_finalize_ex(
        CurLimAlStat* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CurLimAlStat_finalize_w_params(
        CurLimAlStat* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CurLimAlStat_finalize_optional_members(
        CurLimAlStat* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CurLimAlStat_copy(
        CurLimAlStat* dst,
        const CurLimAlStat* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum CurLimAlStatBits
    {
        lim_alert_off  = 1,      
        lim_low_off  = 2,      
        lim_high_off  = 4     
    } CurLimAlStatBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CurLimAlStatBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CurLimAlStatBitsSeq, CurLimAlStatBits);

    NDDSUSERDllExport
    RTIBool CurLimAlStatBits_initialize(
        CurLimAlStatBits* self);

    NDDSUSERDllExport
    RTIBool CurLimAlStatBits_initialize_ex(
        CurLimAlStatBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CurLimAlStatBits_initialize_w_params(
        CurLimAlStatBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CurLimAlStatBits_finalize(
        CurLimAlStatBits* self);

    NDDSUSERDllExport
    void CurLimAlStatBits_finalize_ex(
        CurLimAlStatBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CurLimAlStatBits_finalize_w_params(
        CurLimAlStatBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CurLimAlStatBits_finalize_optional_members(
        CurLimAlStatBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CurLimAlStatBits_copy(
        CurLimAlStatBits* dst,
        const CurLimAlStatBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *CurLimAlValTYPENAME;

    struct CurLimAlValSeq;

    class CurLimAlVal 
    {
      public:
        typedef struct CurLimAlValSeq Seq;

        ice::FLOATType   lower ;
        ice::FLOATType   upper ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CurLimAlVal_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CurLimAlValSeq, CurLimAlVal);

    NDDSUSERDllExport
    RTIBool CurLimAlVal_initialize(
        CurLimAlVal* self);

    NDDSUSERDllExport
    RTIBool CurLimAlVal_initialize_ex(
        CurLimAlVal* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CurLimAlVal_initialize_w_params(
        CurLimAlVal* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CurLimAlVal_finalize(
        CurLimAlVal* self);

    NDDSUSERDllExport
    void CurLimAlVal_finalize_ex(
        CurLimAlVal* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CurLimAlVal_finalize_w_params(
        CurLimAlVal* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CurLimAlVal_finalize_optional_members(
        CurLimAlVal* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CurLimAlVal_copy(
        CurLimAlVal* dst,
        const CurLimAlVal* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *EventReportTYPENAME;

    struct EventReportSeq;
    #ifndef NDDS_STANDALONE_TYPE
    class EventReportTypeSupport;
    class EventReportDataWriter;
    class EventReportDataReader;
    #endif

    class EventReport 
    {
      public:
        typedef struct EventReportSeq Seq;
        #ifndef NDDS_STANDALONE_TYPE
        typedef EventReportTypeSupport TypeSupport;
        typedef EventReportDataWriter DataWriter;
        typedef EventReportDataReader DataReader;
        #endif

        ice::OIDType   object_class ;
        ice::HANDLE   object_instance ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EventReport_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EventReportSeq, EventReport);

    NDDSUSERDllExport
    RTIBool EventReport_initialize(
        EventReport* self);

    NDDSUSERDllExport
    RTIBool EventReport_initialize_ex(
        EventReport* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EventReport_initialize_w_params(
        EventReport* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EventReport_finalize(
        EventReport* self);

    NDDSUSERDllExport
    void EventReport_finalize_ex(
        EventReport* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EventReport_finalize_w_params(
        EventReport* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EventReport_finalize_optional_members(
        EventReport* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EventReport_copy(
        EventReport* dst,
        const EventReport* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum CareActivityCategory
    {
        acat_unknown  = 0,      
        acat_diet  = 1,      
        acat_drug  = 2,      
        acat_encounter  = 3,      
        acat_observation  = 4,      
        acat_procedure  = 5,      
        acat_supply  = 6,      
        acat_other  = 7     
    } CareActivityCategory;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CareActivityCategory_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CareActivityCategorySeq, CareActivityCategory);

    NDDSUSERDllExport
    RTIBool CareActivityCategory_initialize(
        CareActivityCategory* self);

    NDDSUSERDllExport
    RTIBool CareActivityCategory_initialize_ex(
        CareActivityCategory* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CareActivityCategory_initialize_w_params(
        CareActivityCategory* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CareActivityCategory_finalize(
        CareActivityCategory* self);

    NDDSUSERDllExport
    void CareActivityCategory_finalize_ex(
        CareActivityCategory* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CareActivityCategory_finalize_w_params(
        CareActivityCategory* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CareActivityCategory_finalize_optional_members(
        CareActivityCategory* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CareActivityCategory_copy(
        CareActivityCategory* dst,
        const CareActivityCategory* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::OCTET   HostId [6];
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* HostId_get_typecode(void); /* Type code */

    DDS_SEQUENCE_NO_GET(HostIdSeq, HostId);

    NDDSUSERDllExport
    RTIBool HostId_initialize(
        HostId* self);

    NDDSUSERDllExport
    RTIBool HostId_initialize_ex(
        HostId* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool HostId_initialize_w_params(
        HostId* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void HostId_finalize(
        HostId* self);

    NDDSUSERDllExport
    void HostId_finalize_ex(
        HostId* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void HostId_finalize_w_params(
        HostId* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void HostId_finalize_optional_members(
        HostId* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool HostId_copy(
        HostId* dst,
        const HostId* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *GuidTimespecTYPENAME;

    struct GuidTimespecSeq;

    class GuidTimespec 
    {
      public:
        typedef struct GuidTimespecSeq Seq;

        ice::OCTET   seconds [4];
        ice::OCTET   fraction [2];

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* GuidTimespec_get_typecode(void); /* Type code */

    DDS_SEQUENCE(GuidTimespecSeq, GuidTimespec);

    NDDSUSERDllExport
    RTIBool GuidTimespec_initialize(
        GuidTimespec* self);

    NDDSUSERDllExport
    RTIBool GuidTimespec_initialize_ex(
        GuidTimespec* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool GuidTimespec_initialize_w_params(
        GuidTimespec* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void GuidTimespec_finalize(
        GuidTimespec* self);

    NDDSUSERDllExport
    void GuidTimespec_finalize_ex(
        GuidTimespec* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void GuidTimespec_finalize_w_params(
        GuidTimespec* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void GuidTimespec_finalize_optional_members(
        GuidTimespec* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool GuidTimespec_copy(
        GuidTimespec* dst,
        const GuidTimespec* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *GuidPrefixTYPENAME;

    struct GuidPrefixSeq;

    class GuidPrefix 
    {
      public:
        typedef struct GuidPrefixSeq Seq;

        ice::HostId   hostid ;
        ice::GuidTimespec   timestamp ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* GuidPrefix_get_typecode(void); /* Type code */

    DDS_SEQUENCE(GuidPrefixSeq, GuidPrefix);

    NDDSUSERDllExport
    RTIBool GuidPrefix_initialize(
        GuidPrefix* self);

    NDDSUSERDllExport
    RTIBool GuidPrefix_initialize_ex(
        GuidPrefix* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool GuidPrefix_initialize_w_params(
        GuidPrefix* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void GuidPrefix_finalize(
        GuidPrefix* self);

    NDDSUSERDllExport
    void GuidPrefix_finalize_ex(
        GuidPrefix* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void GuidPrefix_finalize_w_params(
        GuidPrefix* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void GuidPrefix_finalize_optional_members(
        GuidPrefix* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool GuidPrefix_copy(
        GuidPrefix* dst,
        const GuidPrefix* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    #define GUID_HOSTID_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00} 
    #define GUID_TIMESTAMP_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00} 
    #define GUID_PREFIX_UNKNOWN {GUID_HOSTID_UNKNOWN,GUID_TIMESTAMP_UNKNOWN} 

    typedef    ice::INTU16   EntityKind ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EntityKind_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EntityKindSeq, EntityKind);

    NDDSUSERDllExport
    RTIBool EntityKind_initialize(
        EntityKind* self);

    NDDSUSERDllExport
    RTIBool EntityKind_initialize_ex(
        EntityKind* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EntityKind_initialize_w_params(
        EntityKind* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EntityKind_finalize(
        EntityKind* self);

    NDDSUSERDllExport
    void EntityKind_finalize_ex(
        EntityKind* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EntityKind_finalize_w_params(
        EntityKind* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EntityKind_finalize_optional_members(
        EntityKind* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EntityKind_copy(
        EntityKind* dst,
        const EntityKind* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::INTU16   EntityKey ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EntityKey_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EntityKeySeq, EntityKey);

    NDDSUSERDllExport
    RTIBool EntityKey_initialize(
        EntityKey* self);

    NDDSUSERDllExport
    RTIBool EntityKey_initialize_ex(
        EntityKey* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EntityKey_initialize_w_params(
        EntityKey* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EntityKey_finalize(
        EntityKey* self);

    NDDSUSERDllExport
    void EntityKey_finalize_ex(
        EntityKey* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EntityKey_finalize_w_params(
        EntityKey* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EntityKey_finalize_optional_members(
        EntityKey* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EntityKey_copy(
        EntityKey* dst,
        const EntityKey* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *EntityIdTYPENAME;

    struct EntityIdSeq;

    class EntityId 
    {
      public:
        typedef struct EntityIdSeq Seq;

        ice::EntityKind   kind_of_entity ;
        ice::EntityKey   entity_key ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EntityId_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EntityIdSeq, EntityId);

    NDDSUSERDllExport
    RTIBool EntityId_initialize(
        EntityId* self);

    NDDSUSERDllExport
    RTIBool EntityId_initialize_ex(
        EntityId* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EntityId_initialize_w_params(
        EntityId* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EntityId_finalize(
        EntityId* self);

    NDDSUSERDllExport
    void EntityId_finalize_ex(
        EntityId* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EntityId_finalize_w_params(
        EntityId* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EntityId_finalize_optional_members(
        EntityId* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EntityId_copy(
        EntityId* dst,
        const EntityId* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    #define KOE_UNKNOWN         (0) 
    #define ENTITY_KEY_UNKNOWN  (0) 
    #define ICE_ENTITYID_UNKNOWN  {KOE_UNKNOWN,ENTITY_KEY_UNKNOWN} 

    extern const char *GUIDTYPENAME;

    struct GUIDSeq;

    class GUID 
    {
      public:
        typedef struct GUIDSeq Seq;

        ice::GuidPrefix   prefix ;
        ice::EntityId   entity_id ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* GUID_get_typecode(void); /* Type code */

    DDS_SEQUENCE(GUIDSeq, GUID);

    NDDSUSERDllExport
    RTIBool GUID_initialize(
        GUID* self);

    NDDSUSERDllExport
    RTIBool GUID_initialize_ex(
        GUID* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool GUID_initialize_w_params(
        GUID* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void GUID_finalize(
        GUID* self);

    NDDSUSERDllExport
    void GUID_finalize_ex(
        GUID* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void GUID_finalize_w_params(
        GUID* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void GUID_finalize_optional_members(
        GUID* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool GUID_copy(
        GUID* dst,
        const GUID* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    #define GUID_DEFAULT {GUID_PREFIX_UNKNOWN,ICE_ENTITYID_UNKNOWN} 

    typedef    ice::INTU32   SequenceNumber ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* SequenceNumber_get_typecode(void); /* Type code */

    DDS_SEQUENCE(SequenceNumberSeq, SequenceNumber);

    NDDSUSERDllExport
    RTIBool SequenceNumber_initialize(
        SequenceNumber* self);

    NDDSUSERDllExport
    RTIBool SequenceNumber_initialize_ex(
        SequenceNumber* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool SequenceNumber_initialize_w_params(
        SequenceNumber* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void SequenceNumber_finalize(
        SequenceNumber* self);

    NDDSUSERDllExport
    void SequenceNumber_finalize_ex(
        SequenceNumber* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void SequenceNumber_finalize_w_params(
        SequenceNumber* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void SequenceNumber_finalize_optional_members(
        SequenceNumber* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool SequenceNumber_copy(
        SequenceNumber* dst,
        const SequenceNumber* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    #define ICE_SEQUENCE_NUMBER_UNKNOWN (0) 

    extern const char *InstanceIdentifierTYPENAME;

    struct InstanceIdentifierSeq;

    class InstanceIdentifier 
    {
      public:
        typedef struct InstanceIdentifierSeq Seq;

        ice::GUID   guid ;
        ice::SequenceNumber   sequence_number ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* InstanceIdentifier_get_typecode(void); /* Type code */

    DDS_SEQUENCE(InstanceIdentifierSeq, InstanceIdentifier);

    NDDSUSERDllExport
    RTIBool InstanceIdentifier_initialize(
        InstanceIdentifier* self);

    NDDSUSERDllExport
    RTIBool InstanceIdentifier_initialize_ex(
        InstanceIdentifier* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool InstanceIdentifier_initialize_w_params(
        InstanceIdentifier* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void InstanceIdentifier_finalize(
        InstanceIdentifier* self);

    NDDSUSERDllExport
    void InstanceIdentifier_finalize_ex(
        InstanceIdentifier* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void InstanceIdentifier_finalize_w_params(
        InstanceIdentifier* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void InstanceIdentifier_finalize_optional_members(
        InstanceIdentifier* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool InstanceIdentifier_copy(
        InstanceIdentifier* dst,
        const InstanceIdentifier* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    #define INSTANCE_IDENTIFIER_UNKNOWN {GUID_DEFAULT,ICE_SEQUENCE_NUMBER_UNKNOWN} 

    extern const char *TopTYPENAME;

    struct TopSeq;

    class Top 
    {
      public:
        typedef struct TopSeq Seq;

        ice::ICE_ID   ice_id ;
        ice::HANDLE   handle ;
        ice::HANDLE   parent_handle ;
        ice::Timespec   source_timestamp ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Top_get_typecode(void); /* Type code */

    DDS_SEQUENCE(TopSeq, Top);

    NDDSUSERDllExport
    RTIBool Top_initialize(
        Top* self);

    NDDSUSERDllExport
    RTIBool Top_initialize_ex(
        Top* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Top_initialize_w_params(
        Top* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Top_finalize(
        Top* self);

    NDDSUSERDllExport
    void Top_finalize_ex(
        Top* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Top_finalize_w_params(
        Top* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Top_finalize_optional_members(
        Top* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Top_copy(
        Top* dst,
        const Top* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *VMOTYPENAME;

    struct VMOSeq;

    class VMO 
    : public ice::Top{
      public:
        typedef struct VMOSeq Seq;

        ice::TYPE   type ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* VMO_get_typecode(void); /* Type code */

    DDS_SEQUENCE(VMOSeq, VMO);

    NDDSUSERDllExport
    RTIBool VMO_initialize(
        VMO* self);

    NDDSUSERDllExport
    RTIBool VMO_initialize_ex(
        VMO* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool VMO_initialize_w_params(
        VMO* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void VMO_finalize(
        VMO* self);

    NDDSUSERDllExport
    void VMO_finalize_ex(
        VMO* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void VMO_finalize_w_params(
        VMO* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void VMO_finalize_optional_members(
        VMO* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool VMO_copy(
        VMO* dst,
        const VMO* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Boolean   CT_boolean ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_boolean_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_booleanSeq, CT_boolean);

    NDDSUSERDllExport
    RTIBool CT_boolean_initialize(
        CT_boolean* self);

    NDDSUSERDllExport
    RTIBool CT_boolean_initialize_ex(
        CT_boolean* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_boolean_initialize_w_params(
        CT_boolean* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_boolean_finalize(
        CT_boolean* self);

    NDDSUSERDllExport
    void CT_boolean_finalize_ex(
        CT_boolean* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_boolean_finalize_w_params(
        CT_boolean* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_boolean_finalize_optional_members(
        CT_boolean* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_boolean_copy(
        CT_boolean* dst,
        const CT_boolean* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_Long   CT_integer ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_integer_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_integerSeq, CT_integer);

    NDDSUSERDllExport
    RTIBool CT_integer_initialize(
        CT_integer* self);

    NDDSUSERDllExport
    RTIBool CT_integer_initialize_ex(
        CT_integer* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_integer_initialize_w_params(
        CT_integer* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_integer_finalize(
        CT_integer* self);

    NDDSUSERDllExport
    void CT_integer_finalize_ex(
        CT_integer* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_integer_finalize_w_params(
        CT_integer* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_integer_finalize_optional_members(
        CT_integer* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_integer_copy(
        CT_integer* dst,
        const CT_integer* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_UnsignedLong   CT_unsignedInt ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_unsignedInt_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_unsignedIntSeq, CT_unsignedInt);

    NDDSUSERDllExport
    RTIBool CT_unsignedInt_initialize(
        CT_unsignedInt* self);

    NDDSUSERDllExport
    RTIBool CT_unsignedInt_initialize_ex(
        CT_unsignedInt* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_unsignedInt_initialize_w_params(
        CT_unsignedInt* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_unsignedInt_finalize(
        CT_unsignedInt* self);

    NDDSUSERDllExport
    void CT_unsignedInt_finalize_ex(
        CT_unsignedInt* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_unsignedInt_finalize_w_params(
        CT_unsignedInt* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_unsignedInt_finalize_optional_members(
        CT_unsignedInt* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_unsignedInt_copy(
        CT_unsignedInt* dst,
        const CT_unsignedInt* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef    DDS_UnsignedLong   CT_positiveInt ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_positiveInt_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_positiveIntSeq, CT_positiveInt);

    NDDSUSERDllExport
    RTIBool CT_positiveInt_initialize(
        CT_positiveInt* self);

    NDDSUSERDllExport
    RTIBool CT_positiveInt_initialize_ex(
        CT_positiveInt* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_positiveInt_initialize_w_params(
        CT_positiveInt* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_positiveInt_finalize(
        CT_positiveInt* self);

    NDDSUSERDllExport
    void CT_positiveInt_finalize_ex(
        CT_positiveInt* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_positiveInt_finalize_w_params(
        CT_positiveInt* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_positiveInt_finalize_optional_members(
        CT_positiveInt* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_positiveInt_copy(
        CT_positiveInt* dst,
        const CT_positiveInt* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *CT_decimalTYPENAME;

    struct CT_decimalSeq;
    #ifndef NDDS_STANDALONE_TYPE
    class CT_decimalTypeSupport;
    class CT_decimalDataWriter;
    class CT_decimalDataReader;
    #endif

    class CT_decimal 
    {
      public:
        typedef struct CT_decimalSeq Seq;
        #ifndef NDDS_STANDALONE_TYPE
        typedef CT_decimalTypeSupport TypeSupport;
        typedef CT_decimalDataWriter DataWriter;
        typedef CT_decimalDataReader DataReader;
        #endif

        DDS_Float   value ;
        DDS_Octet   presentation_precision ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_decimal_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_decimalSeq, CT_decimal);

    NDDSUSERDllExport
    RTIBool CT_decimal_initialize(
        CT_decimal* self);

    NDDSUSERDllExport
    RTIBool CT_decimal_initialize_ex(
        CT_decimal* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_decimal_initialize_w_params(
        CT_decimal* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_decimal_finalize(
        CT_decimal* self);

    NDDSUSERDllExport
    void CT_decimal_finalize_ex(
        CT_decimal* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_decimal_finalize_w_params(
        CT_decimal* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_decimal_finalize_optional_members(
        CT_decimal* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_decimal_copy(
        CT_decimal* dst,
        const CT_decimal* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_DATETIME= 40;
    typedef    DDS_Char *   CT_dateTime ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_dateTime_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_dateTimeSeq, CT_dateTime);

    NDDSUSERDllExport
    RTIBool CT_dateTime_initialize(
        CT_dateTime* self);

    NDDSUSERDllExport
    RTIBool CT_dateTime_initialize_ex(
        CT_dateTime* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_dateTime_initialize_w_params(
        CT_dateTime* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_dateTime_finalize(
        CT_dateTime* self);

    NDDSUSERDllExport
    void CT_dateTime_finalize_ex(
        CT_dateTime* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_dateTime_finalize_w_params(
        CT_dateTime* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_dateTime_finalize_optional_members(
        CT_dateTime* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_dateTime_copy(
        CT_dateTime* dst,
        const CT_dateTime* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_INSTANT= (ice::MAXLEN_CT_DATETIME);
    typedef    DDS_Char *   CT_instant ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_instant_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_instantSeq, CT_instant);

    NDDSUSERDllExport
    RTIBool CT_instant_initialize(
        CT_instant* self);

    NDDSUSERDllExport
    RTIBool CT_instant_initialize_ex(
        CT_instant* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_instant_initialize_w_params(
        CT_instant* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_instant_finalize(
        CT_instant* self);

    NDDSUSERDllExport
    void CT_instant_finalize_ex(
        CT_instant* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_instant_finalize_w_params(
        CT_instant* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_instant_finalize_optional_members(
        CT_instant* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_instant_copy(
        CT_instant* dst,
        const CT_instant* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_DATE= 11;
    typedef    DDS_Char *   CT_date ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_date_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_dateSeq, CT_date);

    NDDSUSERDllExport
    RTIBool CT_date_initialize(
        CT_date* self);

    NDDSUSERDllExport
    RTIBool CT_date_initialize_ex(
        CT_date* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_date_initialize_w_params(
        CT_date* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_date_finalize(
        CT_date* self);

    NDDSUSERDllExport
    void CT_date_finalize_ex(
        CT_date* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_date_finalize_w_params(
        CT_date* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_date_finalize_optional_members(
        CT_date* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_date_copy(
        CT_date* dst,
        const CT_date* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_TIME= 10;
    typedef    DDS_Char *   CT_time ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_time_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_timeSeq, CT_time);

    NDDSUSERDllExport
    RTIBool CT_time_initialize(
        CT_time* self);

    NDDSUSERDllExport
    RTIBool CT_time_initialize_ex(
        CT_time* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_time_initialize_w_params(
        CT_time* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_time_finalize(
        CT_time* self);

    NDDSUSERDllExport
    void CT_time_finalize_ex(
        CT_time* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_time_finalize_w_params(
        CT_time* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_time_finalize_optional_members(
        CT_time* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_time_copy(
        CT_time* dst,
        const CT_time* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_CODE= 64;
    typedef    DDS_Char *   CT_code ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_code_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_codeSeq, CT_code);

    NDDSUSERDllExport
    RTIBool CT_code_initialize(
        CT_code* self);

    NDDSUSERDllExport
    RTIBool CT_code_initialize_ex(
        CT_code* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_code_initialize_w_params(
        CT_code* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_code_finalize(
        CT_code* self);

    NDDSUSERDllExport
    void CT_code_finalize_ex(
        CT_code* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_code_finalize_w_params(
        CT_code* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_code_finalize_optional_members(
        CT_code* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_code_copy(
        CT_code* dst,
        const CT_code* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_ID= 64;
    typedef    DDS_Char *   CT_id ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_id_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_idSeq, CT_id);

    NDDSUSERDllExport
    RTIBool CT_id_initialize(
        CT_id* self);

    NDDSUSERDllExport
    RTIBool CT_id_initialize_ex(
        CT_id* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_id_initialize_w_params(
        CT_id* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_id_finalize(
        CT_id* self);

    NDDSUSERDllExport
    void CT_id_finalize_ex(
        CT_id* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_id_finalize_w_params(
        CT_id* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_id_finalize_optional_members(
        CT_id* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_id_copy(
        CT_id* dst,
        const CT_id* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    static const ice::CT_integer MAXLEN_CT_URI= 260;
    typedef    DDS_Char *   CT_uri ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CT_uri_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CT_uriSeq, CT_uri);

    NDDSUSERDllExport
    RTIBool CT_uri_initialize(
        CT_uri* self);

    NDDSUSERDllExport
    RTIBool CT_uri_initialize_ex(
        CT_uri* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CT_uri_initialize_w_params(
        CT_uri* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CT_uri_finalize(
        CT_uri* self);

    NDDSUSERDllExport
    void CT_uri_finalize_ex(
        CT_uri* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CT_uri_finalize_w_params(
        CT_uri* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CT_uri_finalize_optional_members(
        CT_uri* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CT_uri_copy(
        CT_uri* dst,
        const CT_uri* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *CodingTYPENAME;

    struct CodingSeq;

    class Coding 
    {
      public:
        typedef struct CodingSeq Seq;

        ice::CT_uri   system ;
        DDS_Char *   version ;
        ice::CT_code   code_ ;
        DDS_Char *   display ;
        ice::CT_boolean   user_selected ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Coding_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CodingSeq, Coding);

    NDDSUSERDllExport
    RTIBool Coding_initialize(
        Coding* self);

    NDDSUSERDllExport
    RTIBool Coding_initialize_ex(
        Coding* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Coding_initialize_w_params(
        Coding* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Coding_finalize(
        Coding* self);

    NDDSUSERDllExport
    void Coding_finalize_ex(
        Coding* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Coding_finalize_w_params(
        Coding* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Coding_finalize_optional_members(
        Coding* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Coding_copy(
        Coding* dst,
        const Coding* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *CodeableConceptTYPENAME;

    struct CodeableConceptSeq;

    class CodeableConcept 
    {
      public:
        typedef struct CodeableConceptSeq Seq;

        ice::Coding   coding ;
        DDS_Char *   text ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* CodeableConcept_get_typecode(void); /* Type code */

    DDS_SEQUENCE(CodeableConceptSeq, CodeableConcept);

    NDDSUSERDllExport
    RTIBool CodeableConcept_initialize(
        CodeableConcept* self);

    NDDSUSERDllExport
    RTIBool CodeableConcept_initialize_ex(
        CodeableConcept* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool CodeableConcept_initialize_w_params(
        CodeableConcept* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void CodeableConcept_finalize(
        CodeableConcept* self);

    NDDSUSERDllExport
    void CodeableConcept_finalize_ex(
        CodeableConcept* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void CodeableConcept_finalize_w_params(
        CodeableConcept* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void CodeableConcept_finalize_optional_members(
        CodeableConcept* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool CodeableConcept_copy(
        CodeableConcept* dst,
        const CodeableConcept* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *SimpleQuantityTYPENAME;

    struct SimpleQuantitySeq;

    class SimpleQuantity 
    {
      public:
        typedef struct SimpleQuantitySeq Seq;

        ice::CT_decimal   value ;
        DDS_Char *   unit ;
        ice::CT_uri   system ;
        ice::CT_code   code_ ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* SimpleQuantity_get_typecode(void); /* Type code */

    DDS_SEQUENCE(SimpleQuantitySeq, SimpleQuantity);

    NDDSUSERDllExport
    RTIBool SimpleQuantity_initialize(
        SimpleQuantity* self);

    NDDSUSERDllExport
    RTIBool SimpleQuantity_initialize_ex(
        SimpleQuantity* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool SimpleQuantity_initialize_w_params(
        SimpleQuantity* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void SimpleQuantity_finalize(
        SimpleQuantity* self);

    NDDSUSERDllExport
    void SimpleQuantity_finalize_ex(
        SimpleQuantity* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void SimpleQuantity_finalize_w_params(
        SimpleQuantity* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void SimpleQuantity_finalize_optional_members(
        SimpleQuantity* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool SimpleQuantity_copy(
        SimpleQuantity* dst,
        const SimpleQuantity* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *QuantityTYPENAME;

    struct QuantitySeq;

    class Quantity 
    : public ice::SimpleQuantity{
      public:
        typedef struct QuantitySeq Seq;

        DDS_Char *   comparator ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Quantity_get_typecode(void); /* Type code */

    DDS_SEQUENCE(QuantitySeq, Quantity);

    NDDSUSERDllExport
    RTIBool Quantity_initialize(
        Quantity* self);

    NDDSUSERDllExport
    RTIBool Quantity_initialize_ex(
        Quantity* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Quantity_initialize_w_params(
        Quantity* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Quantity_finalize(
        Quantity* self);

    NDDSUSERDllExport
    void Quantity_finalize_ex(
        Quantity* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Quantity_finalize_w_params(
        Quantity* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Quantity_finalize_optional_members(
        Quantity* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Quantity_copy(
        Quantity* dst,
        const Quantity* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *RangeTYPENAME;

    struct RangeSeq;

    class Range 
    {
      public:
        typedef struct RangeSeq Seq;

        ice::SimpleQuantity   low ;
        ice::SimpleQuantity   high ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Range_get_typecode(void); /* Type code */

    DDS_SEQUENCE(RangeSeq, Range);

    NDDSUSERDllExport
    RTIBool Range_initialize(
        Range* self);

    NDDSUSERDllExport
    RTIBool Range_initialize_ex(
        Range* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Range_initialize_w_params(
        Range* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Range_finalize(
        Range* self);

    NDDSUSERDllExport
    void Range_finalize_ex(
        Range* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Range_finalize_w_params(
        Range* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Range_finalize_optional_members(
        Range* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Range_copy(
        Range* dst,
        const Range* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *RatioTYPENAME;

    struct RatioSeq;

    class Ratio 
    {
      public:
        typedef struct RatioSeq Seq;

        ice::Quantity   numerator ;
        ice::Quantity   denominator ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Ratio_get_typecode(void); /* Type code */

    DDS_SEQUENCE(RatioSeq, Ratio);

    NDDSUSERDllExport
    RTIBool Ratio_initialize(
        Ratio* self);

    NDDSUSERDllExport
    RTIBool Ratio_initialize_ex(
        Ratio* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Ratio_initialize_w_params(
        Ratio* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Ratio_finalize(
        Ratio* self);

    NDDSUSERDllExport
    void Ratio_finalize_ex(
        Ratio* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Ratio_finalize_w_params(
        Ratio* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Ratio_finalize_optional_members(
        Ratio* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Ratio_copy(
        Ratio* dst,
        const Ratio* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *PeriodTYPENAME;

    struct PeriodSeq;

    class Period 
    {
      public:
        typedef struct PeriodSeq Seq;

        ice::CT_dateTime   start ;
        ice::CT_dateTime   end ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* Period_get_typecode(void); /* Type code */

    DDS_SEQUENCE(PeriodSeq, Period);

    NDDSUSERDllExport
    RTIBool Period_initialize(
        Period* self);

    NDDSUSERDllExport
    RTIBool Period_initialize_ex(
        Period* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool Period_initialize_w_params(
        Period* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void Period_finalize(
        Period* self);

    NDDSUSERDllExport
    void Period_finalize_ex(
        Period* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void Period_finalize_w_params(
        Period* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void Period_finalize_optional_members(
        Period* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool Period_copy(
        Period* dst,
        const Period* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum EffectiveTimeType
    {
        et_datetime  = 0,      
        et_period  = 1     
    } EffectiveTimeType;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EffectiveTimeType_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EffectiveTimeTypeSeq, EffectiveTimeType);

    NDDSUSERDllExport
    RTIBool EffectiveTimeType_initialize(
        EffectiveTimeType* self);

    NDDSUSERDllExport
    RTIBool EffectiveTimeType_initialize_ex(
        EffectiveTimeType* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EffectiveTimeType_initialize_w_params(
        EffectiveTimeType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EffectiveTimeType_finalize(
        EffectiveTimeType* self);

    NDDSUSERDllExport
    void EffectiveTimeType_finalize_ex(
        EffectiveTimeType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EffectiveTimeType_finalize_w_params(
        EffectiveTimeType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EffectiveTimeType_finalize_optional_members(
        EffectiveTimeType* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EffectiveTimeType_copy(
        EffectiveTimeType* dst,
        const EffectiveTimeType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *EffectiveTimeTYPENAME;

    struct EffectiveTimeSeq;

    typedef struct EffectiveTime {
        typedef struct EffectiveTimeSeq Seq;

        ice::EffectiveTimeType _d;
        struct EffectiveTime_u 
        {

            ice::Period   period ;
            ice::CT_dateTime   datetime ;
        }_u;

    } EffectiveTime ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* EffectiveTime_get_typecode(void); /* Type code */

    DDS_SEQUENCE(EffectiveTimeSeq, EffectiveTime);

    NDDSUSERDllExport
    RTIBool EffectiveTime_initialize(
        EffectiveTime* self);

    NDDSUSERDllExport
    RTIBool EffectiveTime_initialize_ex(
        EffectiveTime* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool EffectiveTime_initialize_w_params(
        EffectiveTime* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void EffectiveTime_finalize(
        EffectiveTime* self);

    NDDSUSERDllExport
    void EffectiveTime_finalize_ex(
        EffectiveTime* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void EffectiveTime_finalize_w_params(
        EffectiveTime* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void EffectiveTime_finalize_optional_members(
        EffectiveTime* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool EffectiveTime_copy(
        EffectiveTime* dst,
        const EffectiveTime* src);

    NDDSUSERDllExport
    DDS_LongLong EffectiveTime_getDefaultDiscriminator();

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
} /* namespace ice  */
static const DDS_Char * KeyedOctetsTopic= "KeyedOctets";
static const DDS_Long KEYEDOCTETS_MAX_KEY_SIZE= 1024;
static const DDS_Long KEYEDOCTETS_MAX_VALUE_SIZE= 2048;

#endif /* common */

