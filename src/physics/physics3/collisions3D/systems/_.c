#include "voxel_collision_system.c"
#include "sphere_collide_system.c"
#include "sphere_collider_draw_system.c"
#include "voxel_unstuck_system.c"

void define_systems_collisions3D(ecs_world_t *world) {
    zox_system(VoxelCollisionSystem, zox_pip_physics,
        [in] chunks3.VoxLink,
        [in] chunks3.ChunkPosition,
        [out] transforms3.Position3D,
        [out] physics3.Velocity3D,
        [out] transforms3.LastPosition3D,
        [in] generic.Bounds3D,
        [out] physics3.Grounded)
    zox_system(VoxelUnstuckSystem, EcsPostUpdate,
        [in] chunks3.VoxLink,
        [in] chunks3.ChunkLink,
        [in] chunks3.ChunkPosition,
        [in] generic.Bounds3D,
        [out] transforms3.Position3D)
    zox_filter(sphere_colliders,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [in] physics.CollisionDisabled,
        [none] SphereCollider)
    zox_system_ctx(SphereCollideSystem, zox_pip_physics, sphere_colliders,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [in] physics.CollisionDisabled,
        [none] SphereCollider)
#ifdef zox_gizmos_sphere_colliders
    zox_system_1(SphereColliderDrawSystem, zox_pip_mainthread,
        [in] rendering.RenderDisabled,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [none] SphereCollider)
#endif
}