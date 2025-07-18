#include "velocity3D_system.c"
#include "acceleration3D_system.c"
#include "omega3D_system.c"
#include "alpha3D_system.c"
#include "dissipation3D_system.c"
#include "gravity3D_system.c"
#include "physics3D_disable_system.c"
#include "position3D_bounds_system.c" //  move to transforms

void define_systems_physics3(ecs_world_t *world) {
    zox_system(Velocity3DSystem, zox_pip_physics,
        [out] transforms3.Position3D,
        [in] physics3.Velocity3D)
    zox_system(Omega3DSystem, zox_pip_physics,
        [in] Omega3D,
        [out] transforms3.Rotation3D)
    zox_system(Physics3DDisableSystem, zox_pip_physics,
        [out] InitializePhysics3D,
        [out] transforms3.Position3D,
        [out] physics3.Velocity3D)
    zox_system(Gravity3DSystem, zox_pip_physics,
        [in] physics3.Gravity3D,
        [in] physics.DisableGravity,
        [out] physics3.Acceleration3D)
    zox_system(Dissipation3DSystem, zox_pip_physics,
        [none] physics.Frictioned,
        [in] Omega3D,
        [out] Alpha3D)
    zox_system(Acceleration3DSystem, zox_pip_physics,
        [out] physics3.Acceleration3D,
        [out] physics3.Velocity3D)
    zox_system(Alpha3DSystem, zox_pip_physics,
        [out] Alpha3D,
        [out] Omega3D)
    zox_system(Position3DBoundsSystem, zox_pip_physics,
        [in] generic.Position3DBounds,
        [in] generic.Bounds3D,
        [out] transforms3.Position3D)
}