int music_note_index;   // for now just use it here

//! Play music on generates
void MusicPlaySystem(ecs_iter_t *it)
{
    const double music_speed = 2.0;
    const MusicData *musicDatas = ecs_field(it, MusicData, 2);
    MusicTime *musicTimes = ecs_field(it, MusicTime, 3);
    for (int i = 0; i < it->count; i++)
    {
        const MusicData *musicData = &musicDatas[i];
        MusicTime *musicTime = &musicTimes[i];
        musicTime->value += it->delta_time;
        if (musicTime->value >= music_speed)
        {
            musicTime->value -= music_speed;
            music_note_index++;
            if (music_note_index > musicData->length)
            {
                music_note_index = 0;
            }
            int music_note = musicData->value[music_note_index];
            float frequency = note_frequencies[music_note];
            // based sound note off music note, get timings off music notes in array
            spawn_generated_sound(it->world, frequency);
            // printf("Playing note [%i] frequency [%f]\n", music_note, frequency);
        }
    }
}
zoxel_declare_system(MusicPlaySystem);