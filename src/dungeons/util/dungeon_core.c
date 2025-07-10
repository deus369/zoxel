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
    zox_instance(prefab)
    zox_set(e, ChunkLink, { data->chunk })
    // todo: make this set as local position instead - VoxelLocalPosition
    zox_set(e, VoxelPosition, { byte3_to_int3(data->position_local) })
    // zox_set(e2, Scale1D, { data->spawn_data->scale })
    // zox_set(e2, Position3D, { position_real })
    link_node_ChunkOctree(data->node, e);
}