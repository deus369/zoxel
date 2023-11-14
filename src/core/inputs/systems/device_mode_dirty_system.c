void DeviceModeDirtySystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    DeviceMode *deviceModes = ecs_field(it, DeviceMode, 1);
    DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 2);
    for (int i = 0; i < it->count; i++) {
        DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        if (!deviceModeDirty->value) continue;
        DeviceMode *deviceMode = &deviceModes[i];
        ecs_entity_t e = it->entities[i];
        deviceMode->value = deviceModeDirty->value;
        deviceModeDirty->value = 0;
        disable_inputs_until_release(world, e);
#ifdef zox_debug_log_device_mode_system
        zox_log("     > devicemode dirty [%i]\n", deviceMode->value)
#endif
    }
} zox_declare_system(DeviceModeDirtySystem)
