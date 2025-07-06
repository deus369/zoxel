// End Game
void game_end_terrain(ecs_world_t *world, const ecs_entity_t game) {
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
    if (zox_game_type == zox_game_mode_3D) {
        zox_geter(game, RealmLink, realmLink)
        zox_geter(realmLink->value, TerrainLink, terrainLink)
        if (zox_valid(terrainLink->value)) {
            zox_delete(terrainLink->value)
            zox_set(realmLink->value, TerrainLink, { 0 })
        }
        local_terrain = 0;
    }
}