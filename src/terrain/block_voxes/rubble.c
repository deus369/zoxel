ecs_entity_t spawn_realm_block_rubble(
    ecs_world_t *world,
    const byte index,
    char* name,
    const color block_color
) {
    // vox
    const ecs_entity_t v = spawn_vox_basic(world, prefab_vox, block_vox_depth);
    zox_set_unique_name(v, "block_rubble")
    //  zox_set(v, VoxType, { vox_type_rubble })
    zox_set(v, VoxType, { vox_type_flowers })
    zox_set(v, Color, { block_color })
    zox_set(v, GenerateVox, { zox_dirty_trigger })
    zox_set(v, RenderLod, { 0 })
    // for instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2);
    zox_set(prefab_block_vox2, InstanceLink, { v });

    SpawnBlock data = {
        .name = name,
        .prefab = prefab_block_vox_meta,
        // .prefab_block_vox = prefab_block_vox,
        .prefab_block_vox = prefab_block_vox2, // prefab_block_vox_instanced,
        .vox = v,
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = block_color,
        .disable_collision = 1,
    };

    // todo: test non instanced voxes
    process_disabled_block_vox(world, &data, 1);
    return spawn_block_vox_meta(world, &data);
}