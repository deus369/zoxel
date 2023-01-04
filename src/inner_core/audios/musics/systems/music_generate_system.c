const int music_palette_creepy[] = { 0, 1, 3, 5, 6, 9, 10 };
const int music_palette_happy[] = { 0, 2, 3, 5, 7, 9, 10 };
const int music_palette_blues[] = { 0, 2, 4, 7, 9 };
const int music_palette_blues2[] = { 0, 1, 3, 5, 6, 8, 10 };
const int skip_chance = 84;
const char *music_palette_names[] = {
    "creepy",
    "happy",
    "blues",
    "blues2"
};

//! Play music on generates
void MusicGenerateSystem(ecs_iter_t *it)
{
    const GenerateMusic *generateMusics = ecs_field(it, GenerateMusic, 2);
    MusicData *musicDatas = ecs_field(it, MusicData, 3);
    InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 4);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateMusic *generateMusic = &generateMusics[i];
        if (generateMusic->value != 1)
        {
            continue;
        }
        MusicData *musicData = &musicDatas[i];
        InstrumentType *instrumentType = &instrumentTypes[i];
        instrumentType->value = rand() % 8; // give a random instrument
        // reinitialize
        int sounds_per_verse = 8;
        int verses = 6;
        re_initialize_memory_component(musicData, int, verses * sounds_per_verse);
        int sound_index = 0;
        int palete_type = 0;
        palete_type = rand() % 4;
        int first_note = 28 + rand() % 14;
        #ifdef zoxel_debug_music
            zoxel_log("Music palette set to [%i] [%s]\n",
                palete_type, music_palette_names[palete_type]);
        #endif
        for (int j = 0; j < verses; j++)
        {
            first_note += - 4 + rand() % 8;
            if (first_note < 16)
            {
                first_note = 16;
            }
            // palete_type = rand() % 4;
            // printf("palete_type %i\n", palete_type);
            // randomize it a little
            for (int k = 0; k < sounds_per_verse; k++)
            {
                musicData->value[sound_index] = first_note;
                if (palete_type == 0)
                {
                    musicData->value[sound_index] += music_palette_creepy[rand() % 8];
                }
                else if (palete_type == 1)
                {
                    musicData->value[sound_index] += music_palette_happy[rand() % 8];
                }
                else if (palete_type == 2)
                {
                    musicData->value[sound_index] += music_palette_blues[rand() % 6];
                }
                else // if (palete_type == 3)
                {
                    musicData->value[sound_index] += music_palette_blues2[rand() % 8];
                }
                musicData->value[sound_index] += -2 + rand() % 2;
                if (rand() % 100 >= skip_chance)
                {
                    musicData->value[sound_index] = 0;
                    // printf("Skiping at %i\n", sound_index);
                }
                #ifdef zoxel_debug_music
                    zoxel_log(" > [%i] is [%i]\n", sound_index, musicData->value[sound_index]);
                #endif
                sound_index++;
            }
        }
    }
}
zoxel_declare_system(MusicGenerateSystem);