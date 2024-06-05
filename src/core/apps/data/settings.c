#define sdl_gl_major 3
#define sdl_gl_minor 0
const char *sdl_window_name = "Zoxel";
int2 default_window_position = { 0, 0 };
const int2 default_window_size = { 1280, 720 };
// Set Initially
int2 screen_dimensions = { 1920, 1080 };
int2 viewport_dimensions;
unsigned char running = 1;
unsigned char rendering = 1;
unsigned char headless = 0;
unsigned char vsync = 1;
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
// platform speecific
unsigned char screens_count = 1; // assume
#if defined(zoxel_on_android) || defined(zoxel_on_web)
    unsigned char fullscreen = 1;
#else
    unsigned char fullscreen = 1;
#endif
unsigned char screen_index = 0;
unsigned char minimized = 0;
