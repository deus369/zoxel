#ifndef zoxel_transforms2D
#define zoxel_transforms2D

// zoxel_component_includes
zox_component(Position2D, float2)
zox_component(Rotation2D, float)
zox_component(Scale2D, float2)
zox_component(PixelPosition, int2)
zox_component(PixelSize, int2)

// zoxel_util_includes
#include "util/transform2D_util.c"

zox_begin_module(Transforms2D)

// zoxel_component_defines
zox_define_component(Position2D)
zox_define_component(Rotation2D)
zox_define_component(Scale2D)
zox_define_component(PixelPosition)
zox_define_component(PixelSize)

zoxel_end_module(Transforms2D)

#endif