byte running = 1;
byte headless = 0;
// app
int2 default_window_position = { 0, 0 };
const int2 default_window_size = { 480, 480 };
byte fullscreen = 1;
byte screen_index = 0;
byte minimized = 0;
byte screens_count = 1; // assume
byte is_split_screen = 0;
byte halfscreen = 0;
// viewport
int2 screen_dimensions = { 480, 480 };
int2 viewport_dimensions;
byte vsync = 1;
byte rendering = 1;
#include "opengl.c"
