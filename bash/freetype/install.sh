#!/bin/bash
# sudo apt-get install libbrotli-dev

# Define versions and directories
FREETYPE_VERSION="2.13.2"
linux_build_dir="freetype-linux"
windows_build_dir="freetype-windows"
FREETYPE_DIR="freetype-${FREETYPE_VERSION}"
FREETYPE_URL="https://download.savannah.gnu.org/releases/freetype/${FREETYPE_DIR}.tar.gz"
lib_file_1="libfreetype.so"
lib_file_2="libfreetype.so.6"
lib_file_3="libfreetype.so.6.18.1"
lib_directory="../../../lib"

# Function to build FreeType
build_freetype() {
  local target_dir=$1
  local cmake_generator=$2
  mkdir -p ${target_dir}
  cd ${target_dir}
  cmake -G "${cmake_generator}" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ..
  cmake --build . --config Release
  cd ../
}

# Build for Linux
if [ ! -f lib/$lib_file_1 ]; then
  echo " + building freetype for linux"
  echo " ------------------------------ "
  if [ ! -d build/freetype ]; then
    mkdir build/freetype
  fi
  cd build/freetype/
  # Download and extract FreeType
  if [ ! -f ${FREETYPE_DIR}.tar.gz ]; then
    wget ${FREETYPE_URL}
  fi
  tar -xzvf ${FREETYPE_DIR}.tar.gz
  cd ${FREETYPE_DIR}
  build_freetype ${linux_build_dir} "Unix Makefiles"
  cp $linux_build_dir/$lib_file_1 $lib_directory/$lib_file_1
  cp $linux_build_dir/$lib_file_2 $lib_directory/$lib_file_2
  cp $linux_build_dir/$lib_file_3 $lib_directory/$lib_file_3
  cd ../../..
fi

#windows
if [ ! -f lib/freetype.dll ]; then
  echo " + building lib/freetype.dll for windows"
  windows_zip="build/freetype/freetype-windows-binaries.zip"
  windows_dll="https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v2.13.2.zip"
  curl -sL "$windows_dll" -o $windows_zip
  # Check if download was successful
  # Extract the specific file from the zip
  unzip -j -q $windows_zip "freetype-windows-binaries-2.13.2/release dll/win64/freetype.dll" -d "lib"
  echo "freetype.dll has been downloaded and placed into the 'lib' directory."
fi
