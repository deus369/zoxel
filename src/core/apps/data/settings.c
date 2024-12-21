#define sdl_gl_major 3
#define sdl_gl_minor 0
// const char *sdl_window_name = "Zoxel";
int2 default_window_position = { 0, 0 };
const int2 default_window_size = { 480, 480 };
// Set Initially
int2 screen_dimensions = { 480, 480 };
int2 viewport_dimensions;
unsigned char running = 1;
unsigned char rendering = 1;
unsigned char headless = 0;
unsigned char vsync = 1;
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
unsigned char screens_count = 1; // assume
unsigned char fullscreen = 1;
unsigned char screen_index = 0;
unsigned char minimized = 0;
