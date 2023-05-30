void DestroyInFrameSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    for (int i = 0; i < it->count; i++) {
        // zoxel_log(" > event dies [%lu]\n", it->entities[i]);
        zox_delete(it->entities[i])
    }
}
zox_declare_system(DestroyInFrameSystem)