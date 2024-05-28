ecs_entity_t spawn_prefab_vox_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_set(e, GenerateVox, { 1 })
    zox_prefab_set(e, Color, { color_white })
    return e;
}

ecs_entity_t spawn_vox_generated(ecs_world_t *world, const ecs_entity_t prefab, const color vox_color) {
    zox_instance(prefab)
    zox_set(e, Color, { vox_color })
    return e;
}

ecs_entity_t spawn_vox_generated_invisible(ecs_world_t *world, const ecs_entity_t prefab, const color vox_color) {
    zox_instance(prefab)
    zox_set(e, Color, { vox_color })
    zox_set(e, RenderDisabled, { 1 })
    return e;
}
