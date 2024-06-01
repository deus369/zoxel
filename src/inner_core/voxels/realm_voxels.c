// #define zox_log_realm_colors
// statically create them atm
// const unsigned char realm_voxels = 8;
extern float3 game_sky_color;
extern float3 game_sky_bottom_color;

float3 generate_hsv_v_s(const float2 hue_limits, const float2 value_limits, const float2 saturation_limits) {
    return (float3) {
        hue_limits.x + (hue_limits.y - hue_limits.x) * (rand() % 100) * 0.01f,
        saturation_limits.x + (saturation_limits.y - saturation_limits.x) * (rand() % 100) * 0.01f,
        value_limits.x + (value_limits.y - value_limits.x) * (rand() % 100) * 0.01f };
}

void spawn_realm_voxels(ecs_world_t *world, const ecs_entity_t realm) {
    zox_prefab_set(realm, VoxelsDirty, { 1 })
    ecs_entity_t tilemap = spawn_tilemap(world, prefab_tilemap);
    zox_set(realm, TilemapLink, { tilemap })
    zox_set(tilemap, RealmLink, { realm })
    zox_log(" + spawned tilemap [%lu]\n", tilemap)
    zox_get_mutt(realm, VoxelLinks, voxelLinks)
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, zox_blocks_count)
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
    const color color_obsidian = hsv_to_color((float3) { rand() % 360, 33, 33 });
    const ecs_entity_t dirt_vox = spawn_vox_generated_invisible(world, prefab_vox_generated, dirt_color);
    const ecs_entity_t vox_grass = spawn_vox_generated_invisible(world, prefab_vox_generated, grass_color);
    zox_add_tag(vox_grass, BlendVox)
    zox_set(vox_grass, SecondaryColor, { dirt_color }) // bottom half
    const ecs_entity_t vox_sand = spawn_vox_generated_invisible(world, prefab_vox_generated, sand_color);
    const ecs_entity_t vox_stone = spawn_vox_generated_invisible(world, prefab_vox_generated, stone_color);
    const ecs_entity_t dirt_rubble = spawn_vox_generated_invisible(world, prefab_vox_generated, dirt_color);
    zox_add_tag(dirt_rubble, VoxRubble)
    const ecs_entity_t vox_obsidian = spawn_vox_generated_invisible(world, prefab_vox_generated, color_obsidian);
    for (unsigned char i = 0; i < voxelLinks->length; i++) {
        SpawnBlock spawn_data = {
            .index = i,
            .seed = generate_voxel_seed(i),
            .prefab_texture = prefab_vox_texture
        };
        if (i == zox_block_dirt - 1) {
            spawn_data.name = "dirt";
            spawn_data.color = dirt_color;
            spawn_data.bake_vox = 1;
            spawn_data.vox = dirt_vox;
            // spawn_data.textures = 1;
            // spawn_data.texture_tag = zox_id(DirtTexture);
        } else if (i == zox_block_grass - 1) {
            spawn_data.name = "grass";
            spawn_data.color = grass_color;
            spawn_data.bake_vox = 1;
            spawn_data.vox = vox_grass;
        } else if (i == zox_block_sand - 1) {
            spawn_data.name = "sand";
            spawn_data.color = sand_color;
            spawn_data.bake_vox = 1;
            spawn_data.vox = vox_sand;
            // spawn_data.textures = 1;
            // spawn_data.texture_tag = zox_id(SandTexture);
        } else if (i == zox_block_stone - 1) {
            spawn_data.name = "stone";
            spawn_data.color = stone_color;
            spawn_data.bake_vox = 1;
            spawn_data.vox = vox_stone;
            // spawn_data.textures = 1;
            // spawn_data.texture_tag = zox_id(StoneTexture);
        } else if (i == zox_block_obsidian - 1) {
            spawn_data.name = "obsidian";
            spawn_data.color = generate_random_voxel_color();
            spawn_data.bake_vox = 1;
            spawn_data.vox = vox_obsidian;
            // spawn_data.texture_tag = zox_id(ObsidianTexture);
        } else if (i == zox_block_vox_grass - 1) {
            spawn_data.name = "flower";
            // flowers
            spawn_data.color = generate_random_voxel_color();
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.vox = vox_files[test_block_vox_index];
            spawn_data.disable_collision = 1;
            spawn_data.vox_offset = 1;
        } else if (i == zox_block_dirt_vox - 1) {
            spawn_data.name = "dirt_vox";
            // dirt vox
            spawn_data.color = dirt_color;
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.vox = dirt_vox;
        } else if (i == zox_block_dirt_rubble - 1) {
            spawn_data.name = "dirt_rubble";
            spawn_data.color = dirt_color;
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.vox = dirt_rubble;
        }
        if (spawn_data.vox) {
            spawn_data.prefab = prefab_block_vox_meta;
            voxelLinks->value[i] = spawn_block_vox_meta(world, &spawn_data);
        } else {
            spawn_data.prefab = prefab_block;
            voxelLinks->value[i] = spawn_block(world, &spawn_data);
        }
    }
    zox_modified(realm, VoxelLinks)
//#ifdef zox_mod_weathers
    game_sky_color = color_to_float3(sky_color);
    game_sky_bottom_color = game_sky_color;
    fog_color = game_sky_bottom_color;
//#endif
#ifdef zox_log_realm_colors
    zox_log(" + soil hsv: %fx%fx%f\n", dirt_hsv.x, dirt_hsv.y, dirt_hsv.z)
    zox_log(" + soil color: %ix%ix%i\n", dirt_color.r, dirt_color.g, dirt_color.b)
    zox_log(" + grass_hsv: %fx%fx%f\n", grass_hsv.x, grass_hsv.y, grass_hsv.z)
    zox_log(" + grass_color: %ix%ix%i\n", grass_color.r, grass_color.g, grass_color.b)
    zox_log(" + sand_color: %xx%xx%x\n", sand_color.r, sand_color.g, sand_color.b)
    zox_log(" + stone_color: %xx%xx%x\n", stone_color.r, stone_color.g, stone_color.b)
    zox_log(" + stone_hsv: %fx%fx%f\n", stone_hsv.x, stone_hsv.y, stone_hsv.z)
#endif
}

// spawn_data.texture_tag = zox_id(DirtTexture);
// spawn_data.texture_tag = zox_id(GrassTexture);
// spawn_data.texture_tag = zox_id(SandTexture);
// spawn_data.texture_tag = zox_id(StoneTexture);
// 2nd test vox block
// for generated vox blocks
// spawn_data.color = generate_random_voxel_color();
// vox_files[test_block_vox_index2]; // our cool cube
