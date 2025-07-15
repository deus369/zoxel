#if !defined(zox_mod_physics2) && defined(zox_mod_transforms2)
#define zox_mod_physics2

zox_component(Velocity2D, float2)     //! Velocity movement of a 2D Entity.
zox_component(Acceleration2D, float2) //! Accelaration movement of a 2D Entity.
zox_component(Torque2D, float)        //! Rotational velocity of a 2D Entity.
zox_component(Bounds2D, float2)       //! Bounding box of a 2D Entity.
#include "util/physics2D_util.c"
#include "systems/_.c"

zox_begin_module(Physics2)
    zox_define_component(Velocity2D)
    zox_define_component(Torque2D)
    zox_define_component(Acceleration2D)
    zox_define_component(Bounds2D)
    zox_system(Friction2DSystem, zox_pip_physics,
        [none] physics.Frictioned,
        [in] Velocity2D,
        [out] Acceleration2D)
    zox_system(Acceleration2DSystem, zox_pip_physics,
        [out] Velocity2D,
        [out] Acceleration2D)
    zox_system(Velocity2DSystem, zox_pip_physics,
        [out] transforms2.Position2D,
        [in] Velocity2D)
    zox_system(Torque2DSystem, zox_pip_physics,
        [out] transforms2.Rotation2D,
        [in] Torque2D)
    zox_system(Bounds2DSystem, zox_pip_physics,
        [out] transforms2.Position2D,
        [in] Bounds2D)
zox_end_module(Physics2D)

#endif