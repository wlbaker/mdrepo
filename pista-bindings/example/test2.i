%module Crabby

%include "arrays_java.i"

%{
/* headers here are included in the wrapper code */
#include "sponge.h"
%}

%typemap(jtype) (const signed char *arr, size_t sz) "byte[]"
%typemap(jstype) (const signed char *arr, size_t sz) "byte[]"
%typemap(jni) (const signed char *arr, size_t sz) "jbyteArray"
%typemap(javain) (const signed char *arr, size_t sz) "$javainput"

%typemap(in,numinputs=1) (const signed char* arr, size_t sz) {
  $1 = JCALL2(GetByteArrayElements, jenv, $input, NULL);
  const size_t sz = JCALL1(GetArrayLength, jenv, $input);
  $2 = sz;
}

%typemap(freearg) (const signed char *arr, size_t sz) {
  // Or use  0 instead of ABORT to keep changes if it was a copy
  JCALL3(ReleaseByteArrayElements, jenv, $input, $1, JNI_ABORT);
}

%apply (const signed char* arr, size_t sz) { ( char* buff, int len) }

%inline %{
typedef struct {
    const char * content;
    int contentLength;
} Foo;

int write(const char *buf, int len);
%}

