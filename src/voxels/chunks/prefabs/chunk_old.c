/*ecs_entity_t spawn_prefab_chunk(ecs_world_t *world) {
    zox_prefab()
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, Brightness, { 1.4f })
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
    return e;
}

ecs_entity_t spawn_chunk(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    zox_instance(prefab)
    zox_set(e, Position3D, { position })
    spawn_gpu_mesh(world, e);
    return e;
}*/
