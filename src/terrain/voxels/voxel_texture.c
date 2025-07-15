ecs_entity_t spawn_realm_voxel_texture(ecs_world_t *world,
    const byte index,
    char *name,
    char *texture_filename)
{
    SpawnBlock spawn_data = {
        .prefab = prefab_block,
        .prefab_texture = prefab_vox_texture,
        .textures = 1,
        .texture_filename = texture_filename,
        .index = index,
        .seed = generate_voxel_seed(index),
        .name = name,
        .color = color_black,
    };
    return spawn_block(world, &spawn_data);
}