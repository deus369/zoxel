#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/_.c"
zox_component_byte(CharactersSpawned)
zox_component_byte(CharactersEverSpawned)
zox_component_byte(CharacterSpawnZone)
#include "util/_.c"
#include "debug/_.c"
#include "systems/_.c"

static inline byte can_have_characters(ecs_world_t* world, ecs_entity_t chunk) {
    return zox_get_value(chunk, CharacterSpawnZone)
}

zox_begin_module(Characters3DTerrain)
    zox_define_component_byte(CharactersSpawned)
    zox_define_component_byte(CharactersEverSpawned)
    zox_define_component_byte(CharacterSpawnZone)
    define_systems_characters3_terrain(world);
    if (prefab_chunk_height) {
        zox_prefab_set(prefab_chunk_height, CharacterSpawnZone, { 1 })
        zox_prefab_set(prefab_chunk_height, CharactersSpawned, { 0 })
        zox_prefab_set(prefab_chunk_height, CharactersEverSpawned, { 0 })
    }
zox_end_module(Characters3DTerrain)

#endif