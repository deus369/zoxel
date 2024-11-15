#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
echo "gradlew installDebug"
cd build/android-build
bash gradlew installDebug --parallel
cd ../..
# adb shell am start -n org.libsdl.app/.SDLActivity
source bash/android/gradle_run.sh
end_gradle_build
