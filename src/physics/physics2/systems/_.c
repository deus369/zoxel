#include "friction2D_system.c"
#include "acceleration2D_system.c"
#include "velocity2D_system.c"
#include "torque2D_system.c"
#include "bounds2D_system.c"
#include "gravity2D_system.c"

void define_systems_physics2(ecs_world_t* world) {
    zox_system(Friction2DSystem, zox_pip_physics,
            [in] Velocity2D,
            [out] Acceleration2D,
            [none] physics.Frictioned)
    zox_system(Acceleration2DSystem, zox_pip_physics,
            [out] Velocity2D,
            [out] Acceleration2D)
    zox_system(Velocity2DSystem, zox_pip_physics,
            [in] Velocity2D,
            [out] transforms2.Position2D)
    zox_system(Torque2DSystem, zox_pip_physics,
            [out] transforms2.Rotation2D,
            [in] Torque2D)
    zox_system(Bounds2DSystem, zox_pip_physics,
            [in] Bounds2D,
            [out] transforms2.Position2D)
}