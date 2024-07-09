ecs_entity_t spawn_prefab_sound_filepath(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_sound_filepath")
#ifdef zox_lib_sdl_mixer
    zox_prefab_add(e, SDLSound)
#endif
    zox_prefab_add(e, SoundLength)
    return e;
}

ecs_entity_t spawn_sound_filepath(ecs_world_t *world, const ecs_entity_t prefab, Mix_Chunk *sound_data, const float length) {
    zox_instance(prefab)
    zox_set(e, SDLSound, { *sound_data })
    zox_set(e, SoundLength, { length })
    return e;
}
