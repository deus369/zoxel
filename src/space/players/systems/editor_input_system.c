void EditorInputSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has( device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                // gizmos
                if (keyboard->z.pressed_this_frame) toggle_collision_debug(world);      // z : collision gizmos
                // toggle uis
                else if (keyboard->x.pressed_this_frame) toggle_ui_with_tag(spawn_fps_display, FPSDisplay)
                else if (keyboard->c.pressed_this_frame) toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
                else if (keyboard->v.pressed_this_frame) toggle_ui_with_tag(spawn_quad_count_label, QuadsCountLabel)
                else if (keyboard->b.pressed_this_frame) toggle_ui_with_tag(spawn_frame_debugger, FrameDebuggerWindow)
#ifdef zox_test_hierarchy
                else if (keyboard->f.pressed_this_frame) {
                    toggle_ui(world, canvas, &inspector, &spawn_inspector);
                    toggle_ui(world, canvas, &hierarchy, &spawn_editor_hierarchy);
                }
                else if (keyboard->h.pressed_this_frame) toggle_ui(world, canvas, &hierarchy, &spawn_editor_hierarchy);
                else if (keyboard->g.pressed_this_frame) toggle_ui(world, canvas, &inspector, &spawn_inspector);
#endif
            }
        }
    }
} zox_declare_system(EditorInputSystem)
