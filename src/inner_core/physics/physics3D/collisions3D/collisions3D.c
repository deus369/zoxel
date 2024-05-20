#ifndef zoxel_collisions3D
#define zoxel_collisions3D

#define bounce_multiplier 1.0f
// #define bounce_lost_force 0.32f // 0.0f
#define bounce_lost_force 0.12f // 0.12f
const float bounce_threshold = 0.001f;
zox_component(BasicCollider, float)
#include "systems/basic_collision3D_system.c"

zox_begin_module(Collisions3D)
zox_define_component(BasicCollider)
zox_system(BasicCollision3DSystem, zox_pip_physics, [in] VoxLink, [out] chunks.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] blocks.VoxelPosition, [out] chunks.ChunkLink, [out] LastPosition3D, [in] Bounds3D, [out] Grounded)
zoxel_end_module(Collisions3D)

#endif
