ecs_entity_t spawn_realm_block_vox_grass(ecs_world_t *world, const unsigned char index) {
    // use instanced mesh prefab
    // prefab_block_vox_meta
    SpawnBlock spawn_data = {
        .index = (unsigned char) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .name = "grass",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
    };
    spawn_data.vox = string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
    if (!spawn_data.vox) {
        zox_log(" ! [grass] vox not found\n")
        return 0;
    }
    return spawn_block_vox_meta(world, &spawn_data);
}
