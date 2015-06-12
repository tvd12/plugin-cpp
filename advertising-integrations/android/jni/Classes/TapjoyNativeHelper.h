/*
 * TapjoyNativeHelper.h
 *
 *  Created on: Jun 11, 2015
 *      Author: dungtavan
 */

#ifndef CLASSES_TAPJOYNATIVEHELPER_H_
#define CLASSES_TAPJOYNATIVEHELPER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Common native
 */
JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOnConnectSuccess(
			JNIEnv* env, jobject thiz);

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOnConnectFailure(
			JNIEnv* env, jobject thiz);

/**
 * Offerwall native
 */

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnRequestSuccess(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jboolean isContentReady,
			jboolean isContentAvailable );

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnRequestFailure(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jstring error);

JNIEXPORT jboolean Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentReady(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jstring isContentAvailable);

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentShow(
			JNIEnv* env, jobject thiz,
			jstring placementName);

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentDismiss(
			JNIEnv* env, jobject thiz,
			jstring placementName);

#ifdef __cplusplus
}
#endif

#endif /* CLASSES_TAPJOYNATIVEHELPER_H_ */
