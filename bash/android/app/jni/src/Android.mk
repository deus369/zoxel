LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := main

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
		$(LOCAL_PATH)/include/sdl \
		$(LOCAL_PATH)/include/sdl_image \
		$(LOCAL_PATH)/include/sdl_mixer

# Add your application source files here...
LOCAL_SRC_FILES := include/flecs/flecs.c src/main.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

include $(BUILD_SHARED_LIBRARY)
