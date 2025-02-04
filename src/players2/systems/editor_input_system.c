ecs_entity_t big_old_particle_zone = 0;
const int test_particle_zone_spawn_rate = 100;
const float3 big_old_particle_zone_bounds = (float3) { 32, 32, 32 };
// max should be around 10k

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
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has( device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                // gizmos
                if (keyboard->z.pressed_this_frame) toggle_debug_character_bounds(world);      // z : collision gizmos
                if (keyboard->x.pressed_this_frame) toggle_debug_block_voxes_bounds(world);
                if (keyboard->c.pressed_this_frame) is_render_chunk_edges = !is_render_chunk_edges;
                // particle test
                /*else if (keyboard->v.pressed_this_frame) {
                    zox_log(" + adding particles to character\n")
                    const ecs_entity_t character = zox_get_value(e, CharacterLink)
                    // spawn particle system
                    zox_get_muter(character, Children, children)
                    const float3 bounds = zox_get_value(character, Bounds3D)
                    const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, character, 4, float3_multiply_float(bounds, 2), (color) { 255, 0, 0, 255 });
                    add_to_Children(children, particle3D_emitter);
                    // not linked to skill
                    // zox_set(particle3D_emitter, SkillLink, { character })
                }*/

                else if (keyboard->k.pressed_this_frame) {
                    if (big_old_particle_zone) return;
                    zox_log(" + spawning a big old particle zone\n")
                    const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, 0, test_particle_zone_spawn_rate, float3_multiply_float(big_old_particle_zone_bounds, 2), (color) { 158, 118, 44, 200 });
                    big_old_particle_zone = particle3D_emitter;
                }

                // toggle uis
                else if (keyboard->m.pressed_this_frame) toggle_ui_with_tag(spawn_fps_display, FPSDisplay)
                else if (keyboard->v.pressed_this_frame) toggle_ui_with_tag(spawn_game_debug_label, GameDebugLabel)
                // else if (keyboard->v.pressed_this_frame) toggle_ui_with_tag(spawn_quad_count_label, QuadsCountLabel)
                else if (keyboard->b.pressed_this_frame) toggle_ui_with_tag(spawn_frame_debugger, FrameDebuggerWindow)
                // test
                // else if (keyboard->t.pressed_this_frame) trigger_canvas_fade_transition(world, canvas);

                // test game uis
                else if (keyboard->u.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_quests_player, MenuQuests, e)
                else if (keyboard->i.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_items_player, MenuItems, e)
                else if (keyboard->o.pressed_this_frame) toggle_ui_with_tag_e(spawn_menu_stats_player, MenuStats, e)
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
