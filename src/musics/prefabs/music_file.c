#define music_file_path "music"character_slash"music.zox"

ecs_entity_t spawn_prefab_music_file(
    ecs_world_t *world,
    const ecs_entity_t prefab
) {
    zox_prefab_child(prefab)
    zox_prefab_name("music_file")
    return e;
}

// TODO: Load Files for all Music
ecs_entity_t load_music_file(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t prefab_note
) {
    char* music_filepath = concat_file_path(resources_path, music_file_path);
    zox_logv("Loading Music: %s", music_filepath);
    MidiNote loaded_notes[MAX_NOTES];
    int loaded_note_count = load_notes_from_file(loaded_notes, music_filepath);

    /*zox_logv("Loaded %s :: %i:", music_filepath, loaded_note_count);
    zox_logv(" - Notes %s:", music_filepath);
    zox_logv(" - Length: %f", music_length);*/
    free(music_filepath);

    if (loaded_note_count == 0) {
        zox_log("Music Error: No Notes.");
        return 0;
    }
    // test_notes_from_file(music_filepath);
    double music_speed = loaded_notes[0].length;
    if (music_speed < 0.05f || music_speed >= 3) {
        zox_log_error("Music Error: Invalid Speed: %f", music_speed);
        return 0;
    }
    float music_length = 0;
    for (int i = 0; i < loaded_note_count; i++) {
        MidiNote note = loaded_notes[i];
        // trouble shoot
        if (note.length >= 2) {
            zox_log_error("Music Error: Note [%i] Invalid Length: %f", i, note.length);
            return 0;
        }
        int note_index = find_note_index(note.frequency);
        music_length += note.length;
        // zox_log("   - %i - Frequency: %.2f : %.2f Hz, Start time: %.2f, Length: %.2f\n", i + 1, note.frequency, test_frequency, note.time, note.length)
    }

    const ecs_entity_t e = spawn_music(world, prefab, music_speed);
    zox_set(e, MusicLength, { music_length });

    zox_get_muter(e, NoteLinks, noteLinks);
    initialize_NoteLinks(noteLinks, loaded_note_count);

    const byte instrument = music_load_instrument;
    for (int i = 0; i < loaded_note_count; i++) {
        MidiNote note = loaded_notes[i];
        // trouble shoot
        if (note.length >= 2) {
            zox_log_error("Note was past max sound length: %f", note.length);
            note.length = 2;
        }
        int note_index = find_note_index(note.frequency);
        // double test_frequency = note_frequencies[note_index];
        noteLinks->value[i] = spawn_note(world,
            prefab_note,
            note_index,
            instrument,
            note.length,
            music_load_volume);
        // zox_log("   - %i - Frequency: %.2f : %.2f Hz, Start time: %.2f, Length: %.2f\n", i + 1, note.frequency, test_frequency, note.time, note.length)
    }

    return e;
}