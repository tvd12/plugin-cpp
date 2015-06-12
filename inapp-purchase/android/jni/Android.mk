LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#$(call import-add-path,$(LOCAL_PATH)/../../../cocos2dx-plugin-util)

LOCAL_MODULE := inapp_billing_static

LOCAL_MODULE_FILENAME := libinapp_billing_static

LOCAL_SRC_FILES :=\
		Classes/InappHelper.cpp \
		Classes/InappNativeHelper.cpp \

LOCAL_CFLAGS := -std=c++11 -Wno-psabi
LOCAL_EXPORT_CFLAGS := -Wno-psabi

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include \
		$(LOCAL_PATH)/Classes \
		
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include \
		$(LOCAL_PATH)/Classes \

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,android/jni)
