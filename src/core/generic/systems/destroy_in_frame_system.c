void DestroyInFrameSystem(ecs_iter_t *it) {
    for (int i = 0; i < it->count; i++) {
        zoxel_log(" > event dies [%lu]\n", it->entities[i]);
        ecs_delete(it->world, it->entities[i]);
    }
}
zox_declare_system(DestroyInFrameSystem)