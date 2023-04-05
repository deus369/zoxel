#ifndef zoxel_collisions3D
#define zoxel_collisions3D

#define bounce_multiplier 4.0f
#define bounce_lost_force 0.42f
zoxel_component(BasicCollider, float)
#include "systems/basic_collision3D_system.c"

zoxel_begin_module(Collisions3D)
zoxel_define_component(BasicCollider)
zoxel_system(world, BasicCollision3DSystem, EcsPostUpdate, [in] voxels.ChunkLink, [in] voxels.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] voxels.VoxelPosition)
zoxel_end_module(Collisions3D)

#endif