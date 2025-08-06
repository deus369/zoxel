ecs_entity_t tilemap_ui = 0;

void spawn_tilemap_ui(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_9) {
        if (tilemap_ui) {
            zox_log("- removing tilemap ui")
            zox_delete(tilemap_ui)
            tilemap_ui = 0;
        } else {
            // conjure the canvas
            const ecs_entity_t realm = local_realm;
            zox_geter(realm, GameLink, gameLink)
            zox_geter(gameLink->value, PlayerLinks, players)
            const ecs_entity_t player = players->value[0];
            zox_geter(player, CanvasLink, canvasLink)
            // our logic stuff
            zox_log("+ spawning tilemap ui")
            const int2 size = (int2) { 320, 320 };
            const ecs_entity_t tilemap = zox_get_value(realm, TilemapLink)
            const int2 position = (int2) { 8, 8 };
            tilemap_ui = spawn_element_texture(
                world,
                canvasLink->value,
                tilemap,
                position,
                size);
        }
        spawn_sound_from_file_index(world, prefab_sound, 0);
    }
}