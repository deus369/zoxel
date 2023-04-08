#ifndef zoxel_apps
#define zoxel_apps

#define sdl_gl_major 3
#define sdl_gl_minor 0
unsigned char running = 1;
unsigned char rendering = 1;
unsigned char headless = 0;
const int window_index = 0; // 1;
unsigned char vsync = 1;
unsigned char fullscreen = 1; // set full screen default option here
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
SDL_Window* main_window;
SDL_GLContext* main_gl_context;
zoxel_declare_tag(App)
zoxel_component(SDLWindow, SDL_Window*)
zoxel_component(Renderer, SDL_Renderer*)
zoxel_component(Context, SDL_GLContext*)
#include "prefabs/app.c"
#include "util/main_loop_util.c"
#include "util/path_util.c"
#include "util/terminal_util.c"
#include "util/sdl_util.c"
#include "util/webasm_util.c"
#include "util/cleanup_util.c"
#include "util/mouse_util.c"

zoxel_begin_module(Apps)
zoxel_define_tag(App)
zoxel_define_component(SDLWindow)
zoxel_define_component(Context)
zoxel_define_component(Renderer)
ecs_set_hooks(world, SDLWindow, { .dtor = ecs_dtor(SDLWindow) });
ecs_set_hooks(world, Context, { .dtor = ecs_dtor(Context) });
ecs_set_hooks(world, Renderer, { .dtor = ecs_dtor(Renderer) });
spawn_app_prefab(world);
set_data_path();
if (init_sdl() == EXIT_SUCCESS) {
    create_main_window();
    print_sdl();
}
zoxel_end_module(Apps)
#endif
