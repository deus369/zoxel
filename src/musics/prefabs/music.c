ecs_entity_t spawn_prefab_music(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_music")
    zox_add_tag(e, Music)
    zox_prefab_set(e, MusicLength, { 0 })
    zox_prefab_set(e, MusicTime, { 0 })
    zox_prefab_set(e, MusicSpeed, { 0.5 })
    zox_prefab_set(e, MusicPlaying, { 0 })
    zox_prefab_set(e, MusicNote, { 0 })
    // zox_prefab_set(e, InstrumentType, { instrument_piano })
    zox_prefab_add(e, NoteLinks)
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world, const ecs_entity_t prefab, double speed) {
    zox_instance(prefab)
    zox_name("music")
    zox_set(e, MusicSpeed, { speed })
    return e;
}
