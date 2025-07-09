ecs_entity_t spawn_realm_block_grass(ecs_world_t *world, const byte index, const color block_color) {
    const ecs_entity_t vox = spawn_vox_basic(world, prefab_vox);
    zox_set_unique_name(vox, "block_grass")
    zox_add_tag(vox, VoxRubble)
    zox_set(vox, Color, { block_color })
    zox_set(vox, GenerateVox, { 1 })
    zox_set(vox, RenderLod, { 0 })
    zox_set(vox, RubbleHeight, { 24 })
    zox_set(vox, RubbleCount, { 8000 })
    if (!vox) {
        zox_log(" ! grass_vox model not found.\n")
    }
    // use instanced mesh prefab
    SpawnBlock data = {
        .name = "grass",
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .vox = vox,
        .tag = zox_id(BlockVox),
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = generate_random_voxel_color(),
        .model = zox_block_vox,
        .disable_collision = 1,
    };
    // for instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    // thats all fokes
    return spawn_block_vox_meta(world, &data);
}

/*if (disable_block_voxes) {
    data.bake_vox = 1;
    data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    data.model = 0;
    data.tag = 0;
}*/