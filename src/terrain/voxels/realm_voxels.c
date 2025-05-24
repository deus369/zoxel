// #define zox_log_realm_colors
// #define zox_log_spawn_realm_voxels
extern float3 game_sky_color;
extern float3 game_sky_bottom_color;

// todo: spawn each voxel in individual lines
void spawn_realm_voxels(ecs_world_t *world, const ecs_entity_t realm) {
    if (!realm) {
        return;
    }
    // set voxel texture size again
    const byte target_depth = block_vox_depth;
    const byte texture_dim = powers_of_two_byte[target_depth];
    voxel_texture_size = (int2) { texture_dim, texture_dim };

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

    zox_geter(realm, VoxelLinks, oldVoxels)
    if (oldVoxels) {
        for (int i = 0; i < oldVoxels->length; i++) {
            zox_delete(oldVoxels->value[i])
        }
        // clear_memory_component(VoxelLinks, voxels)
    }
    VoxelLinks *voxels = &((VoxelLinks) { 0, NULL });
    resize_memory_component(VoxelLinks, voxels, ecs_entity_t, zox_blocks_count)
    for (int i = 0; i < zox_blocks_count; i++) {
        voxels->value[i] = 0;
    }

    // dirt color - hsv - hue saturation value
    const float2 dirt_hue = (float2) { 0, 360 };
    const float2 dirt_value = (float2) { 28, 36 };
    const float2 dirt_saturation = (float2) { 33, 43 };
    float3 dirt_hsv = generate_hsv_v_s(dirt_hue, dirt_value, dirt_saturation);
    const float2 grass_hue = (float2) { 0, 360 };
    const float2 grass_value = (float2) { 44, 54 };
    const float2 grass_saturation = (float2) { 38, 48 };
    float3 grass_hsv = generate_hsv_v_s(grass_hue, grass_value, grass_saturation);
    // float3 grass_hsv = (float3) { dirt_hsv.x - 360, dirt_hsv.y, dirt_hsv.z };
    if (hsv_to_color(grass_hsv).r > hsv_to_color(dirt_hsv).r)
    {
        float soil_hue = dirt_hsv.x;
        dirt_hsv.x = grass_hsv.x;
        grass_hsv.x = soil_hue;
        // zox_log(" > grass red was greater, swapping hues\n")
    }
    const int sand_hue_shift = 40;
    float3 sand_hsv = (float3) { dirt_hsv.x - sand_hue_shift + (rand() % sand_hue_shift * 2), dirt_hsv.y + 8 + rand() % 8, dirt_hsv.z + 8 + rand() % 8 };
    const float2 stone_hue = (float2) { 0, 360 };
    const float2 stone_value = (float2) { 16, 24 };
    const float2 stone_saturation = (float2) { 6, 12 };
    const float3 stone_hsv = generate_hsv_v_s(stone_hue, stone_value, stone_saturation);
    float3 sky_hsv = (float3) { (float) (((int) grass_hsv.x + 180) % 360), dirt_hsv.y + 32, dirt_hsv.z + 32 };
    const color dirt_color = hsv_to_color(dirt_hsv);
    const color grass_color = hsv_to_color(grass_hsv);
    const color sand_color = hsv_to_color(sand_hsv);
    const color stone_color = hsv_to_color(stone_hsv);
    const color sky_color = hsv_to_color(sky_hsv);
    const color obsidian_color = hsv_to_color((float3) { rand() % 360, 33, 33 });

    // todo: VoxLinks from realm - spawn vox models first before 'voxels'

    /*const ecs_entity_t vox_obsidian = spawn_vox_generated_invisible(world, prefab_vox_generated, obsidian_color);*/
    // const ecs_entity_t vox_disabled = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
    // todo: make all spawn code like this instead of a for loop
    // dark block is  tasty
    voxels->value[zox_block_dark - 1] = spawn_realm_voxel_texture(world, zox_block_dark, "dark", "block_dark");
    voxels->value[zox_block_vox_flower - 1] = spawn_realm_block_vox_flower(world, zox_block_vox_flower);
    voxels->value[zox_block_dungeon_core - 1] = spawn_dungeon_core(world);

    // dirt
    voxels->value[zox_block_dirt - 1] = spawn_realm_block_soil(world, zox_block_dirt, "dirt", dirt_color);
    voxels->value[zox_block_grass - 1] = spawn_realm_block_soil_grass(world, zox_block_grass, "grass", dirt_color, grass_color);
    voxels->value[zox_block_vox_grass - 1] = spawn_realm_block_grass(world, zox_block_vox_grass, grass_color);

    voxels->value[zox_block_stone - 1] = spawn_realm_block_soil(world, zox_block_stone, "stone", stone_color);
    voxels->value[zox_block_sand - 1] = spawn_realm_block_soil(world, zox_block_sand, "sand", sand_color);
    voxels->value[zox_block_obsidian - 1] = spawn_realm_block_soil(world, zox_block_obsidian, "obsidian", obsidian_color);

    voxels->value[zox_block_dirt_rubble - 1] = spawn_realm_block_rubble(world, zox_block_dirt_rubble, "rubble", dirt_color);

    // the rest
    voxels->value[zox_block_dirt_vox - 1] = spawn_realm_block_noisey(world, zox_block_dirt_vox, "dirt pile", dirt_color);

    // renderer
    fog_color = color_to_float3(sky_color);
    viewport_clear_color = fog_color;
    // game colors
    game_sky_color = fog_color;
    game_sky_bottom_color = fog_color;
    zox_set(realm, VoxelLinks, { voxels->length, voxels->value })
    zox_set(realm, VoxelsDirty, { 1 })
#ifdef zox_log_spawn_realm_voxels
    zox_log(" > spawned all realm voxels\n")
#endif
#ifdef zox_log_realm_colors
    zox_log(" + soil hsv: %fx%fx%f\n", dirt_hsv.x, dirt_hsv.y, dirt_hsv.z)
    zox_log(" + soil color: %ix%ix%i\n", dirt_color.r, dirt_color.g, dirt_color.b)
    zox_log(" + grass_hsv: %fx%fx%f\n", grass_hsv.x, grass_hsv.y, grass_hsv.z)
    zox_log(" + grass_color: %ix%ix%i\n", grass_color.r, grass_color.g, grass_color.b)
    zox_log(" + sand_color: %xx%xx%x\n", sand_color.r, sand_color.g, sand_color.b)
    zox_log(" + stone_color: %xx%xx%x\n", stone_color.r, stone_color.g, stone_color.b)
    zox_log(" + stone_hsv: %fx%fx%f\n", stone_hsv.x, stone_hsv.y, stone_hsv.z)
#endif
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [voxels]\n")
#endif
}