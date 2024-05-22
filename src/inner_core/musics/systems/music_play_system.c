void MusicPlaySystem(ecs_iter_t *it) {
#ifdef zox_disable_music
    return;
#endif
    init_delta_time()
    const double music_speed = 2.0;
    zox_iter_world()
    zox_field_in(MusicData, musicDatas, 2)
    zox_field_in(MusicSpeed, musicSpeeds, 3)
    zox_field_in(InstrumentType, instrumentTypes, 4)
    zox_field_out(MusicNote, musicNotes, 5)
    zox_field_out(MusicTime, musicTimes, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MusicData, musicDatas, musicData)
        zox_field_i_in(MusicSpeed, musicSpeeds, musicSpeed)
        zox_field_i_in(InstrumentType, instrumentTypes, instrumentType)
        zox_field_i_out(MusicNote, musicNotes, musicNote)
        zox_field_i_out(MusicTime, musicTimes, musicTime)
        musicTime->value += delta_time / musicSpeed->value;
        if (musicData->length > 0 && musicTime->value >= music_speed) {
            musicTime->value -= music_speed;
            musicNote->value++;
            if (musicNote->value >= musicData->length) musicNote->value = 0;
            int music_note = musicData->value[musicNote->value];
            if (music_note == 0) continue;
            float frequency = note_frequencies[music_note]; // based sound note off music note, get timings off music notes in array
            float note_time = musicSpeed->value * music_speed;
            spawn_generated_sound(world, frequency, note_time, instrumentType->value);
#ifdef zoxel_log_music_playing
            zoxel_log(" > music note played [%i : %i] frequency [%f] instrument [%i]\n", musicNote->value, music_note, frequency, instrumentType->value);
#endif
        }
    }
} zox_declare_system(MusicPlaySystem)
