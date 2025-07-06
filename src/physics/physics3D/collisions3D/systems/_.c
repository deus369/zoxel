#include "voxel_collision_system.c"
#include "sphere_collide_system.c"
#include "sphere_collider_draw_system.c"

void define_systems_collisions3D(ecs_world_t *world) {
    zox_system(VoxelCollisionSystem, zox_pip_physics, [in] VoxLink, [in] chunks.ChunkPosition, [out] Position3D, [out] Velocity3D, [out] LastPosition3D, [in] Bounds3D, [out] Grounded)
    zox_filter(sphere_colliders, [in] Position3D, [in] SphereRadius, [in] CollisionDisabled, [none] SphereCollider)
    zox_system_ctx(SphereCollideSystem, zox_pip_physics, sphere_colliders, [in] Position3D, [in] SphereRadius, [in] CollisionDisabled, [none] SphereCollider)
    #ifdef zox_gizmos_sphere_colliders
        zox_system_1(SphereColliderDrawSystem, zox_pip_mainthread, [in] RenderDisabled, [in] Position3D, [in] SphereRadius, [none] SphereCollider)
    #endif
}