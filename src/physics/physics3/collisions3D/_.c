#ifndef zox_mod_collisions3D
#define zox_mod_collisions3D

// todo: add AABB (then detailed voxel) to Sphere [overlap] events for pickups
// remember: no line detection for boxes, if velocity exceeds clipping it will fall through map!
#include "data/settings.c"
#include "data/axis.c"
zox_declare_tag(SphereCollider)
zox_component_float(BasicCollider)
zox_component_float(SphereRadius)
zox_function_component(OverlapEvent, void, ecs_world_t*, ecs_entity_t, ecs_entity_t)
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Collisions3D)
    zox_define_tag(SphereCollider)
    zox_define_component_float(BasicCollider)
    zox_define_component_float(SphereRadius)
    zox_define_component(OverlapEvent)
    define_systems_collisions3D(world);
zox_end_module(Collisions3D)

#endif