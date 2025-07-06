void toggle_life_terrain(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_k) {
        zox_log("> terrain death toggling")
        if (!zox_valid(local_realm) || !zox_has(local_realm, TerrainLink)) {
            zox_log_error("no realm (local)")
            return;
        }
        zox_geter(local_realm, TerrainLink, terrainLink)
        if (!zox_valid(terrainLink->value)) {
            zox_log("spawning new terrain")
            spawn_terrain_on_realm(world, local_realm);
        } else {
            zox_log("destroying old terrain")
            zox_delete(terrainLink->value)
        }
    }
}