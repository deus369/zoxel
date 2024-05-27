/*
 *  This script pauses for a player and resumes
 *      + added fixes for free roam cameras
*/
const float pause_fade_alpha = 0.86f;
const float pause_fade_time = 0.48f;

void pause_player_post_fade(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    unlock_achievement("achievement_paused_game");
    spawn_menu_paused(world, player, canvas, int2_zero, float2_half);
    zox_set(mouse_entity, MouseLock, { 0 })
}

void pause_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const ecs_entity_t character3D = zox_get_value(player, CharacterLink)
    dispose_in_game_ui(world, player); // check this, ingame ui should now be linked to player, got from canvas
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // test_achievement2
    const unsigned char can_roam = zox_get_value(camera, CanRoam)
    if (can_roam == 2) {
        zox_set(camera, CanRoam, { 1 })
    } else if (can_roam == 0) { // if attached to character
        zox_set(character3D, DisableMovement, { 1 })
    }
    delay_event(world, &pause_player_post_fade, player, pause_fade_time);
    trigger_canvas_half_fade(world, canvas, pause_fade_time, pause_fade_alpha, 1);
}

void resume_player_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    // return to regular ui
    const ecs_entity_t health_stat = zox_gett(character, StatLinks)->value[0];
    spawn_in_game_ui(world, player, (ecs_entity_2) { character, health_stat });
    const unsigned char can_roam = zox_get_value(camera, CanRoam)
    if (can_roam == 0 || can_roam == 2) {
        zox_set(mouse_entity, MouseLock, { 1 })
    }
    if (can_roam == 0) { // not roaming, return character movement
        zox_set(character, DisableMovement, { 0 })
    }
}

void resume_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    zox_delete(menu_paused)
    disable_inputs_until_release(world, player, zox_device_mode_none);
    delay_event(world, &resume_player_delayed, player, pause_fade_time);
    trigger_canvas_half_fade(world, canvas, pause_fade_time, pause_fade_alpha, 0);
}
