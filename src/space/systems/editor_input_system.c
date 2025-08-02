
// todo: move to add key event
void EditorInputSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    zox_sys_in(CanvasLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceLinks, deviceLinks)
        zox_sys_i(CanvasLink, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (zox_has( device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard);
                // toggle uis
                if (keyboard->v.pressed_this_frame) {
                    toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
                } else if (keyboard->b.pressed_this_frame) {
                    toggle_ui_with_tag(spawn_frame_debugger, FrameDebuggerWindow)
                }
                // test game uis
                /*else if (keyboard->u.pressed_this_frame) {
                    toggle_ui_with_tag_e(spawn_menu_quests_player, MenuQuests, e)
                } else if (keyboard->i.pressed_this_frame) {
                    toggle_ui_with_tag_e(spawn_menu_items_player, MenuItems, e)
                } else if (keyboard->o.pressed_this_frame) {
                    toggle_ui_with_tag_e(spawn_menu_stats_player, MenuStats, e)
                } else if (keyboard->p.pressed_this_frame) {
                    toggle_ui_with_tag_e(spawn_menu_skills_player, MenuSkills, e)
                }*/
            }
        }
    }
} zox_declare_system(EditorInputSystem)

// particle test
/*else if (keyboard->v.pressed_this_frame) {
}*/