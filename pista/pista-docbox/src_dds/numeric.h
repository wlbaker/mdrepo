

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from numeric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef numeric_67916774_h
#define numeric_67916774_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "metric.h"
namespace ice {

    extern const char *AbsoluteRangeTYPENAME;

    struct AbsoluteRangeSeq;

    class AbsoluteRange 
    {
      public:
        typedef struct AbsoluteRangeSeq Seq;

        ice::FLOATType   lower_value ;
        ice::FLOATType   upper_value ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* AbsoluteRange_get_typecode(void); /* Type code */

    DDS_SEQUENCE(AbsoluteRangeSeq, AbsoluteRange);

    NDDSUSERDllExport
    RTIBool AbsoluteRange_initialize(
        AbsoluteRange* self);

    NDDSUSERDllExport
    RTIBool AbsoluteRange_initialize_ex(
        AbsoluteRange* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool AbsoluteRange_initialize_w_params(
        AbsoluteRange* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void AbsoluteRange_finalize(
        AbsoluteRange* self);

    NDDSUSERDllExport
    void AbsoluteRange_finalize_ex(
        AbsoluteRange* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void AbsoluteRange_finalize_w_params(
        AbsoluteRange* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void AbsoluteRange_finalize_optional_members(
        AbsoluteRange* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool AbsoluteRange_copy(
        AbsoluteRange* dst,
        const AbsoluteRange* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *DispResolutionTYPENAME;

    struct DispResolutionSeq;

    class DispResolution 
    {
      public:
        typedef struct DispResolutionSeq Seq;

        ice::INTU8   pre_point ;
        ice::INTU8   post_point ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* DispResolution_get_typecode(void); /* Type code */

    DDS_SEQUENCE(DispResolutionSeq, DispResolution);

    NDDSUSERDllExport
    RTIBool DispResolution_initialize(
        DispResolution* self);

    NDDSUSERDllExport
    RTIBool DispResolution_initialize_ex(
        DispResolution* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool DispResolution_initialize_w_params(
        DispResolution* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void DispResolution_finalize(
        DispResolution* self);

    NDDSUSERDllExport
    void DispResolution_finalize_ex(
        DispResolution* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void DispResolution_finalize_w_params(
        DispResolution* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void DispResolution_finalize_optional_members(
        DispResolution* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool DispResolution_copy(
        DispResolution* dst,
        const DispResolution* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *NuObsValueTYPENAME;

    struct NuObsValueSeq;

    class NuObsValue 
    {
      public:
        typedef struct NuObsValueSeq Seq;

        ice::OIDType   metric_id ;
        ice::MeasurementStatus   state ;
        ice::OIDType   unit_code ;
        ice::FLOATType   value ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* NuObsValue_get_typecode(void); /* Type code */

    DDS_SEQUENCE(NuObsValueSeq, NuObsValue);

    NDDSUSERDllExport
    RTIBool NuObsValue_initialize(
        NuObsValue* self);

    NDDSUSERDllExport
    RTIBool NuObsValue_initialize_ex(
        NuObsValue* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool NuObsValue_initialize_w_params(
        NuObsValue* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void NuObsValue_finalize(
        NuObsValue* self);

    NDDSUSERDllExport
    void NuObsValue_finalize_ex(
        NuObsValue* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void NuObsValue_finalize_w_params(
        NuObsValue* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void NuObsValue_finalize_optional_members(
        NuObsValue* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool NuObsValue_copy(
        NuObsValue* dst,
        const NuObsValue* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *NumericContextTYPENAME;

    struct NumericContextSeq;
    #ifndef NDDS_STANDALONE_TYPE
    class NumericContextTypeSupport;
    class NumericContextDataWriter;
    class NumericContextDataReader;
    #endif

    class NumericContext 
    : public ice::MetricContext{
      public:
        typedef struct NumericContextSeq Seq;
        #ifndef NDDS_STANDALONE_TYPE
        typedef NumericContextTypeSupport TypeSupport;
        typedef NumericContextDataWriter DataWriter;
        typedef NumericContextDataReader DataReader;
        #endif

        ice::AbsoluteRange   * nu_measure_range ;
        ice::AbsoluteRange   * nu_physiological_range ;
        ice::DispResolution   * display_resolution ;
        ice::FLOATType   * accuracy ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* NumericContext_get_typecode(void); /* Type code */

    DDS_SEQUENCE(NumericContextSeq, NumericContext);

    NDDSUSERDllExport
    RTIBool NumericContext_initialize(
        NumericContext* self);

    NDDSUSERDllExport
    RTIBool NumericContext_initialize_ex(
        NumericContext* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool NumericContext_initialize_w_params(
        NumericContext* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void NumericContext_finalize(
        NumericContext* self);

    NDDSUSERDllExport
    void NumericContext_finalize_ex(
        NumericContext* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void NumericContext_finalize_w_params(
        NumericContext* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void NumericContext_finalize_optional_members(
        NumericContext* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool NumericContext_copy(
        NumericContext* dst,
        const NumericContext* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *NumericObservedValueTYPENAME;

    struct NumericObservedValueSeq;
    #ifndef NDDS_STANDALONE_TYPE
    class NumericObservedValueTypeSupport;
    class NumericObservedValueDataWriter;
    class NumericObservedValueDataReader;
    #endif

    class NumericObservedValue 
    : public ice::MetricObservedValue{
      public:
        typedef struct NumericObservedValueSeq Seq;
        #ifndef NDDS_STANDALONE_TYPE
        typedef NumericObservedValueTypeSupport TypeSupport;
        typedef NumericObservedValueDataWriter DataWriter;
        typedef NumericObservedValueDataReader DataReader;
        #endif

        ice::NuObsValue   nu_observed_value ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* NumericObservedValue_get_typecode(void); /* Type code */

    DDS_SEQUENCE(NumericObservedValueSeq, NumericObservedValue);

    NDDSUSERDllExport
    RTIBool NumericObservedValue_initialize(
        NumericObservedValue* self);

    NDDSUSERDllExport
    RTIBool NumericObservedValue_initialize_ex(
        NumericObservedValue* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool NumericObservedValue_initialize_w_params(
        NumericObservedValue* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void NumericObservedValue_finalize(
        NumericObservedValue* self);

    NDDSUSERDllExport
    void NumericObservedValue_finalize_ex(
        NumericObservedValue* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void NumericObservedValue_finalize_w_params(
        NumericObservedValue* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void NumericObservedValue_finalize_optional_members(
        NumericObservedValue* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool NumericObservedValue_copy(
        NumericObservedValue* dst,
        const NumericObservedValue* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    static const DDS_Char * NumericMeasContextTopic= "ice--NumericMeasContext";
    static const DDS_Char * NumericMeasContextReqTopic= "ice--NumericMeasContextReq";
    static const DDS_Char * NumericMeasObservedValueTopic= "ice--NumericMeasObservedValue";
    static const DDS_Char * NumericCalcContextTopic= "ice--NumericCalcContext";
    static const DDS_Char * NumericCalcContextReqTopic= "ice--NumericCalcContextReq";
    static const DDS_Char * NumericCalcObservedValueTopic= "ice--NumericCalcObservedValue";
    static const DDS_Char * NumericSettContextTopic= "ice--NumericSettContext";
    static const DDS_Char * NumericSettContextReqTopic= "ice--NumericSettContextReq";
    static const DDS_Char * NumericSettObservedValueTopic= "ice--NumericSettObservedValue";
    static const DDS_Char * NumericSettObservedValueReqTopic= "ice--NumericSettObservedValueReq";
} /* namespace ice  */

#endif /* numeric */

