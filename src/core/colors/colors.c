#ifndef zox_mod_colors
#define zox_mod_colors

zox_component_color(Color)
zox_component_color(SecondaryColor)
zox_component_color_rgb(ColorRGB)
zox_component_color_rgb(SecondaryColorRGB)
zox_memory_component(Colors, color)
zox_memory_component(ColorRGBs, color_rgb)
#include "util/hsv_util.c"
#include "util/color_util.c"

zox_begin_module(Colorz)
zox_define_component_color(Color)
zox_define_component_color(SecondaryColor)
zox_define_component_color_rgb(ColorRGB)
zox_define_component_color_rgb(SecondaryColorRGB)
zox_define_memory_component(ColorRGBs)
zox_define_memory_component(Colors)
zox_prefab_add(prefab_realm, Colors)
zoxel_end_module(Colorz)

#endif
