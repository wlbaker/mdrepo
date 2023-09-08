/*
 *
 * Directors are necessare for callbacks and overriding (virtual) functions in a class.
 * The indicator here only inserts stub code at the end of the wrapper.  Still need to
 * enable specific classes with the "feature" attribute.
*/
#ifdef SWIGPYTHON
%module(directors="1") pypistax;
#else
%module(directors="1") PISTAX;
#endif

/*
 * affects generation of enums..as constant integers, which is what you probably want
 */

%include "stdint.i"

#ifdef SWIGJAVA
%include "enumtypeunsafe.swg"
#endif

%{
/* Includes the header in the wrapper code */
#include <iostream>
#include <stdint.h>

#include "config.h"
#include "pista.h"

#include "pista-cl.h"


#pragma GCC diagnostic ignored "-Wunused-function"
%}

%newobject PistaDev::poll;


#ifdef SWIGPYTHON

%typemap(in,numinputs=0,noblock=1) size_t *len {
    size_t arr_sz = 0; // output parameter

    arg3 = &arr_sz;
}

%typemap(out) int[] {
    int arr_sz = (arg3 == NULL) ? 0 : *arg3;
    $result = PyList_New( arr_sz );
    for(int i =0; i < arr_sz; i++) {
       PyObject *o = PyLong_FromLong((long)$1[i]);
       PyList_SetItem($result,i,o);
    }
}

%typemap(out) float[] {
    int arr_sz = (arg3 == NULL) ? 0 : *arg3;
    $result = PyList_New( arr_sz );
    for(int i =0; i < arr_sz; i++) {
       PyObject *o = PyFloat_FromDouble((double)$1[i]);
       PyList_SetItem($result,i,o);
    }
}

%typemap(out) double[] {
    int arr_sz = (arg3 == NULL) ? 0 : *arg3;
    $result = PyList_New( arr_sz );
    for(int i =0; i < arr_sz; i++) {
       PyObject *o = PyFloat_FromDouble((double)$1[i]);
       PyList_SetItem($result,i,o);
    }
}

%apply int[] {int *};  /* generates a "no typedef defined" error if put at beginning */
%apply float[] {float *};
%apply double[] {double *};

#endif

#ifdef SWIGJAVA

%typemap(in,numinputs=0,noblock=1) size_t *len {
    size_t arr_sz = 0; // output parameter

    arg3 = &arr_sz;
}

//
// this is used when Java calls C++ write method
//
%javaexception("java.io.IOException") write {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("java/io/IOException");
    jenv->ThrowNew(clazz, "Write error");
    return $null;
   }
}

//
// this is used when C++ calls back into Java
// CHECKME -- this is a Swig 3.0 feature documented in swig docs 
// section 25.5.7 Java exceptions from directors
//
%feature("director:except") PistaCommHandler::write(const char data[], size_t len) {
  jthrowable $error = jenv->ExceptionOccurred();
  if ($error) {
    if (Swig::ExceptionMatches(jenv, $error, "java/io/IOException")) {
        // wlb -- dont clear exception, it will remain active
        return -1;
    }
    // throw std::runtime_error("Unexpected exception thrown in PistaCommHandler::write");
    jenv->ExceptionClear();
    throw Swig::DirectorException(jenv, $error);
  }
}


/* Only with RXTX
%javaexception("gnu.io.UnsupportedCommOperationException") config {
*/
%javaexception("java.io.IOException") config {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("gnu/io/UnsupportedCommOperationException");
    jenv->ThrowNew(clazz, "Config error");
    return $null;
   }
}

/* Only with RXTX
%javaexception("gnu.io.PortInUseException") open {
*/
%javaexception("java.io.IOException") open {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("gnu/io/PortInUseException");
    jenv->ThrowNew(clazz, "Could not open port");
    return $null;
   }
}


%apply (char *STRING, size_t LENGTH) { (const char data[], size_t len) }

%javaconst(1);

//
// make int and float array handling work like native
//
%include "arrays_java.i"
%typemap(out) double[] {
    $result = ($1 == NULL) ? NULL : SWIG_JavaArrayOutDouble(jenv, (double*)$1, (arg1)->getFieldQuantifier(arg2) ); 
}
%apply double[] {double *};

%typemap(out) float[] {
    $result = ($1 == NULL) ? NULL : SWIG_JavaArrayOutFloat(jenv, (float *)$1, (arg1)->getFieldQuantifier(arg2) ); 
}
%apply float[] {float *};

%typemap(out) int[] {
    $result = ($1 == NULL ) ? NULL : SWIG_JavaArrayOutInt(jenv, (int *)$1, (arg1)->getFieldQuantifier(arg2) ); 
}
%apply int[] {int *};

#endif


%feature("director") PistaEventHandler;
%feature("director") ProtobufEventHandler;
%feature("director") PistaCommHandler;
%feature("director") PistaDiscoveryHandler;

/* Parse the header file to generate wrappers */
%include "pista.h"

/* %feature("nspace") pistax; */
%include "pista-cl.h"

%inline %{

/***

// A debug class for testing various swig options and configurations

class loco {
    public:

    float *func1( int desc_idx, size_t *len ) {
        static float output[] = {1.0f, 2.0f, 3.0f, 4.0f};
        if( len != NULL && *len > 4 ) {
            *len = sizeof( output )/ sizeof( float );
        }
        return output;
    }
};
***/

%}

