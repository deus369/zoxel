#ifndef zox_mod_colors
#define zox_mod_colors

// globals for now...
byte grayscale_mode = 0;
// color_rgb fog_color = (color_rgb) { 125, 125, 125 };
color_rgb viewport_clear_color = color_rgb_black;
zox_component_color(Color)
zox_component_color(SecondaryColor)
zox_component_color_rgb(ColorRGB)
zox_component_color_rgb(SecondaryColorRGB)
zox_component_color_rgb(FogColor)
zox_memory_component(Colors, color)
zox_memory_component(ColorRGBs, color_rgb)
#include "util/_.c"
#include "data/_.c"
#include "systems/_.c"

/*#define zox_biome_grassland 0
#define zox_biome_desert 1
#define zox_biome_savanna 2
#define zox_biome_forest 3
#define zox_biome_swamp 4
#define zox_biome_mountain 5
#define zox_biome_end 6*/

// hmm figure this out later
extern void set_prefab_debug_label(ecs_world_t *world, DebugLabelEvent value);

zox_begin_module(Colorz)
    zox_define_component_color(Color)
    zox_define_component_color(SecondaryColor)
    zox_define_component_color_rgb(ColorRGB)
    zox_define_component_color_rgb(SecondaryColorRGB)
    zox_define_component_color_rgb(FogColor)
    zox_define_memory_component(ColorRGBs)
    zox_define_memory_component(Colors)
    define_systems_colors(world);
    if (prefab_realm) {
        zox_prefab_add(prefab_realm, Colors)
    }
zox_end_module(Colorz)

#endif