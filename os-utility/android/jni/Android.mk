LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := os_utility_static
LOCAL_MODULE_FILENAME := libos_utility_static

LOCAL_SRC_FILES := \
		Classes/UtilityHelper.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include 

include $(BUILD_STATIC_LIBRARY)
