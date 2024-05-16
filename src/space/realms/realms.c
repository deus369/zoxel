#ifndef zox_realms
#define zox_realms

zox_declare_tag(Realm)
zox_component_entity(RealmLink)
#include "prefabs/realm.c"
#include "systems/terrain_texture_set_system.c"
#include "util/game_util.c"

void initialize_realms(ecs_world_t *world) {
    add_to_event_game_state((zox_game_event) { &realms_game_state });
}

void spawn_prefabs_realms(ecs_world_t *world) {
    spawn_prefab_realm(world);
}

zox_begin_module(Realms)
zox_define_tag(Realm)
zox_define_component_entity(RealmLink)
zox_system(TerrainTextureSetSystem, EcsPreUpdate, [none] textures.core.Tilemap, [out] GenerateTexture, [out] TilemapSize, [out] TextureLinks)
zoxel_end_module(Realms)

#endif
