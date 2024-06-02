const int max_debug_characters = 1024;
double time_update_debug_label_system_rate = 2.0;
double time_update_debug_label_system = 0;

int debug_newline_zext(char buffer[], int buffer_size, int buffer_index) {
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "Day 1.\nToday is a very sunny day.\nHi jerry.");
    return buffer_index;
}

void GameDebugLabelSystem(ecs_iter_t *it) {
    time_update_debug_label_system += zox_delta_time;
    if (time_update_debug_label_system >= time_update_debug_label_system_rate) {
       time_update_debug_label_system = 0;
    } else {
       return;
    }
    const int buffer_size = max_debug_characters;
    zox_iter_world()
    zox_field_out(ZextDirty, zextDirtys, 1)
    zox_field_out(ZextData, zextDatas, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_o(ZextData, zextDatas, zextData)
        zox_field_e()
        const ecs_entity_t canvas = get_root_canvas(world, e);
        // zox_log("canvas; %s - %i\n", zox_get_name(canvas), zox_has(canvas, PlayerLink))
        if (!canvas || !zox_has(canvas, PlayerLink)) continue;
        const ecs_entity_t player = zox_get_value(canvas, PlayerLink)
        if (!player) continue;
#ifdef zox_debug_ui_device_mode
        const DeviceMode *deviceMode = zox_get(player, DeviceMode)
#endif
#ifdef zox_debug_ui_raycaster_target
        const ecs_entity_t raycaster_target = zox_get_value(player, RaycasterTarget)
#endif
        int buffer_index = 0;
        char buffer[buffer_size];
        // debug our computer:
        // Ram, CPU%, GPU?, etc
#ifdef zox_debug_system
        buffer_index = debug_system(buffer, buffer_size, buffer_index);
#endif
        // test this \n
        // snprintf(buffer, sizeof(buffer), "debug ui\nline 2");
        // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), "[debug]");
#ifdef zox_debug_zox_statistics
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "chunks visible [%i / %i]\n", zox_statistics_chunks_visible, zox_statistics_chunks_total);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "characters visible [%i / %i] - r[%i]\n", zox_statistics_characters_visible, zox_statistics_characters_total, zox_statistics_characters_rendered);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "block voxes visible [%i / %i]\n", zox_statistics_block_voxes_visible, zox_statistics_block_voxes_total);
#endif
#ifdef zox_test_newline
        buffer_index = debug_newline_zext(buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_can_jump
        buffer_index = debug_can_jump(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_grounded
        buffer_index = get_label_player_grounded(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_character2D
        buffer_index = get_label_player_character2D(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_character3D
        buffer_index = get_label_player_character3D(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_camera
        buffer_index = get_label_camera(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_camera_planes
        buffer_index = get_label_camera_planes(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_camera_frustum
        buffer_index = get_label_camera_frustum(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_ui_player_level
        buffer_index = get_label_local_character_level(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_ui_player_health
        buffer_index = get_label_local_character_health(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_ui_save_cloud
        if (test_read_byte != 255)
            buffer_index += snprintf(buffer + buffer_index, buffer_size, " cloud [%i] ", test_read_byte);
#endif
#ifdef zox_debug_ui_memorys_allocated
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " memorys [%i]", total_memorys_allocated);
#endif
#ifdef zox_debug_ui_terrain_chunks
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " terrain [%i]", get_terrain_chunks_count(it->world));
#endif
#ifdef zox_debug_ui_characters
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " characters [%i]", get_characters_count(it->world));
#endif
#ifdef zox_debug_ui_statbars
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " statbars [%i]", get_statbars_count(it->world));
#endif
#ifdef zox_debug_ui_particle3Ds
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " particle3Ds [%i %i]", get_count_particle3D_emitters(it->world), get_count_particle3Ds(it->world));

#endif
#ifdef zox_debug_ui_zexts
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " zexts [%i]", get_zexts_count(it->world));
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " zigels [%i]", get_zigels_count(it->world));
#endif
#ifdef zox_debug_ui_node_memory
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " node memory [%i]", node_memory);
#endif
#ifdef zox_debug_ui_raycaster_target
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " raycaster target [%lu]", raycaster_target);
#endif
#ifdef zox_debug_ui_device_mode
        if (deviceMode->value == zox_device_mode_none) {
            buffer_index += snprintf(buffer + buffer_index,buffer_size - buffer_index, "[ ]");
        } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[k]");
        } else if (deviceMode->value == zox_device_mode_gamepad) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[g]");
        } else if (deviceMode->value == zox_device_mode_touchscreen) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[t]");
        }
#endif
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(GameDebugLabelSystem)
