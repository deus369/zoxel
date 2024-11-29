#!/bin/bash
source bash/android/_core.sh
# Directory containing Java installations
java_dir="/usr/lib/jvm/"
if [ is_windows ]; then
    set_java_path_windows
    jdk_ver=$(java -version 2>&1 | head -n 1 | awk -F[\"_] '{print $2}' | cut -d. -f1,2)
    echo " > JDK Version [$jdk_ver]"
else
    jdk_ver=$(java --version 2>&1 | grep openjdk | awk '{split($2, a, "."); print a[1]}')

    echo " > JDK Version [$jdk_ver]"
    # JAVA_HOME=$java_dir/java-$jdk_ver-openjdk # 7 / 11 / 20
    # export JAVA_HOME=$JAVA_HOME


    # Search for a directory containing a close enough Java version
    matching_dir=$(ls -d ${java_dir}java-${jdk_ver}* 2>/dev/null | head -n 1)
    # Check if a matching directory was found
    if [ -z "$matching_dir" ]; then
        echo "Error: No matching Java version directory found in $java_dir" >&2
        exit 1
    fi

    # Set JAVA_HOME to the matching directory
    export JAVA_HOME="$matching_dir"
    echo " > JAVA_HOME is [$JAVA_HOME]"

fi
