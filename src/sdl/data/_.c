const byte sdl_fullscreen_byte = (byte) SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN
#include "opengl_states.c"

byte is_log_sdl = 0;

#define zox_log_sdl(msg, ...)\
    if (is_log_sdl) { zox_log(msg, ##__VA_ARGS__) }
