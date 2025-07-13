// Anchor/Grid Aware Positioning for our UIs and 2D Games!
#if !defined(zox_mod_layouts2D) && defined(zox_mod_transforms2D)
#define zox_mod_layouts2D

zox_component_int2(PixelPosition)
zox_component_int2(PixelSize)
#include "systems/_.c"

zox_begin_module(Layouts2D)
    zox_define_component_int2(PixelPosition)
    zox_define_component_int2(PixelSize)
zox_end_module(Layouts2D)

#endif