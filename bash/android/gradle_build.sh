#!/bin/bash
# note: check Android.mk to find library includes
echo "  > zoxel [bash/android/gradle_build.sh] running"
source bash/android/gradle_pathing.sh
start_gradle_build
cd build/android-build
bash gradlew assembleRelease --parallel
if [ $? -ne 0 ]; then
    echo "  > gradlew assembleRelease command failed"
    # You can add additional error handling here if needed
    clear_gradle_build
    exit 1
else
    echo "  > gradlew assembleRelease command was successful"
fi
cd ../..
end_gradle_build
