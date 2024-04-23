ecs_entity_t prefab_music;
ecs_entity_t local_music;

ecs_entity_t spawn_prefab_music(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_music")
    zox_add_tag(e, Music)
    zox_prefab_set(e, GenerateMusic, { 1 })
    zox_add(e, MusicData)
    zox_prefab_set(e, MusicNote, { 0 })
    zox_prefab_set(e, MusicTime, { 0 })
    zox_prefab_set(e, MusicSpeed, { 0.5 })
    zox_prefab_set(e, InstrumentType, { instrument_piano })
    prefab_music = e;
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world, unsigned char instrument_type) {
    zox_instance(prefab_music)
    zox_name("music")
    double music_speed = 0.14 + (rand() % 100) * 0.008;
#ifdef zoxel_slow_music
    music_speed *= 6.0;
#endif
    zox_set(e, MusicSpeed, { music_speed })
    zox_set(e, InstrumentType, { instrument_type })
#ifdef zoxel_debug_music
    zox_log(" > music speed set to [%lf]\n", music_speed)
#endif
    local_music = e;
    return e;
}
