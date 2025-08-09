entity spawn_prefab_keyboard(ecs *world, const entity prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("keyboard");
    zox_prefab_add(e, Keyboard);
    return e;
}

entity spawn_keyboard(ecs *world) {
    zox_instance(prefab_keyboard);
    zox_name("keyboard");
    zox_set(e, Keyboard, { 0 });
    return e;
}
