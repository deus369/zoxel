// for our settings
void set_master_volume(ecs_world_t* world, void* value) {
    (void) world;
    master_volume = *(float*)value;
    // zox_log("> master volume set to %f", master_volume)
}

void set_volume_sfx(ecs_world_t* world, void* value) {
    (void) world;
    volume_sfx = *(float*)value;
    // zox_log("> sfx volume set to %f", volume_sfx)
}

void set_volume_music(ecs_world_t* world, void* value) {
    (void) world;
    volume_music = *(float*)value;
    // zox_log("> master volume set to %f", volume_music)
}

void initialize_settings_sounds(ecs_world_t *world) {
    zoxs_new_float_lim("master volume", set_master_volume, 0.5f, 0, 1)
    zoxs_new_float_lim("music", set_volume_music, 0.5f, 0, 1)
    zoxs_new_float_lim("sfx", set_volume_sfx, 0.5f, 0, 1)
}

/*zoxs_set("volume", zox_data_type_float, set_master_volume);
zoxs_set("music", zox_data_type_float, set_volume_music);
zoxs_set("sfx", zox_data_type_float, set_volume_sfx);
zoxs_set_float(world, "volume", master_volume);
zoxs_set_float(world, "music", volume_music);
zoxs_set_float(world, "sfx", volume_sfx);
zox_slim_float(world, "volume", 0, 1);
zox_slim_float(world, "music", 0, 1);
zox_slim_float(world, "sfx", 0, 1);*/