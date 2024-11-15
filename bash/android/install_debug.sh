#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
source bash/android/copy_source.sh
source bash/android/gradle_install_debug.sh
end_gradle_build
