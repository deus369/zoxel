#ifndef zoxm_transforms2
#define zoxm_transforms2

zox_component_float2(Position2D)
zox_component_float(Rotation2D)
zox_component_float2(Scale2D)
#include "util/transform2D_util.c"

zox_begin_module(Transforms2)
    zox_define_component_float2(Position2D)
    zox_define_component_float(Rotation2D)
    zox_define_component_float2(Scale2D)
zox_end_module(Transforms2)

#endif