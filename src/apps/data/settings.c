#define sdl_gl_major 3
#define sdl_gl_minor 2
// const char *sdl_window_name = "Zoxel";
const int2 default_window_size = { 480, 480 };
int2 default_window_position = { 0, 0 };
// Set Initially
int2 screen_dimensions = { 480, 480 };
int2 viewport_dimensions;
byte running = 1;
byte rendering = 1;
byte headless = 0;
byte vsync = 1;
byte halfscreen = 0;
byte is_split_screen = 0;
byte override_opengl_es = 0;
byte screens_count = 1; // assume
byte fullscreen = 1;
byte screen_index = 0;
byte minimized = 0;
