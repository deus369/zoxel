#ifndef zoxel_characters3D
#define zoxel_characters3D

// Tags
ECS_DECLARE(Character3D);
// components
zoxel_component(Character3DLink, ecs_entity_t);
// prefabs
#include "prefabs/character3D.c"
// util
#include "util/character3D.c"
// systems

//! A module for 3 dimensional characters.
void Characters3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters3D);
    ECS_TAG_DEFINE(world, Character3D);
    ECS_COMPONENT_DEFINE(world, Character3DLink);
    spawn_prefab_character3D(world);
}
#endif