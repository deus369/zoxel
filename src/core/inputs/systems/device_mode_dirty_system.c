void DeviceModeDirtySystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return;
    DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        DeviceMode *deviceMode = &deviceModes[i];
        DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        // zoxel_log("     > devicemode dirty ? %i\n", deviceModeDirty->value);
        /**if (deviceModeDirty->value >= zox_device_mode_max) {
            // zoxel_log(" ! deviceModeDirty out of range [%i]\n", deviceModeDirty->value);
            deviceModeDirty->value = 0;
            continue;
        }*/
        if (deviceModeDirty->value != 0) {
            // zoxel_log("     > devicemode dirty [%i] -> [%i]\n", deviceModeDirty->value, deviceMode->value);
            deviceMode->value = deviceModeDirty->value;
            deviceModeDirty->value = 0;
        }
    }
}
zox_declare_system(DeviceModeDirtySystem)