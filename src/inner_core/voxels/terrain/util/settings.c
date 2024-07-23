unsigned char get_terrain_lod_from_camera_distance(unsigned char distance_to_camera) {
#ifdef zox_disable_terrain_lod_levels
    return max_octree_depth;
#endif
    unsigned char lod;
    if (distance_to_camera <= initial_terrain_lod) lod = max_octree_depth;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor) lod = max_octree_depth - 1;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 2) lod = max_octree_depth - 2;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 3) lod = max_octree_depth - 3;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 4) lod = max_octree_depth - 4;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 5) lod = 0;
    else lod = 255;
    return lod;
}

void print_terrain_settings() {
    zox_log(" > terrain settings set\n")
    // zox_log("     + terrain seed is [%i]\n", (int) terrain_seed)
    zox_log("     + octree depth is [%i]\n", max_octree_depth)
    zox_log("     + render distance is [%i]\n", terrain_spawn_distance)
    zox_log("     + terrain vertical is [%i]\n", terrain_vertical)
    zox_log("     + lod dividor is [%i]\n", terrain_lod_dividor)
    zox_log("     + height amplifier is [%d]\n", terrain_amplifier)
    zox_log("     + height noise frequency is [%d]\n", terrain_frequency)
    zox_log("     + height boost is [%d]\n", terrain_boost)
    zox_log("     + lowest low is [%d]\n", lowest_voxel_height)
}

void set_terrain_render_distance() {
    if (cpu_tier == 3) {
        terrain_spawn_distance = 16;
        terrain_vertical = 3;
        fog_density *= 0.3f;    // .3 for now to cover up transitions
        // set_max_octree_length(5);
    } else if (cpu_tier == 2) {
        terrain_spawn_distance = 10;
        terrain_vertical = 1;
        fog_density *= 0.5f;
    } else if (cpu_tier == 1) {
        terrain_spawn_distance = 8;
        terrain_vertical = 1;
        fog_density *= 0.7f;
    } else {
        terrain_spawn_distance = 4;
        terrain_vertical = 1;
    }
    // preset settings
#ifdef zox_terrain_tiny
    terrain_mode = terrain_mode_tiny;//testing
#endif
    if (terrain_mode == terrain_mode_medium) {
        terrain_spawn_distance = 6;
        terrain_vertical = 1;
    }
    if (terrain_mode == terrain_mode_large) {
        terrain_spawn_distance = 12;
        terrain_vertical = 2;
    }
    if (terrain_mode == terrain_mode_tiny) {
        terrain_spawn_distance = 1;
        terrain_vertical = 0;
        zox_log(" + terrain mode set to [tiny]\n")
    }
#ifdef zox_terrain_preset_large
    terrain_spawn_distance = 8;
    terrain_vertical = 2;
#endif
#ifdef zox_terrain_preset_enormous
    terrain_spawn_distance = 16;
    terrain_vertical = 3;
#endif
    terrain_frequency = max_octree_depth * real_terrain_frequency; // 0.002216 // 0.008216
    terrain_boost = 0; // -8 * terrain_vertical; //  + max_octree_depth * 4;
    terrain_amplifier = 16 + terrain_vertical * 16;
    lowest_voxel_height = - (terrain_vertical) * 16 + 1;
    // terrain_seed = get_unique_time_seed();
#ifdef zoxel_debug_settings
    print_terrain_settings();
#endif
}
