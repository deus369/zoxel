#define zox_pip_zigels EcsOnUpdate
#define directory_fonts "fonts"
const char *default_font_ttf = "miracode.ttf"; // % is broken idk
const int fonts_used = 78;
const int font_styles_length = 256;
const float point_font_margins = 0.01f;
const int font_texture_mul = 4;
// const int font_texture_size = 128;
const color default_font_outline_color = (color) { 55, 125, 125, 255 };
const color default_font_fill_color = (color) { 55, 185, 125, 255 };
// #define zox_log_font_io
#ifdef zox_debug_font_textures
const color nothing_font_color = { 125, 100, 100, 255 };
#else
const color nothing_font_color = { 0, 0, 0, 0 };
#endif
const byte is_splotches = 1;
// #define zox_debug_font_textures
// const byte splotch_size = 2;