
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from common.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include "commonSupport.h"
#include "commonPlugin.h"

#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

namespace ice {

    /* ========================================================================= */
    /**
    <<IMPLEMENTATION>>

    Defines:   TData,
    TDataWriter,
    TDataReader,
    TTypeSupport

    Configure and implement 'EventReport' support classes.

    Note: Only the #defined classes get defined
    */

    /* ----------------------------------------------------------------- */
    /* DDSDataWriter
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataWriter, TData
    */

    /* Requires */
    #define TTYPENAME   EventReportTYPENAME

    /* Defines */
    #define TDataWriter EventReportDataWriter
    #define TData       ice::EventReport

    #include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"

    #undef TDataWriter
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* DDSDataReader
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataReader, TDataSeq, TData
    */

    /* Requires */
    #define TTYPENAME   EventReportTYPENAME

    /* Defines */
    #define TDataReader EventReportDataReader
    #define TDataSeq    EventReportSeq
    #define TData       ice::EventReport

    #include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"

    #undef TDataReader
    #undef TDataSeq
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* TypeSupport

    <<IMPLEMENTATION >>

    Requires:  TTYPENAME,
    TPlugin_new
    TPlugin_delete
    Defines:   TTypeSupport, TData, TDataReader, TDataWriter
    */

    /* Requires */
    #define TTYPENAME    EventReportTYPENAME
    #define TPlugin_new  ice::EventReportPlugin_new
    #define TPlugin_delete  ice::EventReportPlugin_delete

    /* Defines */
    #define TTypeSupport EventReportTypeSupport
    #define TData        ice::EventReport
    #define TDataReader  EventReportDataReader
    #define TDataWriter  EventReportDataWriter
    #define TGENERATE_SER_CODE
    #define TGENERATE_TYPECODE

    #include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

    #undef TTypeSupport
    #undef TData
    #undef TDataReader
    #undef TDataWriter
    #undef TGENERATE_TYPECODE
    #undef TGENERATE_SER_CODE
    #undef TTYPENAME
    #undef TPlugin_new
    #undef TPlugin_delete

    /* ========================================================================= */
    /**
    <<IMPLEMENTATION>>

    Defines:   TData,
    TDataWriter,
    TDataReader,
    TTypeSupport

    Configure and implement 'CT_decimal' support classes.

    Note: Only the #defined classes get defined
    */

    /* ----------------------------------------------------------------- */
    /* DDSDataWriter
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataWriter, TData
    */

    /* Requires */
    #define TTYPENAME   CT_decimalTYPENAME

    /* Defines */
    #define TDataWriter CT_decimalDataWriter
    #define TData       ice::CT_decimal

    #include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"

    #undef TDataWriter
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* DDSDataReader
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataReader, TDataSeq, TData
    */

    /* Requires */
    #define TTYPENAME   CT_decimalTYPENAME

    /* Defines */
    #define TDataReader CT_decimalDataReader
    #define TDataSeq    CT_decimalSeq
    #define TData       ice::CT_decimal

    #include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"

    #undef TDataReader
    #undef TDataSeq
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* TypeSupport

    <<IMPLEMENTATION >>

    Requires:  TTYPENAME,
    TPlugin_new
    TPlugin_delete
    Defines:   TTypeSupport, TData, TDataReader, TDataWriter
    */

    /* Requires */
    #define TTYPENAME    CT_decimalTYPENAME
    #define TPlugin_new  ice::CT_decimalPlugin_new
    #define TPlugin_delete  ice::CT_decimalPlugin_delete

    /* Defines */
    #define TTypeSupport CT_decimalTypeSupport
    #define TData        ice::CT_decimal
    #define TDataReader  CT_decimalDataReader
    #define TDataWriter  CT_decimalDataWriter
    #define TGENERATE_SER_CODE
    #define TGENERATE_TYPECODE

    #include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

    #undef TTypeSupport
    #undef TData
    #undef TDataReader
    #undef TDataWriter
    #undef TGENERATE_TYPECODE
    #undef TGENERATE_SER_CODE
    #undef TTYPENAME
    #undef TPlugin_new
    #undef TPlugin_delete

} /* namespace ice  */

