#ifdef zoxel_on_web
    #include <emscripten.h>
#endif
#ifdef USE_SDL_3
    #include <SDL3/SDL.h>
    #include <SDL3/SDL_opengl.h>
#else
    #ifdef zoxel_on_android
        #include <SDL.h>
        #include <SDL_opengl.h>
    #else
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_opengl.h>
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
    #include <vulkan/vulkan.h>
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan_wayland.h>
    // #include <wayland-client.h>
#endif