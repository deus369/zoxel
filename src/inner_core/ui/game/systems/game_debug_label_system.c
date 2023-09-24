extern int characters_count;
#define zox_debug_ui_characters
// #define zox_debug_ui_device_mode
// #define zox_debug_ui_node_memory
extern int get_characters_count(ecs_world_t *world);

void GameDebugLabelSystem(ecs_iter_t *it) {
    if (main_player == 0) return;
    #ifdef zox_debug_ui_device_mode
        const DeviceMode *deviceMode = ecs_get(it->world, main_player, DeviceMode);
    #endif
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        // int buffer_index = 0;
        char buffer[32];
        // test this \n
        // snprintf(buffer, sizeof(buffer), "debug ui\nline 2");
        // buffer_index += strlen("debug ui");
        #ifdef zox_debug_ui_node_memory
            snprintf(buffer, sizeof(buffer), "node memory [%i]", node_memory);
        #endif
        #ifdef zox_debug_ui_characters
            snprintf(buffer, sizeof(buffer), "characters [%i]", characters_count);
            // snprintf(buffer, sizeof(buffer), "characters [%i]", get_characters_count(it->world));
        #endif
        #ifdef zox_debug_ui_device_mode
            if (deviceMode->value == zox_device_mode_none) {
                snprintf(buffer + buffer_index, sizeof(buffer), "[none]");
            } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
                snprintf(buffer + buffer_index, sizeof(buffer), "[keyboard]");
            } else if (deviceMode->value == zox_device_mode_gamepad) {
                snprintf(buffer + buffer_index, sizeof(buffer), "[gamepad]");
            } else if (deviceMode->value == zox_device_mode_touchscreen) {
                // snprintf(buffer, sizeof(buffer), "[touchscreen %i]", finger_id);
                snprintf(buffer + buffer_index, sizeof(buffer), "[touchscreen]");
            }
        #endif
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(GameDebugLabelSystem)