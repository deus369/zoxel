#define zoxel_using_sdl

#ifdef zoxel_on_windows
    #include <glew.h>
#endif

#ifdef zoxel_on_web
    #include <emscripten.h>
#endif
#ifdef zox_lib_sdl_direct
    #include <SDL.h>
#else
    #ifdef USE_SDL_3
        #include <SDL3/SDL.h>
    #elif defined(zox_sdl_import_file_only)
        #include <SDL.h>
    #else
        #include <SDL2/SDL.h>
    #endif
#endif
#ifdef zox_lib_sdl_images
    #if defined(zox_sdl_import_file_only)
        #include <SDL_image.h>
    #else
        #include <SDL2/SDL_image.h>
    #endif
#endif

#ifdef zox_include_vulkan

#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_wayland.h>
// #include <wayland-client.h>

#endif
