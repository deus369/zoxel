#define music_file_path "music"character_slash"music.zox"

ecs_entity_t spawn_prefab_music_file(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_music_file")
    return e;
}

ecs_entity_t load_music_file(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t prefab_note) {
    char* music_filepath = concat_file_path(resources_path, music_file_path);
    // zox_log(" > music file: %s\n", music_filepath)
    MidiNote loaded_notes[MAX_NOTES];
    int loaded_note_count = load_notes_from_file(loaded_notes, music_filepath);
    if (loaded_note_count == 0) {
        zox_log("no notes in file [%s]\n", music_filepath)
        free(music_filepath);
        return 0;
    }
    // zox_log(" > loaded %s :: %i:\n", music_filepath, loaded_note_count)
    // zox_log(" > Notes loaded from %s:\n", music_filepath);
    // test_notes_from_file(music_filepath);
    double music_speed = loaded_notes[0].length;
    const ecs_entity_t music = spawn_music(world, prefab, music_speed);
    zox_get_muter(music, NoteLinks, noteLinks)
    resize_memory_component(NoteLinks, noteLinks, ecs_entity_t, loaded_note_count)
    float music_length = 0;
    // zox_log("   - music speed: %f\n", music_speed)
    for (int i = 0; i < loaded_note_count; i++) {
        MidiNote note = loaded_notes[i];
        int note_index = find_note_index(note.frequency);
        // double test_frequency = note_frequencies[note_index];
        noteLinks->value[i] = spawn_note(world, prefab_note, note_index, instrument_piano_file, note.length, 1);
        music_length += note.length;
        // zox_log("   - %i - Frequency: %.2f : %.2f Hz, Start time: %.2f, Length: %.2f\n", i + 1, note.frequency, test_frequency, note.time, note.length)
    }
    // zox_log("   - music length: %f\n", music_length)
    zox_set(music, MusicLength, { music_length })
    free(music_filepath);
    return music;
}
