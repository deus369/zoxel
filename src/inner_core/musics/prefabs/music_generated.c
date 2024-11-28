ecs_entity_t spawn_prefab_music_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_music_generated")
    zox_prefab_set(e, GenerateMusic, { 1 })
    zox_prefab_set(e, MusicNote, { 0 })
    zox_prefab_set(e, InstrumentType, { instrument_piano })
    // zox_set(e, MusicPlaying, { 1 })
    return e;
}

ecs_entity_t spawn_music_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    // settings
    unsigned char instrument_type = instrument_piano;
    double music_speed = 0.54 + 0.32 * (rand() % 100) * 0.01;
    #ifdef zoxel_slow_music
    music_speed *= 6.0;
    #endif
    // zox_log(" > music_speed [%f]\n", music_speed)
    #ifdef zoxel_debug_music
    zox_log(" > music speed set to [%lf]\n", music_speed)
    #endif
    zox_instance(prefab)
    zox_name("music")
    zox_set(e, MusicSpeed, { music_speed })
    zox_set(e, InstrumentType, { instrument_type })
    return e;
}
