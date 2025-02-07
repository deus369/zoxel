// actually amount of detail, so 0 is lowest
// todo: lod should be reversed, 0 highest, and we subtract from max resolution of game

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
        terrain_spawn_distance = 2;
        terrain_vertical = 1;
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
