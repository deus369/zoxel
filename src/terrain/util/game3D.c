void realms_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t game) {
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    const int3 centre_chunk = (int3) { 0, 0, 0 }; // int3_zero
    const ecs_entity_t terrain = spawn_terrain_streaming(world, realm, centre_chunk, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance }, prefab_terrain, prefab_chunk_height);
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;
}
