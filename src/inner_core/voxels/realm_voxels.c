// #define zox_log_realm_colors
// statically create them atm
const unsigned char realm_voxels = 7;

float3 generate_hsv_v_s(const float2 value_limits, const float2 saturation_limits) {
    return (float3) {
        360.0f * (rand() % 100) * 0.01f,
        saturation_limits.x + (saturation_limits.y - saturation_limits.x) * (rand() % 100) * 0.01f,
        value_limits.x + (value_limits.y - value_limits.x) * (rand() % 100) * 0.01f };
}

void spawn_realm_voxels(ecs_world_t *world, const ecs_entity_t realm) {
    zox_get_mutt(realm, VoxelLinks, voxelLinks)
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    // dirt color - hsv - hue saturation value
    const float2 dirt_value = (float2) { 24, 42 };
    const float2 dirt_saturation = (float2) { 20, 33 };
    float3 dirt_hsv = generate_hsv_v_s(dirt_value, dirt_saturation);
    float3 grass_hsv = (float3) { 360.0f - dirt_hsv.x, dirt_hsv.y, dirt_hsv.z };
    if (hsv_to_color(grass_hsv).r > hsv_to_color(dirt_hsv).r)
    {
        float soil_hue = dirt_hsv.x;
        dirt_hsv.x = grass_hsv.x;
        grass_hsv.x = soil_hue;
        zox_log(" > grass red was greater, swapping hues\n")
    }
    float3 sand_hsv = (float3) { dirt_hsv.x, dirt_hsv.y + 16, dirt_hsv.z + 16 };
    float3 stone_hsv = (float3) { 360.0f * (rand() % 100) * 0.01f, 10 + 10.0f * (rand() % 100) * 0.01f, 10 + 20.0f * (rand() % 100) * 0.01f };
    float3 sky_hsv = (float3) { ((int) grass_hsv.x + 180) % 360, dirt_hsv.y + 32,  dirt_hsv.z + 32 };
    const color dirt_color = hsv_to_color(dirt_hsv);
    const color grass_color = hsv_to_color(grass_hsv);
    const color sand_color = hsv_to_color(sand_hsv);
    const color stone_color = hsv_to_color(stone_hsv);
    const color sky_color = hsv_to_color(sky_hsv);
#ifdef zox_log_realm_colors
    zox_log(" + soil hsv: %fx%fx%f\n", dirt_hsv.x, dirt_hsv.y, dirt_hsv.z)
    zox_log(" + soil color: %ix%ix%i\n", dirt_color.r, dirt_color.g, dirt_color.b)
    zox_log(" + grass_hsv: %fx%fx%f\n", grass_hsv.x, grass_hsv.y, grass_hsv.z)
    zox_log(" + grass_color: %ix%ix%i\n", grass_color.r, grass_color.g, grass_color.b)
#endif
    for (unsigned char i = 0; i < voxelLinks->length; i++) {
        SpawnBlock spawn_data = {
            .prefab = prefab_block,
            .index = i,
            .seed = generate_voxel_seed(i),
            .textures = 1
        };
        unsigned char is_multi = 0;
        if (i == zox_block_dirt - 1) {
            spawn_data.color = dirt_color;
            spawn_data.texture_tag = zox_id(DirtTexture);
        } else if (i == zox_block_grass - 1) {
            spawn_data.color = grass_color;
            spawn_data.texture_tag = zox_id(GrassTexture);
        } else if (i == zox_block_sand - 1) {
            spawn_data.color = sand_color;
            spawn_data.texture_tag = zox_id(SandTexture);
        } else if (i == zox_block_stone - 1) {
            spawn_data.color = stone_color;
            spawn_data.texture_tag = zox_id(StoneTexture);
            // testing
            spawn_data.textures = 6;
        } else if (i == zox_block_obsidian - 1) {
            spawn_data.color = generate_random_voxel_color();
            spawn_data.texture_tag = zox_id(ObsidianTexture);
        } else if (i == zox_block_grass_vox - 1) {
            // test vox block
            spawn_data.color = generate_random_voxel_color();
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.vox = vox_files[test_block_vox_index];
            spawn_data.disable_collision = 1;
        } else if (i == zox_block_dirt_vox - 1) {
            // 2nd test vox block
            // spawn_data.color = generate_random_voxel_color();
            spawn_data.color = dirt_color;
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.vox = spawn_vox_generated(world, prefab_vox_generated, spawn_data.color);
            // quick hack
            zox_set(spawn_data.vox, RenderDisabled, { 1 })
            // next spawn textures off vox ^ x6 axis
            // our cool cube
            // vox_files[test_block_vox_index2];
        }
        voxelLinks->value[i] = spawn_block(world, &spawn_data);

    }
    zox_modified(realm, VoxelLinks)
#ifdef zox_mod_weathers
    game_sky_color = color_to_float3(sky_color);
    game_sky_bottom_color = game_sky_color;
    fog_color = game_sky_bottom_color;
#endif
}
