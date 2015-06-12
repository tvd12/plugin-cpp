//
//  PlayServicesHelper.cpp
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 1/7/15.
//
//

#include "AndroidMain.h"
#include "PlayServicesHelper.h"
#include "PlayServicesHeaders.h"
#include "StateManager.h"

extern "C" {

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_nativeOnActivityCreated
(JNIEnv* env, jobject thiz, jobject activity, jobject savedInstanceState) {
    
    AndroidMain::nativeOnActivityCreated(env, activity, savedInstanceState);
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_nativeOnActivityResult
(JNIEnv* env, jobject thiz, jobject activity, jint request_code, jint result_code, jobject result) {
    
    // Forward activity result to GPG
    gpg::AndroidSupport::OnActivityResult(env, activity, request_code, result_code, result);
    
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_signIn
(JNIEnv* env, jobject thiz) {
    
    StateManager::beginUserInitiatedSignIn();
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_signOut
(JNIEnv* env, jobject thiz) {
    
    StateManager::signOut();
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_showAchievements
(JNIEnv *, jobject) {
    
    StateManager::showAchievements();
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_showLeaderboards
(JNIEnv *, jobject) {
    
    StateManager::showLeaderboards();
}

JNIEXPORT void JNICALL Java_com_tvd_android_plugin_GooglePlayServicesUtil_setAuthResultCallback
(JNIEnv * env, jobject thiz, jstring callback) {
    
    AndroidMain::setAuthResultCallback(env, thiz, callback);
}
}
