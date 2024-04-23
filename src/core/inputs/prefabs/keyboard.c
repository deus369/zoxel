ecs_entity_t prefab_keyboard;
ecs_entity_t keyboard_entity;

ecs_entity_t spawn_prefab_keyboard(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_keyboard")
    zox_add_tag(e, Device)
    zox_add(e, Keyboard)
    prefab_keyboard = e;
    return e;
}

ecs_entity_t spawn_keyboard(ecs_world_t *world) {
    zox_instance(prefab_keyboard)
    zox_name("keyboard")
    zox_set(e, Keyboard, { })  // zeros it out?
    keyboard_entity = e;
    return e;
}
