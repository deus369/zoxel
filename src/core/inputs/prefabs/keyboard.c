ecs_entity_t spawn_prefab_keyboard(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("keyboard")
    zox_add(e, Keyboard)
    return e;
}

ecs_entity_t spawn_keyboard(ecs_world_t *world) {
    zox_instance(prefab_keyboard)
    zox_name("keyboard")
    zox_set(e, Keyboard, { })  // zeros it out?
    return e;
}
