// todo: add raycast position here, and character position
// #define zox_log_mouse

int debug_newline_zext(char buffer[], int buffer_size, int buffer_index) {
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "Day 1.\nToday is a very sunny day.\nHi jerry.");
    return buffer_index;
}

#define get_label_generic_function(Name, name)\
int get_label_##name(ecs_world_t *world, char buffer[], int buffer_size, int buffer_index, const ecs_entity_t e) {\
    if (!e || !zox_has(e, Name)) return buffer_index;\
    const Name *children = zox_get(e, Name)\
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[%s]'s children [%i]\n", zox_get_name(e), children->length);\
    for (int i = 0; i < children->length; i++) {\
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  [%i] %s\n", i, zox_get_name(children->value[i]));\
    }\
    return buffer_index;\
}

get_label_generic_function(PlayerLinks, player_links)

int debug_label_device(ecs_world_t *world, const ecs_entity_t device, char buffer[], int buffer_size, int buffer_index) {
        if (!device || !zox_has(device, Children)) return buffer_index;
        zox_geter(device, Children, zevices)
        for (int j = 0; j < zevices->length; j++) {
                const ecs_entity_t zevice = zevices->value[j];
                if (!zox_has(zevice, ZevicePointer)) continue;
                buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " - z [%i]", j);
                if (zox_has(zevice, ZevicePointer)) {
                        const unsigned char click_value = zox_get_value(zevice, ZevicePointer)
                        unsigned char click_type = 0;
                        if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                        else if (devices_get_released_this_frame(click_value)) click_type = 2;
                        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " clk [%i]", click_type);
                }
                if (zox_has(zevice, ZevicePointerPosition)) {
                        const int2 position = zox_get_value(zevice, ZevicePointerPosition)
                        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " pos [%ix%i]", position.x, position.y);
                }
                buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "\n");
        }
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
        const ecs_entity_t character = zox_get_value(player, CharacterLink)
#ifdef zox_debug_ui_device_mode
        const DeviceMode *deviceMode = zox_get(player, DeviceMode)
#endif
#ifdef zox_debug_ui_raycaster_target
        const ecs_entity_t raycaster_target = zox_get_value(player, RaycasterTarget)
#endif
        int buffer_index = 0;
        char buffer[buffer_size];
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%s [v0.0.1]\n", game_name);

        // memset(buffer, 0, buffer_size); // Initialize buffer to zero
#ifdef zox_debug_game_players
        const ecs_entity_t game = zox_get_value(player, GameLink)
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "player [%s]\n", zox_get_name(player));
        buffer_index = get_label_player_links(world, buffer, buffer_size, buffer_index, game);
#endif

#ifdef zox_debug_can_jump
        buffer_index = debug_can_jump(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_grounded
        buffer_index = get_label_player_grounded(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_camera_position
        buffer_index = get_label_camera_position(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_camera_euler
        buffer_index = get_label_camera_euler(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_camera_planes
        buffer_index = get_label_camera_planes(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_camera_frustum
        buffer_index = get_label_camera_frustum(world, player, buffer, buffer_size, buffer_index);
#endif
        // Player / Character
#ifdef zox_debug_ui_player_level
        buffer_index = get_label_local_character_level(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_ui_player_health
        buffer_index = get_label_local_character_health(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_element_links
        buffer_index = get_label_element_links(world, player, buffer, buffer_size, buffer_index);
        buffer_index = get_label_element_links(world, character, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_canvas
        buffer_index = get_label_children(world, canvas, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_chunk_position
        buffer_index = get_label_player_chunk_position(world, player, buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_player_character3D
        buffer_index = get_label_player_character3D(world, player, buffer, buffer_size, buffer_index);
#endif

        // Player 2D!
#ifdef zox_debug_player_character2D
        buffer_index = get_label_player_character2D(world, player, buffer, buffer_size, buffer_index);
#endif

#ifdef zox_debug_ui_save_cloud
        if (test_read_byte != 255)
                buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "cloud data [%i]\n", test_read_byte);
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
        // debug our computer:
        // Ram, CPU%, GPU?, etc
#ifdef zox_debug_system
        buffer_index = debug_system(buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_joystick
        buffer_index = debug_joystick(buffer, buffer_size, buffer_index);
#endif
#ifdef zox_debug_ui_device_mode
        /*if (deviceMode->value == zox_device_mode_none) {
            buffer_index += snprintf(buffer + buffer_index,buffer_size - buffer_index, "[ ]");
        } else */
        if (deviceMode->value == zox_device_mode_keyboardmouse) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[keyboardmouse]\n");
            buffer_index = debug_label_device(world, mouse_entity, buffer, buffer_size, buffer_index);
        } else if (deviceMode->value == zox_device_mode_gamepad) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[gamepad]\n");
        } else if (deviceMode->value == zox_device_mode_touchscreen) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[touchscreen]\n");
            buffer_index = debug_label_device(world, touchscreen_entity, buffer, buffer_size, buffer_index);
        }
#endif
        // test this \n
        // snprintf(buffer, sizeof(buffer), "debug ui\nline 2");
        // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), "[debug]");
#ifdef zox_debug_zox_statistics
        if (zox_statistics_chunks_total) buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "chunks visible [%i / %i]\n", zox_statistics_chunks_visible, zox_statistics_chunks_total);
#endif
#ifdef zox_debug_statistics_characters
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "characters visible [%i / %i] - r[%i]\n", zox_statistics_characters_visible, zox_statistics_characters_total, zox_statistics_characters_rendered);
#endif
#ifdef zox_debug_zox_statistics2
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "block voxes visible [%i / %i]\n", zox_statistics_block_voxes_visible, zox_statistics_block_voxes_total);
#endif
#ifdef zox_test_newline
        buffer_index = debug_newline_zext(buffer, buffer_size, buffer_index);
#endif

#ifdef zox_debug_ui_particle3Ds
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " particle3Ds [%i %i]", get_count_particle3D_emitters(it->world), get_count_particle3Ds(it->world));

#endif
#ifdef zox_debug_ui_zexts
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "zexts [%i]", get_zexts_count(it->world));
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "zigels [%i]", get_zigels_count(it->world));
#endif
#ifdef zox_debug_ui_node_memory
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "node memory [%i]", node_memory);
#endif
#ifdef zox_debug_ui_raycaster_target
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " raycaster target [%lu]", raycaster_target);
#endif
#ifdef zox_log_mouse
        zox_geter(mouse_entity, Children, zevices)
        const int2 mouse_position = zox_get_value(zevices->value[0], ZevicePointerPosition)
        const int2 mouse_delta = zox_get_value(zevices->value[0], ZevicePointerDelta)
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " mouse_position [%ix%i]", mouse_position.x, mouse_position.y);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " mouse_delta [%ix%i]", mouse_delta.x, mouse_delta.y);
#endif
        if (buffer_index == 0) buffer[0] = '\0';
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(GameDebugLabelSystem)
