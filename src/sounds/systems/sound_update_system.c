void SoundUpdateSystem(ecs_iter_t *it) {
    if (!audio_enabled) {
      return;
    }
    zox_field_in(SoundData, soundDatas, 2)
    zox_field_out(SoundDirty, soundDirtys, 3)
    zox_field_out(SDLSound, sdlSounds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SoundData, soundDatas, soundData)
        zox_field_o(SoundDirty, soundDirtys, soundDirty)
        zox_field_o(SDLSound, sdlSounds, sdlSound)
        if (!soundDirty->value || !soundData->value) {
            continue;
        }
        const int memory_length = soundData->length * sizeof(float);
        sdlSound->value = (Mix_Chunk) {
          .volume = global_master_volume,
          .alen = memory_length,
          .abuf = (void*) soundData->value
        };
        soundDirty->value = 0;
        zox_log_sounds("  -> sdl mix sound updated [%f]", zox_current_time)
    }
} zox_declare_system(SoundUpdateSystem)