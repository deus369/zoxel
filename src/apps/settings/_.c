byte running = 1;
byte headless = 0;
// app
int2 default_window_position = { 0, 0 };
const int2 default_window_size = { 480, 480 };
byte minimized = 0;
// viewport
int2 viewport_dimensions;
byte vsync = 1;
byte rendering = 1;
byte is_split_screen = 0;
byte halfscreen = 0;
byte screen_index = 0;
byte screens_count = 1; // assume
int2 screen_dimensions = { 480, 480 };
#include "opengl.c"
#include "fullscreen.c"
#include "maximized.c"

// make our setting
void initialize_settings_apps(ecs_world_t* world) {
    zoxs_new_byte("fullscreen", set_app_fullscreen, fullscreen)
    zoxs_new_byte("maximized", set_app_maximized, maximized)
}
