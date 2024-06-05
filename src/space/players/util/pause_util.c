/*
 *  This script pauses for a player and resumes
 *      + added fixes for free roam cameras
*/
const float pause_fade_alpha = 0.86f;
const float pause_fade_time = 0.48f;

void pause_player_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    unlock_achievement("achievement_paused_game");
    spawn_menu_paused(world, player, canvas, int2_zero, float2_half);
    zox_set(mouse_entity, MouseLock, { 0 })
}

void pause_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    dispose_in_game_ui(world, player); // check this, ingame ui should now be linked to player, got from canvas
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // test_achievement2
    const unsigned char can_roam = zox_get_value(camera, CanRoam)
    if (can_roam == 2) {
        zox_set(camera, CanRoam, { 1 })
    }
    trigger_canvas_half_fade(world, canvas, pause_fade_time, pause_fade_alpha, 1);
    const ecs_entity_t pause_event = delay_event(world, &pause_player_delayed, player, pause_fade_time);
    ecs_entity_t previous_event = zox_get_value(player, PlayerPauseEvent)
    if (zox_valid(previous_event)) {
        zox_delete(previous_event)
        // zox_log("deleted old event\n")
    }
    zox_set(player, PlayerPauseEvent, { pause_event })
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!zox_alive(character)) return;
    if (can_roam == 0) { // if attached to character
        zox_set(character, DisableMovement, { 1 })
    }
}
