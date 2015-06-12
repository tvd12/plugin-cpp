/*
 * ChartboostNativeHelper.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: dungtavan
 */

#include <string>
#include "ChartboostNativeHelper.h"
#include "../../include/ChartboostHelper.h"

using namespace com::tvd::plugin;

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldRequestInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);
	bool result = ChartboostHelper::getInstance()->getDelegate()
			->shouldRequestInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);

	return (jboolean)result;
}

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	bool result = ChartboostHelper::getInstance()->getDelegate()
					->shouldDisplayInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);

	return (jboolean)result;
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didCacheInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadInterstitial(
		JNIEnv* env, jobject thiz, jstring location, jint error) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didFailToLoadInterstitial(std::string(c_location), (int)error);

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didDismissInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didCloseInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didClickInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayInterstitial(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didDisplayInterstitial(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldRequestMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	bool result = ChartboostHelper::getInstance()->getDelegate()
								->shouldRequestMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);

	return (jboolean)result;
}

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	bool result = ChartboostHelper::getInstance()->getDelegate()
						->shouldDisplayMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);

	return (jboolean)result;
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadMoreApps(
		JNIEnv* env, jobject thiz, jstring location, jint error) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didFailToLoadMoreApps(std::string(c_location), (int)error);

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didCacheMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didDismissMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didCloseMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didClickMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayMoreApps(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
						->didDisplayMoreApps(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToRecordClick(
		JNIEnv* env, jobject thiz, jstring puri, jint error) {
	const char* c_location = env->GetStringUTFChars(puri, 0);

	ChartboostHelper::getInstance()->getDelegate()
							->didFailToRecordClick(std::string(c_location), (int)error);

	env->ReleaseStringUTFChars(puri, c_location);
}

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	bool result = ChartboostHelper::getInstance()->getDelegate()
							->shouldDisplayRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);

	return (jboolean)result;
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didCacheRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location, jint error) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didFailToLoadRewardedVideo(std::string(c_location), (int)error);

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didDismissRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didCloseRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didClickRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCompleteRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location, jint reward) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didCompleteRewardedVideo(std::string(c_location), (int)reward);

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayRewardedVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->didDisplayRewardedVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeWillDisplayVideo(
		JNIEnv* env, jobject thiz, jstring location) {
	const char* c_location = env->GetStringUTFChars(location, 0);

	ChartboostHelper::getInstance()->getDelegate()
								->willDisplayVideo(std::string(c_location));

	env->ReleaseStringUTFChars(location, c_location);
}

#ifdef __cplusplus
}
#endif
