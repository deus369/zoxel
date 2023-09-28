ecs_entity_t prefab_chunk;

ecs_entity_t spawn_prefab_chunk(ecs_world_t *world) {
    zox_prefab()
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
        zox_set(e, Scale1D, { 0.05f })
    #endif
    zox_set(e, MeshDirty, { 0 })
    zox_set(e, Brightness, { 1.4f })
    add_seed(world, e, 666);
    add_chunk_octree(world, e, default_chunk_size);
    add_generate_chunk(world, e);
    if (!headless) {
        zox_add(e, MeshIndicies)
        zox_add(e, MeshVertices)
        zox_add(e, MeshColorRGBs)
        zox_add(e, ColorsGPULink)
        add_gpu_mesh(world, e);
    }   
    prefab_chunk = e;
    return e;
}

ecs_entity_t spawn_chunk(ecs_world_t *world, ecs_entity_t prefab_chunk, float3 position, float scale) {
    zox_instance(prefab_chunk)
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Scale1D, { scale })
    spawn_gpu_mesh(world, e);
    return e;
}