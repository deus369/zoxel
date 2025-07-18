#include "wander_system.c"

void define_systems_ai(ecs_world_t *world) {
    zox_system(WanderSystem, EcsOnUpdate,
        [none] Wanderer,
        [in] transforms3.Rotation3D,
        [in] physics3.Velocity3D,
        [out] physics3.Acceleration3D,
        [in] physics3.Omega3D,
        [out] physics3.Alpha3D,
        [in] physics.DisableMovement)
}