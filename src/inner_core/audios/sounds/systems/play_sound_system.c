// Uses SDL mixer to play sounds
// Mix_Chunk *sound
// Mix_PlayChannel( -1, sound, 0 );
// need to also update sounds generated into a SDL ChunkData

//! Plays a sound.
void PlaySoundSystem(ecs_iter_t *it)
{
    const PlaySound *playSounds = ecs_field(it, PlaySound, 2);
    const SDLSound *sdlSounds = ecs_field(it, SDLSound, 3);
    for (int i = 0; i < it->count; i++)
    {
        const PlaySound *playSound = &playSounds[i];
        if (playSound->value != 1)
        {
            continue;
        }
        const SDLSound *sdlSound = &sdlSounds[i];
        //! \todo Link this to sound data
        //! \todo Destroy this sound upon played
        // printf("Played sound 0.\n");
        if (sdlSound->value != NULL) // sounds[0] != NULL)
        {
            Mix_PlayChannel( -1, sdlSound->value, 0 );
            // printf("Volume: %i\n", sdlSound->value->volume);
        }
    }
}
zoxel_declare_system(PlaySoundSystem);