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
    // instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    spawn_data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { spawn_data.vox })
    // our block!
    process_disabled_block_vox(world, &spawn_data, 0);

    ecs_entity_t e = spawn_block_vox_meta(world, &spawn_data);


    // quick fix
    if (!disable_block_voxes) {
        // zox_set(spawn_data.vox, NodeDepth, { 4 });
        zox_geter(spawn_data.vox, ModelLods, modelLods);
        ecs_entity_t v = modelLods->value[0];
        // link a texture to it
        const ecs_entity_t t = spawn_texture(
            world,
            prefab_vox_texture,
            voxel_texture_size
        );
        zox_set_name_e(t, "grass_texture");
        zox_set(t, VoxLink, { v });
        zox_set(t, VoxBakeSide, { direction_left }); // direction_front
        zox_set(e, TextureLink, { t });
    }

    return e;
}