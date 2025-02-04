#ifndef zox_mod_physics
#define zox_mod_physics

#define zox_pip_physics EcsOnUpdate
zox_declare_tag(Frictioned)
zox_component_byte(DisableMovement)
zox_component_byte(CollisionDisabled)
#include "physics2D/physics2D.c"
#include "physics3D/physics3D.c"

zox_begin_module(Physics)
zox_define_tag(Frictioned)
zox_define_component(DisableMovement)
zox_define_component(CollisionDisabled)
zox_import_module(Physics2D)
zox_import_module(Physics3D)
zoxel_end_module(Physics)

#endif
