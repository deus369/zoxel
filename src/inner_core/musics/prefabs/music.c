ecs_entity_t spawn_prefab_music(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_music")
    zox_add_tag(e, Music)
    zox_prefab_set(e, GenerateMusic, { 1 })
    zox_prefab_set(e, MusicNote, { 0 })
    zox_prefab_set(e, MusicTime, { 0 })
    zox_prefab_set(e, MusicSpeed, { 0.5 })
    zox_prefab_set(e, InstrumentType, { instrument_piano })
    zox_prefab_set(e, MusicPlaying, { 1 })
    zox_add(e, NoteLinks)
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world, const ecs_entity_t prefab) {
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
    local_music = e;
    return e;
}
