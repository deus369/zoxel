// #define zox_log_realm_colors
const unsigned char realm_voxels = 6;

void add_to_realm(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, VoxelLinks, { 0, NULL })
}

ecs_entity_t spawn_realm(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    local_realm = e;
    zox_name("realm")
    zox_get_mutt(e, VoxelLinks, voxelLinks)
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    // dirt color - hsv - hue saturation value
    const float max_value = 70;
    const float min_value = 30;
    const float max_saturation = 50;
    const float min_saturation = 24;
    float3 soil_hsv = (float3) { 360.0f * (rand() % 100) * 0.01f, min_saturation + (max_saturation - min_saturation) * (rand() % 100) * 0.01f, min_value + (max_value - min_value) * (rand() % 100) * 0.01f };
    float3 grass_hsv = (float3) { 360.0f - soil_hsv.x, soil_hsv.y, soil_hsv.z };
    if (hsv_to_color(grass_hsv).r > hsv_to_color(soil_hsv).r)
    {
        float soil_hue = soil_hsv.x;
        soil_hsv.x = grass_hsv.x;
        grass_hsv.x = soil_hue;
        zox_log(" > grass red was greater, swapping hues\n")
    }
    float3 sand_hsv = (float3) { soil_hsv.x, soil_hsv.y + 16, soil_hsv.z + 16 };
    float3 stone_hsv = (float3) { 360.0f * (rand() % 100) * 0.01f, 10 + 10.0f * (rand() % 100) * 0.01f, 10 + 20.0f * (rand() % 100) * 0.01f };
    float3 sky_hsv = (float3) { ((int) grass_hsv.x + 180) % 360, soil_hsv.y + 32,  soil_hsv.z + 32 };
    const color soil_color = hsv_to_color(soil_hsv);
    const color grass_color = hsv_to_color(grass_hsv);
    const color sand_color = hsv_to_color(sand_hsv);
    const color stone_color = hsv_to_color(stone_hsv);
    const color sky_color = hsv_to_color(sky_hsv);
    game_sky_color = color_to_float3(sky_color);
    game_sky_bottom_color = game_sky_color;
    fog_color = game_sky_bottom_color;
#ifdef zox_log_realm_colors
    zox_log(" + soil hsv: %fx%fx%f\n", soil_hsv.x, soil_hsv.y, soil_hsv.z)
    zox_log(" + soil color: %ix%ix%i\n", soil_color.r, soil_color.g, soil_color.b)
    zox_log(" + grass_hsv: %fx%fx%f\n", grass_hsv.x, grass_hsv.y, grass_hsv.z)
    zox_log(" + grass_color: %ix%ix%i\n", grass_color.r, grass_color.g, grass_color.b)
#endif
    for (unsigned char i = 0; i < voxelLinks->length; i++) {
        SpawnBlock spawn_data = {
            .prefab = prefab_voxel,
            .index = i,
            .seed = generate_voxel_seed(i)
        };
        if (i == zox_block_dirt - 1) {
            spawn_data.color = soil_color;
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
        } else if (i == zox_block_obsidian - 1) {
            spawn_data.color = generate_random_voxel_color();
            spawn_data.texture_tag = zox_id(ObsidianTexture);
        } else if (i == zox_block_grass_vox - 1) {
            // test vox block
            spawn_data.color = generate_random_voxel_color();
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
        }
        voxelLinks->value[i] = spawn_voxel(world, &spawn_data);
    }
    zox_modified(e, VoxelLinks)
    return e;
}
