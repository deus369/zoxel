void MusicPlaySystem(ecs_iter_t *it) {
#ifdef zox_disable_music
    return;
#endif
    init_delta_time()
    zox_iter_world()
    zox_field_in(MusicPlaying, musicPlayings, 1)
    zox_field_in(NoteLinks, noteLinkss, 2)
    zox_field_in(MusicSpeed, musicSpeeds, 3)
    zox_field_in(InstrumentType, instrumentTypes, 4)
    zox_field_out(MusicNote, musicNotes, 5)
    zox_field_out(MusicTime, musicTimes, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MusicPlaying, musicPlayings, musicPlaying)
        if (!musicPlaying->value) continue;
        zox_field_i(NoteLinks, noteLinkss, noteLinks)
        zox_field_i(MusicSpeed, musicSpeeds, musicSpeed)
        zox_field_i(InstrumentType, instrumentTypes, instrumentType)
        zox_field_o(MusicNote, musicNotes, musicNote)
        zox_field_o(MusicTime, musicTimes, musicTime)
        musicTime->value += delta_time;
        if (!noteLinks->length) continue;
        if (noteLinks->length > 0 && musicTime->value >= musicSpeed->value) {
            musicTime->value -= musicSpeed->value;
            musicNote->value++;
            if (musicNote->value >= noteLinks->length) musicNote->value = 0;
            const ecs_entity_t note = noteLinks->value[musicNote->value];
            const int music_note = zox_get_value(note, SoundFrequencyIndex)
            // const int music_note = musicData->value[musicNote->value];
            if (music_note == 0) continue;
            const float note_volume = zox_get_value(note, SoundVolume)
            if (note_volume == 0) continue;
            const float note_time = zox_get_value(note, SoundLength)
            if (note_time == 0) continue;
            const int note_instrument = zox_get_value(note, InstrumentType)
            const float frequency = note_frequencies[music_note]; // based sound note off music note, get timings off music notes in array
            // const float note_time = musicSpeed->value * music_speed;
            spawn_sound_generated(world, note_instrument, frequency, note_time, note_volume);

            if (rand() % 100 >= 95) musicTime->value += musicSpeed->value;
            // zox_log(" + playing music at [%f] type [%i] length [%f] volume [%f]\n", zox_current_time, note_instrument, note_time, note_volume)
#ifdef zoxel_log_music_playing
            zox_log(" > music note played [%i : %i] frequency [%f] instrument [%i]\n", musicNote->value, music_note, frequency, instrumentType->value)
#endif
        }
    }
} zox_declare_system(MusicPlaySystem)
