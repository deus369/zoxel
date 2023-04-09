#ifndef zoxel_collisions3D
#define zoxel_collisions3D

#define bounce_multiplier 1.0f
#define bounce_lost_force 0.12f // .32
const float bounce_threshold = 0.001f;
zoxel_component(BasicCollider, float)
#include "systems/basic_collision3D_system.c"

// EcsPostUpdate

zoxel_begin_module(Collisions3D)
zoxel_define_component(BasicCollider)
zoxel_system(BasicCollision3DSystem, EcsPreStore, [in] voxels.ChunkLink, [in] voxels.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] voxels.VoxelPosition)
zoxel_end_module(Collisions3D)

#endif