#!/bin/bash

# Define the function
detect_os() {
    local os_type
    if [[ -n "$WSL_DISTRO_NAME" ]]; then
        os_type="WSL"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if grep -q "Microsoft" /proc/version; then
            # os_type="WSL"
            os_type="LINUX"
        else
            os_type="LINUX"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        os_type="MACOS"
    elif [[ "$OSTYPE" == "cygwin" ]]; then
        os_type="CYGWIN"
    elif [[ "$OSTYPE" == "msys" ]]; then
        # os_type="MINGW"
        os_type="WINDOWS"
    elif [[ "$OSTYPE" == "win32" ]]; then
        os_type="WINDOWS"
    else
        os_type="UNKNOWN"
    fi
    echo "$os_type"
}

# Example usage
# os=$(detect_os)
# echo "Detected OS: $os"
