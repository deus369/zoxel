// Anchor/Grid Aware Positioning for our UIs and 2D Games!
#if !defined(zoxm_layouts2) && defined(zoxm_transforms2)
#define zoxm_layouts2

zoxc_int2(PixelPosition);
zoxc_int2(PixelSize);
#include "systems/_.c"

zox_begin_module(Layouts2)
    zox_define_component_int2(PixelPosition);
    zox_define_component_int2(PixelSize);
zox_end_module(Layouts2)

#endif