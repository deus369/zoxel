/*ecs_entity_t chunk_prefab;

ecs_entity_t spawn_chunk_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    add_seed(world, e, 666);
    add_chunk(world, e, default_chunk_size);
    add_noise_chunk(world, e);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab chunk_prefab [%lu].\n", (long int) (e));
    #endif
    chunk_prefab = e;
    return e;
}

ecs_entity_t spawn_chunk(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    zoxel_add_tag(e, NoiseChunk);
    zoxel_log("Spawned TextureData [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    return e;
}*/