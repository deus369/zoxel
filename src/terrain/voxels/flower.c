ecs_entity_t spawn_block_flower(ecs_world_t *world, const byte index) {
    SpawnBlock spawn_data = {
        .name = "flower",
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .tag = zox_id(BlockVox),
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = generate_random_voxel_color(),
        .model = zox_block_vox,
        .disable_collision = 1,
        .vox_offset = 1,
    };
    spawn_data.vox = string_hashmap_get(files_hashmap_voxes, new_string_data("flower"));
    if (!spawn_data.vox) {
        zox_log_error("[flower] vox not found")
        return 0;
    }
    /*if (disable_block_voxes) {
        spawn_data.bake_vox = 1;
        spawn_data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
        spawn_data.model = 0;
        spawn_data.tag = 0;
    } else {*/
    //}//
    // instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    spawn_data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { spawn_data.vox })
    // our block!
    return spawn_block_vox_meta(world, &spawn_data);
}