void set_terrain_render_distance(int core_count) {
    if (core_count > 8) {
        zoxel_log(" > high core count detected [%i]\n", core_count);
        terrain_spawn_distance = 18; // 28;
        terrain_vertical = 3;
        // terrain_amplifier = 80.0;
        lod_division_dividor = 5;
        // max_octree_depth = 5;
    } else if (core_count > 6) {
        zoxel_log(" > average core count detected [%i]\n", core_count);
        terrain_spawn_distance = 18;
        lod_division_dividor = 3;
    } else if (core_count > 4) {
        zoxel_log(" > low (-) core count detected [%i]\n", core_count);
        terrain_spawn_distance = 12;
    } else {
        zoxel_log(" > lowest core count detected [%i]\n", core_count);
        terrain_spawn_distance = 8;
    }
    #ifdef zoxel_is_flat_height
        terrain_vertical = 1;
    #endif
    terrain_frequency = max_octree_depth * 0.008216;
    terrain_boost = -16 * terrain_vertical;
    terrain_amplifier = terrain_vertical * 24;
    lowest_voxel_height = - terrain_vertical * 16 + 1;
    zoxel_log(" > terrain settings set\n");
    zoxel_log("     + octree depth is [%i]\n", max_octree_depth);
    zoxel_log("     + render distance is [%i]\n", terrain_spawn_distance);
    zoxel_log("     + terrain vertical is [%i]\n", terrain_vertical);
    zoxel_log("     + lod dividor is [%i]\n", lod_division_dividor);
    zoxel_log("     + height amplifier is [%d]\n", terrain_amplifier);
    zoxel_log("     + height noise frequency is [%d]\n", terrain_frequency);
    zoxel_log("     + height boost is [%d]\n", terrain_boost);
    zoxel_log("     + lowest low is [%d]\n", lowest_voxel_height);
}

// inner_render_buffer = 1;
// terrain_frequency = 0.016216;
// terrain_frequency = 0.136216;