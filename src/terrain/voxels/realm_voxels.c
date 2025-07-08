void spawn_realm_voxels(ecs_world_t *world, const ecs_entity_t realm) {
    if (!realm) {
        return;
    }
    const byte target_depth = block_vox_depth;
    const byte texture_dim = powers_of_two_byte[target_depth];
    voxel_texture_size = (int2) { texture_dim, texture_dim };

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

    if (!zox_has(realm, VoxelLinks)) {
        zox_log("! realm does not have VoxelLinks [%lu]\n", realm)
        return;
    }

    // get realms colors
    zox_geter(realm, Colors, realm_colors);
    byte color_index = 1;   // skip sky
    // const color sky_color = realm_colors->value[color_index++];
    const color dirt_color = realm_colors->value[color_index++];
    const color grass_color = realm_colors->value[color_index++];
    const color sand_color = realm_colors->value[color_index++];
    const color stone_color = realm_colors->value[color_index++];
    const color obsidian_color = realm_colors->value[color_index++];

    zox_geter(realm, VoxelLinks, old_data)
    if (old_data) {
        for (int i = 0; i < old_data->length; i++) {
            zox_delete(old_data->value[i])
        }
        free(old_data->value);
    }

    VoxelLinks *voxels = &((VoxelLinks) { 0, NULL });
    resize_memory_component(VoxelLinks, voxels, ecs_entity_t, zox_blocks_count)
    for (int i = 0; i < zox_blocks_count; i++) {
        voxels->value[i] = 0;
    }

    // nature blocks
    voxels->value[zox_block_dirt - 1] = spawn_block_soil(world, zox_block_dirt, "dirt", dirt_color);
    voxels->value[zox_block_grass - 1] = spawn_block_soil_grass(world, zox_block_grass, "grass", dirt_color, grass_color);
    voxels->value[zox_block_stone - 1] = spawn_block_soil(world, zox_block_stone, "stone", stone_color);
    voxels->value[zox_block_sand - 1] = spawn_block_soil(world, zox_block_sand, "sand", sand_color);
    voxels->value[zox_block_obsidian - 1] = spawn_block_soil(world, zox_block_obsidian, "obsidian", obsidian_color);

    // decor
    voxels->value[zox_block_vox_grass - 1] = spawn_realm_block_grass(world, zox_block_vox_grass, grass_color);
    voxels->value[zox_block_dirt_rubble - 1] = spawn_realm_block_rubble(world, zox_block_dirt_rubble, "rubble", dirt_color);
    voxels->value[zox_block_dirt_vox - 1] = spawn_realm_block_noisey(world, zox_block_dirt_vox, "dirt pile", dirt_color);
    voxels->value[zox_block_vox_flower - 1] = spawn_block_flower(world, zox_block_vox_flower);

    // gamey blocks
    voxels->value[zox_block_dark - 1] = spawn_realm_voxel_texture(world, zox_block_dark, "dark", "block_dark");
    voxels->value[zox_block_dungeon_core - 1] = spawn_dungeon_core(world);

    zox_set(realm, VoxelLinks, { voxels->length, voxels->value })
    zox_set(realm, VoxelsDirty, { 1 })

    for (int i = 0; i < voxels->length; i++) {
        if (!voxels->value[i]) {
            zox_log_error("[spawn_realm_voxels]: voxel not set [%i]", i)
            zox_log("zox_block_vox_flower [%i]", zox_block_vox_flower - 1)
        }
    }
}