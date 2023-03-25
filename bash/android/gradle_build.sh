#!/bin/bash

echo "  > building android release build"
export ANDROID_SDK_ROOT=/usr/lib/android-sdk
cd build/android-build
bash gradlew assembleRelease --parallel
cd ../..