extern int characters_count;

void GameDebugLabelSystem(ecs_iter_t *it) {
    if (main_player == 0) return;
    const DeviceMode *deviceMode = ecs_get(it->world, main_player, DeviceMode);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    for (int i = 0; i < it->count; i++) {
        ZextDirty *zextDirty = &zextDirtys[i];
        ZextData *zextData = &zextDatas[i];
        char buffer[32];
        // snprintf(buffer, sizeof(buffer), "Characters %i", characters_count);
        if (deviceMode->value == zox_device_mode_none) {
            snprintf(buffer, sizeof(buffer), "[none]");
        } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
            snprintf(buffer, sizeof(buffer), "[keyboard]");
        } else if (deviceMode->value == zox_device_mode_gamepad) {
            snprintf(buffer, sizeof(buffer), "[gamepad]");
        } else if (deviceMode->value == zox_device_mode_touchscreen) {
            snprintf(buffer, sizeof(buffer), "[touchscreen %i]", finger_id);
        }
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(GameDebugLabelSystem)