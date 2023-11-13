extern int get_terrain_chunks_count(ecs_world_t *world);
extern int get_characters_count(ecs_world_t *world);
extern int get_count_particle3Ds(ecs_world_t *world);
extern int get_count_particle3D_emitters(ecs_world_t *world);
// #define zox_debug_ui_memorys_allocated
#define zox_debug_ui_characters
// #define zox_debug_ui_particle3Ds
// #define zox_debug_ui_terrain_chunks
// #define zox_debug_ui_statbars
// #define zox_debug_ui_node_memory
// #define zox_debug_ui_zexts
// #define zox_debug_ui_device_mode
// todo: sometimes it removes a memorys when spawning/unspawning this label

void GameDebugLabelSystem(ecs_iter_t *it) {
    if (!main_player) return;
    #ifdef zox_debug_ui_device_mode
        const DeviceMode *deviceMode = ecs_get(it->world, main_player, DeviceMode);
    #endif
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value) continue;
        ZextData *zextData = &zextDatas[i];
        int buffer_index = 0;
        char buffer[200];
        // test this \n
        // snprintf(buffer, sizeof(buffer), "debug ui\nline 2");
        // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), "[debug]");
        #ifdef zox_debug_ui_memorys_allocated
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " memorys [%i]", total_memorys_allocated);
        #endif
        #ifdef zox_debug_ui_terrain_chunks
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " terrain [%i]", get_terrain_chunks_count(it->world));
        #endif
        #ifdef zox_debug_ui_characters
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " characters [%i]", get_characters_count(it->world));
        #endif
        #ifdef zox_debug_ui_statbars
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " statbars [%i]", get_statbars_count(it->world));
        #endif
        #ifdef zox_debug_ui_particle3Ds
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " particle3Ds [%i %i]", get_count_particle3D_emitters(it->world), get_count_particle3Ds(it->world));

        #endif
        #ifdef zox_debug_ui_zexts
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " zexts [%i]", get_zexts_count(it->world));
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " zigels [%i]", get_zigels_count(it->world));
        #endif
        #ifdef zox_debug_ui_node_memory
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " node memory [%i]", node_memory);
        #endif
        #ifdef zox_debug_ui_device_mode
            if (deviceMode->value == zox_device_mode_none) {
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [none]");
            } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [keyboard]");
            } else if (deviceMode->value == zox_device_mode_gamepad) {
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [gamepad]");
            } else if (deviceMode->value == zox_device_mode_touchscreen) {
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " d [touchscreen]");
                // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " touch_devices [%i]", touch_devices_count);
                // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " fingers [%i]", touch_fingers_count);
            }
        #endif
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
            // zoxel_log(" > %s\n", buffer);
        }
    }
} zox_declare_system(GameDebugLabelSystem)
