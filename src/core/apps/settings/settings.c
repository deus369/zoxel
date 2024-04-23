#define sdl_gl_major 3
#define sdl_gl_minor 0
const char *sdl_window_name = "Zoxel";
int2 screen_dimensions = { 720, 480 };
unsigned char running = 1;
unsigned char rendering = 1;
unsigned char headless = 0;
unsigned char vsync = 1;
unsigned char fullscreen = 1; // set full screen default option here
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
