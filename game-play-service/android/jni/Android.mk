LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

PRIVATE_APP_STL := $(APP_STL)
PRIVATE_APP_STL := $(PRIVATE_APP_STL:_shared=)
PRIVATE_APP_STL := $(PRIVATE_APP_STL:_static=)

LOCAL_MODULE := google_play_services_static

LOCAL_MODULE_FILENAME := libgoogle_play_services_static

LOCAL_SRC_FILES := lib/$(PRIVATE_APP_STL)/$(TARGET_ARCH_ABI)/libgpg.a

LOCAL_STATIC_LIBRARIES := $(APP_STL)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_EXPORT_LDLIBS := -lz -latomic -llog

LOCAL_CFLAGS := -std=c++11

include $(PREBUILT_STATIC_LIBRARY)