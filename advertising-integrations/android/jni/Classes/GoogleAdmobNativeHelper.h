/*
 * GoogleAdmobNativeHelper.h
 *
 *  Created on: Jun 10, 2015
 *      Author: dungtavan
 */

#ifndef CLASSES_GOOGLEADMOBNATIVEHELPER_H_
#define CLASSES_GOOGLEADMOBNATIVEHELPER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdClosed(
			JNIEnv* env, jobject thiz,
			jstring adUnitId);

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdFailedToLoad(
			JNIEnv* env, jobject thiz,
			jstring adUnitId,
			jstring error);

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdLoaded(
			JNIEnv* env, jobject thiz,
			jstring adUnitId);

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdOpened(
			JNIEnv* env, jobject thiz,
			jstring adUnitId);

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdLeftApplication(
			JNIEnv* env, jobject thiz,
			jstring adUnitId);

#ifdef __cplusplus
}
#endif

#endif /* CLASSES_GOOGLEADMOBNATIVEHELPER_H_ */
