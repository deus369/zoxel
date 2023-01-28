int music_note_index;   // for now just use it here

//! Play music on generates
void MusicPlaySystem(ecs_iter_t *it)
{
    #ifdef zoxel_disable_music
    return;
    #endif
    const double music_speed = 1.00;
    const MusicData *musicDatas = ecs_field(it, MusicData, 2);
    const MusicSpeed *musicSpeeds = ecs_field(it, MusicSpeed, 3);
    const InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 4);
    MusicTime *musicTimes = ecs_field(it, MusicTime, 5);
    for (int i = 0; i < it->count; i++)
    {
        const MusicData *musicData = &musicDatas[i];
        const MusicSpeed *musicSpeed = &musicSpeeds[i];
        const InstrumentType *instrumentType = &instrumentTypes[i];
        MusicTime *musicTime = &musicTimes[i];
        musicTime->value += it->delta_time / musicSpeed->value;
        if (musicData->length > 0 && musicTime->value >= music_speed)
        {
            musicTime->value -= music_speed;
            music_note_index++;
            if (music_note_index >= musicData->length)
            {
                music_note_index = 0;
            }
            int music_note = musicData->value[music_note_index];
            if (music_note == 0)
            {
                continue;
            }
            float frequency = note_frequencies[music_note];
            // based sound note off music note, get timings off music notes in array
            float note_time = musicSpeed->value * music_speed * 1.0f;
            spawn_generated_sound(it->world, frequency, note_time, instrumentType->value);
            #ifdef zoxel_log_music_playing
                printf("Playing [%i] Note - [%i] frequency [%f]\n", music_note_index, music_note, frequency);
            #endif
        }
    }
}
zoxel_declare_system(MusicPlaySystem);