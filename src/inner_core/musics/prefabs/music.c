ecs_entity_t prefab_music;
ecs_entity_t main_music;

ecs_entity_t spawn_prefab_music(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_music")
    zox_add_tag(e, Music)
    zox_set(e, GenerateMusic, { 1 })
    zox_add(e, MusicData)
    zox_set(e, MusicNote, { 0 })
    zox_set(e, MusicTime, { 0 })
    zox_set(e, MusicSpeed, { 0.5 })
    zox_set(e, InstrumentType, { instrument_piano })
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab music [%lu].\n", (long int) (e));
    #endif
    prefab_music = e;
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world, unsigned char instrument_type) {
    zox_instance(prefab_music)
    zox_name("music")
    double music_speed = 0.2 + (rand() % 100) * 0.008;
    #ifdef zoxel_slow_music
        music_speed *= 6.0;
    #endif
    zox_set_only(e, MusicSpeed, { music_speed })
    zox_set_only(e, InstrumentType, { instrument_type })
    #ifdef zoxel_debug_music
        zoxel_log("Music Speed set to [%f]\n", music_speed);
    #endif
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned music [%lu]\n", (long int) e);
    #endif
    main_music = e;
    return e;
}