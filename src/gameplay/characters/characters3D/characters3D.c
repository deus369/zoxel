#ifndef zoxel_characters3D
#define zoxel_characters3D

zoxel_declare_tag(Character3D)
zoxel_component(Character3DLink, ecs_entity_t)
#include "prefabs/character3D.c"
#include "util/character3D.c"

//! A module for 3 dimensional characters.
void Characters3DImport(ecs_world_t *world)
{
    zoxel_module(Characters3D)
    zoxel_define_tag(Character3D)
    zoxel_define_component(Character3DLink)
    spawn_prefab_character3D(world);
}
#endif