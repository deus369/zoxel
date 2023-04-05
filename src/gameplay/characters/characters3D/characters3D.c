#ifndef zoxel_characters3D
#define zoxel_characters3D

zoxel_declare_tag(Character3D)
zoxel_component(Character3DLink, ecs_entity_t)
#include "fun/settings.c"
#include "prefabs/character3D.c"
#include "fun/spawn_many.c"

zoxel_begin_module(Characters3D)
zoxel_define_tag(Character3D)
zoxel_define_component(Character3DLink)
spawn_prefab_character3D(world);
set_character_settings(cpu_core_count);
zoxel_end_module(Characters3D)

#endif