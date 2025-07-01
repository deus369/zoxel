ecs_entity_t spawn_realm_block_vox_flower(ecs_world_t *world, const byte index) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("flower"));
    if (vox == 0) {
        zox_log(" ! vox model not found.\n")
    }
    SpawnBlock spawn_data = {
        .index = (byte) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .name = "flower",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
        .prefab_texture = prefab_vox_texture
    };
    // instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    spawn_data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    if (disable_block_voxes) {
        spawn_data.bake_vox = 1;
        spawn_data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
        spawn_data.model = 0;
        spawn_data.tag = 0;
    } else {
        spawn_data.vox = vox;
        spawn_data.vox_offset = 1;
        if (!spawn_data.vox) {
            zox_log(" ! [grass] vox not found\n")
            return 0;
        }
    }
    const ecs_entity_t block_vox_meta = spawn_block_vox_meta(world, &spawn_data);
    // link instance entity here
    return block_vox_meta;
}