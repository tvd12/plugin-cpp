/*
 * TapjoyNativeHelper.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: dungtavan
 */

#include <string>
#include "TapjoyNativeHelper.h"
#include "../../include/TapjoyHelper.h"

using namespace com::tvd::plugin;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Common native
 */
JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOnConnectSuccess(
			JNIEnv* env, jobject thiz) {
	TapjoyHelper::getInstance()->getCommonDelegate()
			->onConnectSuccess();
}

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOnConnectFailure(
			JNIEnv* env, jobject thiz) {
	TapjoyHelper::getInstance()->getCommonDelegate()
			->onConnectFail();
}

/**
 * Offerwall native
 */
JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnRequestSuccess(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jboolean isContentReady,
			jboolean isContentAvailable ) {
	const char* c_placement_name = env->GetStringUTFChars(placementName, 0);

	TapjoyHelper::getInstance()->getOfferwallDelegate()
			->requestDidSucceed(c_placement_name,
					(bool)isContentReady,
					(bool)isContentAvailable);

	env->ReleaseStringUTFChars(placementName, c_placement_name);
}

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnRequestFailure(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jstring error) {
	const char* c_placement_name = env->GetStringUTFChars(placementName, 0);
	const char* c_error = env->GetStringUTFChars(error, 0);

	TapjoyHelper::getInstance()->getOfferwallDelegate()
			->requestDidFail(c_placement_name, c_error);

	env->ReleaseStringUTFChars(placementName, c_placement_name);
	env->ReleaseStringUTFChars(error, c_error);
}

JNIEXPORT jboolean Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentReady(
			JNIEnv* env, jobject thiz,
			jstring placementName,
			jstring isContentAvailable) {

	const char* c_placement_name = env->GetStringUTFChars(placementName, 0);

	bool result = TapjoyHelper::getInstance()->getOfferwallDelegate()
			->contentIsReady(c_placement_name, (bool)isContentAvailable);

	env->ReleaseStringUTFChars(placementName, c_placement_name);

	return (jboolean)result;
}

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentShow(
			JNIEnv* env, jobject thiz,
			jstring placementName) {

	const char* c_placement_name = env->GetStringUTFChars(placementName, 0);

	TapjoyHelper::getInstance()->getOfferwallDelegate()
			->contentDidDisappear(c_placement_name);

	env->ReleaseStringUTFChars(placementName, c_placement_name);

}

JNIEXPORT void Java_com_tvd_android_plugin_TapjoyHelper_nativeOfferwallOnContentDismiss(
			JNIEnv* env, jobject thiz,
			jstring placementName) {

	const char* c_placement_name = env->GetStringUTFChars(placementName, 0);

	TapjoyHelper::getInstance()->getOfferwallDelegate()
			->contentDidDisappear(c_placement_name);

	env->ReleaseStringUTFChars(placementName, c_placement_name);

}

#ifdef __cplusplus
}
#endif
