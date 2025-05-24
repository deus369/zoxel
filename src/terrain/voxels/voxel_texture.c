ecs_entity_t spawn_realm_voxel_texture(ecs_world_t *world, const byte index, char *name, char *texture_filename) {
    SpawnBlock spawn_data = {
        .index = index,
        .seed = generate_voxel_seed(index),
        .prefab_texture = prefab_vox_texture,
        .name = name,
        .color = color_black,
        .textures = 1,
        .texture_filename = texture_filename,
        .prefab = prefab_block,
    };
    return spawn_block(world, &spawn_data);
}