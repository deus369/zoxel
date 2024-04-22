void MusicPlaySystem(ecs_iter_t *it) {
#ifdef zox_disable_music
    return;
#endif
    double delta_time = zox_delta_time;
    const double music_speed = 2.0;
    zox_iter_world()
    const MusicData *musicDatas = ecs_field(it, MusicData, 2);
    const MusicSpeed *musicSpeeds = ecs_field(it, MusicSpeed, 3);
    const InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 4);
    MusicNote *musicNotes = ecs_field(it, MusicNote, 5);
    MusicTime *musicTimes = ecs_field(it, MusicTime, 6);
    for (int i = 0; i < it->count; i++) {
        const MusicData *musicData = &musicDatas[i];
        const MusicSpeed *musicSpeed = &musicSpeeds[i];
        const InstrumentType *instrumentType = &instrumentTypes[i];
        MusicNote *musicNote = &musicNotes[i];
        MusicTime *musicTime = &musicTimes[i];
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
