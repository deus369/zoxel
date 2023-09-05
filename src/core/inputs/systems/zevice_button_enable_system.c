void disable_inputs_until_release(ecs_world_t *world, ecs_entity_t player) {
    const DeviceLinks *deviceLinks = ecs_get(world, player, DeviceLinks);
    for (int j = 0; j < deviceLinks->length; j++) {
        ecs_entity_t device_entity = deviceLinks->value[j];
        if (ecs_has(world, device_entity, Gamepad)) {
            const Children *zevices = ecs_get(world, device_entity, Children);
            for (int k = 0; k < zevices->length; k++) {
                ecs_entity_t zevice_entity = zevices->value[k];
                // zox_set_only(zevice_entity, ZeviceDisabled, { 1 })
                ZeviceDisabled *zeviceDisabled = ecs_get_mut(world, zevice_entity, ZeviceDisabled);
                if (!zeviceDisabled->value) {
                    unsigned char has_input = 0;
                    if (ecs_has(world, zevice_entity, DeviceButton)) {
                        const DeviceButton *deviceButton = ecs_get(world, zevice_entity, DeviceButton);
                        if (deviceButton->value != 0) has_input = 1;
                    }
                    if (ecs_has(world, zevice_entity, DeviceStick)) {
                        const DeviceStick *deviceStick = ecs_get(world, zevice_entity, DeviceStick);
                        if (float_abs(deviceStick->value.x) > joystick_cutoff_buffer || float_abs(deviceStick->value.y) > joystick_cutoff_buffer) has_input = 1;
                    }
                    if (has_input) {
                        zeviceDisabled->value = 1;
                        ecs_modified(world, zevice_entity, ZeviceDisabled);
                        // zoxel_log("  = button disabled [%lu] at %f\n", zevice_entity, zox_current_time);
                    }
                }
            }
        }
    }
}

void ZeviceButtonEnableSystem(ecs_iter_t *it) {
    const DeviceButton *deviceButtons = ecs_field(it, DeviceButton, 1);
    ZeviceDisabled *zeviceDisableds = ecs_field(it, ZeviceDisabled, 2);
    for (int i = 0; i < it->count; i++) {
        ZeviceDisabled *zeviceDisabled = &zeviceDisableds[i];
        if (!zeviceDisabled->value) continue;
        const DeviceButton *deviceButton = &deviceButtons[i];
        // if (!devices_get_is_pressed(deviceButton->value)) zoxel_log("   = button reenabled [%lu] at %f\n", it->entities[i], zox_current_time);
        if (!devices_get_is_pressed(deviceButton->value)) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZeviceButtonEnableSystem)

void ZeviceStickEnableSystem(ecs_iter_t *it) {
    const DeviceStick *deviceSticks = ecs_field(it, DeviceStick, 1);
    ZeviceDisabled *zeviceDisableds = ecs_field(it, ZeviceDisabled, 2);
    for (int i = 0; i < it->count; i++) {
        ZeviceDisabled *zeviceDisabled = &zeviceDisableds[i];
        if (!zeviceDisabled->value) continue;
        const DeviceStick *deviceStick = &deviceSticks[i];
        // if (!devices_get_is_pressed(deviceButton->value)) zoxel_log("   = button reenabled [%lu] at %f\n", it->entities[i], zox_current_time);
        if (!(float_abs(deviceStick->value.x) > joystick_cutoff_buffer || float_abs(deviceStick->value.y) > joystick_cutoff_buffer)) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZeviceStickEnableSystem)