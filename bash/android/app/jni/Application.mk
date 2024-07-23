# APP_STL := c++_shared
APP_ABI := all # armeabi-v7a arm64-v8a x86 x86_64
APP_PLATFORM=android-21 # 16
APP_ALLOW_MISSING_DEPS=true
# release
# LOCAL_CFLAGS += -std=gnu99 -D_DEFAULT_SOURCE -fPIC -Wno-stringop-overread -Wno-stringop-overflow -Ofast -D NDEBUG -s -flto=auto
# debug
# LOCAL_CFLAGS += -std=gnu99 -D_DEFAULT_SOURCE -fPIC -Wno-stringop-overread -Wno-stringop-overflow -Wall -g
# includes
# LOCAL_CFLAGS += -Dzox_lib_sdl_direct -Dzox_lib_sdl_images -Dzox_lib_sdl_mixer
