/*
 * InappNativeHelper.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: dungtavan
 */

#include "InappNativeHelper.h"
#include "InappHelper.h"

extern "C" {

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnLoadPriceSuccess
    (JNIEnv * env, jobject obj, jboolean isSuccess) {
        InappHelper::getInstance()->setLoadPriceSuccess((bool)(isSuccess != JNI_FALSE));
    }

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnInappFail
    (JNIEnv * env, jobject obj) {
        if(InappHelper::getInstance()->getDelegate()) {
            InappHelper::getInstance()->getDelegate()
            ->onInappFail();
        }
    }

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnInappSuccess
    (JNIEnv * env, jobject obj, jstring packageGame, jstring productId, jstring purchaseToken) {
    	const char *packageStr = (env)->GetStringUTFChars(packageGame, 0);
    	const char *productIdStr = (env)->GetStringUTFChars(productId, 0);
    	const char *purchaseTokenStr = (env)->GetStringUTFChars(purchaseToken, 0);

        if(InappHelper::getInstance()->getDelegate()) {
            InappHelper::getInstance()->getDelegate()
            ->onInappSuccess(packageStr, productIdStr, purchaseTokenStr);
        }

        (env)->ReleaseStringUTFChars(packageGame, packageStr);
        (env)->ReleaseStringUTFChars(productId, productIdStr);
        (env)->ReleaseStringUTFChars(purchaseToken, purchaseTokenStr);
    }

}

