#include "velocity3D_system.c"
#include "acceleration3D_system.c"
#include "omega3D_system.c"
#include "alpha3D_system.c"
#include "friction3D_system.c"
#include "dissipation3D_system.c"
#include "gravity3D_system.c"
#include "jump3D_system.c"
#include "physics3D_disable_system.c"
#include "random_jump3D_system.c"
#include "position3D_bounds_system.c" //  move to transforms

void zox_define_systems_physics3D(ecs_world_t *world) {
    zox_system(Velocity3DSystem, zox_pip_physics, [out] Position3D, [in] Velocity3D)
    zox_system(Omega3DSystem, zox_pip_physics, [in] Omega3D, [out] Rotation3D)
    zox_system(Physics3DDisableSystem, zox_pip_physics, [out] InitializePhysics3D, [out] Position3D, [out] Velocity3D)
    zox_system(Gravity3DSystem, zox_pip_physics, [in] Gravity3D, [in] Grounded, [out] Acceleration3D)
    zox_system(RandomJump3DSystem, zox_pip_physics, [in] Grounded, [out] Jump, [none] Jumper)
    zox_system(Jump3DSystem, zox_pip_physics, [in] DisableMovement, [out] Jump, [out] Acceleration3D)
    zox_system(Friction3DSystem, zox_pip_physics, [in] Grounded, [in] Velocity3D, [out] Acceleration3D, [none] physics.Frictioned)
    zox_system(Dissipation3DSystem, zox_pip_physics, [none] physics.Frictioned, [in] Omega3D, [out] Alpha3D)
    zox_system(Acceleration3DSystem, zox_pip_physics, [out] Acceleration3D, [out] Velocity3D)
    zox_system(Alpha3DSystem, zox_pip_physics, [out] Alpha3D, [out] Omega3D)
    zox_system(Position3DBoundsSystem, zox_pip_physics, [in] Position3DBounds, [in] Bounds3D, [out] Position3D) // EcsPostUpdate - move to collisions maybe?
}