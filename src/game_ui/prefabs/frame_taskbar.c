// grid like ui
ecs_entity_t spawn_prefab_frame_taskbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_set(e, ActiveState, { 0 })   // purely for taskbar icon frame atm
    return e;
}
