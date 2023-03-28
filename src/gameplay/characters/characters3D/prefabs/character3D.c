ecs_entity_t character3D_prefab;

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox); // voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_character3D");
    add_seed(world, e, 999);
    add_physics3D(world, e);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    character3D_prefab = e;
    return e;
}

// ecs_entity_t latest_character3D;

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox, float3 position, float4 rotation, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab, position, scale);
    set_vox_from_vox_file(world, e, vox);
    zoxel_set(world, e, Rotation3D, { rotation });
    ecs_defer_end(world);
    // latest_character3D = e;
    return e;
}