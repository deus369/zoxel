#ifndef zoxel_transforms2D
#define zoxel_transforms2D

// zoxel_component_includes
zox_component_float2(Position2D)
zox_component_float(Rotation2D)
zox_component_float2(Scale2D)
zox_component_int2(PixelPosition)
zox_component_int2(PixelSize)

// zoxel_util_includes
#include "util/transform2D_util.c"

zox_begin_module(Transforms2D)
// zoxel_component_defines
zox_define_component_float2(Position2D)
zox_define_component_float(Rotation2D)
zox_define_component_float2(Scale2D)
zox_define_component_int2(PixelPosition)
zox_define_component_int2(PixelSize)
zoxel_end_module(Transforms2D)

#endif
