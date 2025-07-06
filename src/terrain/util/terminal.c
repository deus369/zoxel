

void print_terrain_settings() {
    zox_log(" > terrain settings set\n")
    // zox_log("     + terrain seed is [%i]\n", (int) terrain_seed)
    zox_log("     + terrain_depth is [%i]\n", terrain_depth)
    zox_log("     + render distance is [%i]\n", terrain_spawn_distance)
    zox_log("     + terrain vertical is [%i]\n", terrain_vertical)
    zox_log("     + lod dividor is [%i]\n", terrain_lod_dividor)
    zox_log("     + height amplifier is [%d]\n", terrain_amplifier)
    zox_log("     + height noise frequency is [%d]\n", terrain_frequency)
    zox_log("     + height boost is [%d]\n", terrain_boost)
    zox_log("     + lowest low is [%d]\n", lowest_voxel_height)
}

void process_arguments_terrain(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--tiny") == 0) {
            terrain_size = terrain_mode_tiny;
            zox_log(" + tiny mode enabled\n")
        } else if (strcmp(args[i], "--medium") == 0) {
            terrain_size = terrain_mode_medium;
        } else if (strcmp(args[i], "--large") == 0) {
            terrain_size = terrain_mode_large;
        }
    }
}