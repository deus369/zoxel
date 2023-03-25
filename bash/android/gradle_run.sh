#!/bin/bash

# run the apk
package_name="org.libsdl.app"
activity_name="SDLActivity"
echo "  > running android release build [$package_name] - [$activity_name]"
adb shell am start -n "$package_name/.$activity_name"