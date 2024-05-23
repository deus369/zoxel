#if !defined(zox_realms2) && defined(zox_textures)
#define zox_realms2

// todo: Move module to core and add things to realm from modules!
#include "prefabs/realm.c"
#include "systems/terrain_texture_set_system.c"
#include "util/game_util.c"

void initialize_realms2(ecs_world_t *world) {
    add_to_event_game_state((zox_game_event) { &realms_game_state });
}

void spawn_prefabs_realms2(ecs_world_t *world) {
    add_to_realm(world, prefab_realm);
}

zox_begin_module(Realms2)
zox_system(TerrainTextureSetSystem, EcsPreUpdate, [in] RealmLink, [out] GenerateTexture, [out] TilemapSize, [out] TextureLinks, [none] textures.core.Tilemap)
initialize_realms2(world);
    spawn_prefabs_realms2(world);
zoxel_end_module(Realms2)

#endif
