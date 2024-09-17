// todo: plug this in per game module
void player_start_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, main_menu)
    if (main_menu) zox_delete(main_menu)
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    trigger_canvas_fade_transition(world, canvas, 0.7f, 6.0f);
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_start_game3D_delayed, player, 1.4f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_start_game2D_delayed, player, 1.4f);
    }
}
