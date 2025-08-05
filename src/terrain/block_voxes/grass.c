ecs_entity_t spawn_block_grass(ecs_world_t *world,
    const byte index,
    const color block_color,
    const ecs_entity_t model
) {
    // zox_log("+ spawning realm_block with model [%s]", zox_get_name(model))
    // use instanced mesh prefab
    SpawnBlock data = {
        .name = "grass",
        .prefab = prefab_block_vox_meta,
        .tag = zox_id(BlockVox),
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = generate_random_voxel_color(),
        .model = zox_block_vox,
        .disable_collision = 1,
        .vox = model,
        .prefab_block_vox = prefab_block_vox_instanced
    };

    // thats all fokes
    process_disabled_block_vox(world, &data, 1);


    ecs_entity_t e = spawn_block_vox_meta(world, &data);

    // link a texture to it
    zox_geter(model, ModelLinks, models);
    zox_geter(models->value[0], ModelLods, modelLods);
    ecs_entity_t v = modelLods->value[0];
    const ecs_entity_t t = spawn_texture(
        world,
        prefab_vox_texture,
        voxel_texture_size
    );
    zox_set_name_e(t, "grass_texture");
    zox_set(t, VoxLink, { v });
    zox_set(t, VoxBakeSide, { direction_left }); // direction_front
    zox_set(e, TextureLink, { t });

    return e;
}