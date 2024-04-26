void EditorInputSystem(ecs_iter_t *it) {
    zox_iter_world()
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has( device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                // gizmos
                if (keyboard->z.pressed_this_frame) toggle_collision_debug(world);      // z : collision gizmos
                // toggle uis
                else if (keyboard->v.pressed_this_frame) toggle_ui(world, &game_debug_label, &spawn_game_debug_label);      // v : game debug ui
                else if (keyboard->b.pressed_this_frame) toggle_ui(world, &quads_label, &spawn_quad_count_label);           // b : quad_ui
                else if (keyboard->c.pressed_this_frame) toggle_ui(world, &frame_debugger_window, &spawn_frame_debugger);
                /*else if (keyboard->n.pressed_this_frame) {
                    zox_log(" + quads_label 2 QuadsCount? %s\n", zox_has(quads_label, QuadsCount) ? "yes" : "no")
                }*/
                //    spawn_frame_debugger(world);     // c : console
#ifdef zox_test_hierarchy
                else if (keyboard->f.pressed_this_frame) {
                    toggle_ui(world, &inspector, &spawn_inspector);
                    toggle_ui(world, &hierarchy, &spawn_editor_hierarchy);
                }
                else if (keyboard->h.pressed_this_frame) toggle_ui(world, &hierarchy, &spawn_editor_hierarchy);
                else if (keyboard->g.pressed_this_frame) toggle_ui(world, &inspector, &spawn_inspector);
#endif
            }
        }
    }
} zox_declare_system(EditorInputSystem)
