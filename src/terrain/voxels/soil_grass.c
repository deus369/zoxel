ecs_entity_t spawn_block_soil_grass(
    ecs_world_t *world,
    const byte index,
    char* name,
    const color bottom_color,
    const color top_color
) {
    // vox
    const ecs_entity_t v = spawn_vox_generated_invisible(world, prefab_vox_generated, top_color);
    zox_set(v, VoxType, { vox_type_blended });
    zox_set(v, SecondaryColor, { bottom_color });
    zox_set_unique_name(v, "block_soil_grass");
    zox_set(v, VRegions, { 0 });
    // use instanced mesh prefab
    SpawnBlock data = {
        .index = index,
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = top_color,
        .vox = v,
        .bake_vox = 1,
    };
    return spawn_block_vox_meta(world, &data);
}