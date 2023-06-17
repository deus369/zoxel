void DestroyInFrameSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        zox_delete(e)
        // zoxel_log(" > event dies [%lu]\n", e);
    }
}
zox_declare_system(DestroyInFrameSystem)