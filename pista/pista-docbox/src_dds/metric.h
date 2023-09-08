

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from metric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef metric_611712278_h
#define metric_611712278_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "common.h"
namespace ice {

    typedef     ice::OIDTypeSeq  MetricSourceList ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricSourceList_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricSourceListSeq, MetricSourceList);

    NDDSUSERDllExport
    RTIBool MetricSourceList_initialize(
        MetricSourceList* self);

    NDDSUSERDllExport
    RTIBool MetricSourceList_initialize_ex(
        MetricSourceList* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricSourceList_initialize_w_params(
        MetricSourceList* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricSourceList_finalize(
        MetricSourceList* self);

    NDDSUSERDllExport
    void MetricSourceList_finalize_ex(
        MetricSourceList* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricSourceList_finalize_w_params(
        MetricSourceList* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricSourceList_finalize_optional_members(
        MetricSourceList* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricSourceList_copy(
        MetricSourceList* dst,
        const MetricSourceList* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef     ice::OIDTypeSeq  SiteList ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* SiteList_get_typecode(void); /* Type code */

    DDS_SEQUENCE(SiteListSeq, SiteList);

    NDDSUSERDllExport
    RTIBool SiteList_initialize(
        SiteList* self);

    NDDSUSERDllExport
    RTIBool SiteList_initialize_ex(
        SiteList* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool SiteList_initialize_w_params(
        SiteList* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void SiteList_finalize(
        SiteList* self);

    NDDSUSERDllExport
    void SiteList_finalize_ex(
        SiteList* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void SiteList_finalize_w_params(
        SiteList* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void SiteList_finalize_optional_members(
        SiteList* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool SiteList_copy(
        SiteList* dst,
        const SiteList* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   MetricStatus ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricStatus_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricStatusSeq, MetricStatus);

    NDDSUSERDllExport
    RTIBool MetricStatus_initialize(
        MetricStatus* self);

    NDDSUSERDllExport
    RTIBool MetricStatus_initialize_ex(
        MetricStatus* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricStatus_initialize_w_params(
        MetricStatus* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricStatus_finalize(
        MetricStatus* self);

    NDDSUSERDllExport
    void MetricStatus_finalize_ex(
        MetricStatus* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricStatus_finalize_w_params(
        MetricStatus* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricStatus_finalize_optional_members(
        MetricStatus* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricStatus_copy(
        MetricStatus* dst,
        const MetricStatus* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricStatusBits
    {
        metric_off  = 1,      
        metric_not_ready  = 2,      
        metric_standby  = 4,      
        metric_transduc_discon  = 256,      
        metric_hw_discon  = 512     
    } MetricStatusBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricStatusBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricStatusBitsSeq, MetricStatusBits);

    NDDSUSERDllExport
    RTIBool MetricStatusBits_initialize(
        MetricStatusBits* self);

    NDDSUSERDllExport
    RTIBool MetricStatusBits_initialize_ex(
        MetricStatusBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricStatusBits_initialize_w_params(
        MetricStatusBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricStatusBits_finalize(
        MetricStatusBits* self);

    NDDSUSERDllExport
    void MetricStatusBits_finalize_ex(
        MetricStatusBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricStatusBits_finalize_w_params(
        MetricStatusBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricStatusBits_finalize_optional_members(
        MetricStatusBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricStatusBits_copy(
        MetricStatusBits* dst,
        const MetricStatusBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   MetricAccess ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricAccess_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricAccessSeq, MetricAccess);

    NDDSUSERDllExport
    RTIBool MetricAccess_initialize(
        MetricAccess* self);

    NDDSUSERDllExport
    RTIBool MetricAccess_initialize_ex(
        MetricAccess* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricAccess_initialize_w_params(
        MetricAccess* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricAccess_finalize(
        MetricAccess* self);

    NDDSUSERDllExport
    void MetricAccess_finalize_ex(
        MetricAccess* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricAccess_finalize_w_params(
        MetricAccess* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricAccess_finalize_optional_members(
        MetricAccess* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricAccess_copy(
        MetricAccess* dst,
        const MetricAccess* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricAccessBits
    {
        avail_intermittent  = 1,      
        upd_periodic  = 2,      
        upd_episodic  = 4,      
        msmt_noncontinuous  = 8,      
        acc_evrep  = 16,      
        acc_get  = 32,      
        acc_scan  = 48,      
        gen_opt_sync  = 256,      
        sc_opt_normal  = 1024,      
        sc_opt_extensive  = 2048,      
        sc_opt_long_pd_avail  = 4096,      
        sc_opt_confirm  = 8192     
    } MetricAccessBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricAccessBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricAccessBitsSeq, MetricAccessBits);

    NDDSUSERDllExport
    RTIBool MetricAccessBits_initialize(
        MetricAccessBits* self);

    NDDSUSERDllExport
    RTIBool MetricAccessBits_initialize_ex(
        MetricAccessBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricAccessBits_initialize_w_params(
        MetricAccessBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricAccessBits_finalize(
        MetricAccessBits* self);

    NDDSUSERDllExport
    void MetricAccessBits_finalize_ex(
        MetricAccessBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricAccessBits_finalize_w_params(
        MetricAccessBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricAccessBits_finalize_optional_members(
        MetricAccessBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricAccessBits_copy(
        MetricAccessBits* dst,
        const MetricAccessBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   MetricRelevance ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricRelevance_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricRelevanceSeq, MetricRelevance);

    NDDSUSERDllExport
    RTIBool MetricRelevance_initialize(
        MetricRelevance* self);

    NDDSUSERDllExport
    RTIBool MetricRelevance_initialize_ex(
        MetricRelevance* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricRelevance_initialize_w_params(
        MetricRelevance* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricRelevance_finalize(
        MetricRelevance* self);

    NDDSUSERDllExport
    void MetricRelevance_finalize_ex(
        MetricRelevance* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricRelevance_finalize_w_params(
        MetricRelevance* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricRelevance_finalize_optional_members(
        MetricRelevance* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricRelevance_copy(
        MetricRelevance* dst,
        const MetricRelevance* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricRelevanceBits
    {
        rv_unspec  = 1,      
        rv_internal  = 2,      
        rv_store_only  = 4,      
        rv_no_recording  = 8,      
        rv_phys_ev_ind  = 16,      
        rv_btb_metric  = 32,      
        rv_app_specific  = 256,      
        rv_service  = 512     
    } MetricRelevanceBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricRelevanceBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricRelevanceBitsSeq, MetricRelevanceBits);

    NDDSUSERDllExport
    RTIBool MetricRelevanceBits_initialize(
        MetricRelevanceBits* self);

    NDDSUSERDllExport
    RTIBool MetricRelevanceBits_initialize_ex(
        MetricRelevanceBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricRelevanceBits_initialize_w_params(
        MetricRelevanceBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricRelevanceBits_finalize(
        MetricRelevanceBits* self);

    NDDSUSERDllExport
    void MetricRelevanceBits_finalize_ex(
        MetricRelevanceBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricRelevanceBits_finalize_w_params(
        MetricRelevanceBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricRelevanceBits_finalize_optional_members(
        MetricRelevanceBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricRelevanceBits_copy(
        MetricRelevanceBits* dst,
        const MetricRelevanceBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricCategory
    {
        mcat_unspec  = 0,      
        auto_measurement  = 1,      
        manual_measurement  = 2,      
        auto_setting  = 3,      
        manual_setting  = 4,      
        auto_calculation  = 5,      
        manual_calculation  = 6     
    } MetricCategory;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricCategory_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricCategorySeq, MetricCategory);

    NDDSUSERDllExport
    RTIBool MetricCategory_initialize(
        MetricCategory* self);

    NDDSUSERDllExport
    RTIBool MetricCategory_initialize_ex(
        MetricCategory* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricCategory_initialize_w_params(
        MetricCategory* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricCategory_finalize(
        MetricCategory* self);

    NDDSUSERDllExport
    void MetricCategory_finalize_ex(
        MetricCategory* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricCategory_finalize_w_params(
        MetricCategory* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricCategory_finalize_optional_members(
        MetricCategory* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricCategory_copy(
        MetricCategory* dst,
        const MetricCategory* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *MetricSpecTYPENAME;

    struct MetricSpecSeq;

    class MetricSpec 
    {
      public:
        typedef struct MetricSpecSeq Seq;

        ice::Duration   update_period ;
        ice::MetricCategory   category ;
        ice::MetricAccess   access ;
        ice::MetricRelevance   relevance ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricSpec_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricSpecSeq, MetricSpec);

    NDDSUSERDllExport
    RTIBool MetricSpec_initialize(
        MetricSpec* self);

    NDDSUSERDllExport
    RTIBool MetricSpec_initialize_ex(
        MetricSpec* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricSpec_initialize_w_params(
        MetricSpec* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricSpec_finalize(
        MetricSpec* self);

    NDDSUSERDllExport
    void MetricSpec_finalize_ex(
        MetricSpec* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricSpec_finalize_w_params(
        MetricSpec* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricSpec_finalize_optional_members(
        MetricSpec* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricSpec_copy(
        MetricSpec* dst,
        const MetricSpec* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *VmoSourceEntryTYPENAME;

    struct VmoSourceEntrySeq;

    class VmoSourceEntry 
    {
      public:
        typedef struct VmoSourceEntrySeq Seq;

        ice::OIDType   vmo_type ;
        ice::GLBHANDLE   glb_handle ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* VmoSourceEntry_get_typecode(void); /* Type code */

    DDS_SEQUENCE(VmoSourceEntrySeq, VmoSourceEntry);

    NDDSUSERDllExport
    RTIBool VmoSourceEntry_initialize(
        VmoSourceEntry* self);

    NDDSUSERDllExport
    RTIBool VmoSourceEntry_initialize_ex(
        VmoSourceEntry* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool VmoSourceEntry_initialize_w_params(
        VmoSourceEntry* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void VmoSourceEntry_finalize(
        VmoSourceEntry* self);

    NDDSUSERDllExport
    void VmoSourceEntry_finalize_ex(
        VmoSourceEntry* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void VmoSourceEntry_finalize_w_params(
        VmoSourceEntry* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void VmoSourceEntry_finalize_optional_members(
        VmoSourceEntry* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool VmoSourceEntry_copy(
        VmoSourceEntry* dst,
        const VmoSourceEntry* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef     ice::VmoSourceEntrySeq  VmoSourceList ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* VmoSourceList_get_typecode(void); /* Type code */

    DDS_SEQUENCE(VmoSourceListSeq, VmoSourceList);

    NDDSUSERDllExport
    RTIBool VmoSourceList_initialize(
        VmoSourceList* self);

    NDDSUSERDllExport
    RTIBool VmoSourceList_initialize_ex(
        VmoSourceList* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool VmoSourceList_initialize_w_params(
        VmoSourceList* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void VmoSourceList_finalize(
        VmoSourceList* self);

    NDDSUSERDllExport
    void VmoSourceList_finalize_ex(
        VmoSourceList* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void VmoSourceList_finalize_w_params(
        VmoSourceList* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void VmoSourceList_finalize_optional_members(
        VmoSourceList* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool VmoSourceList_copy(
        VmoSourceList* dst,
        const VmoSourceList* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef    ice::BITS16   MeasurementStatus ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MeasurementStatus_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MeasurementStatusSeq, MeasurementStatus);

    NDDSUSERDllExport
    RTIBool MeasurementStatus_initialize(
        MeasurementStatus* self);

    NDDSUSERDllExport
    RTIBool MeasurementStatus_initialize_ex(
        MeasurementStatus* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MeasurementStatus_initialize_w_params(
        MeasurementStatus* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MeasurementStatus_finalize(
        MeasurementStatus* self);

    NDDSUSERDllExport
    void MeasurementStatus_finalize_ex(
        MeasurementStatus* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MeasurementStatus_finalize_w_params(
        MeasurementStatus* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MeasurementStatus_finalize_optional_members(
        MeasurementStatus* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MeasurementStatus_copy(
        MeasurementStatus* dst,
        const MeasurementStatus* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MeasurementStatusBits
    {
        invalid  = 1,      
        questionable  = 2,      
        not_available  = 4,      
        calibration_ongoing  = 8,      
        test_data  = 16,      
        demo_data  = 32,      
        validated_data  = 256,      
        early_indication  = 512,      
        msmt_ongoing  = 1024,      
        msmt_state_in_alarm  = 16384,      
        msmt_state_al_inhibited  = 32768     
    } MeasurementStatusBits;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MeasurementStatusBits_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MeasurementStatusBitsSeq, MeasurementStatusBits);

    NDDSUSERDllExport
    RTIBool MeasurementStatusBits_initialize(
        MeasurementStatusBits* self);

    NDDSUSERDllExport
    RTIBool MeasurementStatusBits_initialize_ex(
        MeasurementStatusBits* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MeasurementStatusBits_initialize_w_params(
        MeasurementStatusBits* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MeasurementStatusBits_finalize(
        MeasurementStatusBits* self);

    NDDSUSERDllExport
    void MeasurementStatusBits_finalize_ex(
        MeasurementStatusBits* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MeasurementStatusBits_finalize_w_params(
        MeasurementStatusBits* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MeasurementStatusBits_finalize_optional_members(
        MeasurementStatusBits* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MeasurementStatusBits_copy(
        MeasurementStatusBits* dst,
        const MeasurementStatusBits* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricCalState
    {
        not_calibrated  = 0,      
        cal_required  = 1,      
        calibrated  = 2     
    } MetricCalState;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricCalState_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricCalStateSeq, MetricCalState);

    NDDSUSERDllExport
    RTIBool MetricCalState_initialize(
        MetricCalState* self);

    NDDSUSERDllExport
    RTIBool MetricCalState_initialize_ex(
        MetricCalState* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricCalState_initialize_w_params(
        MetricCalState* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricCalState_finalize(
        MetricCalState* self);

    NDDSUSERDllExport
    void MetricCalState_finalize_ex(
        MetricCalState* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricCalState_finalize_w_params(
        MetricCalState* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricCalState_finalize_optional_members(
        MetricCalState* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricCalState_copy(
        MetricCalState* dst,
        const MetricCalState* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
    typedef enum MetricCalType
    {
        cal_unspec  = 0,      
        cal_offset  = 1,      
        cal_gain  = 2,      
        cal_two_point  = 3     
    } MetricCalType;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricCalType_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricCalTypeSeq, MetricCalType);

    NDDSUSERDllExport
    RTIBool MetricCalType_initialize(
        MetricCalType* self);

    NDDSUSERDllExport
    RTIBool MetricCalType_initialize_ex(
        MetricCalType* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricCalType_initialize_w_params(
        MetricCalType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricCalType_finalize(
        MetricCalType* self);

    NDDSUSERDllExport
    void MetricCalType_finalize_ex(
        MetricCalType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricCalType_finalize_w_params(
        MetricCalType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricCalType_finalize_optional_members(
        MetricCalType* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricCalType_copy(
        MetricCalType* dst,
        const MetricCalType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *MetricCalEntryTYPENAME;

    struct MetricCalEntrySeq;

    class MetricCalEntry 
    {
      public:
        typedef struct MetricCalEntrySeq Seq;

        ice::MetricCalType   cal_type ;
        ice::MetricCalState   cal_state ;
        ice::Timespec   cal_time ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricCalEntry_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricCalEntrySeq, MetricCalEntry);

    NDDSUSERDllExport
    RTIBool MetricCalEntry_initialize(
        MetricCalEntry* self);

    NDDSUSERDllExport
    RTIBool MetricCalEntry_initialize_ex(
        MetricCalEntry* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricCalEntry_initialize_w_params(
        MetricCalEntry* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricCalEntry_finalize(
        MetricCalEntry* self);

    NDDSUSERDllExport
    void MetricCalEntry_finalize_ex(
        MetricCalEntry* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricCalEntry_finalize_w_params(
        MetricCalEntry* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricCalEntry_finalize_optional_members(
        MetricCalEntry* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricCalEntry_copy(
        MetricCalEntry* dst,
        const MetricCalEntry* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    typedef     ice::MetricCalEntrySeq  MetricCalibration ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricCalibration_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricCalibrationSeq, MetricCalibration);

    NDDSUSERDllExport
    RTIBool MetricCalibration_initialize(
        MetricCalibration* self);

    NDDSUSERDllExport
    RTIBool MetricCalibration_initialize_ex(
        MetricCalibration* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricCalibration_initialize_w_params(
        MetricCalibration* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricCalibration_finalize(
        MetricCalibration* self);

    NDDSUSERDllExport
    void MetricCalibration_finalize_ex(
        MetricCalibration* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricCalibration_finalize_w_params(
        MetricCalibration* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricCalibration_finalize_optional_members(
        MetricCalibration* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricCalibration_copy(
        MetricCalibration* dst,
        const MetricCalibration* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *MetricMeasureTYPENAME;

    struct MetricMeasureSeq;

    class MetricMeasure 
    {
      public:
        typedef struct MetricMeasureSeq Seq;

        ice::FLOATType   value ;
        ice::OIDType   unit_code ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricMeasure_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricMeasureSeq, MetricMeasure);

    NDDSUSERDllExport
    RTIBool MetricMeasure_initialize(
        MetricMeasure* self);

    NDDSUSERDllExport
    RTIBool MetricMeasure_initialize_ex(
        MetricMeasure* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricMeasure_initialize_w_params(
        MetricMeasure* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricMeasure_finalize(
        MetricMeasure* self);

    NDDSUSERDllExport
    void MetricMeasure_finalize_ex(
        MetricMeasure* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricMeasure_finalize_w_params(
        MetricMeasure* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricMeasure_finalize_optional_members(
        MetricMeasure* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricMeasure_copy(
        MetricMeasure* dst,
        const MetricMeasure* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *MetricContextTYPENAME;

    struct MetricContextSeq;

    class MetricContext 
    : public ice::VMO{
      public:
        typedef struct MetricContextSeq Seq;

        DDS_Long   context_seq_number ;
        ice::MetricSpec   metric_specification ;
        ice::Duration   * max_delay_time ;
        DDS_Char *   vmo_label_string ;
        ice::VmoSourceList   vmo_source_list ;
        ice::MetricSourceList   metric_source_list ;
        ice::OIDType   unit_code ;
        DDS_Char *   unit_label_string ;
        ice::SiteList   msmt_site_list ;
        ice::SiteList   body_site_list ;
        ice::MetricStatus   metric_status ;
        ice::MetricMeasure   * measure_period ;
        ice::MetricMeasure   * averaging_period ;
        ice::Timespec   * start_time ;
        ice::Timespec   * stop_time ;
        ice::MetricCalibration   metric_calibration ;
        ice::SimpleColor   * color ;
        ice::MeasurementStatus   measurement_status ;
        ice::OIDType   metric_id ;
        DDS_Char *   metric_info_label_string ;
        ice::ExtNomenRef   * substance ;
        DDS_Char *   substance_label_string ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricContext_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricContextSeq, MetricContext);

    NDDSUSERDllExport
    RTIBool MetricContext_initialize(
        MetricContext* self);

    NDDSUSERDllExport
    RTIBool MetricContext_initialize_ex(
        MetricContext* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricContext_initialize_w_params(
        MetricContext* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricContext_finalize(
        MetricContext* self);

    NDDSUSERDllExport
    void MetricContext_finalize_ex(
        MetricContext* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricContext_finalize_w_params(
        MetricContext* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricContext_finalize_optional_members(
        MetricContext* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricContext_copy(
        MetricContext* dst,
        const MetricContext* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    extern const char *MetricObservedValueTYPENAME;

    struct MetricObservedValueSeq;

    class MetricObservedValue 
    : public ice::VMO{
      public:
        typedef struct MetricObservedValueSeq Seq;

        DDS_Long   context_seq_number ;
        ice::NomPartition   metric_id_partition ;
        ice::Timespec   * device_timestamp ;
        ice::Duration   * device_relative_timestamp ;

    };
    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    NDDSUSERDllExport DDS_TypeCode* MetricObservedValue_get_typecode(void); /* Type code */

    DDS_SEQUENCE(MetricObservedValueSeq, MetricObservedValue);

    NDDSUSERDllExport
    RTIBool MetricObservedValue_initialize(
        MetricObservedValue* self);

    NDDSUSERDllExport
    RTIBool MetricObservedValue_initialize_ex(
        MetricObservedValue* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool MetricObservedValue_initialize_w_params(
        MetricObservedValue* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    void MetricObservedValue_finalize(
        MetricObservedValue* self);

    NDDSUSERDllExport
    void MetricObservedValue_finalize_ex(
        MetricObservedValue* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void MetricObservedValue_finalize_w_params(
        MetricObservedValue* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void MetricObservedValue_finalize_optional_members(
        MetricObservedValue* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool MetricObservedValue_copy(
        MetricObservedValue* dst,
        const MetricObservedValue* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
} /* namespace ice  */

#endif /* metric */

