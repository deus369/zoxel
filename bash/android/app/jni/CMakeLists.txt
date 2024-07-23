cmake_minimum_required(VERSION 3.6)
project(GAME)
# adds app->jni-> directories of code
add_subdirectory(SDL2)
add_subdirectory(SDL2_image)
add_subdirectory(SDL2_mixer)
add_subdirectory(src)

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -D_DEFAULT_SOURCE -fPIC -Wno-stringop-overread -Wno-stringop-overflow -Ofast -D NDEBUG -s -flto=auto -Dzox_lib_sdl_direct -Dzox_lib_sdl_images -Dzox_lib_sdl_mixer")
