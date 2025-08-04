ecs_entity_t spawn_block_bricks(
    ecs_world_t *world,
    const byte index,
    char* name,
    const color block_color// ,
    // byte vregions
) {
    // vox
    const ecs_entity_t v = spawn_vox_generated_invisible(
        world,
        prefab_vox_generated,
        block_color
    );
    zox_set_unique_name(v, "block_bricks");
    zox_set(v, VoxType, { vox_type_bricks });
    // zox_set(v, VRegions, { vregions });

    // use instanced mesh prefab
    SpawnBlock data = {
        .index = index,
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = block_color,
        .vox = v,
        .bake_vox = 1,
    };
    return spawn_block_vox_meta(world, &data);
}