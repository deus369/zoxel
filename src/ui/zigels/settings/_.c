const float point_font_margins = 0.01f;
const int font_texture_mul = 4;
const color default_font_outline_color = (color) { 55, 125, 125, 255 };
const color default_font_fill_color = (color) { 55, 185, 125, 255 };
color debug_color = { 255, 55, 55, 200 };
color nothing_font_color = { 0, 0, 0, 0 };
const byte is_splotches = 1;
float2 font_point_padding = (float2) { 0.1f, 0.1f };

#include "io.c"