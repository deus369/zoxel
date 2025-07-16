// for our settings
void set_master_volume(ecs_world_t* world, void* value) {
    master_volume = *(float*)value;
    // zox_log("> master volume set to %f", master_volume)
}

void set_volume_sfx(ecs_world_t* world, void* value) {
    volume_sfx = *(float*)value;
    // zox_log("> sfx volume set to %f", volume_sfx)
}

void set_volume_music(ecs_world_t* world, void* value) {
    volume_music = *(float*)value;
    // zox_log("> master volume set to %f", volume_music)
}

void initialize_settings_sounds(ecs_world_t *world) {
    zox_setting_float("master volume", set_master_volume, 0.5f, 0, 1)
    zox_setting_float("music", set_volume_music, 0.5f, 0, 1)
    zox_setting_float("sfx", set_volume_sfx, 0.5f, 0, 1)
}

/*zox_sset("volume", zox_data_type_float, set_master_volume);
zox_sset("music", zox_data_type_float, set_volume_music);
zox_sset("sfx", zox_data_type_float, set_volume_sfx);
zox_sset_float(world, "volume", master_volume);
zox_sset_float(world, "music", volume_music);
zox_sset_float(world, "sfx", volume_sfx);
zox_slim_float(world, "volume", 0, 1);
zox_slim_float(world, "music", 0, 1);
zox_slim_float(world, "sfx", 0, 1);*/