/*
 * ChartboostNativeHelper.h
 *
 *  Created on: Apr 22, 2015
 *      Author: dungtavan
 */

#ifndef ADVERTISING_INTEGRATIONS_JNI_CLASSES_CHARTBOOSTNATIVEHELPER_H_
#define ADVERTISING_INTEGRATIONS_JNI_CLASSES_CHARTBOOSTNATIVEHELPER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldRequestInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadInterstitial(JNIEnv *, jobject, jstring, jint);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayInterstitial(JNIEnv *, jobject, jstring);

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldRequestMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadMoreApps(JNIEnv *, jobject, jstring, jint);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayMoreApps(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToRecordClick(JNIEnv *, jobject, jstring, jint);

JNIEXPORT jboolean Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeShouldDisplayRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCacheRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidFailToLoadRewardedVideo(JNIEnv *, jobject, jstring,
    		jint);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDismissRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCloseRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidClickRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidCompleteRewardedVideo(JNIEnv *, jobject, jstring, jint);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeDidDisplayRewardedVideo(JNIEnv *, jobject, jstring);

JNIEXPORT void Java_com_tvd_android_plugin_ChartboostHelperDelegate_nativeWillDisplayVideo(JNIEnv *, jobject, jstring);


#ifdef __cplusplus
}
#endif

#endif /* ADVERTISING_INTEGRATIONS_JNI_CLASSES_CHARTBOOSTNATIVEHELPER_H_ */
