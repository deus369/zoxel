
unsigned char load_static_sounds()
{
    unsigned char success = 1;
    for (int i = 0; i < static_sounds_length; i++)
    {
        sounds[i] = Mix_LoadWAV(sound_file_names[i]);
        if(sounds[i] == NULL)
        {
            zoxel_log( "Failed to load sound effect[%i]! SDL_mixer Error: %s\n", i, Mix_GetError() );
            success = 0;
        }
    }
    return success;
}

void dispose_static_sounds()
{
    for (int i = 0; i < static_sounds_length; i++)
    {
        Mix_FreeChunk(sounds[i]);
    }
}