#!/bin/bash

android_sdk_path_windows="/c/Android/android-sdk-11" # /cmdline-tools/bin"
android_tools_directory_windows="$android_sdk_path_windows/cmdline-tools/bin"
# java_folder_name_windows="/c/Program Files/Eclipse Adoptium/jdk-8.0.432.6-hotspot"
# java_folder_name_windows="/c/Program Files/Eclipse Adoptium/jdk-11.0.25.9-hotspot"
# java_folder_name_windows="/c/Program Files/OpenJDK/jdk-22.0.2"
java_folder_name_windows="/c/Program Files/Eclipse Adoptium/jdk-17.0.12"

# Function to install a Chocolatey package if not already installed
install_with_choco() {
    local package=$1

    # Check if the package is installed
    if choco list | grep -q "^$package "; then
        echo "$package is already installed."
    else
        echo "$package is not installed. Installing..."
        choco install "$package" -y
        if [ $? -eq 0 ]; then
            echo "$package installed successfully."
        else
            echo "Failed to install $package. Check for errors."
        fi
    fi
}


is_windows() {
    if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
        return 1
    else
        return 0
    fi
}

sdkmanager() {
    if [ is_windows ]; then
        "$android_tools_directory_windows/sdkmanager.bat" "$@"
    else
        sdkmanager "$@"
    fi
}


set_java_path_windows() {
    export ANDROID_SDK="$android_sdk_path_windows"
    export ANDROID_HOME="$android_sdk_path_windows"
    export JAVA_HOME="$java_folder_name_windows"
    export PATH=$PATH:$JAVA_HOME:$android_tools_directory_windows
    # PATH=$PATH:$JAVA_HOME:$ANDROID_SDK
    # sdkmanager --help
    echo " + JAVA_HOME $JAVA_HOME"
    echo " + ANDROID_HOME $ANDROID_HOME"
    # alias sdkmanager="$ANDROID_SDK/sdkmanager.bat"
    # ls "$ANDROID_SDK/sdkmanager.bat"
    # echo "IWAEOEWI"
    # sdkmanager.bat --list
    sdkmanager --list
    return


    # Find the latest version of Java in C:\Program Files\Java and set JAVA_HOME
    JAVA_DIR=$(find "/c/Program Files/Java" -maxdepth 1 -type d -name 'jdk*' | sort -V | tail -n 1)
    # Check if JAVA_DIR is found
    if [ -n "$JAVA_DIR" ]; then
        export JAVA_HOME="$JAVA_DIR"
        export PATH="$JAVA_HOME/bin:$PATH"
        echo " + Java home set to $JAVA_HOME"
        java -version
    else
        echo " ! Java not found"
    fi
}

zmkdir() {
    local dir_path="$1"
    if [ -d $android_sdk_path ]; then
        echo " + directory existed $dir_path"
        return;
    fi
    # Create the directory
    mkdir -p "$dir_path"
    echo " + directory created: $dir_path"
    # Change permissions if not on Windows (Git Bash or Cygwin)
    if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
        echo " > Windows: No chmod needed."
    else
        sudo chmod -R 777 "$dir_path"
        echo " > Permissions set to 777 for: $dir_path"
    fi
}
