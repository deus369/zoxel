
// todo: move to add key event
void EditorInputSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) {
                continue;
            }
            if (zox_has( device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                // toggle uis
                if (keyboard->m.pressed_this_frame) {
                    toggle_ui_with_tag(spawn_fps_display, FPSDisplay)
                } else if (keyboard->v.pressed_this_frame) {
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