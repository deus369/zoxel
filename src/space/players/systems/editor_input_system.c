void EditorInputSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has( device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                // gizmos
                if (keyboard->z.pressed_this_frame) toggle_collision_debug(world);      // z : collision gizmos
                // test
                else if (keyboard->t.pressed_this_frame) trigger_canvas_fade_transition(world, canvas);
                // toggle uis
                else if (keyboard->x.pressed_this_frame) toggle_ui_with_tag(spawn_fps_display, FPSDisplay)
                else if (keyboard->c.pressed_this_frame) toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
                else if (keyboard->v.pressed_this_frame) toggle_ui_with_tag(spawn_quad_count_label, QuadsCountLabel)
                else if (keyboard->b.pressed_this_frame) toggle_ui_with_tag(spawn_frame_debugger, FrameDebuggerWindow)

                // test game uis
                else if (keyboard->i.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_items_player, InventoryMenu, e)
                else if (keyboard->o.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_stats_player, StatsMenu, e)
                else if (keyboard->p.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_skills_player, MenuSkills, e)


#ifdef zox_test_hierarchy
                else if (keyboard->f.pressed_this_frame) {
                    toggle_ui(world, canvas, &inspector, &spawn_inspector);
                    toggle_ui(world, canvas, &hierarchy, &spawn_editor_hierarchy);
                }
                // else if (keyboard->h.pressed_this_frame) toggle_ui(world, canvas, &hierarchy, &spawn_editor_hierarchy);
                // else if (keyboard->g.pressed_this_frame) toggle_ui(world, canvas, &inspector, &spawn_inspector);
#endif
            }
        }
    }
} zox_declare_system(EditorInputSystem)
