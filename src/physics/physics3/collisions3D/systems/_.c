#include "collision_response_system.c"
#include "collision_detect_system.c"
#include "sphere_collide_system.c"
#include "sphere_collider_draw_system.c"
#include "unstuck_system.c"
#include "friction3D_system.c"

void define_systems_collisions3D(ecs_world_t *world) {
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
    /*zox_system(CollisionDetectSystem, zox_pip_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [out] transforms3.Position3D,
        [out] physics3.Velocity3D,
        [out] physics3.LastPosition3D,
        [out] collisions3.Collision,
        [out] collisions3.CollisionDistance)*/
    zox_system(CollisionDetectSystem, zox_pip_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [in] transforms3.Position3D,
        [in] physics3.Velocity3D,
        [in] physics3.LastPosition3D,
        [out] collisions3.Collision,
        [out] collisions3.CollisionDistance)
    zox_system(CollisionResponseSystem, zox_pip_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [in] collisions3.CollisionDistance,
        [out] transforms3.Position3D,
        [out] physics3.Velocity3D,
        [out] physics3.LastPosition3D,
        [out] collisions3.Collision,
        [out] collisions3.Grounded)
    zox_system(UnstuckSystem, zox_pip_physics,
        [in] chunks3.VoxLink,
        [in] generic.Bounds3D,
        [out] physics3.LastUnstuck3,
        [out] transforms3.Position3D)
    zox_system(Friction3DSystem, zox_pip_physics,
        [in] collisions3.Grounded,
        [out] physics3.Velocity3D,
        [out] physics3.Acceleration3D,
        [none] physics.Frictioned)
#ifdef zox_gizmos_sphere_colliders
    zox_system_1(SphereColliderDrawSystem, zox_pip_mainthread,
        [in] rendering.RenderDisabled,
        [in] transforms3.Position3D,
        [in] SphereRadius,
        [none] SphereCollider)
#endif
}