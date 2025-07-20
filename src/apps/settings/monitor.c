extern void zox_app_set_monitor_e(ecs_world_t*, ecs_entity_t, byte);

byte is_log_monitors = 1;
byte monitor = 1;

// use our setting
void zox_set_monitor(ecs_world_t *world, byte value) {
    zoxs_set_byte(world, "monitor", value);
}

void zox_set_monitor_silently(ecs_world_t *world, const ecs_entity_t e, byte value) {
    monitor = value;
    zoxs_set_byte_silently(world, "monitor", value);
    zox_set(e, WindowMonitor, { value })
}

// when setting is set
void set_app_monitor(ecs_world_t* world, void* value) {
    monitor = *(byte*) value;
    if (zox_valid(main_app)) {
        zox_app_set_monitor_e(world, main_app, monitor);
    }
}