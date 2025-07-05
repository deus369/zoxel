#ifndef zox_mod_colors
#define zox_mod_colors

zox_component_color(Color)
zox_component_color(SecondaryColor)
zox_component_color_rgb(ColorRGB)
zox_component_color_rgb(SecondaryColorRGB)
zox_memory_component(Colors, color)
zox_memory_component(ColorRGBs, color_rgb)
#include "util/_.c"
#include "systems/_.c"

// hmm figure this out later
extern void set_prefab_debug_label(ecs_world_t *world, DebugLabelEvent value);

zox_begin_module(Colorz)
    zox_define_component_color(Color)
    zox_define_component_color(SecondaryColor)
    zox_define_component_color_rgb(ColorRGB)
    zox_define_component_color_rgb(SecondaryColorRGB)
    zox_define_memory_component(ColorRGBs)
    zox_define_memory_component(Colors)
    zox_define_systems_colors(world);
    if (prefab_realm) {
        zox_prefab_add(prefab_realm, Colors)
    }
zox_end_module(Colorz)

#endif