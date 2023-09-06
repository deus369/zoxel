// #define zox_debug_zevice_states

void disable_inputs_until_release(ecs_world_t *world, ecs_entity_t player) {
    const DeviceLinks *deviceLinks = ecs_get(world, player, DeviceLinks);
    for (int j = 0; j < deviceLinks->length; j++) {
        // zoxel_log("     > j [%i]\n", j);
        ecs_entity_t device_entity = deviceLinks->value[j];
        if (ecs_has(world, device_entity, Gamepad)) {
            const Children *zevices = ecs_get(world, device_entity, Children);
            for (int k = 0; k < zevices->length; k++) {
                // zoxel_log("         > k [%i]\n", k);
                ecs_entity_t zevice_entity = zevices->value[k];
                ZeviceDisabled *zeviceDisabled = ecs_get_mut(world, zevice_entity, ZeviceDisabled);
                // zoxel_log("             > zeviceDisabled [%i]\n", zeviceDisabled->value);
                if (!zeviceDisabled->value) {
                    unsigned char has_input = 0;
                    if (ecs_has(world, zevice_entity, DeviceStick)) {
                        const DeviceStick *deviceStick = ecs_get(world, zevice_entity, DeviceStick);
                        has_input = zevice_stick_has_input(deviceStick, joystick_min_cutoff2);
                        // zoxel_log("                 > deviceStick [%fx%f]\n", deviceStick->value.x, deviceStick->value.y);
                    } else if (ecs_has(world, zevice_entity, DeviceButton)) {
                        const DeviceButton *deviceButton = ecs_get(world, zevice_entity, DeviceButton);
                        has_input = deviceButton->value !=  0;
                    }
                    // zoxel_log("                 > has_input [%i]\n", has_input);
                    if (has_input) {
                        zeviceDisabled->value = 1;
                        ecs_modified(world, zevice_entity, ZeviceDisabled);
                        #ifdef zox_debug_zevice_states
                            zoxel_log("  = button disabled [%lu] at %f\n", zevice_entity, zox_current_time);
                        #endif
                    }
                } /*else {
                    zoxel_log("  = button was already disabled [%lu] at %f\n", zevice_entity, zox_current_time);
                }*/
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
        unsigned char has_input = devices_get_is_pressed(deviceButton->value);
        #ifdef zox_debug_zevice_states
            if (!has_input) zoxel_log("   = button reenabled [%lu] at %f\n", it->entities[i], zox_current_time);
        #endif
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZeviceButtonEnableSystem)

void ZeviceStickEnableSystem(ecs_iter_t *it) {
    const DeviceStick *deviceSticks = ecs_field(it, DeviceStick, 1);
    ZeviceDisabled *zeviceDisableds = ecs_field(it, ZeviceDisabled, 2);
    for (int i = 0; i < it->count; i++) {
        ZeviceDisabled *zeviceDisabled = &zeviceDisableds[i];
        if (!zeviceDisabled->value) continue;
        const DeviceStick *deviceStick = &deviceSticks[i];
        unsigned char has_input = zevice_stick_has_input(deviceStick, joystick_min_cutoff2 * 0.5f);
        #ifdef zox_debug_zevice_states
            if (!has_input) zoxel_log("   = joystick reenabled [%lu] at %f\n", it->entities[i], zox_current_time);
        #endif
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZeviceStickEnableSystem)

void ZevicePointerEnableSystem(ecs_iter_t *it) {
    const ZevicePointer *zevicePointers = ecs_field(it, ZevicePointer, 1);
    ZeviceDisabled *zeviceDisableds = ecs_field(it, ZeviceDisabled, 2);
    for (int i = 0; i < it->count; i++) {
        ZeviceDisabled *zeviceDisabled = &zeviceDisableds[i];
        if (!zeviceDisabled->value) continue;
        const ZevicePointer *zevicePointer = &zevicePointers[i];
        unsigned char has_input = devices_get_is_pressed(zevicePointer->value);
        #ifdef zox_debug_zevice_states
            if (!has_input) zoxel_log("   = zevice_pointer reenabled [%lu] at %f\n", it->entities[i], zox_current_time);
        #endif
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZevicePointerEnableSystem)