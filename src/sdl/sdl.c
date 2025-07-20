#ifndef zox_mod_sdl
#define zox_mod_sdl

// SDL2
#ifdef zox_lib_sdl_direct
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

// SDL_Image
#ifdef zox_lib_sdl_images
    #if defined(zox_lib_sdl_direct)
        #include <SDL_image.h>
    #else
        #include <SDL2/SDL_image.h>
    #endif
#endif

#ifdef zox_include_vulkan
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan.h>
    #include <vulkan/vulkan_wayland.h>
#endif

// Platforms
#ifdef zoxel_on_windows
    #include <glew.h>
#endif
#ifdef zoxel_on_web
    #include <emscripten.h>
#endif

#include "components/_.c"
#include "data/_.c"
#include "wrapper/_.c"
#include "settings/_.c"
#include "prefabs/app.c"
#include "inputs/_.c"
#include "util/_.c"

zox_begin_module(Sdl)
    zox_module_dispose(dispose_apps_sdl)
    define_components_sdl(world);
    // hooks
    add_to_update_loop(update_sdl);
    add_to_post_update_loop(app_update_gpu);
    add_hook_terminal_command(process_terminal_sdl);
    // set_app_screen_resize(world, prefab_app_sdl, screen_dimensions);
    // prefabs
    prefab_app_sdl = spawn_prefab_app_sdl(world);
    // sub module
    zox_import_module(SdlInputs)
zox_end_module(Sdl)

#endif
