ecs_entity_t character3D_prefab;
ecs_entity_t main_character3D;

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_character3D");
    add_seed(world, e, 999);
    add_physics3D(world, e);
    zoxel_set(world, e, Scale1D, { 1 })
    if (!headless) {
        ecs_remove(world, e, MaterialGPULink);
        add_gpu_colors(world, e);
    }
    // zoxel_add_tag(world, e, LinkChunk)
    zoxel_add(world, e, VoxLink)
    zoxel_set(world, e, ChunkLink, { 0 })
    zoxel_set(world, e, ChunkPosition, { int3_zero })
    zoxel_set(world, e, VoxelPosition, {{ 0, 0, 0 }})
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    character3D_prefab = e;
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox, float3 position, float4 rotation, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zoxel_set(world, e, Position3D, { position })
    // zoxel_set(world, e, Scale1D, { scale })
    zoxel_set(world, e, Rotation3D, { rotation })
    zoxel_set(world, e, VoxLink, { main_terrain_world })
    set_vox_from_vox_file(world, e, vox);
    ecs_defer_end(world);
    main_character3D = e;
    /*if (position.x >= 0 && position.x <= real_chunk_scale && position.z >= 0 && position.z <= real_chunk_scale) {
        main_character3D = e;
    }*/
    /*if (position.x >= -real_chunk_scale && position.x <= real_chunk_scale && position.z >= -real_chunk_scale && position.z <= real_chunk_scale) {
        main_character3D = e;
    }*/
    return e;
}