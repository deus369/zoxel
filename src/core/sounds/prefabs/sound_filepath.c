ecs_entity_t spawn_prefab_sound_filepath(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_sound_filepath")
#ifdef zox_lib_sdl_mixer
    zox_prefab_add(e, SDLSound)
#endif
    return e;
}

#ifdef zox_lib_sdl_mixer
    ecs_entity_t spawn_sound_filepath(ecs_world_t *world, const ecs_entity_t prefab, Mix_Chunk *sound_data, const float length) {
        if (sound_data == NULL) {
            zox_log("sound_data is null.\n")
            return 0;
        }
        zox_instance(prefab)
        zox_set(e, SDLSound, { *sound_data })
        zox_set(e, SoundLength, { length })
        return e;
    }
#endif
