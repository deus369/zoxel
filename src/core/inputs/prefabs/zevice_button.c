ecs_entity_t prefab_zevice_button;

ecs_entity_t spawn_prefab_device_button(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zevice_button")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZeviceButton, { 0 })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    prefab_zevice_button = e;
    return e;
}

ecs_entity_t spawn_device_button(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_zevice_button)
    zox_name("zevice_button")
    zox_prefab_set(e, DeviceButtonType, { type })
    zox_prefab_set(e, RealButtonIndex, { index })
    return e;
}

unsigned char reset_device_button(ZeviceButton *zeviceButton) {
    unsigned char previous_value = zeviceButton->value;
    if (devices_get_pressed_this_frame(zeviceButton->value)) devices_set_pressed_this_frame(&zeviceButton->value, 0);
    else if (devices_get_released_this_frame(zeviceButton->value)) devices_set_released_this_frame(&zeviceButton->value, 0);
    return previous_value != zeviceButton->value;
}
