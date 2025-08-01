


// #### INCLUDES ####

// Platforms
#ifdef zox_windows
    #define max_args 64
    #define max_arg_len 256
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shellapi.h>
#endif

// core includes
#include <signal.h>     // used for detecting cancel
#include <stdlib.h>     // for malloc & free
#include <stdio.h>      // just for sprintf and perror
#include <stdint.h>     // for ints?
// Memory Copies and Strlen!
#include <string.h>
// for thread locks in memory management - pthread_rwlock_init
#include <pthread.h>
// math module
#include <math.h>
#include <float.h>
#include <time.h>

// # Pathing #
// for DIR, readdir, closedir etc
#include <dirent.h>
// for pathing - can we do without?
#include <sys/stat.h>   // pathing
// used in pathing, doing funky stuff??
#include <unistd.h>
// also used in pathing - ENOENT
// and networking - EWOULDBLOCK
#include <errno.h>
//! Included Libraries for App
#ifndef zox_disable_logs
    #include <stdarg.h>
#endif

#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM
#define FLECS_PIPELINE
#include <flecs.h>

// SDL2 & OpenGL
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>

#ifdef zox_windows
    #include <GL/glew.h>
#endif

#include <SDL2/SDL_opengl.h>
#ifdef zox_sdl_images
    #include <SDL2/SDL_image.h>
#endif

#ifdef zox_vulkan
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan.h>
    #include <vulkan/vulkan_wayland.h>
#endif

#ifdef zox_web
    #include <emscripten.h>
#endif

#ifdef zox_android
    #include <android/log.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <SDL2/SDL_system.h>
    #include <sys/types.h>
#endif

#ifdef zox_sdl_mixer
    #include <SDL2/SDL_mixer.h>
#endif

// networking
#ifdef zox_windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif
#include <fcntl.h>  // F_SETFL etc