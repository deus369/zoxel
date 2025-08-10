ecs_entity_t spawn_prefab_music_generated(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("music_generated");
    zox_prefab_set(e, GenerateMusic, { 1 });
    zox_prefab_set(e, MusicNote, { 0 });
    zox_prefab_set(e, InstrumentType, { instrument_piano });
    zox_prefab_set(e, Seed, { 0 });
    return e;
}

ecs_entity_t spawn_music_generated(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    lint seed,
    byte instrument,
    float2 speed_range
) {
    zox_instance(prefab);
    zox_name("music");
    zox_set(e, Seed, { seed });
    zox_set(e, MusicSpeed, { randf_range(speed_range.x, speed_range.y) });
    zox_set(e, InstrumentType, { instrument });
    return e;
}