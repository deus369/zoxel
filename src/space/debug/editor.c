void toggle_editor(ecs_world_t *world, int32_t keycode) {
    // conjure the canvas
    const ecs_entity_t realm = local_realm;
    zox_geter(realm, GameLink, gameLink)
    zox_geter(gameLink->value, PlayerLinks, players)
    const ecs_entity_t player = players->value[0];
    zox_geter(player, CanvasLink, canvasLink)
    // our logic stuff
    if (keycode == SDLK_y) {
        toggle_ui(world, canvasLink->value, &hierarchy, &spawn_editor_hierarchy);
        spawn_sound_from_file_index(world, prefab_sound, 0);
    } else if (keycode == SDLK_u) {
        toggle_ui(world, canvasLink->value, &inspector, &spawn_inspector);
        spawn_sound_from_file_index(world, prefab_sound, 0);
    }
}