void set_fog_density(ecs* world, void* value) {
    fog_density = *(float*)value;
    fog_density = 0.034f * 2.0f * fog_density;
    // zox_log("> [fog_density] set to %f", fog_density)
}

void initialize_settings_rendering(ecs *world) {
    zoxs_new_float_lim("fog density", set_fog_density, 0.5f, 0, 1)
}