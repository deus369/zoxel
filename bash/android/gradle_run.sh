#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
# run the apk
package_name="org.libsdl.app"
activity_name="SDLActivity"
echo "  > running android release build [$package_name] - [$activity_name]"
$ANDROID_SDK_ROOT/platform-tools/adb shell am start -n "$package_name/.$activity_name"

end_gradle_build
