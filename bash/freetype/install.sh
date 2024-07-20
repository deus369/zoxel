#!/bin/bash
# sudo apt-get install libbrotli-dev

echo " ====== ====== ====== ====== ====== ======"
# Define versions and directories
freetype_dir="build/freetype"
if [ ! -d $freetype_dir ]; then
    mkdir $freetype_dir
fi
FREETYPE_VERSION="2.13.2"
linux_build_dir="freetype-linux"
windows_build_dir="freetype-windows"
FREETYPE_DIR="freetype-${FREETYPE_VERSION}"
FREETYPE_URL="https://download.savannah.gnu.org/releases/freetype/${FREETYPE_DIR}.tar.gz"
lib_file_1="libfreetype.so"
lib_file_2="libfreetype.so.6"
lib_file_3="libfreetype.so.6.18.1"
lib_file_windows="libfreetype.dll"
lib_directory="../../../lib"

# make sure t to have include for freetype
if [ ! -d build/freetype/freetype-2.13.2/include ]; then
  cd $freetype_dir
  # Download and extract FreeType
  if [ ! -f ${FREETYPE_DIR}.tar.gz ]; then
    wget ${FREETYPE_URL}
  fi
  tar -xzvf ${FREETYPE_DIR}.tar.gz  > /dev/null 2>&1
  cd ../..
fi

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

echo "OS is [$OSTYPE]"
if [[ "$OSTYPE" == "msys" ]]; then
    echo "Running on Windows"
    is_windows=1
else
    echo "Likely Linux OS"
    is_windows=0
fi

# Build for Linux
if [[ is_windows -eq 0 && ! -f lib/$lib_file_1 ]]; then
  echo " + building freetype for linux"
  echo " ------------------------------ "
  cd $freetype_dir
  # Download and extract FreeType
  if [ ! -f ${FREETYPE_DIR}.tar.gz ]; then
    wget ${FREETYPE_URL}
  fi
  tar -xzvf ${FREETYPE_DIR}.tar.gz  > /dev/null 2>&1
  cd ${FREETYPE_DIR}
  build_freetype ${linux_build_dir} "Unix Makefiles"
  cp $linux_build_dir/$lib_file_1 $lib_directory/$lib_file_1
  cp $linux_build_dir/$lib_file_2 $lib_directory/$lib_file_2
  cp $linux_build_dir/$lib_file_3 $lib_directory/$lib_file_3
  cd ../../..
fi

#windows
if [[ ! -f lib/freetype.dll ]]; then
  echo " + downloading lib/freetype.dll for windows"
  windows_zip="build/freetype/freetype-windows-binaries.zip"
  echo " > zip [$windows_zip]"
  if [ ! -f $windows_zip ]; then
    # windows_dll="https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v-${FREETYPE_VERSION}.zip"
    windows_dll="https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v${FREETYPE_VERSION}.zip"
    echo " > url [$windows_dll]"
    curl -sL "$windows_dll" -o $windows_zip
  fi
  # Check if download was successful
  # Extract the specific file from the zip
  unzip -j -q $windows_zip "freetype-windows-binaries-${FREETYPE_VERSION}/release dll/win64/freetype.dll" -d "lib"
  unzip -j -q $windows_zip "freetype-windows-binaries-${FREETYPE_VERSION}/release dll/win64/freetype.lib" -d "lib"
  echo "freetype.dll and freetype.lib has been downloaded and placed into the 'lib' directory."
fi

echo " ====== ====== ====== ====== ====== ======"
