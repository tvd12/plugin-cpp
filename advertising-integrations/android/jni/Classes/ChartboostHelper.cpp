/*
 * ChartboostHelper.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: dungtavan
 */

#include "ChartboostHelper.h"
#include <jni.h>
#include <string>
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace std;
using namespace cocos2d;
using namespace com::tvd::plugin;

ChartboostHelper::ChartboostHelper() {

}

void ChartboostHelper::init(const std::string appId,
              const std::string appSignature) {

}

void ChartboostHelper::showInterstitial(const string& location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"showInterstitial",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

void ChartboostHelper::cacheInterstitial(const std::string& location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"cacheInterstitial",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

bool ChartboostHelper::hasCachedInterstitial(const std::string &location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"hasCachedInterstitial",
			"(Ljava/lang/String;)Z"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		bool result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return (bool)result;
	}

	return false;
}

void ChartboostHelper::cacheMoreApps(const std::string& location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"cacheMoreApps",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

void ChartboostHelper::showMoreApps(const std::string &location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"showMoreApps",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

bool ChartboostHelper::hasMoreApps(const std::string& location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"hasMoreApps",
			"(Ljava/lang/String;)Z"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		bool result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return (bool)result;
	}

	return false;
}

void ChartboostHelper::cacheRewardedVideo(const std::string &location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"cacheRewardedVideo",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

void ChartboostHelper::showRewardedVideo(const std::string &location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"showRewardedVideo",
			"(Ljava/lang/String;)V"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return;
	}
}

bool ChartboostHelper::hasRewardedVideo(const std::string &location) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"hasRewardedVideo",
			"(Ljava/lang/String;)Z"))
	{
		jstring j_location = t.env->NewStringUTF(location.c_str());
		bool result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, j_location);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_location);

		return (bool)result;
	}

	return false;
}

void ChartboostHelper::setShouldRequestInterstitialsInFirstSession() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/ChartboostHelper",
			"setShouldRequestInterstitialsInFirstSession",
			"(Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);

		return;
	}
}
