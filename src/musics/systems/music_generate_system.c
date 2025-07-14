int get_random_pallete_note(const byte *pallete, int array_length) {
   return pallete[rand() % array_length];
}

void MusicGenerateSystem(ecs_iter_t *it) {
    if (nomusic) {
        return;
    }
    const byte lowest_note = 12;
    const byte highest_note = 36;
    const byte note_verse_difference = 6;
    zox_field_world()
    zox_field_out(GenerateMusic, generateMusics, 1)
    zox_field_out(NoteLinks, noteLinkss, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateMusic, generateMusics, generateMusic)
        zox_field_o(NoteLinks, noteLinkss, noteLinks)
        if (!generateMusic->value) {
            continue;
        }
        int sounds_per_verse = 8;
        int verses = 6;
        resize_memory_component(NoteLinks, noteLinks, ecs_entity_t, verses * sounds_per_verse)
        int sound_index = 0;
        int palete_type = 0;
        palete_type = rand() % music_palette_end;
        int first_note = lowest_note + rand() % (highest_note - lowest_note + 1 - note_verse_difference);
        // music_palette_names[palete_type], instrumentType->value,
        zox_log_notes("+ generating music\n - Palette [%i]\n - Instrument: -\n    - First Note [%i]", palete_type, first_note)
        for (int j = 0; j < verses; j++) {
            first_note += - note_verse_difference + rand() % (note_verse_difference * 2 + 1);
            if (first_note < lowest_note) {
                first_note = lowest_note;
            } else if (first_note > highest_note) {
                first_note = highest_note;
            }
            for (int k = 0; k < sounds_per_verse; k++) {
                int music_note = first_note;
                if (palete_type == music_palette_creepy) {
                    music_note += get_random_pallete_note(music_palette_values_creepy, 7);
                } else if (palete_type == music_palette_happy) {
                    music_note += get_random_pallete_note(music_palette_values_happy, 7);
                } else if (palete_type == music_palette_blues) {
                    music_note += get_random_pallete_note(music_palette_values_blues, 5);
                } else if (palete_type == music_palette_blues2) {
                    music_note += get_random_pallete_note(music_palette_values_blues2, 7);
                } else if (palete_type == music_palette_romantic) {
                    music_note += get_random_pallete_note(music_palette_values_romantic, 6);
                } else if (palete_type == music_palette_epic) {
                    music_note += get_random_pallete_note(music_palette_values_epic, 6);
                } else if (palete_type == music_palette_jazz) {
                    music_note += get_random_pallete_note(music_palette_values_jazz, 5);
                } else if (palete_type == music_palette_rock) {
                    music_note += get_random_pallete_note(music_palette_values_rock, 6);
                } else if (palete_type == music_palette_techno) {
                    music_note += get_random_pallete_note(music_palette_values_techno, 7);
                } else if (palete_type == music_palette_funk) {
                    music_note += get_random_pallete_note(music_palette_values_funk, 5);
                }
                if (rand() % 100 >= music_note_skip) {
                    music_note = 0;
                    // printf("Skiping at %i\n", sound_index);
                } else {
                    music_note += -2 + rand() % 3;
                }
                byte music_instrument = instrument_piano;
                if (rand() % 100 >= 50) {
                    music_instrument = instrument_organ;
                }
                const float note_length = 0.8f + 0.6f * (rand() % 100 * 0.01f);
                const float note_volume = 0.6f + 0.4f * (rand() % 100 * 0.01f);
                const ecs_entity_t note = spawn_note(world,
                    prefab_note,
                    music_note,
                    music_instrument,
                    note_length,
                    note_volume);
                noteLinks->value[sound_index] = note;
                sound_index++;
                zox_log_notes("+ note [%lu:%s] at [%i] is: (%i:%i) [volume[%f]]", note, zox_get_name(note), sound_index, music_note, music_instrument, note_volume)
            }
        }
        generateMusic->value = 0;
    }
}
zox_declare_system(MusicGenerateSystem)
