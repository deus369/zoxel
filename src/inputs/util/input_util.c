// #define zox_debug_zevice_states

// todo: check if this is added back
extern void raycaster_select_element(ecs *world, const entity raycaster_entity, const entity element);

// this disables any buttons (zevices) of a device, until they are released, then they get auto re enabled
void disable_inputs_until_release(ecs *world, const entity player, const byte new_device_mode, const byte old_mode) {
    if (old_mode == 0) {
        return; // no need disable on start
    }
    if (!zox_valid(player)) {
        return;
    }
    if (new_device_mode != zox_device_mode_gamepad) {
        // zox_log_error("Need to reenable this function and refactor it.")
        raycaster_select_element(world, player, 0);
    }
    const DeviceLinks *deviceLinks = zox_get(player, DeviceLinks)
    for (int j = 0; j < deviceLinks->length; j++) {
        entity device = deviceLinks->value[j];
        if (!zox_valid(device)) {
            continue;
        }
        if (zox_has(device, Gamepad)) {
            const Children *zevices = zox_get(device, Children)
            for (int k = 0; k < zevices->length; k++) {
                entity zevice_entity = zevices->value[k];
                ZeviceDisabled *zeviceDisabled = zox_get_mut(zevice_entity, ZeviceDisabled)
                if (!zeviceDisabled->value) {
                    byte has_input = 0;
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                        has_input = zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                        has_input = zeviceButton->value !=  0;
                    }
                    if (has_input) {
                        zeviceDisabled->value = 1;
                        zox_modified(zevice_entity, ZeviceDisabled);
                        zox_log_input("  = button disabled [%lu] at %f", zevice_entity, zox_current_time)
                    }
                }
            }
        }
    }
}
