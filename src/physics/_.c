#ifndef zoxm_physics
#define zoxm_physics

#define zoxp_physics EcsPostUpdate // EcsOnUpdate
zox_tag(Frictioned);
zoxc_byte(DisableMovement);
zoxc_byte(DisableGravity);
zoxc_byte(CollisionDisabled);
#include "physics2/_.c"
#include "physics3/_.c"

zox_begin_module(Physics)
    zox_define_tag(Frictioned);
    zox_define_component_byte(DisableMovement);
    zox_define_component_byte(DisableGravity);
    zox_define_component_byte(CollisionDisabled);
    zox_import_module(Physics2);
    zox_import_module(Physics3);
zox_end_module(Physics)

#endif