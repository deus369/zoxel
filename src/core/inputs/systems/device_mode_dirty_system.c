void DeviceModeDirtySystem(ecs_iter_t *it) {
    DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        DeviceMode *deviceMode = &deviceModes[i];
        DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        if (deviceModeDirty->value != 0) {
            // zoxel_log("     > devicemode dirty [%i] -> [%i]\n", deviceModeDirty->value, deviceMode->value);
            deviceMode->value = deviceModeDirty->value;
            deviceModeDirty->value = 0;
        }
    }
} zox_declare_system(DeviceModeDirtySystem)