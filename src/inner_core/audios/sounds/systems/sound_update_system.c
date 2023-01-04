// Uses SDL mixer to play sounds
// Mix_Chunk *sound
// Mix_PlayChannel( -1, sound, 0 );
// need to also update sounds generated into a SDL Chunkio chunk
extern ecs_entity_t spawn_line2D(ecs_world_t *world, float2 pointA, float2 pointB, float thickness, double life_time);

//! Updates sound to SDL modules
void SoundUpdateSystem(ecs_iter_t *it)
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
        const SoundData *soundData = &soundDatas[i];
        SDLSound *sdlSound = &sdlSounds[i];
        sdlSound->value = (Mix_Chunk *) malloc(sizeof(Mix_Chunk));
        sdlSound->value->volume = 128;
        sdlSound->value->allocated = 1;
        sdlSound->value->alen = soundData->length * 4;
        sdlSound->value->abuf = (Uint8*) malloc(soundData->length * 4 * sizeof(Uint8));
        memcpy(sdlSound->value->abuf, soundData->value, sdlSound->value->alen);
        // this is the debug feature
        #ifdef zoxel_debug_sounds
            double decay_time = soundData->length / sample_rate_f; // 6.0 + rand() % 6;
            int start_position = sound_display_start * soundData->length;
            int end_position = sound_display_end * soundData->length;
            int total_displaying = end_position - start_position;
            for (int i = start_position; i < end_position; i += sound_display_skip_rate)
            {
                float x_position = (i - start_position) / (float) total_displaying;
                // float x_position = (float) i / (float) soundData->length;
                x_position *= 2.0f;
                x_position -= 1.0f;
                spawn_line2D(world, (float2) { x_position, 0 }, (float2) { x_position, soundData->value[i] },
                    0.1f, decay_time);
            }
        #endif
    }
}
zoxel_declare_system(SoundUpdateSystem);
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

/*Uint8 uint8_from_float(float x)
{
    if (x < 0) return 0;
    if (x > 1e-7) return 255;
    return 255.0e7 * x; // this truncates; add 0.5 to round instead
}*/