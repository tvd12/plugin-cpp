/*
 * GoogleAdmobNativeHelper.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: dungtavan
 */

#include <string>
#include "GoogleAdmobNativeHelper.h"
#include "../../include/GoogleAdmobHelper.h"

using namespace com::tvd::plugin;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdClosed(
			JNIEnv* env, jobject thiz,
			jstring adUnitId) {

	const char* c_ad_unit_id = env->GetStringUTFChars(adUnitId, 0);
	GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
			->interstitialDidDismissScreen(c_ad_unit_id);
	env->ReleaseStringUTFChars(adUnitId, c_ad_unit_id);
}

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdFailedToLoad(
			JNIEnv* env, jobject thiz,
			jstring adUnitId,
			jstring error) {

	const char* c_ad_unit_id = env->GetStringUTFChars(adUnitId, 0);
	const char* c_error = env->GetStringUTFChars(error, 0);
	GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
			->interstitial(c_ad_unit_id, c_error);

	env->ReleaseStringUTFChars(adUnitId, c_ad_unit_id);
	env->ReleaseStringUTFChars(error, c_error);
}

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdLoaded(
			JNIEnv* env, jobject thiz,
			jstring adUnitId) {

	const char* c_ad_unit_id = env->GetStringUTFChars(adUnitId, 0);
	GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
			->interstitialDidReceiveAd(c_ad_unit_id);
	env->ReleaseStringUTFChars(adUnitId, c_ad_unit_id);
}

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdOpened(
			JNIEnv* env, jobject thiz,
			jstring adUnitId) {

	const char* c_ad_unit_id = env->GetStringUTFChars(adUnitId, 0);
	GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
			->interstitialWillPresentScreen(c_ad_unit_id);
	env->ReleaseStringUTFChars(adUnitId, c_ad_unit_id);
}

JNIEXPORT void Java_com_tvd_android_plugin_GoogleAdmobHelper_nativeOnAdLeftApplication(
			JNIEnv* env, jobject thiz,
			jstring adUnitId) {

	const char* c_ad_unit_id = env->GetStringUTFChars(adUnitId, 0);
	GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
			->interstitialWillLeaveApplication(c_ad_unit_id);
	env->ReleaseStringUTFChars(adUnitId, c_ad_unit_id);
}

#ifdef __cplusplus
}
#endif
