/*
 *  This script pauses for a player and resumes
 *      + added fixes for free roam cameras
*/

void pause_player_delayed(ecs_world_t *world, const ecs_entity_t player) {
    if (zox_gett_value(player, DeviceMode) == zox_device_mode_keyboardmouse) {
        if (mouse_entity) zox_set(mouse_entity, MouseLock, { 0 })
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (game_ui_has_taskbar) spawn_taskbar(world, prefab_taskbar, canvas, canvas, pause_ui_overlay_layer + 1);
    spawn_menu_paused_player(world, player);
    // spawn_menu_paused(world, player, canvas, int2_zero, float2_half, pause_ui_overlay_layer + 3);
    // zox_log("player paused [%s] [%s]\n", zox_get_name(player), zox_get_name(canvas))
    // unlock_achievement("achievement_paused_game");
}

extern void dispose_menu_game(ecs_world_t *world, const ecs_entity_t player);

void pause_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    dispose_menu_game(world, player); // check this, ingame ui should now be linked to player, got from canvas
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    const byte can_roam = zox_get_value(camera, CanRoam)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (can_roam == 0) { // if attached to character
        if (zox_alive(character)) zox_set(character, DisableMovement, { 1 })
    } else if (can_roam == 2) {
        zox_set(camera, CanRoam, { 1 })
    }
    // zox_log("player paused [%s] [%s]\n", zox_get_name(player), zox_get_name(canvas))
    trigger_canvas_half_fade(world, canvas, pause_fade_time, pause_fade_alpha, 1);
    const ecs_entity_t pause_event = delay_event(world, &pause_player_delayed, player, pause_fade_time);
    ecs_entity_t previous_event = zox_get_value(player, PlayerPauseEvent)
    if (zox_valid(previous_event)) {
        zox_delete(previous_event)
        // zox_log("deleted old event\n")
    }
    zox_set(player, PlayerPauseEvent, { pause_event })
}