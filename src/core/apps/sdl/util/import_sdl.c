#define zoxel_using_sdl
#define zoxel_using_sdl_images

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

#ifdef zoxel_include_vulkan
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan.h>
    #include <vulkan/vulkan_wayland.h>
    // #include <wayland-client.h>
#endif

#ifdef zoxel_on_android
    #include <SDL_image.h>
#else
    #include <SDL2/SDL_image.h>
#endif
