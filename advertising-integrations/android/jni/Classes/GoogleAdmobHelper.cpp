/*
 * GoogleAdmobHelper.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: dungtavan
 */

#include "../../include/GoogleAdmobHelper.h"
#include <jni.h>
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"
#include "GoogleAdmobHelper.h"

using namespace std;
using namespace cocos2d;
using namespace com::tvd::plugin;

GoogleAdmobHelper::GoogleAdmobHelper() :
		mTestDevices(vector<string>()) {

}

void GoogleAdmobHelper::initInterstitial(const std::string &admobId,
		bool debug) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAdmobHelper",
			"initInterstitial",
			"(Ljava/lang/String;)V")) {
		jstring j_unitId = t.env->NewStringUTF(admobId.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_unitId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_unitId);

		return;
	}
}

void GoogleAdmobHelper::addTestDevices(
		const std::vector<std::string> &devices) {
	mTestDevices.insert(mTestDevices.end(), devices.begin(), devices.end());
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAdmobHelper",
			"addTestDevices",
			"(Ljava/lang/String;)V")) {
		jstring j_device = t.env->NewStringUTF(devices[0].c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_device);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_device);

		return;
	}
}

void GoogleAdmobHelper::showInterstitial() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAdmobHelper",
			"showInterstitial",
			"()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);

		return;
	}
}

void GoogleAdmobHelper::requestInterstitial() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAdmobHelper",
			"requestInterstitial",
			"()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);

		return;
	}
}

bool GoogleAdmobHelper::isInterstitialReady() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAdmobHelper",
			"isInterstitialReady",
			"()Z"))
	{
		bool result = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);

		return (bool)result;
	}

	return false;
}
