#ifndef zoxel_transforms2D
#define zoxel_transforms2D

// zoxel_component_includes
zoxel_component(Position2D, float2)
zoxel_component(Rotation2D, float)
zoxel_component(Scale2D, float2)
zoxel_component(PixelPosition, int2)
zoxel_component(PixelSize, int2)

// zoxel_util_includes
#include "util/transform2D_util.c"

zoxel_begin_module(Transforms2D)

// zoxel_component_defines
zoxel_define_component(Position2D)
zoxel_define_component(Rotation2D)
zoxel_define_component(Scale2D)
zoxel_define_component(PixelPosition)
zoxel_define_component(PixelSize)

zoxel_end_module(Transforms2D)

#endif