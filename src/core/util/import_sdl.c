#ifdef zoxel_on_web
    #include <emscripten.h>
#endif
#ifdef USE_SDL_3
    #include <SDL3/SDL.h>
#else
    #ifdef zoxel_on_android
        #include <SDL.h>
    #else
        #include <SDL2/SDL.h>
    #endif
#endif
#ifdef zoxel_on_android
    #ifdef SDL_IMAGES
        #include <SDL_image.h>
    #endif
#else
    #ifdef SDL_IMAGES
        #include <SDL2/SDL_image.h>
    #endif
#endif
#ifdef zoxel_include_vulkan
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan.h>
    #include <vulkan/vulkan_wayland.h>
    // #include <wayland-client.h>
#endif