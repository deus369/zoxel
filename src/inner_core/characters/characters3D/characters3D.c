#ifndef zox_mod_characters3D
#define zox_mod_characters3D

zox_declare_tag(Character3D)
zox_component_entity(Character3DLink)
#include "settings/settings.c"
#include "prefabs/prefabs.c"
#include "util/camera_io.c"
#include "util/character_io.c"
#include "util/player_save.c"
#include "util/spawn_many.c"
#include "util/debug.c"
#include "terrain/characters3D_terrain.c"

zox_begin_module(Characters3D)
set_character_settings();
zox_define_tag(Character3D)
zox_define_component_entity(Character3DLink)
spawn_prefabs_characters3D(world);
zox_import_module(Characters3DTerrain)
zoxel_end_module(Characters3D)

#endif
