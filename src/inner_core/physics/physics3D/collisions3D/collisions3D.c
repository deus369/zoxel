#ifndef zox_collisions3D
#define zox_collisions3D

// remember: no line detection for boxes, if velocity exceeds clipping it will fall through map!
#include "data/settings.c"
zox_component_float(BasicCollider)
#include "util/detect_util.c"
#include "util/response_util.c"
#include "systems/voxel_collision_system.c"

zox_begin_module(Collisions3D)
zox_define_component_float(BasicCollider)
zox_system(VoxelCollisionSystem, zox_pip_physics, [in] VoxLink, [in] chunks.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] LastPosition3D, [in] Bounds3D, [out] Grounded)
zoxel_end_module(Collisions3D)

#endif
