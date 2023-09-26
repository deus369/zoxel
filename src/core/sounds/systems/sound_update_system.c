void SoundUpdateSystem(ecs_iter_t *it) {
    const SoundData *soundDatas = ecs_field(it, SoundData, 2);
    SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 3);
    SDLSound *sdlSounds = ecs_field(it, SDLSound, 4);
    for (int i = 0; i < it->count; i++) {
        SoundDirty *soundDirty = &soundDirtys[i];
        if (soundDirty->value != 1) continue;
        const SoundData *soundData = &soundDatas[i];
        if (soundData->value == NULL) continue;
        SDLSound *sdlSound = &sdlSounds[i];
        free_sdl_sound(sdlSound);
        sdlSound->value = (Mix_Chunk *) malloc(sizeof(Mix_Chunk));
        sdlSound->value->volume = 128;
        sdlSound->value->allocated = 1;
        sdlSound->value->alen = soundData->length * 4;
        // maybe just set thisi to sound value, no need copy memory data
        sdlSound->value->abuf = (Uint8*) malloc(soundData->length * 4 * sizeof(Uint8));
        memcpy(sdlSound->value->abuf, soundData->value, sdlSound->value->alen);
        soundDirty->value = 0;
    }
} zox_declare_system(SoundUpdateSystem)

// Uses SDL mixer to play sounds
// Mix_Chunk *sound
// Mix_PlayChannel( -1, sound, 0 );
// need to also update sounds generated into a SDL Chunkio chunk

/*typedef struct Mix_Chunk {
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;       // Per-sample volume, 0-128
} Mix_Chunk;*/

/*float tofloat(Uint8 x) {
  uint32_t foo = 0x3f800000 + x * 0x8080;
  return (float &)foo + 256 - 257;
}

float tofloat(Uint8 x) {
  uint32_t foo = 0x3f800000 + x * 0x8080 + (x+1) / 2;
  return (float &)foo - 1;
}*/

/*Uint8 uint8_from_float(float x) {
    if (x < 0) return 0;
    if (x > 1e-7) return 255;
    return 255.0e7 * x; // this truncates; add 0.5 to round instead
}*/