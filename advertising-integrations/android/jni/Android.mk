LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := advertising_integrations_static
LOCAL_MODULE_FILENAME := libadvertising_integrations_static

LOCAL_SRC_FILES := \
		Classes/ChartboostHelper.cpp \
		Classes/ChartboostNativeHelper.cpp \
		Classes/AdColonyHelper.cpp \
		Classes/AdColonyNativeHelper.cpp \
		Classes/TapjoyHelper.cpp \
		Classes/GoogleAdmobHelper.cpp \
		Classes/GoogleAdmobNativeHelper.cpp \
		Classes/TapjoyNativeHelper.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include \
		$(LOCAL_PATH)/Classes 
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include \
		$(LOCAL_PATH)/Classes 

include $(BUILD_STATIC_LIBRARY)
