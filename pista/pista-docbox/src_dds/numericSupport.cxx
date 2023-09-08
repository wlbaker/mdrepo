
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from numeric.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include "numericSupport.h"
#include "numericPlugin.h"

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

    Configure and implement 'NumericContext' support classes.

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
    #define TTYPENAME   NumericContextTYPENAME

    /* Defines */
    #define TDataWriter NumericContextDataWriter
    #define TData       ice::NumericContext

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
    #define TTYPENAME   NumericContextTYPENAME

    /* Defines */
    #define TDataReader NumericContextDataReader
    #define TDataSeq    NumericContextSeq
    #define TData       ice::NumericContext

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
    #define TTYPENAME    NumericContextTYPENAME
    #define TPlugin_new  ice::NumericContextPlugin_new
    #define TPlugin_delete  ice::NumericContextPlugin_delete

    /* Defines */
    #define TTypeSupport NumericContextTypeSupport
    #define TData        ice::NumericContext
    #define TDataReader  NumericContextDataReader
    #define TDataWriter  NumericContextDataWriter
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

    Configure and implement 'NumericObservedValue' support classes.

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
    #define TTYPENAME   NumericObservedValueTYPENAME

    /* Defines */
    #define TDataWriter NumericObservedValueDataWriter
    #define TData       ice::NumericObservedValue

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
    #define TTYPENAME   NumericObservedValueTYPENAME

    /* Defines */
    #define TDataReader NumericObservedValueDataReader
    #define TDataSeq    NumericObservedValueSeq
    #define TData       ice::NumericObservedValue

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
    #define TTYPENAME    NumericObservedValueTYPENAME
    #define TPlugin_new  ice::NumericObservedValuePlugin_new
    #define TPlugin_delete  ice::NumericObservedValuePlugin_delete

    /* Defines */
    #define TTypeSupport NumericObservedValueTypeSupport
    #define TData        ice::NumericObservedValue
    #define TDataReader  NumericObservedValueDataReader
    #define TDataWriter  NumericObservedValueDataWriter
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

