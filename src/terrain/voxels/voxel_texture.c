ecs_entity_t spawn_realm_voxel_texture(ecs_world_t *world, const byte index, char *name, char *texture_filename) {
    SpawnBlock spawn_data = {
        .index = index,
        .seed = generate_voxel_seed(index),
        .prefab_texture = prefab_vox_texture,
    };
    spawn_data.name = name; // "dark";
    spawn_data.color = color_black;
    spawn_data.textures = 1;
    spawn_data.texture_filename = texture_filename; // "dark_block";
    spawn_data.prefab = prefab_block;
    return spawn_block(world, &spawn_data);
}