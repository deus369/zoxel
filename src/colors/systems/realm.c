extern double terrain_frequency;

void generate_colors(lint seed, Colors *colors) {

    srand((unsigned int) seed);

    // byte biome_type = rand() % zox_biome_end;
    BiomeData biome = pick_biome(seed);
    terrain_frequency = biome.frequency;

    const float3 dirt_hsv = float6_rand_range(biome.dirt);
    const float3 grass_hsv = float6_rand_range(biome.grass);
    const float3 sand_hsv = float6_rand_range(biome.sand);
    const float3 stone_hsv = float6_rand_range(biome.sand);
    const float3 obsidian_hsv = float6_rand_range(biome.obsidian);
    const float3 sky_hsv = float6_rand_range(biome.sky);

    const color dirt_color = hsv_to_color(dirt_hsv);
    const color grass_color = hsv_to_color(grass_hsv);
    const color sand_color = hsv_to_color(sand_hsv);
    const color stone_color = hsv_to_color(stone_hsv);
    const color sky_color = hsv_to_color(sky_hsv);
    const color obsidian_color = hsv_to_color(obsidian_hsv);

    byte i = 0;
    colors->value[i++] = sky_color;
    colors->value[i++] = dirt_color;
    colors->value[i++] = grass_color;
    colors->value[i++] = sand_color;
    colors->value[i++] = stone_color;
    colors->value[i++] = obsidian_color;

    zox_logv("Biome: %s", biome.name);
    zox_logv("  Dirt: %fx%fx%f", dirt_hsv.x, dirt_hsv.y, dirt_hsv.z);
    zox_logv("  Grass: %fx%fx%f", grass_hsv.x, grass_hsv.y, grass_hsv.z);
    zox_logv("  Sand: %fx%fx%f", sand_hsv.x, sand_hsv.y, sand_hsv.z);
    zox_logv("  Stone: %fx%fx%f", sand_hsv.x, sand_hsv.y, sand_hsv.z);
    zox_logv("  Obsidian: %fx%fx%f", obsidian_hsv.x, obsidian_hsv.y, obsidian_hsv.z);
    zox_logv("  Sky: %fx%fx%f", sky_hsv.x, sky_hsv.y, sky_hsv.z);
}

extern void set_camera_fog_color(ecs_world_t*, color_rgb) ;

void spawn_realm_colors(ecs_world_t *world, const ecs_entity_t realm) {
    if (!zox_valid(realm) || !zox_has(realm, Seed) || !zox_has(realm, Colors)) {
        zox_log_error("invalid realm in [spawn_realm_colors]")
        return;
    }
    zox_geter(realm, Seed, seed)
    zox_geter(realm, Colors, old_data)
    if (old_data->length) {
        dispose_Colors_const(old_data);
    }
    Colors colors = (Colors) { 0, NULL };
    color_rgb sky_color;
    if (!grayscale_mode) {
        initialize_Colors(&colors, 6);
        generate_colors(seed->value, (&colors));
        // zox_set(realm, Colors, { .value = colors->value, .length = colors->length })
        zox_set_ptr(realm, Colors, colors)
        sky_color = color_to_color_rgb(colors.value[0]);
    } else {
        sky_color = color_rgb_grayscale(3);
    }
    // rendering: set global game colors
    // fog_color = sky_color;
    game_sky_color = sky_color;
    game_sky_bottom_color = sky_color;
    // viewport_clear_color = sky_color;
    set_camera_fog_color(world, sky_color);
    zox_logv("At [%f] Realm [colors] [%i] spawned.", zox_current_time, colors.length);
}


    /*const float6 hsvr_dirt = get_dirt_hsv_range(biome_type);
    float3 dirt_hsv = generate_hsv_v_s(
        (float2) { hsvr_dirt.x, hsvr_dirt.y },
        (float2) { hsvr_dirt.z, hsvr_dirt.w },
        (float2) { hsvr_dirt.u, hsvr_dirt.v });

    const float6 hsvr_grass = get_grass_hsv_range(biome_type);
    float3 grass_hsv = generate_hsv_v_s(
        (float2) { hsvr_grass.x, hsvr_grass.y },
        (float2) { hsvr_grass.z, hsvr_grass.w },
        (float2) { hsvr_grass.u, hsvr_grass.v });

    const float6 hsvr_sand = get_sand_hsv_range(biome_type);
    float3 sand_hsv = generate_hsv_v_s(
        (float2) { hsvr_sand.x, hsvr_sand.y },
        (float2) { hsvr_sand.z, hsvr_sand.w },
        (float2) { hsvr_sand.u, hsvr_sand.v });*/
    /*const float2 stone_hue = (float2) { 0, 360 };
    const float2 stone_value = (float2) { 40, 60 };
    const float2 stone_saturation = (float2) { 2, 6 };
    const float3 stone_hsv = generate_hsv_v_s(stone_hue, stone_value, stone_saturation);*/

    /*float3 obsidian_hsv = (float3) {
        rand() % 360,
        8 + rand() % 8,
        13
    };
    if (obsidian_hsv.x + 180 >= dirt_hsv.x + 180 - 45 && obsidian_hsv.x + 180 <= dirt_hsv.x + 180 + 45) {
        obsidian_hsv.x += 180; // if close to dirt, move away the hue
    }
    const float2 sky_hue = (float2) { 0, 360 }; // ((int) grass_hsv.x + 180) % 360)
    const float2 sky_value = (float2) { 54, 66 };
    const float2 sky_saturation = (float2) { 16, 30 };
    float3 sky_hsv = generate_hsv_v_s(sky_hue, sky_value, sky_saturation);*/
    // float3 sky_hsv = (float3) { (float) (((int) grass_hsv.x + 180) % 360), dirt_hsv.y + 32,
        // dirt_hsv.z + 32 };



    // dirt color - hsv - hue saturation value
    /*const float2 dirt_hue = (float2) { dirt_hue_range.x, dirt_hue_range.y }; // 0, 360 };
    const float2 dirt_value = (float2) { dirt_hue_range.y, dirt_hue_range.z }; // 28, 36 };
    const float2 dirt_saturation = (float2) { dirt_hue_range.u, dirt_hue_range.v }; // 23, 33 };
    float3 dirt_hsv = generate_hsv_v_s(dirt_hue, dirt_value, dirt_saturation);*/

    /*const float2 grass_hue = (float2) { 0, 360 };
    const float2 grass_value = (float2) { 42, 66 };         // { 44, 54 };
    const float2 grass_saturation = (float2) { 44, 55 };    // { 38, 48 };
    float3 grass_hsv = generate_hsv_v_s(grass_hue, grass_value, grass_saturation);
    if (hsv_to_color(grass_hsv).r > hsv_to_color(dirt_hsv).r)
    {
        float soil_hue = dirt_hsv.x;
        dirt_hsv.x = grass_hsv.x;
        grass_hsv.x = soil_hue;
    }*/

    /*const int sand_hue_shift = 40;
    float3 sand_hsv = (float3) {
        dirt_hsv.x - sand_hue_shift + (rand() % sand_hue_shift * 2),
        18 + rand() % 8,
        54 + rand() % 16
    };*/