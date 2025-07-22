void spawned_block_vox(ecs_world_t *world, spawned_block_data *data) {
    if (!zox_has(data->block, BlockPrefabLink)) {
        return;
    }
    if (!data->node) {
        zox_log_error("null node in [spawned_block_vox]")
        return;
    }
    // gett block data
    zox_geter_value(data->block, BlockPrefabLink, ecs_entity_t, prefab)
    zox_geter_value_safe(data->block, ModelLink, ecs_entity_t, vox)
    SpawnBlockVox spawn_data = {
        .prefab = prefab,
        .vox = vox,
        .block_index = data->block_index,
        .position_local = data->position_local,
        .position_global = data->position_global,
        .position_real = data->position_real,
        .scale = data->scale,
    };
    // offset property
    /*if (zox_has(data->block, BlockVoxOffset) && zox_gett_value(data->block, BlockVoxOffset)) {
        float3_add_float3_p(&spawn_data.position_real, (float3) { 0, data->scale * -0.25f, 0 });
    }*/
    ecs_entity_t e2;
    if (zox_has(prefab, BlockVox)) {
        e2 = spawn_block_vox(world, &spawn_data);
    } else if (zox_has(prefab, RendererInstance)) {
        e2 = spawn_block_vox_instanced(world, &spawn_data);
    } else {
        // zox_log("   - [DungeonCore]")
        // dungeon blocks
        e2 = zox_instancee(prefab)
        zox_set(e2, ChunkLink, { data->chunk })
        // todo: make this set as local position instead - VoxelLocalPosition
        zox_set(e2, VoxelPosition, { byte3_to_int3(data->position_local) })
        // zox_set(e2, Scale1D, { data->spawn_data->scale })
        // zox_set(e2, Position3D, { position_real })
    }
    link_node_VoxelNode(data->node, e2);
    /*zox_log("+ Placing Block [%s]: linked: [%i]", zox_get_name(data->block), data->node->linked)
    zox_log("   - local [%ix%ix%i] ", spawn_data.position_local.x, spawn_data.position_local.y, spawn_data.position_local.z)
    zox_log("   - global [%ix%ix%i] ", spawn_data.position_global.x, spawn_data.position_global.y, spawn_data.position_global.z)
    zox_log("   - real [%fx%fx%f] ", spawn_data.position_real.x, spawn_data.position_real.y, spawn_data.position_real.z)*/
    // spawn_line3D(world, spawn_data.position_real, float3_add(spawn_data.position_real, (float3) { 0, 2, 0 }), 2, 3);
}