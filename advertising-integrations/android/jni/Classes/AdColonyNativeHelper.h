/*
 * AdColonyNativeHelper.h
 *
 *  Created on: Apr 25, 2015
 *      Author: dungtavan
 */

#ifndef CLASSES_ADCOLONYNATIVEHELPER_H_
#define CLASSES_ADCOLONYNATIVEHELPER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyV4VCReward(
			JNIEnv* env, jobject thiz,
			jboolean success,
			jstring name,
			jint amount,
			jstring zoneId);
JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdAvailabilityChange(
			JNIEnv* env, jobject thiz,
			jboolean available, jstring zoneId);
JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdAttemptFinished(
			JNIEnv* env, jobject thiz,
			jboolean shown,
            jboolean iapEnabled,
            jint iapQuantity,
            jint iapEngagement,
            jstring zoneId,
            jstring iapProductId);

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdStarted(
			JNIEnv* env, jobject thiz,
            jstring zoneId);

#ifdef __cplusplus
}
#endif


#endif /* CLASSES_ADCOLONYNATIVEHELPER_H_ */
