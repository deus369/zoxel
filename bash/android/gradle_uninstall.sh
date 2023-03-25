#!/bin/bash

package_name="org.libsdl.app"
echo "  > uninstalling apk [$package_name]"
adb uninstall $package_name
