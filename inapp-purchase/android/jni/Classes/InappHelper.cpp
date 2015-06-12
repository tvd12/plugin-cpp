//
//  InappHelper.cpp
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 12/15/14.
//
//

#include <string>

#include "InappHelper.h"
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace std;
using namespace cocos2d;

InappHelper::InappHelper() :
mIsLoadPriceSuccess(false),
mDelegate(NULL) {
    
}

InappHelper* InappHelper::getInstance() {
    static InappHelper sInstance;
    
    return &sInstance;
}

void InappHelper::setLoadPriceSuccess(bool isSuccess) {
    mIsLoadPriceSuccess = isSuccess;
    if(getDelegate()) {
        getDelegate()->onLoadPriceSuccess(isSuccess);
    }
}

bool InappHelper::isLoadPriceSuccess() {
    return mIsLoadPriceSuccess;
}

void InappHelper::buyPackage(int package) {
    // android native
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GameInappHelper",
                                       "sBuyPackage",
                                       "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, (jint)package);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

string InappHelper::getPricesString(const char* _indexes) {
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t,
    			"com/tvd/android/plugin/GameInappHelper",
                                       "sGetPricesString",
                                       "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring indexes = t.env->NewStringUTF(_indexes);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, indexes);
        t.env->DeleteLocalRef(t.classID);
        
        string ret = PluginJniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
        t.env->DeleteLocalRef(indexes);
        
        return ret;
    } else {
        return "";
    }
    
}

string InappHelper::getPricesString(unsigned int _indexes[], int n) {
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t,
    			"com/tvd/android/plugin/GameInappHelper",
                                       "sGetPricesString", "([I)Ljava/lang/String;")) {
        jintArray indexes = t.env->NewIntArray(n);
        jint *narr = t.env->GetIntArrayElements(indexes, NULL);
        const jsize length = t.env->GetArrayLength(indexes);
        for(int i = 0 ; i < length ; i++) {
            narr[i] = _indexes[i];
        }
        t.env->ReleaseIntArrayElements(indexes, narr, 0);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, indexes);
        t.env->DeleteLocalRef(t.classID);
        
        string ret = PluginJniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
        t.env->DeleteLocalRef(indexes);
        
        return ret;
    } else {
        return "";
    }
    
}

string InappHelper::getPriceString(unsigned int index) {
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t,
    			"com/tvd/android/plugin/GameInappHelper",
                                       "sGetPricesString",
                                       "(I)Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, (jint)index);
        t.env->DeleteLocalRef(t.classID);
        
        string ret = PluginJniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
        
        return ret;
    } else {
        return "";
    }
    
}
