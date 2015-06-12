//
//  PlayServicesHelper.h
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 1/7/15.
//
//

#ifndef __SupernaturalMemory__PlayServicesHelper__
#define __SupernaturalMemory__PlayServicesHelper__

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    signIn
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_signIn
(JNIEnv *, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    signOut
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_signOut
(JNIEnv *, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    showAchievements
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_showAchievements
(JNIEnv *, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    showLeaderboards
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_showLeaderboards
(JNIEnv *, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    nativeOnActivityCreated
 * Signature: (Landroid/app/Activity;Landroid/os/Bundle;)V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_nativeOnActivityCreated
(JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    nativeOnActivityResult
 * Signature: (Landroid/app/Activity;IILandroid/content/Intent;)V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_nativeOnActivityResult
(JNIEnv *, jobject, jobject, jint, jint, jobject);

/*
 * Class:     com_tvd_android_plugin_GooglePlayServicesUtil
 * Method:    setAuthResultCallback
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_setAuthResultCallback
(JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif

#endif /* defined(__SupernaturalMemory__PlayServicesHelper__) */
