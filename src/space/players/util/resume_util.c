void resume_player_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const unsigned char can_roam = zox_get_value(camera, CanRoam)
    if (can_roam == 0 || can_roam == 2) {
        if (mouse_entity) zox_set(mouse_entity, MouseLock, { 1 })
    }
    // return to regular ui
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!zox_alive(character)) return;
    const StatLinks *statLinks = zox_get(character, StatLinks)
    find_array_component_with_tag(statLinks, HealthStat, health_stat)
    // const ecs_entity_t health_stat = ->value[0];
    spawn_in_game_ui(world, player, (ecs_entity_2) { character, health_stat });
    if (can_roam == 0) { // not roaming, return character movement
        zox_set(character, DisableMovement, { 0 })
    }
}

void resume_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    if (menu_paused) zox_delete(menu_paused)
    find_child_with_tag(canvas, Taskbar, taskbar)
    if (taskbar) zox_delete(taskbar)
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    trigger_canvas_half_fade(world, canvas, pause_fade_time, pause_fade_alpha, 0);
    const ecs_entity_t pause_event = delay_event(world, &resume_player_delayed, player, pause_fade_time);
    ecs_entity_t previous_event = zox_get_value(player, PlayerPauseEvent)
    if (zox_valid(previous_event)) {
        zox_delete(previous_event)
        // zox_log("deleted old event\n")
    }
    zox_set(player, PlayerPauseEvent, { pause_event })
}
