/*
 * InappNativeHelper.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dungtavan
 */

#ifndef CLASSES_INAPPNATIVEHELPER_H_
#define CLASSES_INAPPNATIVEHELPER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnLoadPriceSuccess
    (JNIEnv * env, jobject obj, jboolean isSuccess);

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnInappFail
    (JNIEnv * env, jobject obj);

    JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GameInappHelper_nativeOnInappSuccess
    (JNIEnv * env, jobject obj, jstring packageGame, jstring productId, jstring purchaseToken);

#ifdef __cplusplus
}
#endif

#endif /* CLASSES_INAPPNATIVEHELPER_H_ */
