// grid like ui
ecs_entity_t spawn_prefab_taskbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("taskbar")
    zox_add_tag(e, Taskbar)
    zox_prefab_add(e, Children)
    return e;
}

// temp solution
extern ecs_entity_t spawn_actionbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 position, const float2 anchor,  const unsigned char layer, const unsigned char icon_size);

ecs_entity_t spawn_taskbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, const unsigned char layer) {
    return spawn_actionbar(world, prefab, canvas, parent, (int2) { 0, -24 }, (float2) { 0.5f, 1 }, layer, 36);
}
