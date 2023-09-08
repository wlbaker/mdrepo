/*
 *
 * Directors are necessare for callbacks and overriding (virtual) functions in a class.
 * The indicator here only inserts stub code at the end of the wrapper.  Still need to
 * enable specific classes with the "feature" attribute.
*/

#ifdef SWIGPYTHON
%module pypista;
#else
%module PISTA;
#endif


#ifdef SWIGJAVA
%include "enumtypeunsafe.swg"
#endif

%{
/* Includes the header in the wrapper code */
#include <stdint.h>

#include "config.h"
#include "pista.h"

#ifdef SWIGPYTHON
// PyObject PyInstance_Type;
#endif

#pragma GCC diagnostic ignored "-Wunused-function"
%}
 
/* Parse the header file to generate wrappers */

/* DIDNT WORK
%include "arrays_java.i"
%apply byte[] {const char *};
*/

#ifdef SWIGJAVA

%javaexception("java.io.IOException") write {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("java/io/IOException");
    jenv->ThrowNew(clazz, "Write error");
    return $null;
   }
}

/* only with RXTX
%javaexception("gnu.io.PortInUseException") open {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("gnu/io/PortInUseException");
    jenv->ThrowNew(clazz, "Could not open port");
    return $null;
   }
}

%javaexception("gnu.io.UnsupportedCommOperationException") config {
  try {
     $action
  } catch (int e) {
    jclass clazz = jenv->FindClass("gnu/io/UnsupportedCommOperationException");
    jenv->ThrowNew(clazz, "Config error");
    return $null;
   }
}
*/

%apply (char *STRING, size_t LENGTH) { (const char data[], size_t len) }

%javaconst(1);

#endif

%include "stdint.i"
%include "config.h"

%feature("nspace") pista;
%nspace pista;
namespace pista {
%include "pista.h"
}

