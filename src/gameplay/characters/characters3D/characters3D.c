#ifndef zox_characters3D
#define zox_characters3D

zox_declare_tag(Character3D)
zox_component_entity(Character3DLink)
#include "settings/settings.c"
#include "prefabs/character3D.c"
#include "fun/spawn_many.c"
#include "terrain/characters3D_terrain.c"

void spawn_prefabs_characters3D(ecs_world_t *world) {
    spawn_prefab_character3D(world, prefab_vox);
}

zox_begin_module(Characters3D)
set_character_settings();
zox_define_tag(Character3D)
zox_define_component_entity(Character3DLink)
spawn_prefabs_characters3D(world);
zox_import_module(Characters3DTerrain)
zoxel_end_module(Characters3D)

#endif
