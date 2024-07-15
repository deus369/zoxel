#ifndef zox_mod_collisions3D
#define zox_mod_collisions3D

// todo: add AABB (then detailed voxel) to Sphere [overlap] events for pickups
// remember: no line detection for boxes, if velocity exceeds clipping it will fall through map!
#include "data/settings.c"
#include "data/axis.c"
zox_declare_tag(SphereCollider)
zox_component_float(BasicCollider)
zox_component_float(SphereRadius)
zox_function_component(OverlapEvent, void, ecs_world_t*, ecs_entity_t, ecs_entity_t)
#include "util/detect_util.c"
#include "util/response_util.c"
#include "util/prefab_util.c"
#include "systems/voxel_collision_system.c"
#include "systems/sphere_collide_system.c"
#include "systems/sphere_collider_draw_system.c"

zox_begin_module(Collisions3D)
zox_define_tag(SphereCollider)
zox_define_component_float(BasicCollider)
zox_define_component_float(SphereRadius)
zox_define_component(OverlapEvent)
zox_system(VoxelCollisionSystem, zox_pip_physics, [in] VoxLink, [in] chunks.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] LastPosition3D, [in] Bounds3D, [out] Grounded)
zox_filter(sphere_colliders, [in] Position3D, [in] SphereRadius, [in] CollisionDisabled, [none] SphereCollider)
zox_system_ctx(SphereCollideSystem, zox_pip_physics, sphere_colliders, [in] Position3D, [in] SphereRadius, [in] CollisionDisabled, [none] SphereCollider)
#ifdef zox_gizmos_sphere_colliders
    zox_system_1(SphereColliderDrawSystem, zox_pip_mainthread, [in] RenderDisabled, [in] Position3D, [in] SphereRadius, [none] SphereCollider)
#endif
zoxel_end_module(Collisions3D)

#endif
