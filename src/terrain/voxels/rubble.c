ecs_entity_t spawn_realm_block_rubble(ecs_world_t *world, const byte index, char* name, const color block_color) {
    // vox
    const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    zox_add_tag(vox, VoxRubble)
    // use instanced mesh prefab
    SpawnBlock data = {
        .index = (byte) (index),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = block_color,
        .vox = vox,
        .prefab_block_vox = prefab_block_vox,
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1
    };
    if (disable_block_voxes) {
        data.bake_vox = 1;
        data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    }
    const ecs_entity_t e = spawn_block_vox_meta(world, &data);
    return e;
}