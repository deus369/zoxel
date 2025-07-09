ecs_entity_t spawn_realm_block_rubble(ecs_world_t *world, const byte index, char* name, const color block_color) {
    // vox
    const ecs_entity_t vox = spawn_vox_basic(world, prefab_vox);
    zox_set_unique_name(vox, "block_rubble")
    zox_add_tag(vox, VoxRubble)
    zox_set(vox, Color, { block_color })
    zox_set(vox, GenerateVox, { 1 })
    zox_set(vox, RenderLod, { 0 })
    SpawnBlock data = {
        .name = name,
        .prefab = prefab_block_vox_meta,
        //.prefab_texture = prefab_vox_texture,
        .prefab_block_vox = prefab_block_vox,
        .vox = vox,
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = block_color,
        .disable_collision = 1,
    };
    if (disable_block_voxes) {
        data.bake_vox = 1;
        data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    }
    // for instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    // todo: test non instanced voxes
    return spawn_block_vox_meta(world, &data);
}

//const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
//zox_add_tag(vox, VoxRubble)