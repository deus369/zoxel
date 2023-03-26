ecs_entity_t prefab_music;
ecs_entity_t main_music;

ecs_entity_t spawn_prefab_music(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_music");
    set_unique_entity_name(world, e, "prefab_music");
    zoxel_add_tag(world, e, Music);
    zoxel_set(world, e, GenerateMusic, { 1 });
    zoxel_add(world, e, MusicData);
    zoxel_set(world, e, MusicTime, { 0 });
    zoxel_set(world, e, MusicSpeed, { 0.5 });
    zoxel_set(world, e, InstrumentType, { instrument_piano });
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab music [%lu].\n", (long int) (e));
    #endif
    prefab_music = e;
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world, unsigned char instrument_type) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_music);
    set_unique_entity_name(world, e, "music");
    double music_speed = 0.2 + (rand() % 100) * 0.008;
    #ifdef zoxel_slow_music
        music_speed *= 6.0;
    #endif
    ecs_set(world, e, MusicSpeed, { music_speed });
    ecs_set(world, e, InstrumentType, { instrument_type });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned music [%lu]\n", (long int) e);
    #endif
    #ifdef zoxel_debug_music
        zoxel_log("Music Speed set to [%f]\n", music_speed);
    #endif
    main_music = e;
    return e;
}