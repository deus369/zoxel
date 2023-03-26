const int skip_chance = 84;

//! Play music on generates
void MusicGenerateSystem(ecs_iter_t *it) {
    const unsigned char lowest_note = 12;
    const unsigned char highest_note = 36;
    const unsigned char note_verse_difference = 6;
    const GenerateMusic *generateMusics = ecs_field(it, GenerateMusic, 2);
    MusicData *musicDatas = ecs_field(it, MusicData, 3);
    // InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 4);
    for (int i = 0; i < it->count; i++) {
        const GenerateMusic *generateMusic = &generateMusics[i];
        if (generateMusic->value != 1) {
            continue;
        }
        MusicData *musicData = &musicDatas[i];
        // InstrumentType *instrumentType = &instrumentTypes[i];
        // instrumentType->value = rand() % instrument_end;
        // instrumentType->value = instrument_unique;
        int sounds_per_verse = 8;
        int verses = 6;
        re_initialize_memory_component(musicData, int, verses * sounds_per_verse);
        int sound_index = 0;
        int palete_type = 0;
        palete_type = rand() % music_palette_end;
        int first_note = lowest_note + rand() % (highest_note - lowest_note + 1 - note_verse_difference);
        #ifdef zoxel_debug_music
            zoxel_log("Music Generated!\n - Palette [%i] [%s]\n - Instrument: [%i]\n    - First Note [%i]\n",
                palete_type, music_palette_names[palete_type], instrumentType->value, first_note);
        #endif
        for (int j = 0; j < verses; j++)
        {
            first_note += - note_verse_difference + rand() % (note_verse_difference * 2 + 1);
            if (first_note < lowest_note) {
                first_note = lowest_note;
            } else if (first_note > highest_note) {
                first_note = highest_note;
            }
            // palete_type = rand() % 4;
            // printf("palete_type %i\n", palete_type);
            // randomize it a little
            for (int k = 0; k < sounds_per_verse; k++)
            {
                musicData->value[sound_index] = first_note;
                if (palete_type == music_palette_creepy) {
                    musicData->value[sound_index] += music_palette_values_creepy[rand() % 8];
                } else if (palete_type == music_palette_happy) {
                    musicData->value[sound_index] += music_palette_values_happy[rand() % 8];
                } else if (palete_type == music_palette_blues) {
                    musicData->value[sound_index] += music_palette_values_blues[rand() % 6];
                } else if (palete_type == music_palette_blues2) {
                    musicData->value[sound_index] += music_palette_values_blues2[rand() % 8];
                } else if (palete_type == music_palette_romantic) {
                    musicData->value[sound_index] += music_palette_values_romantic[rand() % 7];
                } else if (palete_type == music_palette_epic) {
                    musicData->value[sound_index] += music_palette_values_epic[rand() % 7];
                } else if (palete_type == music_palette_jazz) {
                    musicData->value[sound_index] += music_palette_values_jazz[rand() % 6];
                } else if (palete_type == music_palette_rock) {
                    musicData->value[sound_index] += music_palette_values_rock[rand() % 7];
                } else if (palete_type == music_palette_techno) {
                    musicData->value[sound_index] += music_palette_values_techno[rand() % 8];
                } else if (palete_type == music_palette_funk) {
                    musicData->value[sound_index] += music_palette_values_funk[rand() % 6];
                }
                musicData->value[sound_index] += -2 + rand() % 3;
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