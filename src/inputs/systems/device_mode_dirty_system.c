void DeviceModeDirtySystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(DeviceMode)
    zox_sys_out(DeviceModeDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_o(DeviceModeDirty, deviceModeDirty)
        zox_sys_o(DeviceMode, deviceMode)
        if (!deviceModeDirty->value) {
            continue;
        }
        byte old_mode = deviceMode->value;
        deviceMode->value = deviceModeDirty->value;
        disable_inputs_until_release(world, e, deviceMode->value, old_mode);
        deviceModeDirty->value = 0;
#ifdef zox_debug_log_device_mode_system
        zox_log("     > devicemode dirty [%i]\n", deviceMode->value)
#endif
    }
} zox_declare_system(DeviceModeDirtySystem)