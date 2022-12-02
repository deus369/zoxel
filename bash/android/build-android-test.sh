#!/bin/bash

zoxel_directory="$HOME/zoxel"
sdl_directory="$HOME/projects/SDL"
ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
export ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
ANDROID_HOME="/usr/lib/android-sdk"
ANDROID_SDK_ROOT="/usr/lib/android-sdk"
export ANDROID_HOME="/usr/lib/android-sdk"
export ANDROID_SDK_ROOT="/usr/lib/android-sdk"

cd $sdl_directory/build-scripts/

./androidbuild.sh org.libsdl.basic_window $zoxel_directory/tests/sdl/basic_window.c

cd $sdl_directory/build/org.libsdl.basic_window/
./gradlew installDebug

#ln -s /usr/src/SDL2_image jni/
#ln -s /usr/src/SDL2_image/external/libwebp-0.3.0 jni/webp
#sed -i -e 's/^LOCAL_SHARED_LIBRARIES.*/& SDL2_image/' jni/src/Android.mk
#.$ANDROID_NDK_HOME/ndk-build -j$(nproc)

# ./gradlew installDebug --sdk_root=$ANDROID_SDK_ROOT

#ant debug install


# ./androidbuild.sh org.libsdl.testgles ../test/testgles.c
