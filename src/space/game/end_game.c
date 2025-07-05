void player_end_game(ecs_world_t *world, const ecs_entity_t player) {
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)

    // these are player uis
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    if (menu_paused) {
        zox_delete(menu_paused) // for second player
    }
    find_child_with_tag(canvas, Taskbar, taskbar)
    if (taskbar) {
        zox_delete(taskbar)
    }

    trigger_canvas_fade_transition(world, canvas, 0.5, 1.0);

    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_end_game3D_delayed, player, 1.2f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_end_game2D_delayed, player, 1.2f);
    }
}

// character uis now destroyed when character dies

/*#ifdef zox_mod_users_ui
    find_child_with_tag(canvas, MenuStatus, menu_status)
    if (menu_status) zox_delete(menu_status)
#endif
#ifdef zox_mod_items_ui
    find_child_with_tag(canvas, MenuItems, menu_items)
    if (menu_items) zox_delete(menu_items)
#endif
#ifdef zox_mod_stats_ui
    find_child_with_tag(canvas, MenuStats, menu_stats)
    if (menu_stats) {
        zox_log("Removing Stats Menu\n")
        zox_delete(menu_stats)
    }
#endif
#ifdef zox_mod_skills_ui
    find_child_with_tag(canvas, MenuSkills, menu_skills)
    if (menu_skills) zox_delete(menu_skills)
#endif
#ifdef zox_mod_quests_ui
    find_child_with_tag(canvas, MenuQuests, menu_quests)
    if (menu_quests) zox_delete(menu_quests)
#endif
#ifdef zox_mod_actions_ui
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (menu_actions) zox_delete(menu_actions)
#endif*/