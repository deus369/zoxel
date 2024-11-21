extern ecs_entity_t prefab_particle3D;

ecs_entity_t spawn_realm_block_vox_grass(ecs_world_t *world, const unsigned char index) {
    // use instanced mesh prefab
    // prefab_block_vox_meta
    SpawnBlock spawn_data = {
        .index = (unsigned char) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_block_vox = prefab_block_vox,
        .name = "grass",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
        .prefab_texture = prefab_vox_texture
    };
    spawn_data.prefab_block_vox = prefab_block_vox_instanced;
    /// spawn_data.prefab_block_vox = prefab_particle3D;
    // zox_log("prefab_particle3D: %lu\n", prefab_particle3D)
#ifdef zox_disable_block_voxes
    spawn_data.bake_vox = 1;
    spawn_data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
    spawn_data.model = 0;
    spawn_data.tag = 0;
#else
    spawn_data.vox = string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
    if (!spawn_data.vox) {
        zox_log(" ! [grass] vox not found\n")
        return 0;
    }
#endif
    return spawn_block_vox_meta(world, &spawn_data);
}
