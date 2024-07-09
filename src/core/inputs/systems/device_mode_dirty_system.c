void DeviceModeDirtySystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_out(DeviceModeDirty, deviceModeDirtys, 2)
    zox_field_out(DeviceMode, deviceModes, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(DeviceModeDirty, deviceModeDirtys, deviceModeDirty)
        if (!deviceModeDirty->value) continue;
        zox_field_e()
        zox_field_o(DeviceMode, deviceModes, deviceMode)
        deviceMode->value = deviceModeDirty->value;
        deviceModeDirty->value = 0;
        disable_inputs_until_release(world, e, deviceMode->value);
#ifdef zox_debug_log_device_mode_system
        zox_log("     > devicemode dirty [%i]\n", deviceMode->value)
#endif
    }
} zox_declare_system(DeviceModeDirtySystem)
