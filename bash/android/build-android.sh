#!/bin/bash

# make -j$(nproc) -f MakefileDev -B; ./zoxel-dev
# cc -std=c99 -fPIC -D_DEFAULT_SOURCE -Wall -g -o zoxel-dev includes/flecs.c src/main.c -lGL -lSDL2 -lm

zoxel_directory="$HOME/zoxel"
sdl_directory="$HOME/projects/SDL"
ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
export ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
ANDROID_HOME="/usr/lib/android-sdk"
ANDROID_SDK_ROOT="/usr/lib/android-sdk"
export ANDROID_HOME="/usr/lib/android-sdk"
export ANDROID_SDK_ROOT="/usr/lib/android-sdk"

cd $zoxel_directory

SRCS="$zoxel_directory/includes/flecs.c $zoxel_directory/src/main.c"
# ./androidbuild.sh org.zoxel.zoxel $zoxel_directory/includes/flecs.c $zoxel_directory/src/main.c
#SRCS="$zoxel_directory/includes/flecs.h $zoxel_directory/includes/flecs.c"
#SRCS="$SRCS $(find $zoxel_directory/src/ -type f -name *.c)"
#SRCS="$SRCS $(find $zoxel_directory/src/ -type f -name *.h)"

echo Running androidbuild.sh
cd $sdl_directory/build-scripts/
./androidbuild.sh org.zoxel.zoxel $SRCS
# sh $sdl_directory/build-scripts/androidbuild.sh org.zoxel.zoxel $SRCS

echo Running gradlew in org.zoxel.zoxel build folder
cd $sdl_directory/build/org.zoxel.zoxel/
./gradlew installDebug
# .$sdl_directory/build/org.zoxel.zoxel/gradlew org.zoxel.zoxel $SRCS

echo Finished Building Zoxel Android
sleep 330

#ln -s /usr/src/SDL2_image jni/
#ln -s /usr/src/SDL2_image/external/libwebp-0.3.0 jni/webp
#sed -i -e 's/^LOCAL_SHARED_LIBRARIES.*/& SDL2_image/' jni/src/Android.mk
#.$ANDROID_NDK_HOME/ndk-build -j$(nproc)

# ./gradlew installDebug --sdk_root=$ANDROID_SDK_ROOT

#ant debug install


# ./androidbuild.sh org.libsdl.testgles ../test/testgles.c
