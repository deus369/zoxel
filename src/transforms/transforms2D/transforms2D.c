#ifndef zox_transforms2D
#define zox_transforms2D

zox_component_float2(Position2D)
zox_component_float(Rotation2D)
zox_component_float2(Scale2D)
zox_component_int2(PixelPosition)
zox_component_int2(PixelSize)
#include "util/transform2D_util.c"

zox_begin_module(Transforms2D)
zox_define_component_float2(Position2D)
zox_define_component_float(Rotation2D)
zox_define_component_float2(Scale2D)
zox_define_component_int2(PixelPosition)
zox_define_component_int2(PixelSize)
zoxel_end_module(Transforms2D)

#endif
