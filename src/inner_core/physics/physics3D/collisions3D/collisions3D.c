#ifndef zoxel_collisions3D
#define zoxel_collisions3D

#define bounce_multiplier 1.0f
#define bounce_lost_force 0.32f
const float bounce_threshold = 0.001f;
zoxel_component(BasicCollider, float)
#include "systems/basic_collision3D_system.c"

zoxel_begin_module(Collisions3D)
zoxel_define_component(BasicCollider)
zoxel_system(BasicCollision3DSystem, EcsPreStore, [in] voxels.VoxLink, [out] voxels.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] voxels.VoxelPosition, [out] voxels.ChunkLink, [in] Bounds3D)
zoxel_end_module(Collisions3D)

#endif