#ifndef zoxel_characters3D
#define zoxel_characters3D

// zoxel_component_includes
zoxel_declare_tag(Character3D)
zoxel_component(Character3DLink, ecs_entity_t)

// zoxel_prefab_includes
#include "prefabs/character3D.c"

// zoxel_fun_includes
#include "fun/settings.c"
#include "fun/spawn_many.c"

zoxel_begin_module(Characters3D)
set_character_settings(cpu_core_count);

// zoxel_component_defines
zoxel_define_tag(Character3D)
zoxel_define_component(Character3DLink)

// zoxel_prefab_defnies
spawn_prefab_character3D(world);

zoxel_end_module(Characters3D)

#endif