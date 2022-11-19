ecs_entity_t terrain_chunk_prefab;

ecs_entity_t spawn_prefab_terrain_chunk(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_terrain_chunk");
    zoxel_add_tag(world, e, TerrainChunk);
    zoxel_add(world, e, MeshUVs);
    add_gpu_uvs(world, e);
    add_texture(world, e, (int2) { 16, 16 });
    add_noise_texture(world, e);
    zoxel_add_tag(world, e, DirtTexture);
    add_gpu_texture(world, e);
    // texture too
    ecs_defer_end(world);
    terrain_chunk_prefab = e;
    return e;
}

ecs_entity_t spawn_terrain_chunk(ecs_world_t *world, ecs_entity_t prefab,
    float3 position, float scale)
{
    // int2 textureSize = { 16, 16 };
    ecs_defer_begin(world);
    // ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab, position, scale);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Scale1D, { scale });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, shader3D_textured);
    spawn_gpu_uvs(world, e);
    spawn_gpu_texture(world, e);
    ecs_defer_end(world);
    return e;
}