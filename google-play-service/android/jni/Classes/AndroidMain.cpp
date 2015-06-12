/* Copyright (c) 2014 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "AndroidMain.h"

// Declare class variables
JavaVM *AndroidMain::mJvm;
char *AndroidMain::mCallbackName;
jobject AndroidMain::mCallbackObj;
jmethodID AndroidMain::mCallbackMID;

void AndroidMain::onLoad(JavaVM *vm) {
  LOGI("ONLOAD");

  // Cache reference to the JVM
  mJvm = vm;

  // Android initialization
  gpg::AndroidInitialization::JNI_OnLoad(vm);
}

void AndroidMain::setAuthResultCallback(JNIEnv *env, jobject thiz, jstring callback) {
  // Store callback name
  mCallbackName = (char*) env->GetStringUTFChars(callback, 0);
  LOGI("Auth Result Callback name: %s\n", mCallbackName);

  // Store object and method
  mCallbackObj = env->NewGlobalRef(thiz);
  jclass cls = env->GetObjectClass(mCallbackObj);
  mCallbackMID = env->GetMethodID(cls, mCallbackName, "(Z)V");

  // Make sure we found the callback method
  if (mCallbackMID == 0) {
    LOGI("Could not locate callback: %s\n", mCallbackName);
    return;
  }
}

void AndroidMain::nativeOnActivityCreated(
	JNIEnv *env, jobject thiz, jobject savedInstanceState) {
	LOGI("ONCREATE");

  auto callback = [&](gpg::AuthOperation op, gpg::AuthStatus status) {
  	LOGI("OnAuthActionFinished Callback");

    // Get JNI Environment
    JNIEnv *env;
    mJvm->AttachCurrentThread(&env, NULL);

    // Callback to Java
    if (IsSuccess(status)) {
        LOGI("You are logged in!");
        env->CallVoidMethod(mCallbackObj, mCallbackMID, true);
    } else {
        LOGI("You are not logged in!");
        env->CallVoidMethod(mCallbackObj, mCallbackMID, false);
    }
  };

  // Android support activity created callback
  gpg::AndroidSupport::OnActivityCreated(env, thiz, savedInstanceState);

  // Get the platform configuration.
  gpg::AndroidPlatformConfiguration platform_configuration;
  platform_configuration.SetActivity(thiz);

  // Now, create the game service (see StateManager.cpp)
  // and pass in our callback
  StateManager::initServices(platform_configuration, NULL, callback);
}
