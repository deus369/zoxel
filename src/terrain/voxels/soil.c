ecs_entity_t spawn_block_soil(ecs_world_t *world, const byte index, char* name, const color block_color) {
    // vox
    const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    zox_set_unique_name(vox, "block_soil")
    zox_set(vox, VoxType, { vox_type_soil })
    // use instanced mesh prefab
    SpawnBlock data = {
        .index = index,
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = block_color,
        .vox = vox,
        .bake_vox = 1,
    };
    return spawn_block_vox_meta(world, &data);
}