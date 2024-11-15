#!/bin/bash
source bash/android/gradle_pathing.sh
clear_gradle_build
start_gradle_build
source bash/android/sdl/copy_settings.sh
source bash/android/sdl/copy_source.sh
source bash/android/gradle_build.sh
source bash/android/gradle_sign.sh
source bash/android/gradle_install.sh
source bash/android/gradle_run.sh
end_gradle_build
