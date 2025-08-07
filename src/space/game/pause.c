/*
 *  This script pauses for a player and resumes
 *      + added fixes for free roam cameras
*/

void pause_player_ending(
    ecs *world,
    const entity player
) {
    // if (zox_gett_value(player, DeviceMode) == zox_device_mode_keyboardmouse) {
        if (local_mouse) {
            zox_set(local_mouse, MouseLock, { 0 })
        }
    // }
    const entity canvas = zox_get_value(player, CanvasLink)
    if (game_ui_has_taskbar) {
        spawn_taskbar(world, prefab_taskbar, canvas, canvas, pause_ui_overlay_layer + 1);
    }
    spawn_menu_paused(world, player);
}

extern void dispose_menu_game(ecs *world, const entity player);

void pause_player(
    ecs *world,
    const entity player
) {
    dispose_menu_game(world, player); // check this, ingame ui should now be linked to player, got from canvas
    zox_geter_value(player, CanvasLink, entity, canvas);
    zox_geter_value(player, CameraLink, entity, camera);
    zox_geter_value(player, CharacterLink, entity, character);
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    zox_geter_value(camera, CanRoam, byte, can_roam);
    if (can_roam == 0) { // if attached to character
        if (zox_alive(character)) {
            zox_set(character, DisableMovement, { 1 })
        }
    } else if (can_roam == 2) {
        zox_set(camera, CanRoam, { 1 })
    }
    // zox_log("player paused [%s] [%s]\n", zox_get_name(player), zox_get_name(canvas))
    trigger_canvas_half_fade(
        world,
        canvas,
        pause_fade_time,
        pause_fade_alpha,
        1
    );
    const entity pause_event = delay_event(
        world,
        &pause_player_ending,
        player,
        pause_fade_time
    );
    zox_geter_value(player, PlayerPauseEvent, entity, previous_event);
    if (zox_valid(previous_event)) {
        zox_delete(previous_event)
        // zox_log("deleted old event\n")
    }
    zox_set(player, PlayerPauseEvent, { pause_event })
}