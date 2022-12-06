// Uses SDL mixer to play sounds
// Mix_Chunk *sound
// Mix_PlayChannel( -1, sound, 0 );
// need to also update sounds generated into a SDL Chunk

//! Plays a sound.
void PlaySoundSystem(ecs_iter_t *it)
{
    const PlaySound *playSounds = ecs_field(it, PlaySound, 2);
    for (int i = 0; i < it->count; i++)
    {
        const PlaySound *playSound = &playSounds[i];
        if (playSound->value == 1)
        {
            //! \todo Link this to sound data
            //! \todo Destroy this sound upon played
            // printf("Played sound 0.\n");
            if (sounds[0] != NULL)
            {
                Mix_PlayChannel( -1, sounds[0], 0 );
            }
        }
    }
}
ECS_SYSTEM_DECLARE(PlaySoundSystem);