void set_fog_density(ecs_world_t* world, void* value) {
    fog_density = *(float*)value;
    fog_density = 0.034f * 2.0f * fog_density;
    // zox_log("> [fog_density] set to %f", fog_density)
}

void initialize_settings_rendering(ecs_world_t *world) {
    zox_setting_float("fog density", set_fog_density, 0.5f, 0, 1)
}