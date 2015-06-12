/*
 * AdColonyHelper.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: dungtavan
 */

#include <jni.h>
#include <string>

#include "../../include/AdColonyHelper.h"
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace std;
using namespace cocos2d;
using namespace com::tvd::plugin;

AdColonyHelper::AdColonyHelper() {

}

void AdColonyHelper::init(const std::string& appId,
              std::vector<std::string> &zoneIds,
              bool logging){

}

void AdColonyHelper::checkeExistenceVideoAd(const std::string &zoneId) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"checkeExistenceVideoAd",
			"(Ljava/lang/String;)V"))
	{
		jstring j_zoneid = t.env->NewStringUTF(zoneId.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_zoneid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_zoneid);

		return;
	}
}

void AdColonyHelper::playVideoAdForZone(const std::string &zoneId) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"showVideoAd",
			"(Ljava/lang/String;)V"))
	{
		jstring j_zoneid = t.env->NewStringUTF(zoneId.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_zoneid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_zoneid);

		return;
	}
}

void AdColonyHelper::playVideoAdForZone(const std::string &zoneId,
                            bool showPrePopup,
                            bool showPostPopup) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"showVideoAd",
			"(Ljava/lang/String;ZZ)V"))
	{
		jstring j_zoneid = t.env->NewStringUTF(zoneId.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_zoneid,
				(jboolean)showPrePopup,
				(jboolean)showPostPopup);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_zoneid);

		return;
	}
}

int AdColonyHelper::zoneStatusForZone(const std::string &zoneId) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"statusForZone",
			"(Ljava/lang/String;)I"))
	{
		jstring j_zoneid = t.env->NewStringUTF(zoneId.c_str());
		jint result = t.env->CallStaticIntMethod(t.classID, t.methodID, j_zoneid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_zoneid);

		return (int)result;
	}

	return 0;
}

void AdColonyHelper::setCustomId(const std::string &customId) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"setCustomId",
			"(Ljava/lang/String;)V"))
	{
		jstring j_customId = t.env->NewStringUTF(customId.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_customId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_customId);

		return;
	}
}

std::string AdColonyHelper::getCustomId() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"getCustomId",
			"()V"))
	{
		jstring result = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID));
		t.env->DeleteLocalRef(t.classID);

		std::string c_result = PluginJniHelper::jstring2string(result);

		t.env->DeleteLocalRef(result);

		return c_result;
	}

	return "";
}

std::string AdColonyHelper::getOpenUDID() {
	return "";
}

std::string AdColonyHelper::getUniqueDeviceId() {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"getDeviceId",
			"()V"))
	{
		jstring result = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID));
		t.env->DeleteLocalRef(t.classID);

		std::string c_result = PluginJniHelper::jstring2string(result);

		t.env->DeleteLocalRef(result);

		return c_result;
	}

	return "";
}

std::string AdColonyHelper::getODIN1() {
	return "";
}

std::string AdColonyHelper::getAdvertisingIdentifier() {
	return "";
}

std::string AdColonyHelper::getVendorIdentifier() {
	return "";
}

bool AdColonyHelper::isVirtualCurrencyRewardAvailableForZone(const std::string &zoneId) {
	return true;
}

int AdColonyHelper::getVirtualCurrencyRewardsAvailableTodayForZone(const std::string &zoneId) {
	return 1;
}

std::string AdColonyHelper::getVirtualCurrencyNameForZone(const std::string &zoneId) {
	return "life";
}

int AdColonyHelper::getVirtualCurrencyRewardAmountForZone(const std::string &zoneId) {
	return 1;
}

int AdColonyHelper::getVideosPerReward(const std::string &currencyName) {
	return 1;
}

int AdColonyHelper::getVideoCreditBalance(const std::string &currencyName) {
	return 1;
}

void AdColonyHelper::setOptions(const std::map<std::string, std::string> &options) {

}

void AdColonyHelper::cancelAd() {

}

bool AdColonyHelper::videoAdCurrentlyRunning() {

}

void AdColonyHelper::turnAllAdsOff() {

}

void AdColonyHelper::setUserMetadata(const std::string& metadataType,
                         const std::string& value) {

}

void AdColonyHelper::userInterestedIn(const std::string& topic) {

}

void AdColonyHelper::notifyIAPComplete(const std::string &transactionId,
                           const std::string &productId,
                           int quantity,
                           int price,
                           const std::string &currencyCode) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/AdColonyHelper",
			"notifyIAPComplete",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D;)V"))
	{
		jstring j_productid = t.env->NewStringUTF(productId.c_str());
		jstring j_transactionid = t.env->NewStringUTF(transactionId.c_str());
		jstring j_currencycode = t.env->NewStringUTF(currencyCode.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, j_productid,
				j_transactionid, j_currencycode, (jdouble)price);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_productid);
		t.env->DeleteLocalRef(j_transactionid);
		t.env->DeleteLocalRef(j_currencycode);

		return;
	}
}

