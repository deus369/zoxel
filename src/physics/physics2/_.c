#if !defined(zoxm_physics2) && defined(zoxm_transforms2)
#define zoxm_physics2

zoxc_float2(Velocity2D);     //! Velocity movement of a 2D Entity
zoxc_float2(Acceleration2D); //! Accelaration movement of a 2D Entity
zoxc_float(Torque2D);        //! Rotational velocity of a 2D Entity
zoxc_float2(Bounds2D);       //! Bounding box of a 2D Entity
#include "util/physics2D_util.c"
#include "systems/_.c"

zox_begin_module(Physics2)
    zox_define_component(Velocity2D);
    zox_define_component(Torque2D);
    zox_define_component(Acceleration2D);
    zox_define_component(Bounds2D);
    define_systems_physics2(world);
zox_end_module(Physics2D)

#endif