typedef struct {
    Finger primary_touch;
    Finger secondary_touch;
} Touchscreen;
zox_custom_component(Touchscreen)

#define touchscreen_zero {\
    .primary_touch = finger_zero,\
    .secondary_touch = finger_zero\
}

unsigned char touchscreen_is_any_input(const Touchscreen *touchscreen) {
    return finger_is_any_input(&touchscreen->primary_touch) ||
        finger_is_any_input(&touchscreen->secondary_touch);
}

void device_reset_touchscreen(ecs_world_t *world, ecs_entity_t e) {
    if (!e || !ecs_is_alive(world, e)) return;
    Touchscreen *touchscreen = ecs_get_mut(world, e, Touchscreen);
    reset_key(&touchscreen->primary_touch.value);
    touchscreen->primary_touch.delta = int2_zero;
    ecs_modified(world, e, Touchscreen);
}