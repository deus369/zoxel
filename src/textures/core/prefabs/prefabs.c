#include "texture.c"
#include "noise_texture.c"
#include "dirt_texture.c"
#include "tilemap.c"
ecs_entity_t prefab_texture;
ecs_entity_t prefab_texture_noise;
ecs_entity_t prefab_tilemap;

void spawn_prefabs_textures_core(ecs_world_t *world) {
    prefab_texture = spawn_prefab_texture(world, voxel_texture_size);
    prefab_texture_noise = spawn_prefab_texture_noise(world, voxel_texture_size);
    prefab_tilemap = spawn_prefab_tilemap(world);
    // realms
    zox_prefab_set(prefab_realm, TilemapLink, { 0 })
}
