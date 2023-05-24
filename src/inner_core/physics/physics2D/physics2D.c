#ifndef zoxel_physics2D
#define zoxel_physics2D

zox_component(Velocity2D, float2)     //! Velocity movement of a 2D Entity.
zox_component(Acceleration2D, float2) //! Accelaration movement of a 2D Entity.
zox_component(Torque2D, float)        //! Rotational velocity of a 2D Entity.
zox_component(Bounds2D, float2)       //! Bounding box of a 2D Entity.
#include "util/physics2D_util.c"
#include "systems/friction2D_system.c"
#include "systems/acceleration2D_system.c"
#include "systems/velocity2D_system.c"
#include "systems/torque2D_system.c"
#include "systems/bounds2D_system.c"
#include "systems/gravity2D_system.c"

zox_begin_module(Physics2D)
zox_define_component(Velocity2D)
zox_define_component(Torque2D)
zox_define_component(Acceleration2D)
zox_define_component(Bounds2D)
zox_system(Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity2D, [out] Acceleration2D)
zox_system(Acceleration2DSystem, EcsOnUpdate, [out] Velocity2D, [out] Acceleration2D)
zox_system(Velocity2DSystem, EcsOnUpdate, [out] Position2D, [in] Velocity2D)
zox_system(Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D)
zox_system(Bounds2DSystem, EcsOnUpdate, [out] Position2D, [in] Bounds2D)
zoxel_end_module(Physics2D)

#endif