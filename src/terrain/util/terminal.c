void print_terrain_settings() {
    zox_log(" > terrain settings set\n")
    // zox_log("     + terrain seed is [%i]\n", (int) terrain_seed)
    zox_log("     + terrain_depth is [%i]\n", terrain_depth)
    zox_log("     + render distance is [%i]\n", terrain_spawn_distance)
    zox_log("     + terrain vertical is [%i]\n", terrain_vertical)
    zox_log("     + height amplifier is [%d]\n", terrain_amplifier)
    zox_log("     + height noise frequency is [%d]\n", terrain_frequency)
    zox_log("     + height boost is [%d]\n", terrain_boost)
    zox_log("     + lowest low is [%d]\n", lowest_voxel_height)
}

void process_arguments_terrain(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--tiny") == 0) {
            terrain_lod_far = 3;
            render_distance_y = 3;
            zox_log("+ [tiny terrain] [%ix%i]", terrain_lod_far, render_distance_y)
        } else if (strcmp(args[i], "--medium") == 0) {
            terrain_lod_far = 6;
            render_distance_y = 3;
            zox_log("+ [medium terrain] [%ix%i]", terrain_lod_far, render_distance_y)
        } else if (strcmp(args[i], "--large") == 0) {
            terrain_lod_far = 12;
            render_distance_y = 4;
            zox_log("+ [large terrain] [%ix%i]", terrain_lod_far, render_distance_y)
        }
    }
}