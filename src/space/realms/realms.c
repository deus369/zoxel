#ifndef zoxel_realms
#define zoxel_realms

// zoxel_component_includes
zox_declare_tag(Realm)
zox_component(RealmLink, ecs_entity_t)
// zoxel_prefab_includes
#include "prefabs/realm.c"
// zoxel_system_includes
#include "systems/terrain_texture_set_system.c"

void spawn_prefabs_realms(ecs_world_t *world) {
    spawn_prefab_realm(world);
}

zox_begin_module(Realms)
// zoxel_component_defines
zox_define_tag(Realm)
zox_define_component(RealmLink)
// zoxel_system_defines
zox_system(TerrainTextureSetSystem, EcsPreUpdate, [none] textures.core.Tilemap, [in] GenerateTexture, [out] TilemapSize, [out] TextureLinks)
zoxel_end_module(Realms)

#endif