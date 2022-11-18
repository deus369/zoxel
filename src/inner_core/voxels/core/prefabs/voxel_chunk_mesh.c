ecs_entity_t voxel_prefab;

ecs_entity_t spawn_voxel_chunk_mesh_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, custom_mesh_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "voxel_prefab");
    add_seed(world, e, 666);
    add_chunk(world, e, chunk_size);
    add_generate_chunk(world, e);
    ecs_set(world, e, Brightness, { 1.4f });
    ecs_set(world, e, Scale1D, { 0.05f });
    voxel_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_voxel_chunk_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Scale1D, { scale });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    ecs_defer_end(world);
    return e;
}

ecs_entity_t prefab_noise_chunk;

ecs_entity_t spawn_prefab_noise_chunk(ecs_world_t *world)
{
    ecs_defer_begin(world);
    
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_noise_chunk");

    ecs_add(world, e, NoiseChunk);
    ecs_add(world, e, AnimateChunk);

    prefab_noise_chunk = e;
    ecs_defer_end(world);
    return e;
}


ecs_entity_t spawn_voxel_noise_chunk_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale)
{
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab, position, scale);
    zoxel_set(world, e, AnimateChunk, { (((rand() % 100) / 100.0f) * noiseChunkAnimateSpeed) }); // 0.0 });
    return e;
}