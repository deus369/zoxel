ecs_entity_t spawn_realm_block_grass(ecs_world_t *world, const byte index, const color block_color) {
    const ecs_entity_t vox = spawn_vox_basic(world, prefab_vox);
    zox_set_unique_name(vox, "block_grass")
    zox_set(vox, VoxType, { vox_type_rubble })
    zox_set(vox, Color, { block_color })
    zox_set(vox, GenerateVox, { 1 })
    zox_set(vox, RenderLod, { 0 })
    zox_set(vox, RubbleHeight, { 24 })
    zox_set(vox, RubbleCount, { 8000 })
    // use instanced mesh prefab
    SpawnBlock data = {
        .name = "grass",
        .prefab = prefab_block_vox_meta,
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
    process_disabled_block_vox(world, &data, 1);
    return spawn_block_vox_meta(world, &data);
}