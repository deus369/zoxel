ecs_entity_t prefab_voxel;

ecs_entity_t spawn_prefab_voxel(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, Voxel)
    ecs_defer_end(world);
    prefab_voxel = e;
    return e;
}

ecs_entity_t spawn_voxel(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_instance(prefab_voxel)
    ecs_defer_end(world);
    return e;
}