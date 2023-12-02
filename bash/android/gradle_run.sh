#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
echo "  > running android release build [$package_name] - [$activity_name]"
$adb shell am start -n "$package_name/.$activity_name"
end_gradle_build
