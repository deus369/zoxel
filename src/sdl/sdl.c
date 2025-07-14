#ifndef zox_sdl
#define zox_sdl

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
    #else
        #include <SDL2/SDL.h>
    #endif
#endif

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

#define zox_opengl_compatibility 0
#define zox_opengl_core 1
#define zox_opengl_es 2
byte opengl_mode = zox_opengl_compatibility;
byte is_log_sdl = 0;
#include "components/_.c"
#include "prefabs/app_sdl.c"
#include "data/settings.c"
#include "inputs/_.c"
#include "util/_.c"

void process_arguments_sdl(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--opengles") == 0) {
            opengl_mode = zox_opengl_es;
            zox_log("+ opengl_mode -> [opengl_es]")
        } else if (strcmp(args[i], "--openglcore") == 0) {
            opengl_mode = zox_opengl_core;
            zox_log("+ opengl_mode -> [opengl_core]")
        } else if (strcmp(args[i], "--logsdl") == 0) {
            is_log_sdl = 1;
            zox_log("setting enabled [logsdl]")
        }
    }
}

zox_begin_module(Sdl)
    zox_module_dispose(dispose_apps_sdl)
    define_components_sdl(world);
    // spawn just one prefab
    spawn_prefab_app_sdl(world);
    // attach to loops
    add_to_update_loop(update_sdl);
    add_to_post_update_loop(app_update_gpu);
    set_app_screen_resize(world, prefab_app_sdl, screen_dimensions);
    zox_import_module(SdlInputs)
    add_hook_terminal_command(process_arguments_sdl);
zox_end_module(Sdl)

#endif
