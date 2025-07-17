void spawn_block_dungeon_blocks(ecs_world_t *world, spawn_blocks_data *data) {
    // zox_log("spawn_block_dungeon_core")
    data->blocks->value[zox_block_dungeon_core - 1] = spawn_realm_dungeon_core(world);
    data->blocks->value[zox_block_dark - 1] = spawn_realm_voxel_texture(world,
        zox_block_dark,
        "dark",
        "block_dark");
}