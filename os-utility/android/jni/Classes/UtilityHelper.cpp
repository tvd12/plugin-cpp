#include "UtilityHelper.h"
#include <jni.h>
#include <string>

#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace cocos2d;
using namespace com::tvd::plugin;

void UtilityHelper::rateUs() {
	PluginJniMethodInfo t;
		if (PluginJniHelper::getStaticMethodInfo(t,
				"com/tvd/android/plugin/UtilityHelper",
				"sRateUs",
				"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			return;
		}
}

void UtilityHelper::vibrate() {
	PluginJniMethodInfo t;
			if (PluginJniHelper::getStaticMethodInfo(t,
					"com/tvd/android/plugin/UtilityHelper",
					"sVibrate",
					"()V"))
			{
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
				t.env->DeleteLocalRef(t.classID);
				return;
			}
}

void UtilityHelper::sendFeedback(const std::string &email,
		const std::string &emailSubject,
		const std::string &mailbody) {
	PluginJniMethodInfo t;
	    if(PluginJniHelper::getStaticMethodInfo(t,
	                                       "com/tvd/android/plugin/UtilityHelper",
	                                       "sSendFeedback",
	                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
	        jstring cemail = t.env->NewStringUTF(email.c_str());
	        jstring csubject = t.env->NewStringUTF(emailSubject.c_str());
	        jstring cbody = t.env->NewStringUTF(mailbody.c_str());
	        t.env->CallStaticVoidMethod(t.classID, t.methodID, cemail,
	        		csubject, cbody);
	        t.env->DeleteLocalRef(t.classID);
	        t.env->DeleteLocalRef(cemail);
	        t.env->DeleteLocalRef(csubject);
	        t.env->DeleteLocalRef(cbody);
	    } else {

	    }
}

std::string UtilityHelper::getSystemVersion() {
	std::string result = "";
		PluginJniMethodInfo t;
		if (PluginJniHelper::getStaticMethodInfo(t,
							"com/tvd/android/plugin/UtilityHelper",
							"sGetSystemVersion",
							"()Ljava/lang/String;"))
		{
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			result = PluginJniHelper::jstring2string(str);
			t.env->DeleteLocalRef(str);
		}

		return result;
}

std::string UtilityHelper::getAppVersion() {
	std::string result = "";
		PluginJniMethodInfo t;
		if (PluginJniHelper::getStaticMethodInfo(t,
							"com/tvd/android/plugin/UtilityHelper",
							"sGetAppVersion",
							"()Ljava/lang/String;"))
		{
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			result = PluginJniHelper::jstring2string(str);
			t.env->DeleteLocalRef(str);
		}

		return result;
}

std::string UtilityHelper::getOSName() {
	return "Android";
}

std::string UtilityHelper::getDeviceName() {
	return getDeviceModel();
}

std::string UtilityHelper::getDeviceModel() {
	std::string result = "";
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
						"com/tvd/android/plugin/UtilityHelper",
						"sGetDeviceModel",
						"()Ljava/lang/String;"))
	{
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		result = PluginJniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
	}

	return result;
}
