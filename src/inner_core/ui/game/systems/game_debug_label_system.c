// refactor this, module updates can add debug lines to it per frame
extern int get_terrain_chunks_count(ecs_world_t *world);
extern int get_characters_count(ecs_world_t *world);
extern int get_count_particle3Ds(ecs_world_t *world);
extern int get_count_particle3D_emitters(ecs_world_t *world);
extern int get_label_local_character_level(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index);
extern int get_label_local_character_health(ecs_world_t *world, const ecs_entity_t character,char buffer[], int buffer_size, int buffer_index);
extern int debug_can_jump(ecs_world_t *world, const ecs_entity_t character,char buffer[], int buffer_size, int buffer_index);
extern ecs_entity_t local_character3D;

// #define zox_debug_ui_memorys_allocated
#define zox_debug_ui_device_mode
#define zox_debug_ui_save_cloud
#define zox_debug_ui_player_level
// #define zox_debug_ui_player_health
// #define zox_debug_ui_raycaster_target
// #define zox_debug_ui_characters
// #define zox_debug_ui_particle3Ds
// #define zox_debug_ui_terrain_chunks
// #define zox_debug_ui_statbars
// #define zox_debug_ui_node_memory
// #define zox_debug_ui_zexts
// #define zox_debug_can_jump

#ifdef zox_debug_ui_save_cloud
    extern unsigned char test_read_byte;
    extern unsigned char test_read_byte2;
#endif

void GameDebugLabelSystem(ecs_iter_t *it) {
    const ecs_entity_t character = local_character3D;
    zox_iter_world()
#ifdef zox_debug_ui_device_mode
    const DeviceMode *deviceMode = zox_get(zox_players[0], DeviceMode)
#endif
#ifdef zox_debug_ui_raycaster_target
    const ecs_entity_t raycaster_target = zox_get_value(zox_players[0], RaycasterTarget)
#endif
    zox_field_out(ZextDirty, zextDirtys, 2)
    zox_field_out(ZextData, zextDatas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_i_out(ZextData, zextDatas, zextData)
        int buffer_index = 0;
        const int buffer_size = 256;
        char buffer[buffer_size];
        // test this \n
        // snprintf(buffer, sizeof(buffer), "debug ui\nline 2");
        // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), "[debug]");
#ifdef zox_debug_can_jump
        buffer_index = debug_can_jump(world, character, buffer, buffer_size, buffer_index);
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
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " memorys [%i]", total_memorys_allocated);
#endif
#ifdef zox_debug_ui_terrain_chunks
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " terrain [%i]", get_terrain_chunks_count(it->world));
#endif
#ifdef zox_debug_ui_characters
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " characters [%i]", get_characters_count(it->world));
#endif
#ifdef zox_debug_ui_statbars
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " statbars [%i]", get_statbars_count(it->world));
#endif
#ifdef zox_debug_ui_particle3Ds
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " particle3Ds [%i %i]", get_count_particle3D_emitters(it->world), get_count_particle3Ds(it->world));

#endif
#ifdef zox_debug_ui_zexts
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " zexts [%i]", get_zexts_count(it->world));
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " zigels [%i]", get_zigels_count(it->world));
#endif
#ifdef zox_debug_ui_node_memory
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " node memory [%i]", node_memory);
#endif
#ifdef zox_debug_ui_raycaster_target
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " raycaster target [%lu]", raycaster_target);
#endif
#ifdef zox_debug_ui_device_mode
        if (deviceMode->value == zox_device_mode_none) {
            buffer_index += snprintf(buffer + buffer_index,buffer_size, "[ ]");
        } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size, "[k]");
        } else if (deviceMode->value == zox_device_mode_gamepad) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size, "[g]");
        } else if (deviceMode->value == zox_device_mode_touchscreen) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size, "[t]");
        }
#endif
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
            // zoxel_log(" > %s\n", buffer);
        }
    }
} zox_declare_system(GameDebugLabelSystem)

/*if (deviceMode->value == zox_device_mode_none) {
buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [none]");
} else if (deviceMode->value == zox_device_mode_keyboardmouse) {
buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [keyboard]");
} else if (deviceMode->value == zox_device_mode_gamepad) {
buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [gamepad]");
} else if (deviceMode->value == zox_device_mode_touchscreen) {
buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [touchscreen]");
// buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " touch_devices [%i]", touch_devices_count);
// buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " fingers [%i]", touch_fingers_count);
}*/
