static inline float get_distance_to_voxel_grid(float v, float direction, float scale) {
    float face = v;
    if (direction == 1) {
        face = floorf(v / scale) * scale;
    } else if (direction == 2) {
        face = ceilf(v / scale) * scale;
    }
    return absf(face - v);
}

#include "collision_response_system.c"
#include "collision_detect_old.c" // use old again
#include "sphere_collide_system.c"
#include "sphere_collider_draw_system.c"
#include "unstuck_system.c"
#include "friction3D_system.c"
#include "collision_debug.c"

void define_systems_collisions3(ecs *world) {
    // todo: reset collision on detection - so we can use it anywhere in our cycle
    //      maybe we keep last_collision state? and we response based on it?? idk
    //      idk how the systems might overlap so its hard
    zox_filter(sphere_colliders,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [in] physics.CollisionDisabled,
        [none] SphereCollider);
    zox_system(CollisionDetectSystem, zoxp_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [in] transforms3.Position3D,
        [in] physics3.LastPosition3D,
        [out] collisions3.Collision,
        [out] collisions3.CollisionDistance);
    zox_system_1(CollisionDebugSystem, zoxp_physics,
        [in] chunks3.VoxLink,
        [in] collisions3.CollisionDistance,
        [in] transforms3.Position3D,
        [in] physics3.LastPosition3D,
        [in] collisions3.Collision,
        [in] generic.Bounds3D,
    );
    zox_system(CollisionResponseSystem, zoxp_physics,
        [in] chunks3.VoxLink,
        [in] collisions3.CollisionDistance,
        [out] transforms3.Position3D,
        [out] physics3.Velocity3D,
        [out] physics3.LastPosition3D,
        [out] collisions3.Collision,
        [out] collisions3.Grounded);
    zox_system(UnstuckSystem, zoxp_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [out] physics3.LastUnstuck3,
        [out] transforms3.Position3D);
    zox_system(Friction3DSystem, zoxp_physics,
        [in] collisions3.Grounded,
        [out] physics3.Velocity3D,
        [none] physics.Frictioned);
    // TODO: split up between response and detect
    zox_system_ctx_1(SphereCollideSystem, zoxp_physics, sphere_colliders,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [in] physics.CollisionDisabled,
        [none] SphereCollider);
#ifdef zox_gizmos_sphere_colliders
    zox_system_1(SphereColliderDrawSystem, zoxp_mainthread,
        [in] rendering.RenderDisabled,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [none] SphereCollider)
#endif
}