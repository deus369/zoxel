void spawn_terrain_on_realm(ecs_world_t *world, const ecs_entity_t realm) {
    const int3 render_size = (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance };
    const ecs_entity_t terrain = spawn_terrain_streaming(world, realm, int3_zero, render_size, prefab_terrain, prefab_chunk_height);
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;
}

void game_start_terrain3D(ecs_world_t *world, const ecs_entity_t game) {
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    zox_geter(game, RealmLink, realmLink)
    spawn_terrain_on_realm(world, realmLink->value);
}