void set_render_distance(ecs_world_t* world, void* value) {
    float percentage = *(float*)value;
    terrain_lod_near = terrain_lod_near_min + (int) (percentage * (terrain_lod_near_max - terrain_lod_near_min));
    terrain_lod_far = terrain_lod_near + terrain_lod_far_buffer + (int) (percentage * terrain_lod_far_max);
}

void initialize_settings_streaming(ecs_world_t *world) {
    zoxs_new_float_lim("render distance", set_render_distance, settings_terrain_lod_start, 0, 1)
}