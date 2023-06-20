#ifndef zoxel_apps
#define zoxel_apps

// zoxel_settings
#define sdl_gl_major 3
#define sdl_gl_minor 0
unsigned char running = 1;
unsigned char rendering = 1;
unsigned char headless = 0;
unsigned char vsync = 1;
unsigned char fullscreen = 1; // set full screen default option here
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
SDL_Window* main_window;
SDL_GLContext* main_gl_context;
// zoxel_component_includes
zox_declare_tag(App)
zox_component(SDLWindow, SDL_Window*)
zox_component(Renderer, SDL_Renderer*)
zox_component(Context, SDL_GLContext*)
// zoxel_prefab_includes
#include "prefabs/app.c"
// zoxel_util_includes
#include "util/main_loop_util.c"
#include "util/path_util.c"
#include "util/terminal_util.c"
#include "util/sdl_util.c"
#include "util/webasm_util.c"
#include "util/cleanup_util.c"
#include "util/mouse_util.c"
#include "util/platform_util.c"

unsigned char initialize_sdl() {
    set_data_path();
    return (init_sdl() == EXIT_SUCCESS);
}

void spawn_prefabs_apps(ecs_world_t *world) {
    // spawn_prefab_app(world);
    // debug_platform();
    // print_sdl();
    // create_main_window(world);
    initialize_sdl();
    spawn_prefab_app(world);
    create_main_window(world);
}

zox_begin_module(Apps)
// zoxel_component_defines
zox_define_tag(App)
zox_define_component_w_dest(SDLWindow)
zox_define_component_w_dest(Context)
zox_define_component_w_dest(Renderer)
// zoxel_system_defines
// why cant i do this later
spawn_prefabs_apps(world);
zoxel_end_module(Apps)

#endif
