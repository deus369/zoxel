void set_render_distance(ecs_world_t* world, void* value) {
    float percentage = *(float*)value;
    terrain_lod_far = terrain_lod_near + (int) (percentage * terrain_lod_far_max);
}

void initialize_settings_streaming(ecs_world_t *world) {
    zox_setting_float("render distance", set_render_distance, 0.5f, 0, 1)
}