// Uses SDL mixer to play sounds
// Mix_Chunk *sound
// Mix_PlayChannel( -1, sound, 0 );
// need to also update sounds generated into a SDL Chunkio chunk
/*
typedef struct Mix_Chunk {
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;       // Per-sample volume, 0-128
} Mix_Chunk;*/

/*float tofloat(Uint8 x)
{
  uint32_t foo = 0x3f800000 + x * 0x8080;
  return (float &)foo + 256 - 257;
}

float tofloat(Uint8 x)
{
  uint32_t foo = 0x3f800000 + x * 0x8080 + (x+1) / 2;
  return (float &)foo - 1;
}*/


Uint8 uint8_from_float(float x)
{
    if (x < 0) return 0;
    if (x > 1e-7) return 255;
    return 255.0e7 * x; // this truncates; add 0.5 to round instead
}

//! Updates sound to SDL modules
void UpdateSoundSystem(ecs_iter_t *it)
{
    const SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 2);
    const SoundData *soundDatas = ecs_field(it, SoundData, 3);
    SDLSound *sdlSounds = ecs_field(it, SDLSound, 4);
    for (int i = 0; i < it->count; i++)
    {
        const SoundDirty *soundDirty = &soundDirtys[i];
        if (soundDirty->value != 1)
        {
            continue;
        }
        // printf("Updated sound.\n");
        const SoundData *soundData = &soundDatas[i];
        SDLSound *sdlSound = &sdlSounds[i];
        sdlSound->value = (Mix_Chunk *) malloc(sizeof(Mix_Chunk));
        sdlSound->value->volume = 128;
        sdlSound->value->allocated = 1;
        sdlSound->value->alen = soundData->length * 4;
        sdlSound->value->abuf = (Uint8*) malloc(soundData->length * 4 * sizeof(Uint8));
        memcpy(sdlSound->value->abuf, soundData->value, sdlSound->value->alen);
        // Mix_PlayChannel( -1, sdlSound->value, 0 );
    }
}
ECS_SYSTEM_DECLARE(UpdateSoundSystem);


        // sdlSound->value = Mix_LoadWAV(sound_file_names[0]);
        // Mix_Chunk* 
        /*Mix_Chunk* sound_copy_from = sounds[0];
        sdlSound->value = (Mix_Chunk *) malloc(sizeof(Mix_Chunk));
        sdlSound->value->allocated = 1;
        sdlSound->value->volume = sound_copy_from->volume; // 1.0f;
        sdlSound->value->abuf = (Uint8*) malloc(sound_copy_from->alen * sizeof(Uint8));
        sdlSound->value->alen = sound_copy_from->alen;
        for (int j = 0; j < sound_copy_from->alen; j++)
        {
            sdlSound->value->abuf[j] = sound_copy_from->abuf[j];
        }
        for (int j = 0; j < sound_copy_from->alen; j++)
        {
            sdlSound->value->abuf[j] += rand() % 50;
        }*/

        // for (int j = 0; j < sdlSound->value->alen; j += 4)
        // for (int j = 0; j < sdlSound->value->alen; j++)
        //{
            // sdlSound->value->abuf[j] = 255 - sdlSound->value->abuf[j];
            // sdlSound->value->abuf[j] = (Uint8) soundData->value[j];
            // sdlSound->value->abuf[j] = uint8_from_float(soundData->value[j]);
            // sdlSound->value->abuf[j] = (Uint8*) soundData->value[j];
            // float value = soundData->value[j];
            /*sdlSound->value->abuf[j + 0] = (value >> 24) & 0xFF;
            sdlSound->value->abuf[j + 1] = (value >> 16) & 0xFF;
            sdlSound->value->abuf[j + 2] = (value >> 8) & 0xFF;
            sdlSound->value->abuf[j + 3] = value & 0xFF;*/
        //}
