ecs_entity_t spawn_prefab_music_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_music_generated")
    zox_prefab_set(e, GenerateMusic, { 1 })
    zox_prefab_set(e, MusicNote, { 0 })
    zox_prefab_set(e, InstrumentType, { instrument_piano })
    return e;
}

ecs_entity_t spawn_music_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    // settings
    byte instrument_type = instrument_piano;
    double music_speed = 0.54 + 0.32 * (rand() % 100) * 0.01;
    zox_instance(prefab)
    zox_name("music")
    zox_set(e, MusicSpeed, { music_speed })
    zox_set(e, InstrumentType, { instrument_type })
    return e;
}