/*
 * TapjoyHelper.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: dungtavan
 */

#include "../../include/TapjoyHelper.h"
#include <jni.h>
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace std;
using namespace cocos2d;
using namespace com::tvd::plugin;

TapjoyHelper::TapjoyHelper() :
mCommonDelegate(NULL),
mViewDelegate(NULL),
mVideoDelegate(NULL),
mPlacementDelegate(NULL),
mDirectPlayDelegate(NULL),
mOfferwallDelegate(NULL),
mVideoUnit(""),
mOfferwallUnit("") {

}

void TapjoyHelper::init(const std::string &sdkKey,
          const std::string &userId,
          bool debug) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/TapjoyHelper",
			"connect",
			"(Ljava/lang/String;Z)V")) {
		jstring j_sdkKey = t.env->NewStringUTF(sdkKey.c_str());
		jboolean j_debug = (jboolean)debug;
		t.env->CallStaticVoidMethod(t.classID, t.methodID,
				j_sdkKey, j_debug);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(j_sdkKey);

		return;
	}
}

void TapjoyHelper::initViewController() {

}

void TapjoyHelper::addCurrencyEarnedListener() {

}

void TapjoyHelper::removeCurrencyEarnedListener() {

}

void TapjoyHelper::requestOfferwall(const std::string &offerwallUnit) {

}
void TapjoyHelper::showOfferwall() {

}

void TapjoyHelper::requestDirectPlayVideo(const std::string &videoUnit) {

}
void TapjoyHelper::showDirectPlayVideo() {

}
bool TapjoyHelper::hasDirectPlayVideo() {

}
bool TapjoyHelper::isDirectPlayVideoReady() {

}

std::string TapjoyHelper::getCurrentBalance() {

}

std::string TapjoyHelper::spendCurrency(int value) {

}

std::string TapjoyHelper::awardCurrecy(int value) {

}

bool TapjoyHelper::requestContent(const std::string &placementName) {

}

bool TapjoyHelper::showContent() {

}
