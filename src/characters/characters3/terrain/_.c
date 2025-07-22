#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

byte is_testing_instancing = 0;
#include "settings/_.c"
zox_component_byte(CharactersSpawned)
zox_component_byte(CharactersEverSpawned)
#include "util/_.c"
#include "debug/_.c"
#include "systems/_.c"

zox_begin_module(Characters3DTerrain)
    zox_define_component_byte(CharactersSpawned)
    zox_define_component_byte(CharactersEverSpawned)
    define_systems_characters3_terrain(world);
    if (prefab_chunk_height) {
        zox_prefab_set(prefab_chunk_height, CharactersSpawned, { 0 })
        zox_prefab_set(prefab_chunk_height, CharactersEverSpawned, { 0 })
    }
zox_end_module(Characters3DTerrain)

#endif