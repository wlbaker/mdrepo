/*
 * jniUtil.h
 *
 *  Created on: Oct 10, 2009
 *      Author: bbaker
 */

#ifndef JNIUTIL_H_
#define JNIUTIL_H_

extern "C" {
TaskHandle getTaskHandle( JNIEnv *env, jobject jobj );
TaskHandle getTaskHandleFromTaskField( JNIEnv *env, jobject jobj );
jobject getObjField( JNIEnv *env, jobject jobj, const char *fieldName, const char *sig );
int getIntField( JNIEnv *env, jobject jobj, const char *fieldName );
jstring getChannelName( JNIEnv *env, jobject jobj );
void *getCallbackHandle2( JNIEnv *env, jobject jobj );

int throwDaqError( JNIEnv *env, const char *errBuff );
}

#endif /* JNIUTIL_H_ */
