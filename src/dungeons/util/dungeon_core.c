void spawn_world_dungeon_core(ecs_world_t *world, spawned_block_data *data) {
    if (!zox_has(data->block, BlockPrefabLink)) {
        return;
    }
    if (!data->node) {
        zox_log_error("null node in [spawned_block_vox]")
        return;
    }
    zox_geter_value(data->block, BlockPrefabLink, ecs_entity_t, prefab)
    if (!zox_has(prefab, DungeonCore)) {
        return;
    }
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
    ecs_entity_t e2 = zox_instancee(prefab)
    zox_set(e2, ChunkLink, { data->chunk })
    // todo: make this set as local position instead - VoxelLocalPosition
    zox_set(e2, VoxelPosition, { byte3_to_int3(data->position_local) })
    // zox_set(e2, Scale1D, { data->spawn_data->scale })
    // zox_set(e2, Position3D, { position_real })
    link_node_ChunkOctree(data->node, e2);
}