define_fun_stopwatch(time_realm_blocks, 0);

void spawn_realm_blocks(ecs_world_t *world, const ecs_entity_t realm) {
    if (!realm) {
        return;
    }
    if (!zox_has(realm, VoxelLinks)) {
        zox_log_error("realm does not have VoxelLinks [%lu]", realm)
        return;
    }
    startwatch(time_realm_blocks);

    // clear old
    zox_geter(realm, VoxelLinks, old_data)
    if (old_data) {
        for (int i = 0; i < old_data->length; i++) {
            zox_delete(old_data->value[i])
        }
        free(old_data->value);
    }

    const byte target_depth = block_vox_depth;
    const byte texture_dim = powers_of_two_byte[target_depth];
    voxel_texture_size = (int2) { texture_dim, texture_dim };

    // get realms colors
    zox_geter(realm, Colors, realm_colors);
    color dirt_color;
    color grass_color;
    color sand_color;
    color stone_color;
    color obsidian_color;
    if (realm_colors->length < 5 || grayscale_mode) {
        zox_log("+ grayscale_mode enabled")
        dirt_color = color_grayscale(88);
        grass_color = color_grayscale(144);
        sand_color = color_grayscale(166);
        stone_color = color_grayscale(45);
        obsidian_color = color_grayscale(13);
    } else {
        byte color_index = 1;   // skip sky
        // const color sky_color = realm_colors->value[color_index++];
        dirt_color = realm_colors->value[color_index++];
        grass_color = realm_colors->value[color_index++];
        sand_color = realm_colors->value[color_index++];
        stone_color = realm_colors->value[color_index++];
        obsidian_color = realm_colors->value[color_index++];
    }

    // get models
    zox_geter(realm, ModelLinks, models);

    VoxelLinks blocks = (VoxelLinks) { 0, NULL };
    initialize_VoxelLinks(&blocks, zox_blocks_end);
    for (int i = 0; i < blocks.length; i++) {
        blocks.value[i] = 0;
    }
    tapwatch(time_realm_blocks, "initialized");

    // nature blocks
    blocks.value[zox_block_dirt - 1] = spawn_block_soil(world, zox_block_dirt, "dirt", dirt_color);
    tapwatch(time_realm_blocks, "built soil");

    blocks.value[zox_block_grass - 1] = spawn_block_soil_grass(world, zox_block_grass, "grass", dirt_color, grass_color);
    tapwatch(time_realm_blocks, "built soil_grass");

    blocks.value[zox_block_sand - 1] = spawn_block_soil(world, zox_block_sand, "sand", sand_color);
    tapwatch(time_realm_blocks, "built sand");

    blocks.value[zox_block_stone - 1] = spawn_block_stone(world, zox_block_stone, "stone", stone_color);
    tapwatch(time_realm_blocks, "built stone");

    blocks.value[zox_block_obsidian - 1] = spawn_block_stone(world, zox_block_obsidian, "obsidian", obsidian_color);
    zox_add_tag(blocks.value[zox_block_obsidian - 1], BlockInvinsible)
    tapwatch(time_realm_blocks, "built obsidian");

    blocks.value[zox_block_bricks - 1] = spawn_block_bricks(
        world,
        zox_block_bricks,
        "bricks",
        obsidian_color);
    tapwatch(time_realm_blocks, "built bricks");

    // decor
    ecs_entity_t model_group_grass = models->value[0];
    blocks.value[zox_block_vox_grass - 1] = spawn_block_grass(world,
        zox_block_vox_grass,
        grass_color,
        model_group_grass);

    blocks.value[zox_block_dirt_rubble - 1] = spawn_realm_block_rubble(world, zox_block_dirt_rubble, "rubble", dirt_color);
    tapwatch(time_realm_blocks, "built rubble");

    blocks.value[zox_block_dirt_vox - 1] = spawn_realm_block_noisey(world, zox_block_dirt_vox, "dirt pile", dirt_color);
    tapwatch(time_realm_blocks, "built pile");

    blocks.value[zox_block_vox_flower - 1] = spawn_block_flower(world, zox_block_vox_flower);
    tapwatch(time_realm_blocks, "built flower");

    spawn_blocks_data spawned_data = (spawn_blocks_data) {
        .realm = realm,
        .blocks = &blocks,
    };
    run_hook_spawn_blocks(world, &spawned_data);
    tapwatch(time_realm_blocks, "ran hooks");


    for (int i = 0; i < blocks.length; i++) {
        if (!blocks.value[i]) {
            zox_log_error("[realm_blocks]: voxel invalid at [%i]", i)
        }
    }
    zox_set_ptr(realm, VoxelLinks, blocks);
    zox_set(realm, VoxelsDirty, { 1 });

    zox_logv("At [%f] Realm [blocks] [%i] spawned.", zox_current_time, blocks.length);
    endwatch(time_realm_blocks, "ending");
}



void spawn_realm_tilemaps(ecs_world_t *world, const ecs_entity_t realm) {

    // spawn a tilemap!
    if (zox_has(realm, TilemapLink)) {
        ecs_entity_t tilemap = zox_get_value(realm, TilemapLink)
        if (tilemap) {
            zox_delete(tilemap)
        }
        tilemap = spawn_tilemap(world, prefab_tilemap);
        zox_set(realm, TilemapLink, { tilemap })
        if (tilemap) {
            zox_set(tilemap, RealmLink, { realm })
        }
    }
}