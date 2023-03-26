#ifndef zoxel_transforms2D
#define zoxel_transforms2D

zoxel_component(Position2D, float2)     //! A simple 2D position component.
zoxel_component(Rotation2D, float)      //! Rotates in 2D!
zoxel_component(Scale2D, float2)        //! Scales in 2D!
zoxel_component(PixelPosition, int2)
zoxel_component(PixelSize, int2)
#include "util/transform2D_util.c"

void Transforms2DImport(ecs_world_t *world) {
    zoxel_module(Transforms2D)
    zoxel_define_component(Position2D)
    zoxel_define_component(Rotation2D)
    zoxel_define_component(Scale2D)
    zoxel_define_component(PixelPosition)
    zoxel_define_component(PixelSize)
}
#endif