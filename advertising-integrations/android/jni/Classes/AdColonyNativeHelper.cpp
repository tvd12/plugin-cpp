/*
 * AdColonyNativeHelper.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: dungtavan
 */

#include <string>
#include "AdColonyNativeHelper.h"
#include "../../include/AdColonyHelper.h"

using namespace com::tvd::plugin;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyV4VCReward(
			JNIEnv* env, jobject thiz,
			jboolean success,
			jstring name,
			jint amount,
			jstring zoneId) {
	const char* c_name = env->GetStringUTFChars(name, 0);
	const char* c_zoneid = env->GetStringUTFChars(zoneId, 0);
	AdColonyHelper::getInstance()->getDelegate()
			->onAdColonyV4VCReward((bool)success,
					std::string(c_name),
					(int)amount,
					std::string(c_zoneid));

	env->ReleaseStringUTFChars(name, c_name);
	env->ReleaseStringUTFChars(zoneId, c_zoneid);
}

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdAvailabilityChange(
			JNIEnv* env, jobject thiz,
			jboolean available, jstring zoneId) {
	const char* c_zoneid = env->GetStringUTFChars(zoneId, 0);
	AdColonyHelper::getInstance()->getDelegate()
			->onAdColonyAdAvailabilityChange((bool)available,
					std::string(c_zoneid));

	env->ReleaseStringUTFChars(zoneId, c_zoneid);
}

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdAttemptFinished(
			JNIEnv* env, jobject thiz,
			jboolean shown,
            jboolean iapEnabled,
            jint iapQuantity,
            jint iapEngagement,
            jstring zoneId,
            jstring iapProductId) {
	const char* c_zoneid = env->GetStringUTFChars(zoneId, 0);
	const char* c_productid = env->GetStringUTFChars(iapProductId, 0);
	AdColonyHelperAdInfo *helperInfor =
			new AdColonyHelperAdInfo((bool)shown,
					(bool)iapEnabled,
					(int)iapQuantity,
					(int)iapEngagement,
					std::string(c_zoneid),
					std::string(c_productid));
	AdColonyHelper::getInstance()->getDelegate()
				->onAdColonyAdAttemptFinishedWithInfo(helperInfor);
	env->ReleaseStringUTFChars(zoneId, c_zoneid);
	env->ReleaseStringUTFChars(iapProductId, c_productid);

    delete helperInfor;
    helperInfor = 0;
}

JNIEXPORT void Java_com_tvd_android_plugin_AdColonyHelperListener_nativeOnAdColonyAdStarted(
			JNIEnv* env, jobject thiz,
            jstring zoneId) {
	const char* c_zoneid = env->GetStringUTFChars(zoneId, 0);
	AdColonyHelper::getInstance()->getDelegate()
			->onAdColonyAdStartedInZone(std::string(c_zoneid));
	env->ReleaseStringUTFChars(zoneId, c_zoneid);
}

#ifdef __cplusplus
}
#endif
