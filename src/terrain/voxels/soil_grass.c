ecs_entity_t spawn_block_soil_grass(ecs_world_t *world, const byte index, char* name, const color bottom_color, const color top_color) {
    // vox
    const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, top_color);
    zox_add_tag(vox, BlendVox)
    zox_set(vox, SecondaryColor, { bottom_color }) // bottom half
    zox_set_unique_name(vox, "block_soil_grass")
    // use instanced mesh prefab
    SpawnBlock data = {
        .index = (byte) (index),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = top_color,
        .vox = vox,
        .bake_vox = 1,
    };
    return spawn_block_vox_meta(world, &data);
}