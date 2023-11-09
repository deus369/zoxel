#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
# cd $android_directory
echo "gradlew installDebug"
echo "-----"
cd build/android-build
bash gradlew installDebug --parallel
cd ../..

# echo "  > running android release build"
# adb shell am start -n org.libsdl.app/.SDLActivity
source bash/android/gradle_run.sh
end_gradle_build

# ./gradlew installDebug --debug --stacktrace
# ./gradlew installDebug --debug
# ./gradlew installDebug
# ./gradlew
# ./gradlew run
# echo ""
# echo "Building android debug build."
# echo "-----"
# ./gradlew buildDebug --parallel # --debug  --stacktrace
# echo ""
# echo "Installing app-debug.apk."
# echo "-----"
# adb install $android_directory/app/build/outputs/apk/debug/app-debug.apk
# echo ""
# echo ""
# echo Finished Installing Debug Zoxel Android
# echo ""
# ./gradlew run
# ./gradlew installDebug --debug --stacktrace
# ./gradlew installDebug --debug # --stacktrace
# ./gradlew installDebug --parallel # --debug  --stacktrace
# ./gradlew installRelease --parallel # --debug  --stacktrace
# ./gradlew buildRelease --parallel # --debug  --stacktrace
# ./gradlew buildRelease --parallel # --debug  --stacktrace
